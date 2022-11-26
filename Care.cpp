// care for cyberpets commands
#include "Main.h"
#include "Care.h"
#include "CyberPet.h"
#include <iostream>
#include <string>

void feed(int* food, CyberPet* pet) {
	if (pet == NULL) return;

	if ((*food) < 1) {
		std::cout << "You do not have enough food! You can purchase food using 'purchase'. Cancelling...\n";
		return;
	}

	int amount;
	std::string input;
	std::cout << "How much would you like to feed your CyberPet? (You have " << *food << " food) ";
	std::getline(std::cin, input);
	amount = std::stoi(input);

	if (amount < 1) {
		std::cout << "You cannot feed your CyberPet 0 food. Cancelling...\n";
		return;
	}
	amount = bound(amount, 1, 4 - pet->getHungerValue());
	
	if (amount > *food) {
		std::cout << "You do not have enough food! Cancelling...\n";
		return;
	}

	(*food) -= amount;
	pet->setHungerValue(pet->getHungerValue() + amount);
}

void nap(CyberPet* pet) {
	if (pet == NULL) return;
	pet->setTirednessValue(4);
	std::cout << pet->getName() << " takes a nap.\n" << pet->getName() << " wakes up feeling " << pet->getTiredness();
}

void play(CyberPet* pet) {
	if (pet == NULL) return;
	pet->setHappiness(pet->getHappiness() + (8 + rand() % 17));
	std::cout << "You play with " << pet->getName() << ". (Happiness: " << pet->getHappiness() << "%)\n";
}