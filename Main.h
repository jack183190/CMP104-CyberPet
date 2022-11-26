#include <vector>
#include "CyberPet.h"

int getCurrentTime();
int bound(int, int, int);

void help();
void info(double*, int*, std::vector<CyberPet*>*);

CyberPet* choosePet(std::vector<CyberPet*>*);