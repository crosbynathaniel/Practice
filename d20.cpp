/* 
 * D20.cpp
 * A pseudo-random d20 algorithm testbed for my game
 */

//for roll()
#include <cstdio>
#include <cstdlib>
#include <ctime>

#define DIE_SIDES 20
 
int roll() {
	int rolls[3];
	
	//init randomizer	
	srand(time(NULL));

	//generate 3 random d20 numbers
	for (int i = 0; i < 3; i++) { 
		rolls[0] = rand() % DIE_SIDES + 1;
		rolls[1] = rand() % DIE_SIDES + 1;
		rolls[2] = rand() % DIE_SIDES + 1;
	}
	
	printf("The rolls are: %d, %d, and %d.\n", rolls[0], rolls[1], rolls[2]);
	int average = ((rolls[0]+rolls[1]+rolls[2])/3);
	printf("The average of the rolls is: %d \n", average);

	return average;

}


int main() { 
	roll();
	return 0;
}
