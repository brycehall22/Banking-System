#pragma once

#include <map>
#include <fstream>
#include <iostream>
#include "accounts.h"

void saveToFile(const map<int, Account*>& accounts);
void loadFromFile(map<int, Account*>& accounts, int& accountIdCounter);