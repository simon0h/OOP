//Simon Oh
//Homework 5 for OOP
//Dynamic memory
//Model a game of medieval times with warriors and nobles

//There is a problem with the program where it would run properly most of the times but occasionally, there would be a segmentation error because one of the Noble's warriors vector would change from its normal size to a huge number. 
//In my tesing, the size of the warriors vector within the class would change from 1 to size of 18446744073709551579 for the warriors in only Linus_Torvadls. No other classes had their warriors altered excpet for Linus_Torvalds whenever there was an error. 
//The change seems to happen somewhere in getPower() method in the Noble class, but I could not find what the issue was.

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Warrior {

friend ostream& operator<<(ostream& os, const Warrior& w);

public:

	Warrior (const string& name, double power): name(name), warriorPower(power), isHired(false) {

	}

	const string& getName() const {
		return name;
	}

	double getPower() const {
		return warriorPower;
	}

	void setPower(double newPower) {
		warriorPower = newPower * warriorPower;
	}

	bool getJob() const {
		return isHired;
	}

	void setJob(bool job) {
		isHired = job;
	}

private:
	string name;
	double warriorPower;
	bool isHired;
};

size_t findWarrior(const vector<Warrior*>& warriors, const string& name);

class Noble {

friend ostream& operator<<(ostream& os, const Noble& n);

public:

	Noble (const string& name): name(name), isAlive(true){

	}

	const string& getName() const {
		return name;
	}

	double getPower() {
		double power = 0;
		double warriorPower = 0;
		for (size_t i = 0; i < warriors.size(); i++) {
			warriorPower = warriors[i]->getPower();
			power += warriorPower;
		}
		return power;
	}

	void setPower(double newPower) {
		if (newPower == 0) {
			isAlive = false;
		}
		for (size_t i = 0; i < warriors.size(); i++) {
			warriors[i]->setPower(newPower);
		}
	}

	bool getLife() const {
		return isAlive;
	}

	void remove(Warrior* warrior) {
		for (size_t i = 0; i < warriors.size(); i++) {
			if (warriors[i] == warrior) {
				Warrior* toPop = warriors[i + 1];
				warriors[i + 1] = warrior;
				warriors[i] = toPop;
			}
		}
		warriors.pop_back();
	}

	void hire(Warrior* warrior) {
		if (warrior->getJob()) {
			cout << warrior->getName() << " has been hired already." << endl; //Error handling
		}
		else {
			warrior->setJob(true);
			warriors.push_back(warrior);
		}
	}

	void fire(Warrior* warrior) {
		string warriorName;
		warriorName = warrior->getName();
		size_t warriorLoc;
		warriorLoc = findWarrior(warriors, warriorName);
		if (warriorLoc == warriors.size()) {
			cout << "The warrior " << warriorName << " does not exist in your army." << endl; //Error handling
		}
		else {
			cout << "You don't work for me anymore " << warrior->getName() <<"! -- " << name << endl;
			warrior->setJob(false);
			remove(warrior);
		}
	}

	void battle(Noble* noble) {
		double power = getPower();
		double opponentPower = noble->getPower();
		double ratio;
		cout << name << " battles " << noble->getName() << endl;
		if (power == opponentPower) {
			if (!isAlive && !noble->getLife()) {
				cout << "Oh, NO! They're both dead! Yuck!" << endl;
			}
			else {
				cout << "Mututal annihilation: " << name << " and " << noble->getName() << " die at each other's hands." << endl;
				setPower(0);
				noble->setPower(0);
			}
		}
		else if (power > opponentPower) {
			if (!(noble->getLife())) {
				cout << "He's dead, " << name << endl;
			}
			else {
				cout << name << " defeats " << noble->getName() << endl;
				ratio = 1 - (opponentPower / power);
				setPower(ratio);
				noble->setPower(0);
			}
		}
		else if (opponentPower > power) {
			cout << noble->getName() << " defeats " << name << endl;
			ratio = 1 - (power / opponentPower);
			setPower(0);
			noble->setPower(ratio);
		}
	}

private:
	vector<Warrior*> warriors;
	string name;
	bool isAlive;
};

ostream& operator<<(ostream& os, const Warrior& w) {
	os << "        " << w.name << ": " << w.warriorPower;
	return os;
}

ostream& operator<<(ostream& os, const Noble& n) {
	os << n.name << " has an army of " << n.warriors.size() << endl;
	for (size_t i = 0; i < n.warriors.size(); i++) {
		os << *n.warriors[i] << endl;
	}
	return os;
}

size_t findNoble(const vector<Noble*>& nobles, const string& name) { //Function to find the given noble in the vector nobles
	for (size_t i = 0; i < nobles.size(); i++) {
		if (nobles[i]->getName() == name) {
			return i;
		}
	}
	return nobles.size(); //If the noble does not exist, returns the length of nobles so it can be used for error checking
}

size_t findWarrior(const vector<Warrior*>& warriors, const string& name) { //Function to find the given warrior in the vector warriors
	for (size_t i = 0; i < warriors.size(); i++) {
		if (warriors[i]->getName() == name) {
			return i;
		}
	}
	return warriors.size(); //If the warrior does not exist, returns the length of warriors so it can be used for error checking
}

void display(const vector<Noble*>& nobles, const vector<Warrior*>& warriors) { //The display method prints things like "Status" and loops through the noble vector
	bool unemployed = false;
	cout << "Status" << "\n" << "=====" << "\n" << "Nobles: " << endl;
	if (nobles.size() == 0) {
		cout << "NONE" << endl;
	}
	else {	
		for (size_t i = 0; i < nobles.size(); i++) {
			cout << *nobles[i];
		}
	}
	cout << "Unemployed Warriors: " << endl;
	for (size_t j = 0; j < warriors.size(); j++) {
		if (!warriors[j]->getJob()) {
			unemployed = true;
			cout << *warriors[j] << endl;
		}
	}
	if (!unemployed) {
		cout << "NONE" << endl;
	}
}

void determineCommand(ifstream& fileStream, vector<Noble*>& nobles, vector<Warrior*>& allWarriors) {
	string command;
	string nobleName;
	string opponentName;
	string warriorName;
	double power;
	size_t nobleLoc = 0;
	size_t opponentLoc = 0;
	size_t warriorLoc = 0;
	while (fileStream >> command) {
		if (command == "Noble") {
			fileStream >> nobleName;
			nobleLoc = findNoble(nobles, nobleName);
			if (nobleLoc < nobles.size()) { //Because nobleLoc returns nobles.size() + 1 if a noble is not found in the vector, if nobleLoc returns a value less than the size, we know the noble exist
				cout << "The noble " << nobleName << " already exists." << endl; //Error handling
			}
			else {
				Noble* noble = new Noble(nobleName);
				nobles.push_back(noble);
			}
		}
		else if (command == "Warrior") {
			fileStream >> warriorName >> power;
			warriorLoc = findWarrior(allWarriors, warriorName);
			if (warriorLoc == allWarriors.size()) { //Same explanation as like 229 but with warriors
				cout << "The warrior " << warriorName << " already exists." << endl; //Error handling
			}
			else {
				Warrior* warrior = new Warrior(warriorName, power);
				allWarriors.push_back(warrior);
			}
		}
		else if (command == "Hire" || command == "Fire") {
			fileStream >> nobleName >> warriorName;
			nobleLoc = findNoble(nobles, nobleName);
			warriorLoc = findWarrior(allWarriors, warriorName);
			if (nobleLoc == nobles.size()) {
				cout << "The noble " << nobleName << " does not exist." << endl; //Error handling
			}
			else if (warriorLoc == allWarriors.size()) {
				cout << "The warrior " << warriorName << " does not exist." << endl; //Error handling
			}
			else if (!nobles[nobleLoc]->getLife()) {
				if (command == "Fire") {
					cout << nobleName << "is dead and cannot fire anyone." << endl;
				}
				else {
					cout << nobleName << "is dead and cannot hire anyone." << endl;
				}
			}
			else {
				Noble* noble = nobles[nobleLoc];
				Warrior* warrior = allWarriors[warriorLoc];
				if (command == "Fire") {
					noble->fire(warrior);
				}
				else {
					noble->hire(warrior);
				}
			}
		}
		else if (command == "Battle") {
			fileStream >> nobleName >> opponentName;
			nobleLoc = findNoble(nobles, nobleName);
			opponentLoc = findNoble(nobles, opponentName);
			if (nobleLoc == nobles.size()) {
				cout << "The noble " << nobleName << " does not exist." << endl;
			}
			if (opponentLoc == nobles.size()) {
				cout << "The noble " << opponentName << " does not exist." << endl;
			}
			else {
				Noble* noble = nobles[nobleLoc];
				Noble* opponent = nobles[opponentLoc];
				noble->battle(opponent);
			}
		}
		else if (command == "Status") {
			display(nobles, allWarriors);
		}
		else if (command == "Clear") {
			size_t nobleSize = nobles.size();
			size_t warriorSize = allWarriors.size();
			for (size_t i = 0; i < nobleSize; i++) {
				delete nobles[i];
			}
			nobles.clear();
			for (size_t j = 0; j < warriorSize; j++) {
				delete allWarriors[j];
			}
			allWarriors.clear();
		}
	}
}

void openFile(ifstream& fileStream) {
	fileStream.open("nobleWarriors.txt");
	if (!fileStream) {
		cerr << "Could not open file." << endl;
	}
}

int main() {
	ifstream fileStream;
	vector<Noble*> nobles;
	vector<Warrior*> allWarriors;
	openFile(fileStream);
	determineCommand(fileStream, nobles, allWarriors);
	fileStream.close();
}




















