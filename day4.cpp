

#include <iostream>

#include "Utils.h"
#include <map>
#include <algorithm>

struct Timestamp {	
public:
	int year;
	int month;
	int day;
	int hour;
	int minute;
	std::string date;
	std::string dateAndTime;

	Timestamp(std::string line) {
		dateAndTime = Utils::SplitString(line, "]")[0];
		dateAndTime = dateAndTime.substr(1, dateAndTime.size());
		std::vector<std::string> dAt = Utils::SplitString(dateAndTime, " ");
		date = dAt[0];
		std::vector<std::string> ymd = Utils::SplitString(date, "-");
		year = atoi(ymd[0].c_str());
		month = atoi(ymd[1].c_str());
		day = atoi(ymd[2].c_str());

		std::string time = dAt[1];
		std::string h = Utils::SplitString(time, ":")[0];
		std::string m = Utils::SplitString(time, ":")[1];

		minute = atoi(m.c_str());
		hour = atoi(h.c_str());
	}
};

struct Shift {
	std::string guard;
	std::vector<std::string> shiftLine;
	std::string date;
	Shift() {
		shiftLine = std::vector<std::string>(60, ".");
	}

	void addInformation(std::string line) {
		Timestamp timestamp(line);
		date = timestamp.date;
		std::string info = getInformation(line);
		if (info.find("Guard") != std::string::npos) {
			guard = Utils::SplitString(info, " ")[1];
			shiftLine[timestamp.minute] = "B";
		}
		else if (info.find("asleep") != std::string::npos) {
			shiftLine[timestamp.minute] = "$";
		}
		else if (info.find("wakes") != std::string::npos) {
			shiftLine[timestamp.minute] = "%";
		}
	}

	std::string getInformation(std::string line) {
		return Utils::SplitString(line, "] ")[1];
	}

	int SleepTime() {
		int sleepingTime = 0;
		bool sleeping = false;
		int tick = 0;
		for (int i = 0; i < shiftLine.size(); ++i) {
			if (shiftLine[i].find("$") != std::string::npos) {
				sleeping = true;
			}
			if (shiftLine[i].find("%") != std::string::npos) {
				if (sleeping == false) {
					//he was already sleeping before 00:00
					sleepingTime += i;
				}
				else {
					sleepingTime += tick;
					tick = 0;
					sleeping = false;
				}
			}
			if (sleeping == true) {
				tick++;
			}

		}
		return sleepingTime;
	}

};




void printShift(Shift &shift) {
	std::cout<<"Date="<<shift.date << " " << "Guard="<<shift.guard << std::endl;
	for (int i = 0; i < shift.shiftLine.size(); ++i) {
		std::cout << shift.shiftLine[i];
	}
	std::cout << std::endl;
}



bool compareFunction(std::string a, std::string b) {
	Timestamp time_a(a);
	Timestamp time_b(b);
	return (time_a.dateAndTime < time_b.dateAndTime);
}

int sleepTimeForGuardsShift(std::vector<Shift> &shifts) {
	int sum = 0;
	for (int i = 0; i < shifts.size(); i++) {
		sum += shifts[i].SleepTime();
	}
	return sum;
}

int findMostOccuredSleepingMinute(std::vector<Shift> shifts) {
	std::vector<int> minutes(60);
	for (int i = 0; i < shifts.size(); ++i) {
		std::vector<std::string> shiftLine = shifts[i].shiftLine;
		bool sleeping = false;
		for (int j = 0; j < shiftLine.size(); ++j) {
			if (shiftLine[j].find("$") != std::string::npos) {
				sleeping = true;
			}
			if (shiftLine[j].find("%") != std::string::npos) {
				if (sleeping == false) {
					//he was already sleeping before 00:00
					for (int b = 0; b < j; b++) {
						minutes[b] += 1;
					}
					
				}
				else {
					minutes[j] += 1;
					sleeping = false;
				}
			}
			if (sleeping == true) {
				minutes[j] += 1;
			}
		}
		
	}
	int max = 0;
	int index = 0;
	for (int i = 0; i < minutes.size(); ++i) {
		if (minutes[i] > max) {
			max = minutes[i];
			index = i;
		}
	}
	return index;
}


std::map<std::string, std::vector<Shift>> guardShifts;

int main() {

	std::vector<std::string> lines = Utils::ReadFile("input.txt");
	std::sort(lines.begin(), lines.end(), compareFunction);
	Shift shift;
	for (int i = 0; i < lines.size(); ++i) {
		if (lines[i].find("Guard") != std::string::npos) {
			auto it = guardShifts.find(shift.guard);
			if (it == guardShifts.end()) {
				std::vector<Shift> shifts;
				guardShifts[shift.guard] = shifts;
			}
			guardShifts[shift.guard].push_back(shift);
			shift = Shift();
		}
		shift.addInformation(lines[i]);
	}
	//add the last one
	auto it = guardShifts.find(shift.guard);
	if (it == guardShifts.end()) {
		std::vector<Shift> shifts;
		guardShifts[shift.guard] = shifts;
	}
	guardShifts[shift.guard].push_back(shift);
	

	int maxSleepingTime = 0;
	std::string guard;
	int findMostMinute = 0;
	it = guardShifts.begin();
	while (it != guardShifts.end()) {
		int sleepTimeForGuard = 0;
		std::vector<Shift> shifts = it->second;
		int time = sleepTimeForGuardsShift(shifts);
		if (time > maxSleepingTime) {
			maxSleepingTime = time;
			guard = it->first;
			findMostMinute = findMostOccuredSleepingMinute(shifts);
		}
		it++;
	}

	std::cout << "Guard=" << guard << std::endl;
	std::cout << "SleepingTime=" << maxSleepingTime << std::endl;
	std::cout << "Minuted occured " << findMostMinute << std::endl;
	
	std::cout << "Done" << std::endl;

	getchar();
	return 0;
}