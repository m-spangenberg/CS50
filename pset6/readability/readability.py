import re

from cs50 import get_string

# readability.py


def main():
    """ execute program """
    string = get_string("Text: ")
    calc(string)


def calc(string):
    """ calculate readability usng Coleman-Liau formula """

    total_letters = countLetters(string)
    total_words = countWords(string)
    total_sentences = countSentences(string)

    # average number of letters per 100 words
    L = (total_letters / total_words) * 100
    # average number of sentences per 100 words
    S = (total_sentences / total_words) * 100

    index = 0.0588 * L - 0.296 * S - 15.8

    # print out grade
    if index > 16:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {index:.0f}")


def countLetters(string):
    """ count a-z and A-Z as letters """
    letter_count = 0
    for letter in string:
        if letter.isalpha():
            letter_count += 1

    return letter_count


def countWords(string):
    """ count words using .split() """
    word_count = len(string.split())
    return word_count


def countSentences(string):
    """ count sentences by finding '.', '!' and '?' as sentence boundaries """
    sentence_count = 0
    for letter in string:
        if letter in [".", "!", "?"]:
            sentence_count += 1

    return sentence_count


if __name__ == "__main__":
    main()