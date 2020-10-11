//Simon Oh
//N19471254
//Homework 6
//Cyclical association and seperate compilation
//Model a game of medieval times with warriors and nobles

#include <iostream>
#include <string>
#include "hw06_Warrior.h"
#include "hw06_Noble.h"
using namespace std;

Warrior::Warrior(const string& name, double power): name(name), power(power), boss(nullptr) {

}

const string& Warrior::getName() const {
	return name;
}

void Warrior::setBoss(Noble* noble) {
	boss = noble;
}

Noble* Warrior::getBoss() const {
	return boss;
}

void Warrior::setUnemployed() {
	boss = nullptr;
}

void Warrior::runaway() {
	cout << name << " flees in terror, abandoning his lord, " << boss->getName() << endl;
	boss->removeWarrior(this);
	setUnemployed();
}

double Warrior::getPower() const {
	return power;
}

void Warrior::setPower(double ratio) {
	if (ratio == 0) {
		power = 0;
	}
	else {
		power *= (1 - ratio);
	}
}

ostream& operator<<(ostream& os, const Warrior& warrior) {
	os << warrior.name << ": " << warrior.power;
	return os;
}