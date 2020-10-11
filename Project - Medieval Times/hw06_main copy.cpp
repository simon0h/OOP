//Simon Oh
//N19471254
//Homework 6
//Cyclical association and seperate compilation
//Model a game of medieval times with warriors and nobles
//I am getting a linker error and I am not sure what the cause is 

#include <iostream>
#include "hw06_Warrior.h"
#include "hw06_Noble.h"
using namespace std;

int main(){
	Noble art("King Arthur");
	Noble lance("Lancelot du Lac");
	Noble jim("Jim");
	Noble linus("Linus Torvalds");
	Noble billie("Bill Gates");
	Warrior cheetah("Tarzan", 10);
	Warrior wizard("Merlin", 15);
	Warrior theGovernator("Conan", 12);
	Warrior nimoy("Spock", 15);
	Warrior lawless("Xena", 20);
	Warrior mrGreen("Hulk", 8);
	Warrior dylan("Hercules", 3);
	jim.hire(nimoy);
	lance.hire(theGovernator);
	art.hire(wizard);
	lance.hire(dylan);
	linus.hire(lawless);
	billie.hire(mrGreen);
	art.hire(cheetah);
	cout << jim << endl;
	cout << lance << endl;
	cout << art << endl;
	cout << linus << endl;
	cout << billie << endl;
	cheetah.runaway();
	cout << art << endl;
	art.battle(lance);
	jim.battle(lance);
	linus.battle(billie);
	billie.battle(lance);
}