// By Jack Briggs - 2202960
#include <string>
#pragma once

class CyberPet {
private:
	std::string name;
	int hunger;
	int tiredness;
	int happiness;
	int lastDecrement;
	int boughtAt;
public:
	CyberPet(std::string);

	std::string getName();
	int getHappiness();
	int getHungerValue();
	int getTirednessValue();

	void setHappiness(int);
	void setHungerValue(int);
	void setTirednessValue(int);

	std::string getTiredness();
	std::string getHunger();

	int getWorth();
	bool isDead();
	void tick(double*);
	int getAge();
};