from PIL import Image, ImageFilter
# dot operators look within an imported module and access functions
before = Image.open("bridge.bmp")
after = before.filter(ImageFilter.BoxBlur(10))
after.save("out.bmp")