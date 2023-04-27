/******** INCLUDES ********/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>



/******** TOOLS ********/

 char * get_secret_code() {
    char * digits = (char * ) malloc(sizeof(char) * 4);

    int c = 0;
    int is_uniq =0;
 
    srand(time(0));
    
    for (int i = 0; strlen(digits) < 4; i++) {
        char snum = rand() % 8 + '0';
        
        if (digits== 0) {
            is_uniq = 1;
        }
        
        for (int i = 0; digits[i] != '\0'; i++) {
            if (digits[i] == snum) {
                is_uniq = 0;
            }
        }
        
        is_uniq = 1;

        if (is_uniq) {
            digits[c++] = snum;
        }
     
    }
    return digits;
}

/******** HIT THE TARGET OR NOT ? ********/
int misplaced_pieces(char* param_1, char* param_2)
{
    int missed_piece = 0;
    for (int i = 0; param_1[i] != '\0'; i++)
    {
        for (int c = 0; param_2[c] != '\0'; c++)
        {
            if ((param_1[i] = param_2[c]) && (i != c)) missed_piece++;
        }
    }
    return missed_piece;
}

int well_placed_pieces(char* param_1, char* param_2)
{
    int well_part = 0;
    unsigned long int i;
    for (i = 0; i < strlen(param_1); i++)
    {
        if (param_1[i] == param_2[i]) well_part++;
    }
    return well_part;
}


/******** RE-ENTRY OF ELEMENTS ********/

int again_and_again(char* param)
{
    int c;
    int b;

    for (c = 0; param[c] != '\0'; c++)
    {
        for (b = c + 1; param[b] != '\0'; b++)
        {
            if (param[c] == param[b]) return 1;
        }
    }
    return 0;
}

/******** CHECKING FOR CORRECT ENTRY OF ELEMENTS ********/

int invalid_input(char* params)
{
    if (strlen(params) != 4) return 1;
    int c = 0;
    do
    {
        if ((params[c] < '0' || params[c] > '9') || again_and_again(params))return 1;
        c++;
    }
    while(params[c] != '\0');
    return 0;
}

/******** USER'S INPUT ********/

char* play()
{
    char* entry = (char*)malloc(sizeof(char) * 10);
    int c = 0;
    char v;

    while (read(0, &v, 1) > 0)
    {
        if (v != '\n')
        {
            entry[c] = v;
            c++;
        }else return entry;
    }
    return NULL;
}

/******** LET'S PLAY ********/

int main(int argc, char* argv[])
{
    int attempts = 10;
    int attempt_counter = 0;

    char* secret_code = (char*)malloc(sizeof(char) * 10);
    char* entry;
    /* checking for the correct input signals, if nothing is entered, 
    the program will generate a secret code itself 
    and set the number of attempts by default */

    if (argc < 2) secret_code = get_secret_code();
    
    /* condition for the correct input of only one signal 
    either "-c" or "-t" */
    else if (argc == 3)
    {
        if ((strcmp(argv[1], "-c") == 0))
        {
            strcpy(secret_code, argv[2]);
            if (invalid_input(secret_code)) 
            {
                printf("WRONG INPUT!\n");
                return 1;
            }
        }
        else if (strcmp(argv[1], "-t") == 0) 
        {
            attempts = atoi(argv[2]);
            secret_code = get_secret_code();        
        }
        else
        {
            printf("WRONG SIGANL!\n");
            return 1;
        }
    }
    /* there is already a check for the correct input of two signals 
    and "-c" and "-t" */
    else if (argc == 5)
    {
        if ((strcmp(argv[1], "-c") == 1) || (strcmp(argv[3], "-t") == 1))
        {
            printf("WRONG SIGNAL!\n"); 
            return 1;             
        }
        if ((strcmp(argv[1], "-c") == 0))
        {
            strcpy(secret_code, argv[2]);
            if (invalid_input(secret_code)){
                printf("WRONG INPUT!\n");
                return 1;
            }
        }
        if ((strcmp(argv[3], "-t") == 0))
        {
            attempts = atoi(argv[4]);
        }
        else
        {
            printf("WRONG SIGNAL!\n");
            return 1;
        }
    }
    
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    // printf("%s\n", secret_code);
    
    while (attempt_counter < attempts) {
        printf("---\nRound%d\n", attempt_counter);
        entry = play();

        if (entry == NULL) return 0;
            

        if (invalid_input(entry)) {
            printf("Wrong input!\n");
            continue;
        }
        int good = well_placed_pieces(secret_code, entry);
        // int bad = misplaced_pieces(secret_code, entry);
        if (good == 4) 
        {
            printf("Congratz! You did it!\n");
            break;
        } 
        else 
        {
            printf("Well Placed pieces: %d\n", good);
            // printf("Misplaced pieces: %d\n", bad);
        }
        attempt_counter++;
    }
    return 0;
}