from cs50 import get_int

# credit.py

cardDB = {
    "vendor1": {"vendor": "AMEX", "qualifiers": [31, 34, 37, 5], "digits": [15]},
    "vendor2": {"vendor": "MASTERCARD", "qualifiers": [51, 52, 53, 54, 55, 13, 44, 0, 9], "digits": [16]},
    "vendor3": {"vendor": "VISA", "qualifiers": [4, 11, 81, 22], "digits": [13, 16]}
}

# get input
number = get_int("Number: ")


def calc(number):
    """ calculate the total value of alternating digits in number """
    # pass the user input to a list
    number_list = [int(i) for i in str(number)]

    num_second = ""
    num_first = 0
    count = 0

    # multiply every number in the list by 2 starting at -2
    for num in number_list[-2::-2]:
        num_second += str(num * 2)

    number_list2 = [int(i) for i in str(num_second)]
    for num3 in number_list2:
        count += num3

    # sum every 2nd number starting from -1
    for num2 in number_list[::-2]:
        num_first += num2

    return num_first + count


def cardVendor():
    """ verify the card vendor """
    card_validity = True

    # last digit as a product of Luhn’s Algorithm
    last_digit = abs(calc(number)) % 10
    # length of number
    len_number = len(str(number))
    # last two digits of number
    two_numbers = abs(number) % 100

    for key in cardDB:
        if two_numbers > 9 and two_numbers in cardDB[key]["qualifiers"]:
            if len_number in cardDB[key]["digits"] and last_digit == 0:
                print(cardDB[key]["vendor"])
                card_validity = False
                break
        elif (two_numbers % 10) in cardDB[key]["qualifiers"]:
            if len_number in cardDB[key]["digits"] and last_digit == 0:
                print(cardDB[key]["vendor"])
                card_validity = False
                break

    if card_validity:
        print("INVALID")


cardVendor()