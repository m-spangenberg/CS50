import csv
import sys
import os
import re


def main():
    """ DNA profiler """

    # check validity of supplied arguments
    if len(sys.argv) < 3:
        print("usage: python dna.py databases/large.csv sequences/1.txt")
        quit()
    elif os.path.isfile(sys.argv[1]) is not True or os.path.isfile(sys.argv[2]) is not True:
        print("error: You must provide a valid filepath")
        quit()
    else:
        pass

    # path to dna database
    dna_database = sys.argv[1]
    # path to dna sample
    dna_sample = sys.argv[2]
    # database buffer
    dna_buffer = []
    # list of people in database
    people = []

    # open the dna sample and read into memory
    with open(dna_sample) as sample_file:
        sample_reader = csv.reader(sample_file, delimiter=',')
        for row in sample_reader:
            sample = row[0]

    # open the databse csv and read contents into memory
    with open(dna_database, newline='\n') as database_file:
        database_reader = csv.DictReader(database_file, delimiter=',')

        # make a list of dictionaries
        # create database dictionary
        for row in database_reader:
            dna_buffer.append(row)
            people.append(row['name'])
            dna = dict.fromkeys(people, 0)

        # get a list of STRs from dna database
        STR_list = database_reader.fieldnames[1:]

    # call the parseSTR function to build a profile from the sample
    profile = dict.fromkeys(STR_list)
    for STR in STR_list:
        profile[STR] = parseSTR(STR, sample)

    # on exact match, print out the name of the person
    counter = 0
    found = False

    for p, f in profile.items():
        counter += 1
        for d in dna_buffer:
            for n, a in d.items():
                if p == n and int(f) == int(a):
                    dna[d['name']] += 1

    for hi, sc in dna.items():
        if sc == len(profile):
            if counter == len(profile):
                found = True
                print(hi)

    # else, send 'em packing!
    if found == False:
        print('No match')


def parseSTR(STR, sample):
    """ parse the occurence of a contiguous STR in a sample"""
    # https://stackoverflow.com/a/68428559
    # I hope this is within the problem set rules set out for Week 6 - Regex is magic!
    STR_lookup = sorted(re.findall(f'(?:{STR})+', sample), reverse=True)
    if STR_lookup:
        STRcount = len(STR_lookup[0]) // len(STR)
    else:
        STRcount = 0
    return STRcount


if __name__ == '__main__':
    """ call the main function of this program """
    main()