#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "history.h"

#define MAX_SIZE 100

int main()
{
  printf("Welcome!\n");
  /* create command history */
  List *commandHistory = init_history();

  /* start program */
  while (1) {
    /* print menu, prompt for user to enter a command, save and read command */
    char userInput[MAX_SIZE];
    printf("\nPlease enter:\n- a command \n- '!' followed by the chosen command id \n- 'p' to print the command history \n- 'f' to forget the command history \n- 'q' to quit the program\n");
    fputs("\n>", stdout);
    // char *fgets(char *s, int size, FILE *stream); // returns NULL on error or EOF when no chars were read
    if(fgets(userInput, sizeof(userInput), stdin)){
      int inputIdx = 0;
      /* remove '/n' char from input */
      while(userInput[inputIdx]){
        inputIdx++;
        if(userInput[inputIdx] == '\n'){
          userInput[inputIdx] = '\0';
        }
      }
      printf("Command entered: %s\n\n", userInput);
      /* 'q' to quit program */
      if(userInput[0] == 'q' && userInput[1] == '\0'){
        free_history(commandHistory);
        printf("Ending the program...\n");
        exit(0);
      }
      /* '!' signals an attempt to access a chosen command from command history */
      if(userInput[0] == '!' && userInput[1] != '\0'){
        /* convert string to int: atoi() */
        int chosenCommand = 0;
        for (int i = 1 ; userInput[i] >= '0' && userInput[i] <= '9'; ++i)
          chosenCommand = 10 * chosenCommand + (userInput[i] - '0');
        /* attempt to get the chosen command, if found, process the tokens */
        if(chosenCommand){
          char *command = get_history(commandHistory, chosenCommand);
          if(command){
            printf("Entering chosen command !%d:\n>%s\n", chosenCommand, command);
            char **commandToken = tokenize(command);
            print_tokens(commandToken);
            free_tokens(commandToken);
          }else{
            printf("Fetching of command '%s' failed, please try again.\n", userInput);
          }
        }else{
          printf("'%s' is not a valid command, please try again.\n", userInput);
        }
      }
      /* 'v' to print the command history */
      else if(userInput[0] == 'p' && userInput[1] == '\0'){
        print_history(commandHistory);
      }
      /* 'f' to forget the command history and create the new command history */
      else if(userInput[0] == 'f' && userInput[1] == '\0'){
        free_history(commandHistory);
        commandHistory = init_history();
      }
      /* enter a new command and save in command history */
      else if(userInput && userInput[0] != '\0' && userInput[0] != '!'){
        /* tokenize, print, and free tokens*/
        char **tokens = tokenize(&userInput[0]);
        print_tokens(tokens);
        free_tokens(tokens);
        add_history(commandHistory, &userInput[0]);
      }else{
        printf("User input is not valid, please try again.");
      }
    }else{
      printf("Reading user input failed, please try again.\n");
    }
  }
}
