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

#ifndef HW07_PROTECTOR_H
#define HW07_PROTECTOR_H

class Noble;

Protector::Protector(const string& name, double power): name(name), power(power), employment(false), isAlive(true), boss(nullptr) {

}

const string Protector::getName() const {
	return name;
}

double Protector::getPower() const {
	return power;
}

void Protector::setPower(double ratio) {
	if (ratio == 0) {
		isAlive = false;
		power = 0.0;
	}
	else {
		power *= ratio;
	}
}

bool Protector::getEmployment() const {
	return employment;
}

bool Protector::getLife() const {
	return isAlive;
}

Lord* Protector::getBoss() const {
	return boss;
}

void Protector::setBoss(Lord* bossPtr) {
	boss = bossPtr;
}

void Protector::quit() {
	if (boss) {
		cout << name << " has decided to quit from " << boss->getName() << "." << endl;
		boss->remove(this);
		boss = nullptr;
	}
	else {
		cout << name << " is not employed by any Nobles." << endl;
	}
}

Wizard::Wizard(const string& name, double power): Protector(name, power) {

}

void Wizard::defend() const {
	cout << "POOF" << endl;
}

Warrior::Warrior(const string& name, double power): Protector(name, power) {

}

void Warrior::defend() const {
	cout << Protector::getName() << " says: Take that in the name of my lord, " << Protector::getBoss()->getName() << endl;
}

Archer::Archer(const string& name, double power): Warrior(name, power) {

}

void Archer::defend() const {
	cout << "TWANG! ";
	Warrior::defend();
}

Swordsman::Swordsman(const string& name, double power): Warrior(name, power) {

}

void Swordsman::defend() const {
	cout << "CLANG! ";
	Warrior::defend();
}

#endif