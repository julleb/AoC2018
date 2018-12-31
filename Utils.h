#ifndef UTILS_H
#define UTILS_H


#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>

namespace Utils {
	std::vector<std::string> ReadFile(const char *fileName) {
		std::vector<std::string> lines;
		std::string line;
		std::ifstream myfile(fileName);
		if (myfile.fail() == true) {
			std::cout << "Failed open file" << std::endl;
			return lines;
		}
		if (myfile.is_open()) {
			while (getline(myfile, line)) {
				lines.push_back(line);
			}
		}
		myfile.close();
		return lines;
	}

	std::vector<std::string> SplitString(std::string s, std::string delimiter) {
		std::vector<std::string> splittedString;
		size_t pos = 0;
		std::string token;
		while ((pos = s.find(delimiter)) != std::string::npos) {
			token = s.substr(0, pos);
			splittedString.push_back(token);
			s.erase(0, pos + delimiter.length());
		}
		splittedString.push_back(s);
		return splittedString;
	}

	std::string StringToUpperCase(std::string str) {
		std::transform(str.begin(), str.end(), str.begin(), ::toupper);
		return str;
	}
	std::string StringToLowerCase(std::string str) {
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);
		return str;
	}
}


#endif
