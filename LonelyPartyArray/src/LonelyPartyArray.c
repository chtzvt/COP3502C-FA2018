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

#define DEBUG
#ifdef DEBUG
  #define debugf(fmt, ...) fprintf(stderr, fmt, ## __VA_ARGS__); fflush(stderr)
#else
  #define debugf(fmt, ...) ((void)0)
#endif

int index_is_valid(int index, LonelyPartyArray *party);
int index_exists(int index, LonelyPartyArray *party);
int create_fragment(int fragment_index, LonelyPartyArray *party);
int fragment_exists(int index, LonelyPartyArray *party);

LonelyPartyArray *createLonelyPartyArray(int num_fragments, int fragment_length)
{
  int max_cap, i;
  LonelyPartyArray *LPA = malloc(sizeof(LonelyPartyArray));
  
  debugf("(createLonelyPartyArray) Allocated space for LPA: %d at address %p\n", (int)sizeof(LonelyPartyArray), LPA);
  
  if(num_fragments <= 0 || fragment_length <= 0){
    debugf("(createLonelyPartyArray) Terminated early: num_fragments[%d] or fragment_length[%d] were <= 0\n", num_fragments, fragment_length);
    return NULL;
  }
  
  max_cap = num_fragments * fragment_length;
  debugf("(createLonelyPartyArray) Computed maximum capacity for LPA: %d\n", max_cap);
  
  LPA->num_fragments = num_fragments;
  LPA->fragment_length = fragment_length;
  LPA->num_active_fragments = 0;
  LPA->size = 0;
    
  LPA->fragments = malloc(sizeof(int *) * num_fragments);
  debugf("(createLonelyPartyArray) Allocated %d to hold %d fragments in LPA->fragments at address %p\n", (int)(sizeof(int *) * num_fragments), num_fragments, LPA->fragments);
  
  LPA->fragment_sizes = malloc(sizeof(int) * num_fragments);
  debugf("(createLonelyPartyArray) Allocated %d to hold the sizes of %d fragments in LPA->fragment_sizes at address %p\n", (int)(sizeof(int) * num_fragments), num_fragments, LPA->fragment_sizes);

  if(LPA->fragments == NULL){
    debugf("(createLonelyPartyArray) Terminated early due to malloc failure! LPA->fragments is NULL\n");
    return NULL;
  }
  
  debugf("(createLonelyPartyArray) LPA fragments will now be initialized:\n");
  for(i = 0; i < num_fragments; i++){
    debugf("(createLonelyPartyArray) \tInitializing fragment %d (of %d members) to NULL\n", i, num_fragments);
    LPA->fragments[i] = NULL;
    
    debugf("(createLonelyPartyArray) \tUpdating fragment size table for ID %d\n", i);
    LPA->fragment_sizes[i] = 0;
  }
  
  printf("-> A new LonelyPartyArray has emerged from the void. (capacity: %d, fragments: %d)\n", max_cap, num_fragments);
  
  return LPA;
}

LonelyPartyArray *destroyLonelyPartyArray(LonelyPartyArray *party)
{
  int i, j;
    
  if (party == NULL){
    debugf("(destroyLonelyPartyArray) Terminating early because party is NULL");
    return NULL;
  }
  
  debugf("(destroyLonelyPartyArray) LPA struct members will now be free()'d:\n");
  for(i = 0; i < party->num_fragments; i++){
    if(party->fragments[i] == NULL){
      debugf("(destroyLonelyPartyArray) \tFragment at index %d is NULL (won't attempt to free() it)\n", i);
      continue;
    }
    
    debugf("(destroyLonelyPartyArray) \tFreeing members of LPA->fragments[%d]\n", i);
    for(j = 0; j < party->fragment_sizes[i]; j++){
        debugf("(destroyLonelyPartyArray) \t\tFreeing member %d of LPA->fragments[%d] at address %p\n", j, i, &(party->fragments[i][j]));
        free(&(party->fragments[i][j]));
    }
  }
  
  debugf("(destroyLonelyPartyArray) Freeing LPA fragment array at address %p\n", &(party->fragment_sizes[i]));
  free(party->fragments);
  
  debugf("(destroyLonelyPartyArray) Freeing fragment size counter at address %p\n", &(party->fragment_sizes[i]));
  free(party->fragment_sizes);
  
  debugf("(destroyLonelyPartyArray) Freeing LPA at address[%p]\n", party);
  free(party);
  
  printf("-> The LonelyPartyArray has returned to the void.\n");
  
  return NULL;
}

int set(LonelyPartyArray *party, int index, int key){
  int target_fragment, index_localized, was_empty = 0;
  
  if(party == NULL){
    debugf("(set) Terminating early because LPA is NULL\n");
    return LPA_FAILURE;
  }
  
  target_fragment = (index % party->fragment_length) - 1;
  if(target_fragment < 0)
    target_fragment = 0;
    
  debugf("(set) Computed index of target fragment %d from provided index of %d\n", target_fragment, index);
  
  if(index_is_valid(index, party) < 0){
    debugf("(set) Terminating early because index %d is invalid\n", index);
    return LPA_FAILURE;
  }
  
  if(fragment_exists(target_fragment, party) < 0)
    if(create_fragment(target_fragment, party) < 0){
      debugf("(set) Terminating early because we FAILED to create a new fragment at LPA->fragments[%d] for the provided index %d\n", target_fragment, index);
      return LPA_FAILURE;
    }
  
  index_localized = index % party->fragment_length;
  
  if(party->fragments[target_fragment][index_localized] == UNUSED)
    was_empty = 1;
  else
    debugf("(set) INFO: Cell %d in fragment %d was not empty when we were called\n", index_localized, target_fragment);
    
  debugf("(set) Storing value %d at index %d of fragment %d...\n", key, index_localized, target_fragment);
  party->fragments[target_fragment][index_localized] = key;
  
  if(was_empty == 1){
    party->fragment_sizes[target_fragment]++;
    debugf("(set) Size of fragment %d updated to %d (from %d)\n", target_fragment, party->fragment_sizes[target_fragment], party->fragment_sizes[target_fragment]-1);
    party->size++;
    debugf("(set) Overall LPA size updated to %d (from %d)\n", party->size, party->size-1);
  }
  
  return LPA_SUCCESS;
}

int index_is_valid(int index, LonelyPartyArray *party){
  if(index >= 0 && index <= (party->num_fragments * party->fragment_length - 1)){
    return 0;
  } else {
    debugf("(index_is_valid) WARNING: index %d does not fall within the bounds of [0, %d] for LPA\n", index, (party->num_fragments * party->fragment_length - 1));
    return -1;
  }
}

int fragment_exists(int fragment_index, LonelyPartyArray *party){
  if(party->fragments[fragment_index] == NULL){
    debugf("(fragment_exists) INFO: fragment at index %d does not exist for LPA (but it may be created soon)\n", fragment_index);
    return -1;
  }
  
  return 0;
}

int create_fragment(int fragment_index, LonelyPartyArray *party){
  int i;
  party->fragments[fragment_index] = malloc(sizeof(int) * party->fragment_length);
  debugf("(create_fragment) Allocated %d to LPA->fragments[%d] to store %d ints at address %p\n", (int)(sizeof(int) * party->fragment_length), fragment_index, party->fragment_length, party->fragments[fragment_index]);
  
  if(party->fragments[fragment_index] == NULL){
    debugf("(create_fragment) Terminating early because malloc() FAILED for fragment_index %d\n", fragment_index);
    return -1;
  }
  
  debugf("(create_fragment) Fragment at index %d will now be initialized\n", fragment_index);
  for(i = 0; i < party->fragment_length; i++)
    party->fragments[fragment_index][i] = UNUSED;
  
  party->num_active_fragments++;
  debugf("(create_fragment) Active fragment counter updated to %d (from %d)\n", party->num_active_fragments, party->num_active_fragments-1);
  
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
