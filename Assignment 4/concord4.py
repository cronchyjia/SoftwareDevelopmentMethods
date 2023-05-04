#!/usr/bin/env python3

import sys
import re
import fileinput

COLUMN_INDEX = 29
START_INDEX = 9
END_INDEX = 61

class concord():


    def __init__(self, input=None, output=None):
        self.input = input
        self.output = output

        self.exclude = self.__read_ex_words(self.input)
        self.sentence = self.__read_lines(self.input)
        self.words = self.__split(self.sentence)
        self.dictionary = self.__add_to_dict(self.words, self.exclude)
        self.string = self.__align(self.dictionary)

        if(self.output != None):
            with open(self.output, 'w') as f:
                self.string.pop(0)
                f.write('\n'.join(self.string))
                f.write('\n')
            f.close()

    def full_concordance(self):
        return self.string


    '''
    Takes in the words that should be capilized and adds them to a list called ex_words.
        Parameter: input file
        Returns: list
    '''
    def __read_ex_words(self, f):
        ex_words = []

        with fileinput.input(f) as f:
            for lines in f:
                line = lines.strip()

                if(line == "\"\"\"\""):
                    break

                if(line != "\'\'\'\'"):
                    ex_words.append(line)
        return ex_words


    '''
    Takes in the sentences and adds them to a list called lines, will also get rid of any blank lines and not add them to the list.
        Parameter: input file
        Returns: list
    '''
    def __read_lines(self, f):

        lines = []

        with fileinput.input(f) as f:
            for sentences in f:
                line = sentences.strip()

                if(line == "\"\"\"\""):
                    continue

                lines.append(line)
        filtered = filter(None, lines)
        return filtered


    '''
    Splits up the list into individual elements, sentneces -> words.
        Parameters: list
        Returns: list
    '''
    def __split(self, lines):
        words = []

        for sentence in lines:
            split_words = re.split("\s", sentence)
            words.append(split_words)
        return words


    '''
    Creates a sorted dictionary from two lists. If a word is not in the exclusion list then a key, value pair is added to the dictionary.
    The key is the keyword, and the value is the sentences.
    If words are duplicated, a letter is added to the end so that it is a unique key in the dict
        Parameters: list, list
        Returns: dictionary
    '''
    def __add_to_dict(self, words, low):
        dictionary = {}

        copy = 1
        for line in words:
            for word in line:
                if((word not in low) and (word.lower() not in low)):
                    key = word.upper()
                    pattern = r"\b" + word + r"\b"
                    string = ' '.join(line)

                    if(key in dictionary.keys()):
                        value = re.sub(pattern, key, string)
                        dictionary[key + str("A" * copy)] = value
                        copy += 1
                    else:
                        value = re.sub(pattern, key, string)
                        dictionary[key] = value

        indexed = sorted(dictionary.items())
        return indexed


    '''
    Aligns the uppercased word at column 30
    Cuts off words before column 10 and after column 60
        Parameters: list
        Returns: list
    '''
    def __align(self, sorted_tup):
        aligned = []

        for diction in sorted_tup:
            line = diction[1]
            look_for = str(diction[0])
            index = diction[1].find(look_for[:2])

            if(index < COLUMN_INDEX):
                white_space = COLUMN_INDEX - index
                indexed_string = (white_space * ' ') + line

            elif(index > COLUMN_INDEX):
                remove = index - COLUMN_INDEX
                indexed_string = ((START_INDEX - 1) * ' ') + line[remove + (START_INDEX - 1):]

            elif(index == COLUMN_INDEX):
                indexed_string = line

            string = list(indexed_string)

            left_column = 8
            for i in range(left_column):
                string[i] = ' '

            while(string[left_column] != ' '):
                string[left_column] = ' '
                left_column += 1

            right_column = 60
            for i in range(END_INDEX, len(string)):
                string[i] = ' '

            if(len(string) >= END_INDEX):
                while(string[right_column] != ' '):
                    string[right_column] = ' '
                    right_column -= 1

            line = (str("".join(string))).rstrip()
            aligned.append(line)
        return aligned