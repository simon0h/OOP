//Simon Oh
//N19471254
//Homework 7
//Model nobles and protectors with inheritance

#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Lord;
class Noble;

class Protector {
public:
	Protector(const string& name, double power): name(name), power(power), employment(false), isAlive(true), boss(nullptr) {

	}

	const string getName() const {
		return name;
	}

	double getPower() const {
		return power;
	}

	void setPower(double ratio) {
		if (ratio == 0) {
			isAlive = false;
			power = 0.0;
		}
		else {
			power *= ratio;
		}
	}

	bool getEmployment() const {
		return employment;
	}

	bool getLife() const {
		return isAlive;
	}

	Lord* getBoss() const {
		return boss;
	}

	void setBoss(Lord* bossPtr) {
		boss = bossPtr;
	}

	void quit();

	virtual void defend() const = 0;

private:
	string name;
	double power;
	bool employment;
	bool isAlive;
	Lord* boss;
};

class Wizard: public Protector {
public:
	Wizard(const string& name, double power): Protector(name, power) {

	}

	void defend() const {
		cout << "POOF" << endl;
	}

};

class Warrior: public Protector {
public:
	Warrior(const string& name, double power): Protector(name, power) {

	}

	void defend() const;
};

class Archer: public Warrior {
public:
	Archer(const string& name, double power): Warrior(name, power) {

	}

	void defend() const {
		cout << "TWANG! ";
		Warrior::defend();
	}
};

class Swordsman: public Warrior {
public:
	Swordsman(const string& name, double power): Warrior(name, power) {

	}

	void defend() const {
		cout << "CLANG! ";
		Warrior::defend();
	}
};

class Noble {
public:
	Noble(const string& name): name(name), isAlive(true) {

	}

	const string getName() const {
		return name;
	}

	bool getLife() const {
		return isAlive;
	}

	void setLife(bool life) {
		isAlive = life;
	}

	virtual double getPower() const {

	}

	virtual void setPower(double ratio) {

	}

	virtual void defend() const = 0;

	void battle(Noble& opponent) {
		double myPower = getPower();
		double opponentPower = opponent.getPower();
		string opponentName = opponent.getName();
		cout << name << " battles " << opponentName << endl;
		//cout << name << "'s power: " << myPower << ", " << opponentName << "'s power: " << opponentPower << endl;
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

private:
	string name;
	bool isAlive;
};

class Lord: public Noble {
public:
	Lord(const string& name): Noble(name) {

	}

	double getPower() const {
		double power = 0;
		for (size_t i = 0; i < protectors.size(); i++) {
			power += protectors[i]->getPower();
		}
		return power;
	}

	void setPower(double ratio) {
		if (ratio == 0) {
			Noble::setLife(false);
		}
		for (size_t i = 0; i < protectors.size(); i++) {
			protectors[i]->setPower(ratio);
		}
	}

	void defend() const {
		if (Noble::getLife()) {
			for (size_t i = 0; i < protectors.size(); i ++) {
				protectors[i]->defend();
			}
		}
	}

	void hires(Protector& protector) {
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

	void fires(Protector& protector) {
		for (size_t i = 0; i < protectors.size(); i ++) {
			if (protectors[i] == &protector) {
				cout << "You're fired, " << protector.getName() << "-- " << Noble::getName() << endl;
				remove(&protector);
				return;
			}
		}
		cout << Noble::getName() << " has not hired " << protector.getName() << "." << endl;
	}

	void remove(Protector* protector) {
		for (size_t i = 0; i < protectors.size(); i ++) {
			if (protectors[i] == protector) {
				protectors[i] = protectors[protectors.size() - 1];
				protectors.pop_back();
			}
		}
	}

private:
	vector<Protector*> protectors;
};

class PersonWithStrengthToFight: public Noble {
public:
	PersonWithStrengthToFight(const string& name, double power): Noble(name), power(power) {

	}

	double getPower() const {
		return power;
	}

	void setPower(double ratio) {
		if (ratio == 0) {
			Noble::setLife(false);
			power = 0.0;
		}
		else {
			power *= ratio;
		}
	}

	void defend() const {
        cout << "UGH!" << endl;
	}

private:
	double power;
};

void Warrior::defend() const {
	cout << Protector::getName() << " says: Take that in the name of my lord, " << Protector::getBoss()->getName() << endl;
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

int main() {
	Lord sam("Sam");
	Archer samantha("Samantha", 200);
	sam.hires(samantha);
	Lord joe("Joe");
	PersonWithStrengthToFight randy("Randolf the Elder", 250);
	joe.battle(randy);
	joe.battle(sam);
	Lord janet("Janet");
	Swordsman hardy("TuckTuckTheHardy", 100);
	Swordsman stout("TuckTuckTheStout", 80);
	janet.hires(hardy);
	janet.hires(stout);
	PersonWithStrengthToFight barclay("Barclay the Bold", 300);
	janet.battle(barclay);
	janet.hires(samantha);
	Archer pethora("Pethora", 50);
	Archer thora("Thorapleth", 60);
	Wizard merlin("Merlin", 150);
	janet.hires(pethora);
	janet.hires(thora);
	sam.hires(merlin);
	janet.battle(barclay);
	sam.battle(barclay);
	joe.battle(barclay);	
	merlin.quit();
}

// Joe battles Randolf the Elder
// Randolf the Elder defeats Joe
// Joe battles Sam
// He's dead, Sam
//????
// Janet battles Barclay the Bold
// CLANG!  TuckTuckTheHardy says: Take that in the name of my
// lord, Janet
// CLANG!  TuckTuckTheStout says: Take that in the name of my
// lord, Janet
// Barclay the Bold defeats Janet
// Janet battles Barclay the Bold
// He's dead, Barclay the Bold
// Sam battles Barclay the Bold
// TWANG!  Samantha says: Take that in the name of my lord, Sam
// POOF!
// Sam defeats Barclay the Bold
// Joe battles Barclay the Bold
// Oh, NO!  They're both dead!  Yuck!









