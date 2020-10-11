//Simon Oh
//N19471254
//Homework 6
//Cyclical association and seperate compilation
//Model a game of medieval times with warriors and nobles

#include <iostream>
#include <string>
#include "hw06_Noble.h"
#include "hw06_Warrior.h"
using namespace std;

Noble::Noble(const string& name): name(name), living(true) {

}

const string& Noble::getName() const{
	return name;
}

double Noble::getPower() {
	double power = 0;
	for (size_t i = 0; i < warriors.size(); i++) {
		power += warriors[i]->getPower();
	}
	return power;
}

void Noble::setPower(double newPower) {
	double ratio;
	if (newPower == 0) {
		living = false;
	}
	double myPower = getPower();
	ratio = newPower / myPower;
	for (size_t i = 0; i < warriors.size(); i++) {
		warriors[i]->setPower(ratio);
	}
}

bool Noble::isAlive() const {
	return living;
}

size_t Noble::findWarrior(Warrior* warrior) const {
	for (size_t i = 0; i < warriors.size(); i++) {
		if (warriors[i] == warrior) {
			return i;
		}
	}
	return warriors.size();
}

void Noble::removeWarrior(Warrior* warrior) {
	for (size_t i = 0; i < warriors.size(); i++) {
		if (warriors[i] == warrior) {
			warriors[i] = warriors[warriors.size() - 1];
			warriors.pop_back();
			break;
		}
	}
}

void Noble::hire(Warrior& warrior) {
	if (!living) {
		cout << "You are dead and cannot hire anyone." << endl;
	}
	else if (warrior.getBoss() != nullptr) {
		cout << warrior.getName() << " has been hired already and cannot be hired." << endl;
	}
	else {
		warriors.push_back(&warrior);
		warrior.setBoss(this);
	}
}

void Noble::fire(Warrior& warrior) {
	if (!living) {
		cout << "You are dead and cannot fire anyone." << endl;
	}
	else if (findWarrior(&warrior) == warriors.size()) {
		cout << warrior.getName() << " has not been hired by you and cannot be fired." << endl;
	}
	else {
		cout << "You don't work for me anymore " << warrior.getName() << "! -- " << name << endl;
		warrior.setUnemployed();
		removeWarrior(&warrior);
	}
}

void Noble::battle(Noble& opponent) {
	double power = getPower();
	double opponentPower = opponent.getPower();
	cout << name << " battles " << opponent.getName() << endl;
	if (power == opponentPower) {
		if (!living && !opponent.isAlive()) {
			cout << "Oh, NO! They're both dead! Yuck!" << endl;
		}
		else {
			cout << "Mututal annihilation: " << name << " and " << opponent.getName() << " die at each other's hands." << endl;
			setPower(0);
			opponent.setPower(0);
			living = false;
		}
	}
	else if (power < opponentPower) {
		cout << opponent.getName() << " defeats " << name << endl;
		setPower(0);
		living = false;
		opponent.setPower(power);
	}
	else if (power > opponentPower) {
		if (!opponent.isAlive()) {
			cout << "He's dead, " << name << endl;
		}
		else {
			cout << name << " defeats " << opponent.getName() << endl;
			setPower(opponentPower);
			opponent.setPower(0);
		}
	}
}

ostream& operator<<(ostream& os, const Noble& noble) {
	os << noble.name << " has an army of " << noble.warriors.size() << endl;
	for (size_t i = 0; i < noble.warriors.size(); i++) {
		os << "        " << *noble.warriors[i];
		if (i < noble.warriors.size() - 1) {
			os << endl;
		}
	}
	return os;
}