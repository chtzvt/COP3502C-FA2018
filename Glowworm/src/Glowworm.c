#include "Glowworm.h"
#include<stdio.h>
#include<stdlib.h>
#include<strings.h>

// The Glowworm type represents a glowworm, including its associated properties
// and metadata.
typedef struct {
	// 0 or 1, for dead or alive.
	char isAlive;
	// The length of our worm's body, excluding the head and tail segments.
	int bodyLength;
	// The index of the tail on the platform. This is 1-indexed (see print_worm).
	int tailIndex;
	// Maximum overall length of the glowworm, including the head and tail segments.
	int maxLength;
} glowworm;

// Lots of helper functions! See their definitions for documenation.
void appear(glowworm *worm, char *food);
void print_worm(glowworm *worm);
void print_platform(int len);
void eat_char(glowworm *worm, char *food);
void grow(glowworm *worm);
void shrink(glowworm *worm);
void inch_forward(glowworm *worm);
void kill(glowworm *worm);
void chill(glowworm *worm);
void print_usage(void);

int main(int argc, char **argv)
{
	// My glowworm's name is Bubba. He's a champ.
	glowworm bubba = {.isAlive = 1, .bodyLength = 1, .tailIndex = 1, .maxLength = 0};
	int i;
	
	// Handle cases where too few arguments are provided, so we don't segfault.
	if(argc < 2 || argv[2] == NULL){
		print_usage();
		return 1;
	}
	
	// Before running, set Bubba's max length to whatever the user has provided.
	bubba.maxLength = atoi(argv[1]);
	appear(&bubba, argv[2]);
	
	// Loop over the input string, and let our helpers handle the rest.
	for(i = 0; i < strlen(argv[2]); i++){
		eat_char(&bubba, &argv[2][i]);
		print_worm(&bubba);
		print_platform(bubba.maxLength);
		
		if(bubba.isAlive == 0)
			break; // Stop eating when Bubba dies. Sad!
	}
	
	return 0;
}

// Appear prints the provided input string, along with the initial state of our
// worm. It does not modify the glowworm's state whatsoever.
void appear(glowworm *worm, char *food){
	printf("%s\n\nGlowworm appears! Hooray!\n", food);
	print_worm(worm);
	print_platform(worm->maxLength);
}

// Print_worm conveniently does exactly what its name would imply. It takes the
// maxumum overall length, number of body segments, and index of the tail from
// our glowworm to figure out where (and how) to print it out.
void print_worm(glowworm *worm){
	
	// The index of our worm's head is going to be in front of the tail
	// and all body segments, so we can compute it from those lengths.
	int headIndex = worm->tailIndex + worm->bodyLength + 1;
	int i;
	
	// If the head is actually further away than the overall maxumum length of our
	// worm, it means that the head should actually wrap around to the beginning
	// of the platform and get behind the tail.
	if(headIndex > worm->maxLength)
		headIndex -= worm->maxLength;

	// Unlike most things in CS, Glowworm body parts are 1-indexed for clarity.
	// I found that this makes some of the growing/shrinking logic somewhat easier
	// to follow.
	for(i = 1; i < worm->maxLength + 1; i++) {
		
		// The head lives at the "head index", so we'll print it there.
		if(i == headIndex){
			printf(worm->isAlive == 1 ? "G" : "x");
			continue;
		}
		
		// Same deal with our tail
		if(i == worm->tailIndex){
			printf("~");
			continue;
		}
		
		// Is the head in front of the tail?
		if(headIndex > worm->tailIndex){
			if(i > worm->tailIndex && i < headIndex){
				// The body segment nearest to the head should be capitalized
				if(i == headIndex - 1){
					// Additionally, that final segment will be different depending on
					// whether or not the glowworm is dead. We'll use the ternary operator
					// here to account for this concisely.
					printf(worm->isAlive == 1 ? "O" : "X");
				} else {
					printf("o");
				}
			} else {
				// We'll need to put spaces at any index between the head and the tail,
				// so that they'll be properly spaced apart
				if(i < headIndex && i < worm->tailIndex)
					printf(" ");
			}
		}
		
		// Is the tail in front of the head? If so, Bubba has wrapped- we'll need to
		// take the laws of Translocational Worm Physics into account.
		if(headIndex < worm->tailIndex){
			// Is our cursor in front of the tail, but behind the head?
			// If it is, we're in the body section, so we'll have to print some segments.
			if(i > worm->tailIndex || i < headIndex){
				// The body segment closest to the head should be capitalized
				if(i == headIndex - 1 || (i+1) - worm->maxLength == headIndex){
					printf(worm->isAlive == 1 ? "O" : "X");
				} else {
					printf("o");
				}
			} else {
				// Is our cursor outside of the worm? Cool- we'll print spaces if so.
				printf(" ");
			}
		}
		
	}
	
	printf("\n");
}

// Print_platform prints a platform of a user-specified length underneath our worm.
void print_platform(int len){
	int i;
	
	for(i = len; i != 0; i--)
		printf("=");

	printf("\n\n");
}

// Eat_char "consumes" individual characters from the input string and maps them
// to the appropriate action that our glowworm should take. With the exception
// of chill, each function called by eat_char modifies the worm's state in some
// way.
void eat_char(glowworm *worm, char *food){
	switch(*food){
		case 'o':
		case 'O':
		case '@':
			grow(worm);
			break;
		
		case 's':
		case 'S':
			shrink(worm);
			break;
		
		case '-':
		case '=':
			inch_forward(worm);
			break;
			
		case 'x':
		case 'X':
		case '%':
			kill(worm);
			break;
			
		default:
			chill(worm);
	}
}

// Grow will increase the length of the glowworm's body by one, except in cases
// where growing would cause the worm to exceed the overall maximum length,
// whereupon we'll noop and "chill" instead.
void grow(glowworm *worm){
	// 3 isn't a magic number- it's the body's current length plus a new segment,
	// plus two more segments to account for the head and tail.
	if((worm->bodyLength + 3) > worm->maxLength){
		chill(worm);
		return;
	}
	
	printf("Glowworm grows:\n");
	worm->bodyLength++;
}

// Shrink will "shrink" a given worm. Each call to shrink decrements the number
// of body segments by 1 until there's a single segment left, at which point your
// worm will cease shrinking and chill instead.
void shrink(glowworm *worm){
	if(worm->bodyLength == 1){
		chill(worm);
		return;
	}
	
	printf("Glowworm shrinks:\n");
	worm->bodyLength--;
}

// Inch_forward manipulates the position of a glowworm's tail in order to move it
// around the platform. When the tail's position reaches the end of the platform,
// it'll wrap back to position 1.
void inch_forward(glowworm *worm){
	printf("Glowworm inches forward:\n");
	
	if(worm->tailIndex + 1 > worm->maxLength)
		worm->tailIndex = 1;
	else
		worm->tailIndex++; // See Bubba Run
}

// Kill murders a glowworm in cold blood by setting its "isAlive" property to 0.
void kill(glowworm *worm){
	printf("Glowworm meets its demise. SAD.\n");
	worm->isAlive = 0; // This kills the worm 8<
}

// Chill doesn't do anything to our glowworm- it merely prints an informative
// message.
void chill(glowworm *worm){
	printf("Glowworm chills:\n");
}

// Print_usage learns users some glowworm arguments real good, so they can call
// our wonderful program _correctly_ from their shell.
void print_usage(void){
	printf("Usage: ./glowworm [maximum worm length] [food string]\n");
}

// Difficultyrating ranks the overall difficulty of the given assignment, based
// on the author's subjective view.
double difficultyRating(void)
{
	// In all seriousness, though- this was an enjoyable assignment, and I had
	// fun solving it :)
	
	return 2.0;
}

// Hoursspent returns 3.0.
double hoursSpent(void)
{
	return 3.0;
}
