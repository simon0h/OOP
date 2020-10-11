//Simon Oh
//N19471254
//Homework 6
//Cyclical association and seperate compilation
//Model a game of medieval times with warriors and nobles

#include <iostream>
#include <string>
#include <vector>
#ifndef NOBLE_H
#define NOBLE_H

class Warrior;

class Noble {

friend std::ostream& operator<<(std::ostream& os, const Noble& noble);

public:
	Noble(const std::string& name);

	const std::string& getName() const;

	double getPower();

	void setPower(double newPower);

	bool isAlive() const;

	size_t findWarrior(Warrior* warrior) const;

	void removeWarrior(Warrior* warrior);

	void hire(Warrior& warrior);

	void fire(Warrior& warrior);

	void battle(Noble& opponent);

private:
	std::string name;
	bool living;
	std::vector<Warrior*> warriors;
};

#endif