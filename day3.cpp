

#include <iostream>

#include "Utils.h"



struct Claim {
	std::string id;
	int x;
	int y;
	int size_x;
	int size_y;
	Claim(std::string line) {
		std::vector<std::string > v = Utils::SplitString(line, "@");
		id = v[0].substr(1, v[0].size());
		id = Utils::SplitString(id, " ")[0];
		std::string coords = Utils::SplitString(v[1], ":")[0];
		std::string size = Utils::SplitString(v[1], ":")[1];
		coords = coords.substr(1, coords.size());
		size = size.substr(1, size.size());

		size_x = atoi(Utils::SplitString(size, "x")[0].c_str());
		size_y = atoi(Utils::SplitString(size, "x")[1].c_str());
		x = atoi(Utils::SplitString(coords, ",")[0].c_str());
		y = atoi(Utils::SplitString(coords, ",")[1].c_str());
	}

	void Print() {
		std::cout << "id=" << id << std::endl;
		std::cout << "x=" << x << std::endl;
		std::cout << "y=" << y << std::endl;
		std::cout << "size_x=" << size_x << std::endl;
		std::cout << "size_y=" << size_y << std::endl;
	}
};


int size = 1000;
std::vector<std::vector<std::string> > claims(size, std::vector<std::string>(size));

void addClaim(Claim &claim) {
	for (int y = 0; y < claim.size_y; ++y) {
		for (int x = 0; x < claim.size_x; ++x) {
			int r_x = x + claim.x;
			int r_y = y + claim.y;
			if (claims[r_y][r_x] == ".") {
				claims[r_y][r_x] = claim.id;
				continue;
			}
			claims[r_y][r_x] = "X";
			
		}
	}
}

void initClaims() {
	for (int i = 0; i < claims.size(); i++) {
		for (int j = 0; j < claims[i].size(); ++j) {
			claims[i][j] = ".";
		}
	}
}

void printClaims() {
	for (int i = 0; i < claims.size(); i++) {
		for (int j = 0; j < claims[i].size(); ++j) {
			std::cout << claims[i][j];
		}
		std::cout<<std::endl;
	}
}

int amountOfInches() {
	int amount = 0;
	for (int i = 0; i < claims.size(); i++) {
		for (int j = 0; j < claims[i].size(); ++j) {
			if (claims[i][j] == "X") {
				amount++;
			}
		}
	}
	return amount;
}


bool isClaimedOverlapped(Claim &claim) {
	for (int y = 0; y < claim.size_y; ++y) {
		for (int x = 0; x < claim.size_x; ++x) {
			int r_x = x + claim.x;
			int r_y = y + claim.y;
			if (claims[r_y][r_x] == "X") {
				return true;
			}
		}
	}
	return false;
}

int main() {
	initClaims();
	std::vector<Claim> claimList;

	std::vector<std::string> lines = Utils::ReadFile("input.txt");
	for (int i = 0; i < lines.size(); ++i) {
		Claim claim(lines[i]);
		addClaim(claim);
		claimList.push_back(claim); //hope the default-copy constructor is doing right.
	}
	for (int i = 0; i < claimList.size(); ++i) {
		if (!isClaimedOverlapped(claimList[i])) {
			std::cout << "Id not overlapped=" << claimList[i].id << std::endl;
			break;
		}
	}
	std::cout << "Done" << std::endl;

	getchar();
	return 0;
}