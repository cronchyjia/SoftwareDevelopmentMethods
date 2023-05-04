#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define EX_WORDS 20
#define EX_WORD_LEN 20
#define INPUT_LINES 100
#define INPUT_LINE_LEN 70
#define INDEX_WORDS 100

/*
 *functions
 */
void empty_line(char arr[][EX_WORD_LEN], int index);
int token_words(char ex[][EX_WORD_LEN], char line[], int ex_sz, char buff[][EX_WORD_LEN]);
void remove_word(char arr[][EX_WORD_LEN], int remove, int buff_sz);

//struct for each line - keeps track of number of copies needed
struct line{
        char line[INPUT_LINE_LEN];
        char index[INDEX_WORDS];
};

/*
 * Comparison for line structs
 *      used for qsort
 *      logic adapted from:
 *              https://stackoverflow.com/questions/13372688/sorting-members-of-structure-array
 */
static int compare(const void *str_one, const void *str_two){
        struct line *line_one = (struct line *)str_one;
        struct line *line_two = (struct line *)str_two;
        return strcmp(line_one->index, line_two->index);
        }

int main(int argc, char *argv[]){

        //initializes exclude words, input arrays and their size
        char exclude[EX_WORDS][EX_WORD_LEN];
        char input[INPUT_LINES][INPUT_LINE_LEN];
        int exclude_sz = 0;
        int input_sz = 0;
        char *token;
        int sentence_sz = 0;


        //get the exclude words into the exclude arr
        while(fgets(exclude[exclude_sz], EX_WORD_LEN, stdin) != NULL){

                //remove \n char
                exclude[exclude_sz][strcspn(exclude[exclude_sz], "\n")] = 0;

                if(strncmp(exclude[exclude_sz], "\"\"\"\"", 4) == 0){
                        empty_line(exclude, exclude_sz);
                        break;
                }

                if(exclude_sz + 1 ==2 && strncmp(exclude[exclude_sz], "\'\'\'\'", 4) == 0){
                        empty_line(exclude, exclude_sz);
                        exclude_sz = 0;
                }
                else{
                        exclude_sz = exclude_sz + 1;
                }
        }

        struct line sentence[INPUT_LINES];

        //second loop to loop through the lines and do things
        while(fgets(input[input_sz], INPUT_LINE_LEN, stdin) != NULL){
        char buff[INDEX_WORDS][EX_WORD_LEN];

                //remove \n char
                input[input_sz][strcspn(input[input_sz], "\n")] = 0;

                int buff_sz = token_words(exclude, input[input_sz], exclude_sz, buff);


                //input line is regular and default
                for(int i =0; i < buff_sz; i++){
                        struct line temp;
                        strcpy(temp.line, input[input_sz]);
                        strcpy(temp.index, buff[i]);

                        char *letter = strstr(temp.line, temp.index);
                        if(letter){
                                while(*letter != '\0'){
                                        if(*letter == ' '){
                                                break;
                                        }
                                        *letter = toupper(*letter);
                                        letter++;
                                }
                        }
                        sentence[sentence_sz] = temp;
                        sentence_sz++;
                }

        }

        qsort(sentence, sentence_sz, sizeof(struct line), compare);

        for(int i = 0; i < sentence_sz; i++){
                printf("%s\n", sentence[i].line);
        }

        return 0;
}

/*
 * Emptys the line
 */
void empty_line(char arr[][EX_WORD_LEN], int index){
        for(int i = 0; i < EX_WORD_LEN; i++){
                arr[index][i] = '\0';
        }
}

/*
 * Tokenize the sentence
 */
int token_words(char exclude[][EX_WORD_LEN], char line[], int ex_sz, char buff[][EX_WORD_LEN]){
        char temp[INPUT_LINE_LEN];
        strcpy(temp, line);
        int buff_sz = 0;

        for(char *tok = strtok(temp, " "); tok != NULL; tok = strtok(NULL, " ")){
                strcpy(buff[buff_sz], tok);
                buff_sz = buff_sz + 1;
        }

        for(int i = 0; i < buff_sz; i++){
                for(int j = 0; j < ex_sz; j++){
                        if(strncmp(buff[i], exclude[j], INPUT_LINE_LEN) == 0){
                                remove_word(buff, i, buff_sz);
                                buff_sz--;
                                i--;
                        }
                }
        }
        return buff_sz;
}

/*
 * Removes a word if they are the same
 */
void remove_word(char arr[][EX_WORD_LEN], int remove, int buff_sz){
        for(int i = 0; i < buff_sz - 1; i++){
                if(i == remove){
                        strcpy(arr[remove], arr[i+1]);
                        remove++;
                }
        }
}
