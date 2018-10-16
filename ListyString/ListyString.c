/*
  Charlton Trezevant
  Sean Szumlanski
  COP 3502C
  
  Assignment #3 - ListyString.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "ListyString.h"

#define DEBUG
#ifdef DEBUG
  #define debugf(fmt, ...) fprintf(stderr, fmt, ## __VA_ARGS__); fflush(stderr)
#else
  #define debugf(fmt, ...) ((void)0)
#endif

void print_usage(char *name);
char *listy_to_string(ListyString *list);
ListyNode *get_listy_tail(ListyString *list);

/*int main(int argc, char **argv)
{
  // Handle cases where too few arguments are provided, so we don't segfault.
	if (argc < 2 || argv[1] == NULL)
  {
    debugf("(main) Error: Invalid arguments\n");
		print_usage(argv[0]);
		return 1;
	}
  
  return processInputFile(argv[1]);
}*/

int processInputFile(char *filename)
{
  FILE *ifp;
  char *raw_string = NULL, *cmd;
  int i;
  ListyString *listy;
  
  ifp = fopen(filename, "r");
  
  if (ifp == NULL){
    debugf("(processInputFile) [1] Invalid filename provided.\n");
    return 1;
  }
  
  fscanf(ifp, "%s", raw_string);
  
  listy = createListyString(raw_string);
  
  if (listy == NULL){
    debugf("(processInputFile) [1] ListyString creation failed.\n");
    return 1;
  }
  
  return 0;
}

ListyString *createListyString(char *str)
{
  ListyString *list;
  ListyNode *prev_node, *tmp;
  int i;
  
  list = malloc(sizeof(ListyString));
  list->length = 0;
  list->head = NULL;
  debugf("(createListyString) malloc'd %d for a ListyString of length %d\n", (int)(sizeof(ListyString)), list->length);
  
  if (str == NULL){
    debugf("(createListyString) [NULL] Recieved a NULL input string\n");
    return list;
  }
  
  list->length = strlen(str);
  
  // May want to double check on how to handle strlen of 0 here.
  if (list->length < 1){
    debugf("(createListyString) [NULL] Recieved an input string with a length of 0\n");
    return list;
  }

  prev_node = malloc(sizeof(ListyNode));
  list->head = prev_node;
  list->head->data = str[0];
  
  for (i = 1; i < list->length; i++)
  {
    tmp = malloc(sizeof(ListyNode));
    debugf("(createListyString) malloc'd %d for a ListyString node at index %d to hold %c\n", (int)(sizeof(ListyNode)), i, str[i]);
    
    tmp->data = str[i];
    tmp->next = NULL;
    
    prev_node->next = tmp;
    prev_node = tmp;
  }

  return list;
}

ListyString *destroyListyString(ListyString *listy)
{
  ListyNode *next_node, *tmp;
  int i;
  
  if (listy == NULL || listy->head == NULL)
    return NULL;
    
  tmp = listy->head;
    
  for (i = 0; i < listy->length - 1; i++)
  {
    next_node = tmp->next;
    
    free(tmp);
    
    tmp = next_node;
  }
  
  free(listy);
  
  return NULL;
}

ListyString *cloneListyString(ListyString *listy)
{
  char *listy_contents;
  
  if (listy == NULL)
  {
    debugf("(cloneListyString) [NULL] ERROR: Terminating early due to NULL pointer!\n");
    return NULL;
  }

  listy_contents = listy_to_string(listy);

  return createListyString(listy_contents);
}

void replaceChar(ListyString *listy, char key, char *str)
{
  int str_len;
  
  if(listy == NULL || listy->head == NULL)
  {
    debugf("(replaceChar) [void] Called with NULL arguments\n");
    return;
  }
  
  str_len = strlen(str);


}

void reverseListyString(ListyString *listy)
{
  ListyNode *next, *prev, *head;
  
  if(listy == NULL || listy->head == NULL)
  {
    debugf("(reverseListyString) [void] Called with NULL arguments\n");
    return;
  }
  
  prev = listy->head;
  prev->next = NULL;
  head = listy->head->next;
  next = head;
  
  while (head != NULL)
  {
    head = head->next;
    next->next = prev;
    prev = next;
    next = head;
  }
  
  listy->head = head;
}

ListyString *listyCat(ListyString *listy, char *str)
{
  int str_len, i;
  ListyNode *tail;
  
  if(listy == NULL && str == NULL)
  {
    debugf("(listyCat) [NULL] Called with NULL arguments\n");
    return NULL;
  }
  
  if(listy == NULL && str != NULL)
  {
    debugf("(listyCat) [createListyString()] Called with NULL ListyString and non-NULL string\n");
    return createListyString(str);
  }
  
  if(str == NULL)
  {
    debugf("(listyCat) [ListyString] Called with non-NULL ListyString and NULL string\n");
    return listy;
  }
  
  tail = get_listy_tail(listy);
  str_len = strlen(str);
  
  for (i = 0; i < str_len; i++)
  {
    tail->next = malloc(sizeof(ListyNode));
    tail->next->data = str[i];
    tail = tail->next;
  }
  
  return listy;
}

int listyCmp(ListyString *listy1, ListyString *listy2)
{
  int i;
  ListyNode *l1_tmp, *l2_tmp;
  
  // Two NULL pointers are considered equivalent
  if (listy1 == NULL && listy2 == NULL)
  {
    debugf("(listyCmp) [0] INFO: Encountered two NULL ListyStrings\n");
    return 0;
  }
  
  // Perform checks specific to non-NULL listystrings
  if (listy1 != NULL && listy2 != NULL)
  {
    // Two non-NULL listystrings with NULL head pointers are equivalent
    if (listy1->head == NULL && listy2->head == NULL)
    {
      debugf("(listyCmp) [0] INFO: Encountered two non-NULL ListyStrings with NULL heads\n");
      return 0;
    }
    
    // Two non-NULL listystrings with unequal lengths must be non-equivalent
    if(listy1->length != listy2->length)
    {
      debugf("(listyCmp) [-1] INFO: Encountered two non-NULL ListyStrings with unequal lengths\n");
      return -1;
    }
  }
  else
  {
    // A NULL listystring pointer is not equivalent to a non-NULL one
    debugf("(listyCmp) [-1] INFO: Returning -1 \n");
    return -1;
  }

  l1_tmp = listy1->head;
  l2_tmp = listy2->head;

  for (i = 0; i < listy1->length; i++)
  {
    if (l1_tmp->data != l2_tmp->data)
      return -1;
      
    l1_tmp = l1_tmp->next;
    l2_tmp = l2_tmp->next;
  }
  
  return 0;
}

int listyLength(ListyString *listy)
{
  if (listy == NULL)
  {
    debugf("(listyLength) [-1] INFO: Y'all passed me an empty string\n");
    return -1;
  }
  
  return listy->length;
}

void printListyString(ListyString *listy)
{
  if (listy == NULL)
  {
    printf("(empty string)\n");
    debugf("(printListyString) INFO: Y'all passed me an empty string\n");
  }
  
  printf("%s\n", listy_to_string(listy));
}

char *listy_to_string(ListyString *list)
{
  ListyNode *tmp;
  char *str;
  int i;
  
  if (list == NULL || list->head == NULL)
  {
    debugf("(listy_to_string) [NULL] ERROR: Terminating early due to NULL pointer!\n");
    return NULL;
  }
  
  tmp = list->head;
  str = malloc(sizeof(char) * (list->length+1));
  
  // May need to implement proper bounds checking for the very last node,
  // which will not have a next pointer.
  for (i = 0; i < list->length - 1; i++)
  {
    str[i] = tmp->data;
    tmp = tmp->next;
    
    if (tmp == NULL)
    {
      debugf("(listy_to_string) [NULL] ERROR: Recieved malformed listy string- encountered a NULL node at index %d\n", i);
      return NULL;
    }
  }
  
  // Terminate our character array with a null sentinel
  str[list->length] = '\0';
  
  return str;
}

ListyNode *get_listy_tail(ListyString *list)
{
  ListyNode *tmp;
  int i;
  
  if (list == NULL || list->head == NULL)
  {
    debugf("(get_listy_tail) [NULL] ERROR: Terminating early due to NULL pointer!\n");
    return NULL;
  }
  
  tmp = list->head;
  
  // Verify bounds checking here
  for (i = 1; i < list->length - 1; i++)
  {
    tmp = tmp->next;
    
    if (tmp == NULL)
    {
      debugf("(get_listy_tail) [NULL] ERROR: Recieved malformed listy string- encountered a NULL node at index %d\n", i);
      return NULL;
    }
  }
  
  return tmp;
}

ListyNode *find_listy_char(ListyString *list, char key)
{
  ListyNode *tmp;
  int i;
  
  if (list == NULL || list->head == NULL)
  {
    debugf("(find_listy_char) [NULL] ERROR: Terminating early due to NULL pointer!\n");
    return NULL;
  }
  
  tmp = list->head;
  
  // Verify bounds checking here
  for (i = 1; i < list->length - 1; i++)
  {
    if (tmp == NULL)
    {
      debugf("(get_listy_tail) [NULL] ERROR: Recieved malformed listy string- encountered a NULL node at index %d\n", i);
      return NULL;
    }
    
    if (tmp->data == key)
      return tmp;
    
    tmp = tmp->next;
  }
  
  return NULL;
}

void print_usage(char *name)
{
	printf("Usage: %s  [input file]\n", name);
}


double difficultyRating(void)
{
  return 4.0;
}


double hoursSpent(void)
{
  return 5.0;
}
