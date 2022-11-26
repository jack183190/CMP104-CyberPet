// By Jack Briggs - 2202960
#include <string>
#include <iostream>
#include <chrono>
#include <vector>
#include "CyberPet.h"
#include "Main.h"
#include "Purchase.h"
#include "Sell.h"
#include "Care.h"

//https://stackoverflow.com/questions/19555121/how-to-get-current-timestamp-in-milliseconds-since-1970-just-the-way-java-gets
// time since epoch in millis
int getCurrentTime() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

// forces x to be between min and max, inclusive
int bound(int x, int min, int max) {
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

int main() {
	// game variables
	bool hasBoughtPet = false;
	double money = 50.0;
	int food = 0;
	std::vector<CyberPet*> pets;
	int tutorialStep = 0;

	// game loop
	std::string command;
	do {
		// tutorial
		switch (tutorialStep) {
		case 0:
			if (hasBoughtPet) {
				tutorialStep++;
				continue;
			}
			std::cout << "Welcome to CyberPet! In this game, you must purchase and take care of up to 3 CyberPets while managing your finances.\nCyberPets cost money to purchase and feed.\nCyberPets produce money every minute.\nCyberPets that are older than 10 minutes can be sold for money.\nYou will lose the game if you have no CyberPets.\n\n";
			help();
			std::cout << "\nTUTORIAL: Purchase a CyberPet!\n";
			break;
		case 1:
			if (food > 0) {
				tutorialStep++;
				continue;
			}
			std::cout << "\nTUTORIAL: Purchase 1 pet food.\n";
			break;
		case 2:
			if (money >= 100) {
				tutorialStep++;
				std::cout << "Tutorial complete!\n";
				break;
			}
			std::cout << "\nTUTORIAL: Earn $100. $" << money << " / 100\n";
			break;
		}

		// commands
		std::cout << "\nEnter a command: ";
		std::getline(std::cin, command);
		if (command == "purchase") purchase(&money, &food, &pets);
		else if (command == "sell") sell(&money, choosePet(&pets), &pets);
		else if (command == "feed") feed(&food, choosePet(&pets));
		else if (command == "nap") nap(choosePet(&pets));
		else if (command == "play") play(choosePet(&pets));
		else if (command == "help") help();
		else if (command == "info") info(&money, &food, &pets);
		else std::cout << "Invalid command. Use 'help' for help.\n";

		// every pet will calculate the amount their attributes (hunger, tiredness, happiness) should have gone down
		// since tick was last called
		for (CyberPet* pet : pets) {
			pet->tick(&money);
			hasBoughtPet = true; // they have a pet so must have bought one
		}

		// game over?
		if (pets.size() == 0 && hasBoughtPet) {
			std::cout << "Your last CyberPet has perished, game over!\n";
			break;
		}

	} while (command != "exit");
	return 0;
}

// info command
void info(double* money, int* food, std::vector<CyberPet*>* pets) {
	std::cout << "Money: $" << *money << " : Food: " << *food << " : CyberPets: " << (*pets).size() << " / 3\n";
	for (CyberPet* pet : *pets) {
		std::cout << pet->getName() + " : " << pet->getHunger() << " : " << pet->getTiredness() << " : Happiness: " << pet->getHappiness() << " : Age: " << pet->getAge() << "m : Worth: $" << pet->getWorth() << "\n";
	}
	std::cout << "\n";
}

// commands list
void help() {
	std::cout << "'exit' to exit.\n";
	std::cout << "'help' to display this message again.\n";
	std::cout << "'purchase' to purchase a CyberPet or food.\n";
	std::cout << "'sell' to sell a CyberPet\n";
	std::cout << "'feed' to feed a CyberPet\n";
	std::cout << "'play' to play with a CyberPet\n";
	std::cout << "'nap' to make a CyberPet take a nap.\n";
	std::cout << "'info' for information on your CyberPets.\n";
}

// prompt the user to pick a pet
CyberPet* choosePet(std::vector<CyberPet*>* pets) {
	std::cout << "Select a CyberPet: \n";
	for (int i = 0; i < (*pets).size(); i++) {
		std::cout << (*pets).at(i)->getName();
		if (i + 1 < (*pets).size()) std::cout << ", ";
		std::cout << "\n";
	}

	std::string name;
	std::getline(std::cin, name);

	for (int i = 0; i < (*pets).size(); i++) {
		CyberPet* pet = (*pets).at(i);
		if (pet->getName() == name) return pet;
	}
	std::cout << "You do not have a CyberPet named " << name << ", cancelling...";
	return NULL;
}
