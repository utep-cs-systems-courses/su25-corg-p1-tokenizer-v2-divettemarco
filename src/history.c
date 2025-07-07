#include <stdio.h>
#include <stdlib.h>
#include "history.h"

/* Initialize the linked list to keep the history. */
List *init_history(){
  /* allocate space for command history */
  List *historyList = (List *)malloc(sizeof(List *));
  historyList -> root = NULL;
  return historyList;
}

/* Add a history item to the end of the list.
   List* list - the linked list
   char* str - the string to store
*/
void add_history(List *list, char *str){
  /* allocate memory for the new command */
  Item *itemToInsert = (Item *)malloc(sizeof(Item));

  /* allocate memory for the string to add and copy from str */
  // get length of str
  char *nowStr = str;
  int strLen = 0;
  while(*nowStr){
    strLen++;
    nowStr++;
  }
  // allocate memory for string member and copy str
  itemToInsert -> str = (char *) malloc((strLen + 1) * sizeof(char));
  char * tempStr = itemToInsert -> str;
  while(*tempStr++ = *str++);
  printf("Adding %s to the command history.\n", itemToInsert -> str);
  itemToInsert -> next = NULL;

  /* if root is null, insert the new item as the root */
  if(!list -> root){
    itemToInsert -> id = 1;
    list -> root = itemToInsert;
    printf("Successfully added command %d . %s to the list\n", list -> root -> id, list -> root -> str);
    return;
  }

  /* traverse list of items until next is NULL, then insert the new item at the end of the list */
  Item *currItem = list -> root;
  while(currItem -> next){
    currItem = currItem->next;
  }
  itemToInsert -> id = currItem -> id + 1;
  /* insert item to the end of the list */
  currItem -> next = itemToInsert;
  printf("Successfully added command %d . %s to the list\n", currItem->next->id, currItem->next->str);
}

/* Retrieve the string stored in the node where Item->id == id.
   List* list - the linked list
   int id - the id of the Item to find */
char *get_history(List *list, int id){
  /* traverse list until terminator item or item with input id is found */
  Item *tempItem = list->root;
  while(tempItem){
    if(tempItem -> id == id)
      return tempItem -> str;
    tempItem = tempItem -> next;
  }
  return NULL;
}

/*Print the entire contents of the list. */
void print_history(List *list){
  /* return if there are no items */
  if(list -> root == NULL){
    printf("Command history list is empty...\n");
    return;
  }
  /* print command history */
  Item *tempItem = list -> root;
  printf("Command history:\n");
  while(tempItem){
    printf("%   d. %s\n", tempItem -> id, tempItem -> str);
    tempItem = tempItem -> next;
  }
}

/*Free the history list and the strings it references. */
void free_history(List *list){
  /* return if there are no items to free */
  if(!list -> root){
    printf("There is no command history to free.\n");
    return;
  }
  /* free all command history strings and items from memory */
  printf("Forgetting command history.\n");
  Item *tempItem;
  Item *currItem;
  for(currItem = list -> root; currItem; currItem = tempItem){
    tempItem = currItem -> next;
    /* free str and item */
    free(currItem -> str);
    currItem -> str = NULL;
    free(currItem);
  }
  /* free list */
  free(list);
}
