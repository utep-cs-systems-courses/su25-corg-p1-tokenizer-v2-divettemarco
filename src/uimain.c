#include <stdio.h>
#include "tokenizer.h"
#include "history.h"

#define MAX_SIZE 100

int main()
{
  puts("Welcome!");

  while (1) { // Infinite while loop

    fputs(">", stdout);
    char userInput[MAX_SIZE];
    userInput;
    /*
      char *fgets(char *s, int size, FILE *stream);

      returns NULL on error or when EOF occurs while no characters have been read
      */
    if(fgets(userInput, sizeof(userInput), stdin)){
    /* given the user input, echo it back to the interface */
      if(userInput == NULL)
      printf("user input: %s", userInput);
      for(int i = 0; (userInput+i < (userInput + sizeof(userInput) - 1)) && (*(userInput+i) != '\0'); i++){
        char currChar = *(userInput+i);
        /**
           printf("print char[%d] = %c\n", i, currChar);
           printf("space_char(%c) returns: %d\n", currChar, space_char(currChar));
           printf("non_space_char(%c) returns: %d\n", currChar, non_space_char(currChar));
        */
      }
    }

    printf("%s", userInput);
    //printf("\n");
  }

 done: // To exit from program
  return 0;
}
