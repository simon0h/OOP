//Simon Oh
//N19471254
//Homework 7
//Model nobles and protectors with inheritance

#include <string>
#include <iostream>
#include <vector>

class Lord;
class Noble;

class Protector {
public:
	Protector(const std::string& name, double power);

	const std::string getName() const;

	double getPower() const;

	void setPower(double ratio);

	bool getEmployment() const;

	bool getLife() const;

	Lord* getBoss() const;

	void setBoss(Lord* bossPtr);

	void quit();

	virtual void defend() const = 0;

private:
	std::string name;
	double power;
	bool employment;
	bool isAlive;
	Lord* boss;
};

class Wizard: public Protector {
public:
	Wizard(const std::string& name, double power);

	void defend() const;

};

class Warrior: public Protector {
public:
	Warrior(const std::string& name, double power);

	void defend() const;
};

class Archer: public Warrior {
public:
	Archer(const std::string& name, double power);

	void defend() const;
};

class Swordsman: public Warrior {
public:
	Swordsman(const std::string& name, double power);

	void defend() const;
};