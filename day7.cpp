
#include "Utils.h"

#include <map>

struct Node {
	char value;
	std::map<char, Node*> neighbours;
	std::map<char, Node*> dependantOn;
	bool visited = false;

	Node(char v) {
		value = v;
	}
	Node() {

	}

	Node(const Node &c) {
		//std::cout << "copy" << std::endl;
		value = c.value;
		neighbours = c.neighbours;
		dependantOn = c.dependantOn;
		visited = c.visited;
	}

	bool hasNeighbours() {
		return neighbours.size();
	}

	bool hasDependencies() {
		return dependantOn.size();
	}

	std::vector<char> getNodesAvialable() {
		auto it = neighbours.begin();
		std::vector<char> nexts;
		while (it != neighbours.end()) {
			Node *neighbourNode = it->second;
			
			bool available = true;
			auto nIt = neighbourNode->dependantOn.begin();
			while (nIt != neighbourNode->dependantOn.end()) {
				if (nIt->second->visited == false) {
					available = false;
					break;
				}
				nIt++;
			}
			if (available == true) {
				nexts.push_back(neighbourNode->value);
			}
			it++;
		}
		return nexts;
	}
};


void printMap(std::map<char, Node*> map) {
	auto it = map.begin();
	while (it != map.end()) {
		std::cout << it->first << std::endl;
		it++;
	}
}

std::map<char, Node*> nodeMap;
std::vector<char> availableNodes;

void buildNodeMap() {
	std::vector<std::string> lines = Utils::ReadFile("input.txt");
	for (int i = 0; i < lines.size(); ++i) {
		std::vector<std::string> splittedLine = Utils::SplitString(lines[i], " ");
 		char dependantValue = splittedLine[1][0];
		char nodeValue = splittedLine[7][0];

		//std::cout << nodeValue << " is dependant on " << dependantValue << std::endl;
		if (nodeMap.find(nodeValue) == nodeMap.end()) {
			Node *np = new Node(nodeValue);
			nodeMap[nodeValue] = np;
		}
		if (nodeMap.find(dependantValue) == nodeMap.end()) {
			Node *np = new Node(dependantValue);
			nodeMap[dependantValue] = np;
		}
		
		Node *dependantNode = nodeMap[dependantValue];
		Node *node = nodeMap[nodeValue];
		node->dependantOn[dependantNode->value] = dependantNode;
		dependantNode->neighbours[node->value] = node;
	}
}

void getFirstAvialable() {
	auto it = nodeMap.begin();
	while (it != nodeMap.end()) {
		Node *node = it->second;
		if (node->hasDependencies() == false) {
			availableNodes.push_back(node->value);
		}
		it++;
	}
}

int getTheBestAvialableIndex(std::vector<char> &avialables) {
	int index = -1;
	if (avialables.size() == 0) {
		std::cout<<"hits"<<std::endl;
		return index;
	}
	char best = 'Z';
	for (int i = 0; i < avialables.size(); i++) {
		if (avialables[i] <= best) {
			best = avialables[i];
			index = i;
		}
	}
	return index;
}

int main() {
	buildNodeMap();
	getFirstAvialable();
	char c = availableNodes[0];
	availableNodes.erase(availableNodes.begin() + 0);
	Node *node = nodeMap[c];
	std::cout << "StartNode " << node->value << std::endl;
	while (node->hasNeighbours() == true) {
		std::cout << node->value;
		node->visited = true;
		std::vector<char> avialables = node->getNodesAvialable();
		//std::cout << "Node " << node->value << std::endl;
		for (int i = 0; i < avialables.size(); i++) {
			//std::cout << " has avaialbe " << avialables[i] << std::endl;
			availableNodes.push_back(avialables[i]);
		}
		int index = getTheBestAvialableIndex(availableNodes);
		if (index == -1) {
			std::cout << "failed" << std::endl;
			getchar();
			return 1;
		}
		char nextNode = availableNodes[index];
		availableNodes.erase(availableNodes.begin() + index);
		node = nodeMap[nextNode];
	}
	std::cout <<node->value<< std::endl;
	std::cout << "done" << std::endl;
	getchar();
}
