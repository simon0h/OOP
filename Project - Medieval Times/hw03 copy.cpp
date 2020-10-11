//Simon Oh
//Homework 3 for OOP
//OOP - Data hiding, encapsulation, delegation and operator overloading
//Model a game of medieval times with warriors who fight each other using classes

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Warrior {

friend ostream& operator<<(ostream& os, const Warrior& w);

public:

	Warrior(const string& name, const string& weaponName, int weaponPower): warriorName(name), weapon(weaponName, weaponPower) {

	}

	string getName() const {
		return warriorName;
	}

	int getPower() const{
		return weapon.getPower();
	}

	void setPower(int newPower) {
		weapon.setPower(newPower);
	}

private:
	string warriorName;
	
	class Weapon {

	friend ostream& operator<<(ostream& os, const Warrior::Weapon& w);		

	public:

		Weapon(const string& weaponName, int weaponPower): weaponName(weaponName), weaponPower(weaponPower) {

		}

		int getPower() const {
			return weaponPower;
		}

		void setPower(int newPower) {
			weaponPower = newPower;
		}	

	private:
		string weaponName;
		int weaponPower;
	};

	Weapon weapon;
	friend ostream& operator<<(ostream& os, const Warrior::Weapon& w); //I had to declare the method twice because it would not work otherwise
};

ostream& operator<<(ostream& os, const Warrior& w) { //Overloading the output operator for Warrior class
    os << "Warrior: " << w.warriorName << w.weapon;
    return os;
}

ostream& operator<<(ostream& os, const Warrior::Weapon& we) { //Overloading the output operator for Weapon class
	os << ", weapon: " << we.weaponName << ", " << we.weaponPower;
	return os;
}

void openFile(ifstream& warriorStream);
void determineCommand(ifstream& warriorStream, vector<Warrior> warriors);
void battle(vector<Warrior>& warriors, const string& warriorName, const string& opponentName);
size_t findWarrior(vector<Warrior>& warriors, const string& name);
void display(vector<Warrior>& warriors);

void openFile(ifstream& warriorStream) {
	warriorStream.open("warrior2.txt");
	if (!warriorStream) {
		cerr << "Could not open the file." << endl;;
	}
}

void determineCommand(ifstream& warriorStream, vector<Warrior> warriors) { //Takes the stream and the vector then determines what to do with each line of a file
	string command;
	string warriorName;
	string opponentName;
	string weaponName;
	int weaponPower;

	while (warriorStream >> command) {
		if (command == "Warrior") {
			warriorStream >> warriorName >> weaponName >> weaponPower;
			Warrior warrior(warriorName, weaponName, weaponPower);
			warriors.push_back(warrior);
		}
		else if (command == "Battle") {
			warriorStream >> warriorName >> opponentName;
			battle(warriors, warriorName, opponentName);
		}
		else if (command == "Status") {
			display(warriors);
		}
	}
}

void battle(vector<Warrior>& warriors, const string& warriorName, const string& opponentName) {
	size_t warriorLoc;
	size_t opponentLoc;
	int warriorPower;
	int opponentPower;

	warriorLoc = findWarrior(warriors, warriorName); //Finds the location of the warrior and stores it in a variable
	opponentLoc = findWarrior(warriors, opponentName);
	warriorPower = warriors[warriorLoc].getPower(); //Gets the power of a warrior and stores it in a variable
	opponentPower = warriors[opponentLoc].getPower();
	cout << warriorName << " battles " << opponentName << endl;
	if (warriorPower > opponentPower) { //If the warrior has more power than the challenger
		if (opponentPower > 0) {
			cout << warriorName << " defeats " << opponentName << endl;
			warriors[warriorLoc].setPower(warriorPower - opponentPower);
			warriors[opponentLoc].setPower(0);
		}
		else { //If the opponent is dead
			cout << "He's dead, " << warriorName << endl;
		}
	}
	else if (warriorPower < opponentPower) { //If the challenger has more power than the warrior
		cout << opponentName << " defeats " << warriorPower << endl;
		warriors[warriorLoc].setPower(0);
		warriors[opponentLoc].setPower(warriorPower - opponentPower);
	}
	else if (warriorPower == opponentPower) { //If the warrior and the challlenger have the same power
		if (warriorPower > 0) {
			cout << "Mututal Annihilation: " << warriorName << " and " << opponentName << " die at each other's hands" << endl;
			warriors[warriorLoc].setPower(0);
			warriors[opponentLoc].setPower(0);
		}
		else {
			cout << "Oh, NO! They're both dead! Yuck!" << endl;
		}
	}
}

size_t findWarrior(vector<Warrior>& warriors, const string& name) { //Finds the warrior in the warriors vector by name and returns the index
	size_t location = 0;			
	for (size_t i = 0; i < warriors.size(); i++) {
		if (warriors[i].getName() == name) {
			location = i;
		}
	}
	return location;
}

void display(vector<Warrior>& warriors) {
	cout << "There are: " << warriors.size() << " warriors" << endl;
	for (size_t i = 0; i < warriors.size(); i++) {
		cout << warriors[i] << endl;
	}
}

int main() {
	ifstream warriorStream;
	vector<Warrior> warriors;

	openFile(warriorStream);
	determineCommand(warriorStream, warriors);
	warriorStream.close();
}










