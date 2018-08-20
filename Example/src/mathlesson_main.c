/*
  Grok Example Project
*/

#include <stdio.h>

int main(){
  char name[10];
  int number1, number2;

  printf("What is your name? ");
  scanf(" %s", name);

  printf("\nHi %s! Could you give me two integers to add together?\n", name);

  printf("Number 1: ");
  scanf(" %d", &number1);

  printf("Number 2: ");
  scanf(" %d", &number2);

  printf("\nThe sum of %d and %d is %d. Neat!\n\n", number1, number2, (number1 + number2));

  printf("Bye for now, %s\n", name);

  return 0;
}
