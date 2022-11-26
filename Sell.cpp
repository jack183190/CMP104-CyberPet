#include <iostream>
#include "Sell.h";
#include "Main.h";
#include <vector>
#include <string>
#include <algorithm>

void sell(double* money, CyberPet* pet, std::vector<CyberPet*>* pets) {
	// if the player sells their last cyberpet, they lose, so don't let that happen
	if ((*pets).size() < 2) {
		std::cout << "You must have at least two CyberPets to sell one. Cancelling...\n";
		return;
	}

	if (pet->getAge() < 10) {
		std::cout << pet->getName() << " is too young to be sold!\nCancelling...\n";
		return;
	}

	std::cout << pet->getName() << " is worth $" << pet->getWorth() << ". Enter 'confirm' to sell, or 'cancel' to cancel.\n";
	std::string confirm;
	std::getline(std::cin, confirm);
	if (confirm == "confirm") {
		(*money) += pet->getWorth();
		std::cout << "You have sold " << pet->getName() << ". You now have $" << *money << ".\n";
		for (int i = 0; i < (*pets).size(); i++) {
			if ((*pets).at(i) != pet) continue;
			(*pets).erase((*pets).begin() + i);
			return;
		}
	}
	std::cout << "Cancelling...\n";
	return;
}