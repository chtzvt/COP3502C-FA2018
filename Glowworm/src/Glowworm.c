#include "Glowworm.h"
#include<stdio.h>
#include<strings.h>

// CAN ONLY USE printf(), strlen(), and atoi()
// NO GLOBALS

#include<stdint.h>
typedef struct {
	char isAlive;
	uint8_t bodyLength;
	uint8_t tailIndex;
	uint8_t maxLength;
} glowworm;


// You'll need to set this up to accept command line parameters.
int main(int argc, char **argv)
{
	glowworm billy = {1, 0, 0};

	eat_char(worm, argv[i])
	print_worm(&billy);

	return 0;
}


void print_worm(glowworm *worm){
	int headIndex = worm->tailIndex + worm->bodyLength;
	
	if(headIndex > worm->maxLength)
		headIndex -= worm->maxLength;
		
	for(int i = 0; i < worm->maxLength; i++) {
		
		
	}
	
	print_platform(worm->maxLength);
}

void print_platform(int len){
	for(int i = len; i != 0; i--)
		printf("=");

	printf("\n\n\n");
}

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

void chill(glowworm *worm){
	printf("Glowworm chills:\n");
}

void grow(glowworm *worm){
	if((worm->bodyLength + 1) > worm->maxLength){
		chill(worm);
		return;
	}
	
	printf("Glowworm grows:\n");
	worm->bodyLength++;
}

void shrink(glowworm *worm){
	if(worm->bodyLength == 1){
		chill(worm);
		return;
	}
	
	printf("Glowworm shrinks:\n");
	worm->bodyLength--;
}

void inch_forward(glowworm *worm){
	printf("Glowworm inches forward:");
	worm->tailIndex++;
}

void kill(glowworm *worm){
	printf("Glowworm meets its demise. SAD.");
	worm->isAlive = 0;
}

double difficultyRating(void)
{
	// Change this before submitting.
	return -1.0;
}

double hoursSpent(void)
{
	// Change this before submitting.
	return -1.0;
}
