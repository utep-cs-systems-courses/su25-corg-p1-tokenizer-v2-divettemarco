#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "history.h"

/* Return true (non-zero) if c is a whitespace characer
   ('\t' or ' ').  
   Zero terminators are not printable (therefore false) */
int space_char(char c){
  return c == '\t' || c == ' ';
}

/* Return true (non-zero) if c is a non-whitespace 
   character (not tab or space).  
   Zero terminators are not printable (therefore false) */ 
int non_space_char(char c){
  return c != '\0' && !space_char(c);
}

/* Returns a pointer to the first character of the next 
   space-separated token in zero-terminated str.  Return a zero pointer if 
   str does not contain any tokens. */
char *token_start(char *str){
  /*read all character */
  while(*str){
    /* return the pointer to the first character that is a non space character */
    if(non_space_char(*str))
      return str;
    str++;
  }
  return '\0';
}

/* Returns a pointer terminator char following *token */
char *token_terminator(char *token){
  /* finds the first space char and returns token terminator */
  while(non_space_char(*token))
    token++;
  return token;
}

/* Counts the number of tokens in the string argument. */
int count_tokens(char *str){
  int tokenCount = 0;
  /* find the start of each token and update the tokenCount for each token found */
  for(char *p = token_start(str); p; p = token_start(token_terminator(p)))
    tokenCount++;
  return tokenCount;
}

/* Returns a freshly allocated new zero-terminated string
   containing <len> chars from <inStr> */
char *copy_str(char *inStr, short len){
  /* allocate memory then copy input string */
  char *strCopyHead = (char *) malloc(sizeof(char) * (len + 1));
  for(int i = 0; i < len; i++)
    strCopyHead[i] = inStr[i];
  strCopyHead[len] = '\0';
  return strCopyHead;
}

/* Returns a freshly allocated zero-terminated vector of freshly allocated 
   space-separated tokens from zero-terminated str.

   For example, tokenize("hello world string") would result in:
     tokens[0] = "hello"
     tokens[1] = "world"
     tokens[2] = "string" 
     tokens[3] = 0
*/
char **tokenize(char* str){
  printf("Tokenizing command: %s\n", str);
  int tokenCount = count_tokens(str);
  /* allocate space for the pointers*/
  char **tokens = (char **)malloc(sizeof(char *) * (tokenCount+1));
  char *tokenStart = token_start(str);
  /* store a pointer to each token */
  for(int i = 0; i < tokenCount; i++){
    char *tokenEnd = token_terminator(tokenStart);
    tokens[i] = copy_str(tokenStart, tokenEnd - tokenStart);
    tokenStart = token_start(tokenEnd);
  }
  /* return terminated token list */
  tokens[tokenCount] = NULL;
  return tokens;
}

/* Prints all tokens. */
void print_tokens(char **tokens){
  /* return if there are no tokens to print */
  if(!tokens || !tokens[0]){
    printf("There are no tokens to print.\n");
    return;
  }
  /* traverse pointers to print each token */
  printf("Input tokens:\n");
  for(int i = 0; tokens[i]; i++)
    printf("   %d. %s\n", i, tokens[i]);
}

/* Frees all tokens and the vector containing them. */
void free_tokens(char **tokens){
  /* return if there are no tokens to free */
  if(!tokens){
    printf("There are no tokens to free.\n");
    return;
  }
  printf("Freeing tokens...\n");
  /* first free the tokens, then the vector */
  char **currToken = tokens;
  for(int i = 0; currToken[i]; i++){
    free(currToken[i]);
    currToken[i] = NULL;

  }
  free(tokens);
  tokens = NULL;
}
