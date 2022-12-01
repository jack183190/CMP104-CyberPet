// By Jack Briggs - 2202960
#include <string>
#include "CyberPet.h"
#include <iostream>
#include "Main.h"

CyberPet::CyberPet(std::string passedName) {
	name = passedName;
	hunger = 4;
	tiredness = 4;
	happiness = 100;
	lastDecrement = getCurrentTime();
	boughtAt = getCurrentTime();
}

int CyberPet::getWorth() {
	return round(pow(hunger * 1.2 + tiredness, 1.8) * happiness / 250) * getAge() / 5;
}

bool CyberPet::isDead() {
	return hunger * tiredness * happiness == 0; // if any value is 0, pet is dead
}

// should attributes be decremented
void CyberPet::tick(double* money) {
	int currentTime = getCurrentTime();
	// while loop because it could have been multiple minutes since last call
	while (lastDecrement + 60 * 1000 < currentTime) {
		lastDecrement += 60 * 1000; // 1 minute
		setHungerValue(hunger > 0 ? hunger - (75 / happiness) : hunger);
		setTirednessValue(tiredness > 0 ? tiredness - 1 : tiredness);
		setHappiness(happiness * 0.9 - 1);
		if (happiness < 0) happiness = 0;

		if (!isDead()) (*money) += getWorth() / 10;
	}

	if (hunger <= 3) std::cout << "Warning! Your CyberPet " << name << " is " << getHunger() << ".\n";
	if (tiredness <= 3) std::cout << "Warning! Your CyberPet " << name << " is " << getTiredness() << ".\n";
	if (happiness <= 60) std::cout << "Warning! Your CyberPet " << name << "'s happiness is " << happiness << "%.\n";
}

std::string CyberPet::getName() {
	return name;
}

int CyberPet::getAge() {
	return (getCurrentTime() - boughtAt) / (60 * 1000); // age in minutes
}

int CyberPet::getHungerValue() {
	return hunger;
}

int CyberPet::getTirednessValue() {
	return tiredness;
}

int CyberPet::getHappiness() {
	return happiness;
}

//https://stackoverflow.com/questions/6905598/c-equivalent-to-java-this
void CyberPet::setHungerValue(int hunger) {
	this->hunger = bound(hunger, 0, 4);
}

void CyberPet::setTirednessValue(int tiredness) {
	this->tiredness = bound(tiredness, 0, 4);
}

void CyberPet::setHappiness(int happiness) {
	this->happiness = bound(happiness, 0, 100);
}

// user friendly hunger
std::string CyberPet::getHunger() {
	switch (hunger) {
	case 1:
		return "starving";
	case 2:
		return "rather hungry";
	case 3:
		return "slightly peckish";
	case 4:
		return "well fed";
	default:
		return "dead from starvation";
	}
}

// user friendly tiredness
std::string CyberPet::getTiredness() {
	switch (tiredness) {
	case 1:
		return "exhausted";
	case 2:
		return "tired";
	case 3:
		return "awake";
	case 4:
		return "wide awake";
	default:
		return "dead from sleep deprivation";
	}
}