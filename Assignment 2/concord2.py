#!/usr/bin/env python3
import sys

COLUMN_INDEX = 29
START_INDEX = 9
END_INDEX = 61

'''
        Takes in the words that should not be caplized and adds them to a list called lower
Retruns: list
'''
def exclude_words():
    lower_case = []

    for lines in sys.stdin:
        line = lines.strip()

        if(line == "\"\"\"\""):
            break

        if(line != "\'\'\'\'"):
            lower_case.append(line)

        if(lower_case[0] != '2'):
                return 0
        else:
                return lower_case



'''
        Takes in the sentences to be used later and adds them to a list called lines
Returns: list
'''
def add_lines():
        lines = []

        for sentences in sys.stdin:
                line = sentences.strip()

                if(line == "\"\"\"\""):
                        continue

                lines.append(line)
        return lines



'''
        Splits the list up into individual words
Parameters: list
Returns: list
'''
def split(lines):
        words = []

        for sentence in lines:
                split_words = sentence.split()
                words.append(split_words)
        return words



'''
        Puts the words in a dict; keys are uppercased word, values are the sentences
        If words are duplicated, a letter is added to the end so that it is a unique key in the dict
Parameters: list, list
Returns: dictonary
'''
def add_to_dict(words, low):
        dictionary = {}

        copy = 1
        for line in words:
                count = 0
                for word in line:
                        if((word not in low) and (word.lower() not in low)):
                                key = word.upper()
                                if(key in dictionary.keys()):
                                        value = line[:]
                                        value[count] = key
                                        dictionary[key + str("A" * copy)] = value
                                        copy += 1
                                else:
                                        value = line[:]
                                        value[count] = key
                                        dictionary[key] = value

                        if(count == int(len(line)) - 1):
                                count = 0

                        else:
                                count += 1
        return dictionary


'''
        Concatenates the sentences in the values and alphabetizes the keys in the dict
Parameters: dictionary
Returns: list
'''
def indexed(diction):
        for i in sorted(diction.keys()):
                joined = ' '.join(diction[i])
                diction[i] = joined

        indexed = (sorted(diction.items()))
        return indexed



'''
        Aligns the uppercased word at column 30
        Cuts off words before column 10 and after column 60
Parameter: list
'''
def align(sorted_tup):
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

                line = str("".join(string))
                print(line.rstrip())



def main():
        exclude = exclude_words()
        if(exclude == 0):
                print('Input is version 1, concord2.py expected version 2')
        else:
                lines = add_lines()
                words = split(lines)
                dictionary = add_to_dict(words, exclude)
                sorted_li = indexed(dictionary)
                string = align(sorted_li)



if __name__ == "__main__":
        main()