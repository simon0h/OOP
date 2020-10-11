//Simon Oh
//N19471254
//Homework 7
//Model nobles and protectors with inheritance

#include <string>
#include <iostream>
#include <vector>
#include "hw07_Protector.h"
#include "hw07_Noble.h"
using namespace std;

#ifndef HW07_NOBLE_H
#define HW07_NOBLE_H

class Protector;

Noble::Noble(const string& name): name(name), isAlive(true) {

}

const string Noble::getName() const {
	return name;
}

bool Noble::getLife() const {
	return isAlive;
}

void Noble::setLife(bool life) {
	isAlive = life;
}

double Noble::getPower() const { //Virtual method setPower is not defined here because even though Lord and Person with Strength to Fight both need getPower, they are implemented differently

}

void Noble::setPower(double ratio) { //Pure virtual method setPower is not defined here because even though Lord and Person with Strength to Fight both need setPower, they are implemented differently

}

void Noble::battle(Noble& opponent) {
	double myPower = getPower();
	double opponentPower = opponent.getPower();
	string opponentName = opponent.getName();
	cout << name << " battles " << opponentName << endl;
	if (!opponent.getLife() && isAlive) {
		cout << "He's dead, " << name << endl;
	}
	else if(!opponent.getLife() && !isAlive) {
		cout << "Oh, NO! They're both dead! Yuck!" << endl;
	}
	else {
		if (myPower > opponentPower) {
			opponent.defend();
			cout << name << " defeats " << opponentName << endl;
			setPower( 1 - (opponentPower/myPower));
			opponent.setPower(0);
		}
		else if (myPower < opponentPower) {
			defend();
			cout << opponentName << " defeats " << name << endl;
			setPower(0);
			opponent.setPower(1 - (myPower/opponentPower));
		}
		else {
			defend();
			opponent.defend();
			cout << "Mututal annihilation: " << name << " and " << opponentName << " die at each other's hands." << endl;
		}
	}
}


Lord::Lord(const string& name): Noble(name) {

}

double Lord::getPower() const {
	double power = 0;
	for (size_t i = 0; i < protectors.size(); i++) {
		power += protectors[i]->getPower();
	}
	return power;
}

void Lord::setPower(double ratio) {
	if (ratio == 0) {
		Noble::setLife(false);
	}
	for (size_t i = 0; i < protectors.size(); i++) {
		protectors[i]->setPower(ratio);
	}
}

void Lord::defend() const {
	if (Noble::getLife()) {
		for (size_t i = 0; i < protectors.size(); i ++) {
			protectors[i]->defend();
		}
	}
}

void Lord::hires(Protector& protector) {
	if (!Noble::getLife()) {
		cout << Noble::getName() << " is dead and cannot hire " << protector.getName() << "." << endl;
	}
	else if (protector.getEmployment()) {
		cout << protector.getName() << " has been hired already and cannot be hired." << endl;
	}
	else if (!protector.getLife()) {
		cout << protector.getName() << " is dead and cannot be hired." << endl;
	}
	else {
		protectors.push_back(&protector);
		protector.setBoss(this);
	}
}

void Lord::fires(Protector& protector) {
	for (size_t i = 0; i < protectors.size(); i ++) {
		if (protectors[i] == &protector) {
			cout << "You're fired, " << protector.getName() << "-- " << Noble::getName() << endl;
			remove(&protector);
			return;
		}
	}
	cout << Noble::getName() << " has not hired " << protector.getName() << "." << endl;
}

void Lord::remove(Protector* protector) {
	for (size_t i = 0; i < protectors.size(); i ++) {
		if (protectors[i] == protector) {
			protectors[i] = protectors[protectors.size() - 1];
			protectors.pop_back();
		}
	}
}

PersonWithStrengthToFight::PersonWithStrengthToFight(const string& name, double power): Noble(name), power(power) {

}

double PersonWithStrengthToFight::getPower() const {
	return power;
}

void PersonWithStrengthToFight::setPower(double ratio) {
	if (ratio == 0) {
		Noble::setLife(false);
		power = 0.0;
	}
	else {
		power *= ratio;
	}
}

void PersonWithStrengthToFight::defend() const {
    cout << "UGH!" << endl;
}

#endif