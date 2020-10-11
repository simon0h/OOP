//Simon Oh
//Homework 4 for OOP
//OOP - Classes and association
//Model a game of medieval times with warriors and nobles

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Warrior {

public:

	Warrior(const string& name, double warriorPower): warriorName(name), warriorPower(warriorPower), isEmployeed(false) {

	}

	const string& getName() const {
		return warriorName;
	}

	double getPower() const {
		return warriorPower;
	}

	void setPower(double ratio) {
		warriorPower = warriorPower * ratio;
	}

	bool getJobStatus() const {
		return isEmployeed;
	}

	void setJobStatus(bool status) {
		isEmployeed = status;
	}

private:
	string warriorName;
	double warriorPower; //The warriorPower is a double because the ratio between the power of the warrior and the opponent could be a decimal
	bool isEmployeed;
};

class Noble {

public:
	Noble(const string& name): name(name), isAlive(true) {

	}

	const string& getName() const {
		return name;
	}

	double getPower() const {
		double power;
		for (size_t i = 0; i < warriors.size(); i++) {
			power += warriors[i]->getPower();
		}
		return power;
	}

	void setPower(double ratio) {
		if (ratio == 0) { //If this warrior is dead
			isAlive = false;
			setWarriors(ratio, false);
		}
		else {
			setWarriors(ratio, true);
		}
	}

	void setWarriors(double ratio, bool isDead) {
		for (size_t i = 0; i < warriors.size(); i++) {
			warriors[i]->setPower(ratio);
		}
	}

	bool getLifeStatus() const {
		return isAlive;
	}

	bool partOfMyArmy(Warrior& employee) const {
		for (size_t i = 0; i < warriors.size(); i++) {
			if (&employee == warriors[i]) {
				return true;
			}
		}
		return false;
	}

	void remove(Warrior& employee) { //A method called by fire method to remove the fired warrior from the vector
		employee.setJobStatus(false);
		for (size_t i = 0; i < warriors.size(); i++) { //When the warrior is found, pushed him until the end and pops him
			if (warriors[i] == &employee) {
				//toSwap = warriors[i + 1];
				warriors[i] = warriors[i + 1];
				//warriors[i + 1] = &employee; //FIX THE LOOP 
			}
		}
		warriors.pop_back();
	}

	void hire(Warrior& employee) {
		if (isAlive) {
			if (!employee.getJobStatus()) {				
				warriors.push_back(&employee);
				employee.setJobStatus(true);
			}
			else {
				cout << "This warrior has been hired already and cannot be hired." << endl;
			}
		}
		else { //If the noble is dead
			cout << "You are dead and cannot hire anyone" << endl;
		}
	}

	void fire(Warrior& employee) {
		if (isAlive) {
			if (partOfMyArmy(employee)) {
				cout << employee.getName() << ", you're fired! -- " << name << endl;
				remove(employee);
			}
			else {
				cout << "This warrior has been hired and cannot be fired." << endl;
			}
		}
		else { //If the noble is dead
			cout << "You are dead and cannot fire anyone" << endl;
		}
	}

	void battle(Noble& opponent) {
		double power = getPower();
		string opponentName = opponent.getName();
		double opponentPower = opponent.getPower();
		double ratio;

		cout << name << " battles " << opponentName << endl;
		if (power == opponentPower) {
			if (power == 0) {
				cout << "Oh, NO! They're both dead! Yuck!"<< endl;
			}
			else {
				cout << "Mutual Annihilalation: " << name << " and " << opponentName << " die at each other's hands." << endl;
				setPower(0);
				opponent.setPower(0);
			}
		}
		else if (!opponent.getLifeStatus()) {
			cout << "He's dead, " << name << endl;;
		}
		else if (power > opponentPower) {
			cout << name << " defeats " << opponentName << endl;
			ratio = 1 - (opponentPower / power);
			setPower(ratio);
			opponent.setPower(0);
		}
		else if (power < opponentPower) {
			cout << opponentName << " defeats " << name << endl;
			cout << ratio << endl;
			setPower(0);
			opponent.setPower(ratio);
		}
	}

	void display() const {
		cout << getName() << " has an army of " << warriors.size() << endl;
		for (size_t i = 0; i < warriors.size(); i++) {
			cout << "        " << warriors[i]->getName() << ": " << warriors[i]->getPower() << endl;
		}
	}

private:
	string name;
	bool isAlive;
	vector<Warrior*> warriors;
};


int main() {
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
	jim.display();
	lance.display();
	art.display();
	linus.display();
	billie.display();
	art.fire(cheetah);
	art.display();
	art.battle(lance);
	jim.battle(lance);
	linus.battle(billie);
	billie.battle(lance);

	jim.display();
	lance.display();
	art.display();
	linus.display();
	billie.display();
}







