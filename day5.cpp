

#include <iostream>

#include "Utils.h"
#include <algorithm>

bool isOppositePolarity(char v, char n) {
	std::string value(1,v);
	std::string next(1, n);
	if (Utils::StringToLowerCase(value) == Utils::StringToLowerCase(next)) {
		if (value != next) {
			return true;
		}
	}
	return false;
}

//should probably make a linkedlist for performance.
std::string react(std::string polymer) {
	while (true) {
		bool found = false;;
		for (int i = 0; i < polymer.size(); ++i) {
			char value = polymer[i];
			if ((i + 1) >= polymer.size()) break;
			char next = polymer[i + 1];
			if (isOppositePolarity(value, next)) {
				polymer.erase(i, 2);
				i -= 2; //performance fix -> we may create another polarity of the reaction
				found = true;
			}
		}
		if (found == false) break;
	}
	return polymer;
	
}


int partTwo(std::string &polymer) {
	std::string abc = "abcdefghijklmnopqrstuvwxyz";
	int smallestUnit = polymer.length();
	for (int i = 0; i < abc.length(); ++i) {
		std::string temp = polymer;
		int smallCharPos = 0;
		int upperCharPos = 0;
		while (true) {
			bool found = false;
			int upperCharPos = temp.find(abc[i]-32);
			if (upperCharPos != std::string::npos) {
				temp.erase(upperCharPos, 1);
				found = true;
			}
			int smallCharPos = temp.find(abc[i]);
			if (smallCharPos != std::string::npos) {
				temp.erase(smallCharPos, 1);
				found = true;
			}
			if (found == false) break;
		}
		std::cout << "Replaced " << abc[i] << std::endl;
		temp = react(temp);	
		if (temp.size() < smallestUnit) {

			smallestUnit = temp.size();
		}
	}
	std::cout << "smallestUnit = " << smallestUnit << std::endl;
	return 1;
}

int main() {
	std::string polymer = Utils::ReadFile("input.txt")[1];
	partTwo(polymer);
	getchar();
	return 0;
	
}
