#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // for every vertical row of pixels
    for (int i = 0; i < height; i++)
    {
        // for every horizontal pixel
        for (int x = 0; x < width; x++)
        {
            // average of each pixel rounded to the nearest integer
            int z = round((double)(image[i][x].rgbtRed + image[i][x].rgbtGreen + image[i][x].rgbtBlue) / 3);

            // assign new averaged pixel to rgb channels at [i][x]
            image[i][x].rgbtRed = z;
            image[i][x].rgbtGreen = z;
            image[i][x].rgbtBlue = z;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        // for every horizontal pixel
        for (int x = 0; x < width; x++)
        {
            // calculate sepia for rgb, round and clamp to 255.
            int sepiaRed = round((.393 * image[i][x].rgbtRed) + (.769 * image[i][x].rgbtGreen) + (.189 * image[i][x].rgbtBlue));
            int sepiaGreen = round((.349 * image[i][x].rgbtRed) + (.686 * image[i][x].rgbtGreen) + (.168 * image[i][x].rgbtBlue));
            int sepiaBlue = round((.272 * image[i][x].rgbtRed) + (.534 * image[i][x].rgbtGreen) + (.131 * image[i][x].rgbtBlue));

            if (sepiaRed > 255)
            {
                image[i][x].rgbtRed = 255;
            }
            else
            {
                image[i][x].rgbtRed = sepiaRed;
            }

            if (sepiaGreen > 255)
            {
                image[i][x].rgbtGreen = 255;
            }
            else
            {
                image[i][x].rgbtGreen = sepiaGreen;
            }

            if (sepiaBlue > 255)
            {
                image[i][x].rgbtBlue = 255;
            }
            else
            {
                image[i][x].rgbtBlue = sepiaBlue;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // create a buffer
    RGBTRIPLE imgbuf[height][width];

    // for every vertical row of pixels
    for (int i = 0; i < height; i++)
    {
        // for every horizontal pixel
        for (int x = 0; x < width; x++)
        {
            int z = width - 1 - x;
            imgbuf[i][x].rgbtRed = image[i][z].rgbtRed;
            imgbuf[i][x].rgbtGreen = image[i][z].rgbtGreen;
            imgbuf[i][x].rgbtBlue = image[i][z].rgbtBlue;
        }
    }

    // for every vertical pixel
    for (int i = 0; i < height; i++)
    {
        // for every horizontal pixel
        for (int x = 0; x < width; x++)
        {
            image[i][x] = imgbuf[i][x];
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // create a buffer
    RGBTRIPLE imgbuf2[height][width];

    // for every vertical row of pixels
    for (int i = 0; i < height; i++)
    {
        // for every horizontal pixel
        for (int x = 0; x < width; x++)
        {
            // pixel counter
            int p = 0;

            // create colour channel buffers
            double r = 0;
            double g = 0;
            double b = 0;

            /* Pixel Search Grid
            [i-1, x-1][i-1, x-0][i-1, x+1]
            [i+0, x-1][i+0, x+0][i+0, x+1]
            [i+1, x-1][i+1, x+0][i+1, x+1]
            nth pizel is at 0, 0 */

            // search space of -1 to +1
            for (int y = -1; y < 2; y++)
            {
                for (int z = -1; z < 2; z++)
                {
                    // check pixel is between 0 and max
                    if (i + y >= 0 && i + y < height)
                    {
                        if (x + z >= 0 && x + z < width)
                        {
                            r += image[i + y][x + z].rgbtRed;
                            g += image[i + y][x + z].rgbtGreen;
                            b += image[i + y][x + z].rgbtBlue;
                            p++;
                        }
                    }
                }
            }

            // set new colour to the nearest integer in image buffer
            imgbuf2[i][x].rgbtRed =  round(r / p);
            imgbuf2[i][x].rgbtGreen = round(g / p);
            imgbuf2[i][x].rgbtBlue = round(b / p);
        }
    }

    // for every vertical row of pixels
    for (int i = 0; i < height; i++)
    {
        // for every horizontal pixel
        for (int x = 0; x < width; x++)
        {
            image[i][x] = imgbuf2[i][x];
        }
    }

    return;
}