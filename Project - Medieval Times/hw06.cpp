//Simon Oh
//N19471254
//Homework 6
//Cyclical association and seperate compilation
//Model a game of medieval times with warriors and nobles

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Noble;

class Warrior {

friend ostream& operator<<(ostream& os, const Warrior& warrior);

public:
	Warrior(const string& name, double power);

	const string& getName() const;

	void setBoss(Noble* noble);

	Noble* getBoss() const;

	void setUnemployed();

	void runaway();

	double getPower() const;

	void setPower(double ratio);

private:
	string name;
	double power;
	Noble* boss;
};

class Noble {

friend ostream& operator<<(ostream& os, const Noble& noble);

public:
	Noble(const string& name);

	const string& getName() const;

	double getPower();

	void setPower(double newPower);

	bool isAlive() const;

	size_t findWarrior(Warrior* warrior) const;

	void removeWarrior(Warrior* warrior);

	void hire(Warrior& warrior);

	void fire(Warrior& warrior);

	void battle(Noble& opponent);

private:
	string name;
	bool living;
	vector<Warrior*> warriors;
};

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

ostream& operator<<(ostream& os, const Warrior& warrior) {
	os << warrior.name << ": " << warrior.power;
	return os;
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

int main(){
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
	cout << jim << endl;
	cout << lance << endl;
	cout << art << endl;
	cout << linus << endl;
	cout << billie << endl;
	cheetah.runaway();
	cout << art << endl;
	art.battle(lance);
	jim.battle(lance);
	linus.battle(billie);
	billie.battle(lance);
}











