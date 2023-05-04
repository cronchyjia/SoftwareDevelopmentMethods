#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "emalloc.h"
#include "seng265-list.h"

#define KEYWORD 40
#define INPUT_LINES 100
#define COLUMN_INDEX 29
#define START_INDEX 9
#define END_INDEX 61



/*
 *functions
 */
int compare(node_t *list, char *tok);
void upper(char *letter);
struct node_t *read_in_exclusion(node_t *head_ex);
struct node_t *read_in_lines(node_t *head_node, node_t *head_ex);
void align(node_t *ordered);


int compare(node_t *list, char *tok){
    node_t *temp1;
    temp1 = list;

    while (temp1 != NULL && tok != NULL) {
        if(strcmp(temp1->text, tok) == 0){
                return 0;
        }
        temp1 = temp1->next;
    }
    return 1;
}


void upper(char *letter){
    if(letter){
        while(*letter != '\0'){
                if(*letter == ' '){
                        break;
                }
                *letter = toupper(*letter);
                letter++;
        }
    }
}


struct node_t *read_in_exclusion(node_t *head_ex){
    node_t *temp_ex = NULL;

    char line_ex[INPUT_LINES];
    while(fgets(line_ex, sizeof(line_ex), stdin) != NULL){

        line_ex[strcspn(line_ex, "\n")] = '\0';

        if(line_ex[0] == '1'){
            printf("Input is version 1, concord3 expected version 2\n");
            exit(0);
        }

        if(strncmp(line_ex, "\"\"\"\"", 4) == 0){
            break;
        }

        if(strncmp(line_ex, "\'\'\'\'", 4) == 0){
            continue;
        }

        else{
            temp_ex = new_node_one(line_ex);
            head_ex = add_end(head_ex, temp_ex);
            char *up_let = line_ex;
            upper(up_let);
            temp_ex = new_node_one(line_ex);
            head_ex = add_end(head_ex, temp_ex);
            memset(line_ex, '\0', sizeof(line_ex));
        }
    }
    return head_ex;
}


struct node_t *read_in_lines(node_t *head_node, node_t *head_ex){
    node_t *temp_node = NULL;
    node_t *capital = NULL;

    char line[INPUT_LINES];
    while(fgets(line, sizeof(line), stdin) != NULL){
        line[strcspn(line, "\n")] = '\0';
        temp_node = new_node_one(line);

        char* token = strtok(line, " ");
        while (token) {
                if(compare(head_ex, token) == 1){
                        capital = new_node(temp_node->text, token);
                        char *letter = strstr(capital->text, temp);
                        upper(letter);
                        char *key_let = capital->key;
                        upper(key_let);
                        head_node = add_inorder(head_node, capital);
                }
                token = strtok(NULL, " ");
        }
    memset(line, '\0', sizeof(line));
    }
    return head_node;
}


void align(node_t *ordered){
    int index;
    
    while(ordered != NULL){
            char *storage = emalloc(END_INDEX * sizeof(char));
            char *string = strstr(ordered->text, ordered->key);
            index = (int)(string - ordered->text);

            int whitespace;
            int remove;
            if(index < COLUMN_INDEX){
                whitespace = COLUMN_INDEX - index;
                memset(storage, ' ', whitespace);
                strcat(storage, ordered->text);
            }

            if(index == COLUMN_INDEX){
                strcpy(storage, (ordered->text));
            }

            if(index > COLUMN_INDEX){
                remove = index - COLUMN_INDEX;
                strcpy(storage, (ordered->text) + remove);
            }

            int left_column = 8;
            memset(storage, ' ', left_column);
            while(storage[left_column] != ' '){
                storage[left_column] = ' ';
                left_column++;
            }

            int right_column = 61;
            int complete_word = 60;
            while(storage[right_column] != '\0'){
                storage[right_column] = '\0';
                right_column++;
            }
            while(storage[complete_word] != ' ' && storage[complete_word] != '\0'){
                storage[complete_word] = '\0';
                complete_word--;
            }
            storage[complete_word] = '\0';
            printf("%s\n", storage);
            memset(storage, '\0', sizeof(*storage));
            ordered = ordered->next;
    }
}


int main(int argc, char *argv[]){
    node_t *head_exclude = NULL;
    head_exclude = read_in_exclusion(head_exclude);

    node_t *ordered = NULL;
    ordered = read_in_lines(ordered, head_exclude);
    align(ordered);
}