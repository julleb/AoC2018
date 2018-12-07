


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

int getIntegerFromLine(std::string line) {
    
    std::string intString = line.substr(1, line.length());
    int intInLine = std::atoi(intString.c_str());
    if(line[0] == '-') {
        return 0-intInLine;
    }else {
       return intInLine;
     }
}

int partOne() {
    int frequency = 0;
    std::vector<std::string> lines = readFile("input.txt");
    for(int i = 0; i < lines.size(); ++i) {
        frequency += getIntegerFromLine(lines[i]);
    }
    std::cout<<"frequency="<<frequency<<std::endl;
}

int partTwo() { 
    int frequency = 0;
    std::map<int, int> freqs;
    std::vector<std::string> lines = readFile("input.txt");
    for(int i = 0; i < lines.size(); ++i) {
        int value = getIntegerFromLine(lines[i]);
        frequency += value;
        if (freqs.find(frequency) != freqs.end()) {
            std::cout << "twice="<<frequency << std::endl;
            return 0;
        }
        freqs[frequency] = 1;
        if(i+1 == lines.size()) i = -1; 
    }
}

int main() {
    partTwo();
}
