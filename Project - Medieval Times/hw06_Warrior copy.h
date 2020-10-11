//Simon Oh
//N19471254
//Homework 6
//Cyclical association and seperate compilation
//Model a game of medieval times with warriors and nobles

#include <iostream>
#include <string>
#ifndef WARRIOR_H
#define WARRIOR_H

class Noble;

class Warrior {

friend std::ostream& operator<<(std::ostream& os, const Warrior& warrior);

public:
	Warrior(const std::string& name, double power);

	const std::string& getName() const;

	void setBoss(Noble* noble);

	Noble* getBoss() const;

	void setUnemployed();

	void runaway();

	double getPower() const;

	void setPower(double ratio);

private:
	std::string name;
	double power;
	Noble* boss;
};

#endif