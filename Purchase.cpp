#include "Purchase.h";
#include <iostream>
#include <string>
#include "Main.h";

void purchase(double* money, int* food, std::vector<CyberPet*>* pets) {
	std::cout << "\nWhat would you like to purchase? Options:\n'pet'\n'food'\n'cancel'\n";
	std::string what;
	std::getline(std::cin, what);

	if (what == "pet") purchasePet(money, pets);
	else if (what == "food") purchaseFood(money, food, pets);
	else if (what != "cancel") std::cout << "Invalid option, cancelling.\n";
	else std::cout << "Cancelling.\n";
}

void purchasePet(double* money, std::vector<CyberPet*>* pets) {
	std::cout << "\nPurchasing a pet costs $10.\nYou cannot sell a pet until it is 10 minutes old.\nYou cannot have more than 3 CyberPets.\nYou have $" << *money << ".\nYou have " << (*pets).size() << " CyberPets.\n";
	// can user purchase a pet
	if (*money < 10) {
		std::cout << "You do not have enough money, cancelling...\n";
		return;
	}

	if ((*pets).size() >= 3) {
		std::cout << "You cannot have more than 3 CyberPets, cancelling...\n";
		return;
	}

	// get name
	std::string name;
	std::cout << "What would you like to name your CyberPet? \nEnter 'cancel' to cancel. ";
	std::getline(std::cin, name);
	if (name == "cancel") {
		std::cout << "Cancelling...\n";
		return;
	}

	// does user already have a pet with this name
	for (int i = 0; i < (*pets).size(); i++) {
		if ((*pets).at(i)->getName() != name) continue;
		std::cout << "You already have a pet named " << name << ", cancelling...";
		return;
	}

	// purchase
	(*money) -= 10;
	CyberPet* pet = new CyberPet(name);
	(*pets).push_back(pet);
	std::cout << "\nYou have purchased a pet named '" << name << "' for $10.\n";
}

void purchaseFood(double* money, int* food, std::vector<CyberPet*>* pets) {
	std::cout << "\nFood prices fluctuate often.\n";
	// calculate price increase based on avg hunger of pets
	double price = 0.05;
	double averageHunger = 0;
	for (CyberPet* pet : (*pets)) {
		averageHunger += pet->getHungerValue() / 2;
	}
	if (averageHunger < 20) price += 0.025;
	else if (averageHunger < 40) price += 0.01;

	// get amount to buy
	std::cout << "You have $" << *money << ".\nPlease enter the amount of food you wish to buy. ($" << price << "/ea)\n";
	int amount;
	std::string input;
	std::getline(std::cin, input);
	amount = std::stoi(input);

	if (amount < 1) {
		std::cout << "Must order at least 1 food. Cancelling...\n";
		return;
	}

	// calculate price
	price *= amount;
	if (amount > 100) price *= 0.75;
	else if (amount > 50) price *= 0.8;
	else if (amount > 10) price *= 0.9;
	// confirm
	std::cout << amount << " food will cost $" << price << ". Enter 'confirm' to confirm, or 'cancel' to cancel.\n";

	std::string confirm;
	std::getline(std::cin, confirm);
	if (confirm != "confirm") {
		std::cout << "Cancelling...\n";
		return;
	}

	if (*money < price) {
		std::cout << "You do not have enough money for this transaction. Cancelling...\n";
		return;
	}

	(*money) -= price;
	(*food) += amount;
	std::cout << "You have bought " << amount << " food for " << price << ".\n";
}