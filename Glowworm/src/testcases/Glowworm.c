#include "Glowworm.h"
#include<stdio.h>
#include<stdlib.h>
#include<strings.h>

#include<stdint.h>
typedef struct {
	char isAlive;
	uint8_t bodyLength;
	uint8_t tailIndex;
	uint8_t maxLength;
} glowworm;

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

// You'll need to set this up to accept command line parameters.
int main(int argc, char **argv)
{
	glowworm billy = {.isAlive = 1, .bodyLength = 1, .tailIndex = 1, .maxLength = 0};
	
	if(argc < 2){
		print_usage();
		return 1;
	}
	
	billy.maxLength = atoi(argv[1]);
	appear(&billy, argv[2]);
	
	for(int i = 0; i < strlen(argv[2]); i++){
		eat_char(&billy, &argv[2][i]);
		print_worm(&billy);
		print_platform(billy.maxLength);
		
		if(billy.isAlive == 0)
			break; // Sad!
	}
	
	return 0;
}

void appear(glowworm *worm, char *food){
	printf("%s\n\nGlowworm appears! Hooray!\n", food);
	print_worm(worm);
	print_platform((*worm).maxLength);
}

void print_worm(glowworm *worm){
	int headIndex = worm->tailIndex + worm->bodyLength + 1;
	
	if(headIndex > worm->maxLength)
		headIndex -= worm->maxLength;

	for(int i = 1; i < worm->maxLength + 1; i++) {
		if(i == headIndex){
			printf(worm->isAlive == 1 ? "G" : "x");
			continue;
		}
		
		if(i == worm->tailIndex){
			printf("~");
			continue;
		}
		
		if(headIndex > worm->tailIndex){
			if(i > worm->tailIndex && i < headIndex){
				if(i == headIndex - 1){
					printf(worm->isAlive == 1 ? "O" : "X");
				} else {
					printf("o");
				}
			} else {
				if(i < headIndex && i < worm->tailIndex)
					printf(" ");
			}
		}
		
		if(headIndex < worm->tailIndex){
			if(i > worm->tailIndex || i < headIndex){
				if(i == headIndex - 1 || (i+1) - worm->maxLength == headIndex){
					printf(worm->isAlive == 1 ? "O" : "X");
				} else {
					printf("o");
				}
			} else {
				printf(" ");
			}
		}
		
	}
	printf("\n");
}

void print_platform(int len){
	for(int i = len; i != 0; i--)
		printf("=");

	printf("\n\n");
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

void grow(glowworm *worm){
	if((worm->bodyLength + 3) > worm->maxLength){
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
	printf("Glowworm inches forward:\n");
	
	if(worm->tailIndex + 1 > worm->maxLength)
		worm->tailIndex = 1;
	else
		worm->tailIndex++;
}

void kill(glowworm *worm){
	printf("Glowworm meets its demise. SAD.\n");
	worm->isAlive = 0;
}

void chill(glowworm *worm){
	printf("Glowworm chills:\n");
}

void print_usage(void){
	printf("Usage: ./glowworm [maximum worm length] [food string]\n");
}

double difficultyRating(void)
{
	// Change this before submitting.
	return 1.0;
}

double hoursSpent(void)
{
	// Change this before submitting.
	return 2.0;
}
