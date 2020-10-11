//Simon Oh
//Homework 2 for OOP
//Functions, structs, vectors and file I/O
//Model a game of medieval times with warriors who fight each other

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Warrior{
	string name;
	int power;
};

void determineCommand(vector<Warrior>& warriors, ifstream& warriorOpen);
void newWarrior(vector<Warrior>& warriors, ifstream& warriorOpen);
void battle(vector<Warrior>& warriors, ifstream& warriorOpen);
void status(const vector<Warrior>& warriors);

void open(ifstream& warriorOpen) {   
    warriorOpen.open("warrior.txt");
    if (!warriorOpen) {
        cerr << "Could not open the file." << endl;
    }
}

void determineCommand(vector<Warrior>& warriors, ifstream& warriorOpen) {
	string command;
	string name;
	string opponent;
	while (warriorOpen >> command) {
		if (command == "Warrior") {
			newWarrior(warriors, warriorOpen);
		}
		else if (command == "Battle") {
			battle(warriors, warriorOpen);
		}
		else {
			status(warriors);
		}		
	}
}

void newWarrior(vector<Warrior>& warriors, ifstream& warriorOpen) {
	Warrior warrior;
	string name;
	int power;
	warriorOpen >> name >> power;
	warrior.name = name;
	warrior.power = power;
	warriors.push_back(warrior);
}

void battle(vector<Warrior>& warriors, ifstream& warriorOpen) {//Used to carry out the tasks when two warriors want to battle
	string name;
	string opponentName;
	int warPow;
	int opponentWarPow;
	int warLoc;
	int opponentLoc;
	warriorOpen >> name >> opponentName;
	warLoc = warriorIndex(warriors, name);
	warPow = warriors[warLoc].power;
	opponentLoc = warriorIndex(warriors, opponentName);
	opponentWarPow = warriors[opponentLoc].power;
	cout << name << " battles " << opponentName << endl;
	if (opponentWarPow > 0) {//Checks if the second warrior is dead or not 
		if (warPow > opponentWarPow) {//If the first warrior is stronger than second warrior
			cout << name << " defeats " << opponentName << endl;
			warPow = warPow - opponentWarPow;
			warriors[warLoc].power = warPow;
			warriors[opponentLoc].power = 0;
		}
		if (opponentWarPow > warPow) {//If the second warrior is stronger than first warrior
			cout << name << " defeats " << opponentName << endl;
			opponentWarPow = opponentWarPow - warPow;
			warriors[warLoc].power = 0;
			warriors[opponentLoc].power = opponentWarPow;
		}
		if (warPow == opponentWarPow) {//If the first warrior and the second warrior have the same power
			cout << "Mutual Annihilation: " << name << " and " << opponentName << " die at each other's hands" << endl;
			warriors[warLoc].power = 0;
			warriors[opponentLoc].power = 0;
		}
	}
	else if ((opponentWarPow == 0) && (warPow != 0)) {//If the second warrior is dead, sends a message
		cout << "He's dead, " << name << endl;
	}
	else{//If both of the warriors are dead, sends a message
		cout << "Oh, NO! They're both dead! Yuck!" << endl;
	}
}

int warriorIndex(vector<Warrior>& warriors, string name) {
	int location;
	for (size_t i = 0; i < warriors.size(); ++i) {//Finds the two warriors in vector warrior
		if (warriors[i].name == name) {
			location = i;
		}
	}
	return location;
}

void status(const vector<Warrior>& warriors) {
	cout << "There are: " << warriors.size() << " warriors" << endl;
	for (size_t i = 0; i < warriors.size(); ++i) {
		cout << "Warrior: " << warriors[i].name << ", strength " << warriors[i].power << endl;
	}
}

int main(){
	ifstream warriorOpen;
	vector<Warrior> warriors;
	open(warriorOpen);
	determineCommand(warriors, warriorOpen); 
	warriorOpen.close();
} 
