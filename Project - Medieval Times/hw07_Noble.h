//Simon Oh
//N19471254
//Homework 7
//Model nobles and protectors with inheritance

#include <string>
#include <iostream>
#include <vector>

class Protector;

class Noble {
public:
	Noble(const std::string& name);

	const std::string getName() const;

	bool getLife() const;

	void setLife(bool life);

	virtual double getPower() const;

	virtual void setPower(double ratio);

	virtual void defend() const = 0;

	void battle(Noble& opponent);

private:
	std::string name;
	bool isAlive;
};

class Lord: public Noble {
public:
	Lord(const std::string& name);

	double getPower() const;

	void setPower(double ratio);

	void defend() const;

	void hires(Protector& protector);

	void fires(Protector& protector);

	void remove(Protector* protector);

private:
	std::vector<Protector*> protectors;
};

class PersonWithStrengthToFight: public Noble {
public:
	PersonWithStrengthToFight(const std::string& name, double power);

	double getPower() const;

	void setPower(double ratio);

	void defend() const;

private:
	double power;
};