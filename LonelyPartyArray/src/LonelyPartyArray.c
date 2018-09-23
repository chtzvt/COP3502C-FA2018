/*
  Charlton Trezevant
  Dr.Sean Szumlanski
  COP 3502 - Sept 2018
  
  Program #2 - Lonely Party Array
  
  ---
  There once was a young boy named Alec.
  He wanted a string so he'd malloc.
  "Oh the bytes that I'll free!"
  He cried out with glee.
  Segmentation fault
  
  -Unknown Author
*/

#include<stdio.h>
#include<stdlib.h>
#include "LonelyPartyArray.h"

/*
typedef struct LonelyPartyArray
{
	int size;                  // number of occupied cells across all fragments
	int num_fragments;         // number of fragments (arrays) in this struct
	int fragment_length;       // number of cells per fragment
	int num_active_fragments;  // number of allocated (non-NULL) fragments
	int **fragments;           // array of pointers to individual fragments
	int *fragment_sizes;       // stores number of used cells in each fragment
} LonelyPartyArray;

-LonelyPartyArray *createLonelyPartyArray(int num_fragments, int fragment_length);
-LonelyPartyArray *destroyLonelyPartyArray(LonelyPartyArray *party);
LonelyPartyArray *cloneLonelyPartyArray(LonelyPartyArray *party);  // optional (bonus)
-int set(LonelyPartyArray *party, int index, int key);
int get(LonelyPartyArray *party, int index);
int delete(LonelyPartyArray *party, int index);
int containsKey(LonelyPartyArray *party, int key);
int isSet(LonelyPartyArray *party, int index);
int printIfValid(LonelyPartyArray *party, int index);
LonelyPartyArray *resetLonelyPartyArray(LonelyPartyArray *party);
int getSize(LonelyPartyArray *party);
int getCapacity(LonelyPartyArray *party);
int getAllocatedCellCount(LonelyPartyArray *party);
long long unsigned int getArraySizeInBytes(LonelyPartyArray *party);
long long unsigned int getCurrentSizeInBytes(LonelyPartyArray *party);

*/

int index_is_valid(int index, LonelyPartyArray *party);
int index_exists(int index, LonelyPartyArray *party);
int create_fragment(int fragment_index, LonelyPartyArray *party);
int fragment_exists(int index, LonelyPartyArray *party);

LonelyPartyArray *createLonelyPartyArray(int num_fragments, int fragment_length)
{
  int max_cap, i;
  LonelyPartyArray *LPA = malloc(sizeof(LonelyPartyArray));
  
  if(num_fragments <= 0 || fragment_length <= 0)
    return NULL;
  
  max_cap = num_fragments * fragment_length;
  
  LPA->num_fragments = num_fragments;
  LPA->fragment_length = fragment_length;
  LPA->num_active_fragments = 0;
  LPA->size = 0;
    
  LPA->fragments = malloc(sizeof(int *) * num_fragments);
  
  if(LPA->fragments == NULL)
    return NULL;
  
  for(i = 0; i < num_fragments; i++){
    LPA->fragments[i] = NULL;
    LPA->fragment_sizes[i] = 0;
  }
  
  printf("-> A new LonelyPartyArray has emerged from the void. (capacity: %d, fragments: %d)\n", max_cap, num_fragments);
  
  return LPA;
}

LonelyPartyArray *destroyLonelyPartyArray(LonelyPartyArray *party)
{
  int i, j;
    
  if (party == NULL)
    return NULL;
    
  for(i = 0; i < party->num_fragments; i++){
    if(party->fragments[i] == NULL)
      continue;
  
    for(j = 0; j < party->fragment_sizes[i]; j++)
      free(&party->fragments[i][j]);
      
    free(&party->fragments[i]);
    free(&party->fragment_sizes[i]);
  }
  
  free(&party);
  
  printf("-> The LonelyPartyArray has returned to the void.");
  
  return NULL;
}

int set(LonelyPartyArray *party, int index, int key){

  int target_fragment = index % party->fragment_length;
  
  if(party == NULL || index_is_valid(index, party) == 0 || fragment_exists(index, party) < 0)
    return LPA_FAILURE;

  if(create_fragment(target_fragment, party) < 0)
    return LPA_FAILURE;
  
  party->fragments[target_fragment][index] = key;
  
  return LPA_SUCCESS;
}

int index_is_valid(int index, LonelyPartyArray *party){
  return (index >= 0 && index <= (party->num_fragments * party->fragment_length - 1));
}

int fragment_exists(int index, LonelyPartyArray *party){
  int fragment_index = index % party->fragment_length;
  
  if(party->fragments[fragment_index] != NULL)
    return -1;
  
  return 0;
}

int create_fragment(int fragment_index, LonelyPartyArray *party){
  int i;
  party->fragments[fragment_index] = malloc(sizeof(int) * party->fragment_length);

  if(party->fragments[fragment_index] == NULL)
    return -1;
    
  for(i = 0; i < party->fragment_length; i++)
    party->fragments[fragment_index][i] = UNUSED;
  
  return 0;
}

double difficultyRating(void)
{
  return 5.0;
}

double hoursSpent(void)
{
  return 5.0;
}
