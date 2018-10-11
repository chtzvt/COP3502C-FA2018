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

//#define DEBUG
#ifdef DEBUG
  #define debugf(fmt, ...) fprintf(stderr, fmt, ## __VA_ARGS__); fflush(stderr)
#else
  #define debugf(fmt, ...) ((void)0)
#endif


void print_usage(char *name);

int main(int argc, char **argv)
{
  // Handle cases where too few arguments are provided, so we don't segfault.
	if(argc < 2 || argv[2] == NULL){
		print_usage(argv[0]);
		return 1;
	}
  
  return processInputFile(argv[1]);
}

int processInputFile(char *filename)
{
  FILE *ifp;
  char *raw_string, *cmd;
  int i;
  ListyString *listy;
  
  ifp = fopen(filename, "r");
  
  if (ifp == NULL)
    return 1;
  
  fscanf(temperatures, "%f", &currentTemp);
  
  listy = createListyString(raw_string);
  
  if (listy == NULL)
    return 1;
  
  return 0;
}

ListyString *createListyString(char *str)
{
  ListyString *list;
  ListyNode *head, *prev_node, *tmp;
  int i, raw_len = strlen(str);
  
  // May want to double check on how to handle strlen of 0 here.
  if(raw_len < 0)
    return NULL;
  
  list = malloc(sizeof(ListyString));
  list->length = raw_len;
  
  list->head = malloc(sizeof(ListyNode));
  head->data = str[0];
    
  for(i = 1; i < raw_len - 1; i++){
    tmp = malloc(sizeof(ListyNode));
    
    tmp->data = str[i];
    
    prev_node->next = tmp;
    prev_node = tmp;
  }
  
  return list;
}

ListyString *destroyListyString(ListyString *listy)
{
  ListyNode *next_node, *tmp;
  int i;
  
  if(listy == NULL || listy->head == NULL)
    return NULL;
    
  tmp = listy->head;
    
  for(i = 0; i < listy->length - 1; i++){
    next_node = tmp->next;
    
    free(tmp);
    
    tmp = next_node;
  }
  
  free(listy);
  
  return NULL;
}

ListyString *cloneListyString(ListyString *listy)
{
  
}

void replaceChar(ListyString *listy, char key, char *str)
{
  
}

void reverseListyString(ListyString *listy)
{
  
}

ListyString *listyCat(ListyString *listy, char *str)
{
  
}

int listyCmp(ListyString *listy1, ListyString *listy2)
{
  
}

int listyLength(ListyString *listy)
{
  
}

void printListyString(ListyString *listy)
{
  
}

void print_usage(char *name)
{
	printf("Usage: %s  [input file]\n", name);
}


double difficultyRating(void)
{
  return 5.0;
}


double hoursSpent(void)
{
  return 5.0;
}
