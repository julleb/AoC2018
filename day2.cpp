


#include "iostream"
#include <fstream>
#include <string>
#include  <cstdlib>
#include <vector>
#include <map>

std::vector<std::string> readFile(const char *fileName) { 
    std::vector<std::string> lines;
    std::string line;
    std::ifstream myfile(fileName);
    if (myfile.is_open()) {
        while ( getline (myfile,line) ) {
            lines.push_back(line);
        }
    }
    myfile.close();
    return lines; 
}

bool lineContainsSameLetter(std::string line, int amountOfSameLetter) {
    std::vector<char> keys;
    std::map<char, int> amountsPerLetter;
    for(int i = 0; i < line.length(); ++i) {
        //std::cout<<line[i]<<std::endl;
        char letter = line[i];
        keys.push_back(letter);
        amountsPerLetter[letter] += 1;
    }
    
    for(int i = 0; i < keys.size(); ++i) {
        char letter = keys[i];
        int amount = amountsPerLetter[letter];
        if(amount == amountOfSameLetter) return true;
    }
    return false;
}

int partOne() {
    std::vector<std::string> lines = readFile("input.txt");
    int twice = 0;
    int treeTimes = 0;
    for(int i = 0; i < lines.size(); ++i) {
        if(lineContainsSameLetter(lines[i], 2)) {
            twice++;
        } 
        if(lineContainsSameLetter(lines[i], 3)) {
            treeTimes++;
        }
    }
    std::cout<<"hash="<<treeTimes*twice<<std::endl;
}

int partTwo() {
}

int main() {
    partOne();
}
