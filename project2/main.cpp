#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "PriorityQueue.h"

using namespace std;

typedef struct instruction {
	string instr;
	int k;
	int p;
} Instruction;

string removeSymbols(string s) {
	s.erase(remove(s.begin(), s.end(), '<'), s.end());
	s.erase(remove(s.begin(), s.end(), '>'), s.end());
	return s;
}

void parseNumbers(Instruction temp, stringstream parse) {
	switch(temp.instr) {
		case "findContestant":
		case "showLocation":
			parse >> temp.k;
			temp.p = -1;
			break;

		case "insertContestant":
		case "earnPoints":
		case "losePoints":
			parse >> temp.k >> temp.p;
			break;

		case "eliminateWeakest":
		case "showContestants":
		case "showHandles":
		case "crownWinner":
			temp.k = -1;
			temp.p = -1;
			break;

		default:
			cout << "Error: invalid operation name in input file, the program will now exit.\n";
			exit(0);
	}
}

int parseInput(int argc, char input_file[], vector<Instruction> &instructions) {
	if(argc != 3) {
		cout << "Usage: ./submission [input_file] [output_file]\n";
		exit(0);
	}
	ifstream input(input_file);
	int size = 0;
	Instruction temp;
	string line;
	while(getline(input, line)) {
		if(line.find_first_of("0123456789") != 0) {
			removeSymbols(line);
			stringstream parse(line);
			parse >> temp.instr;
			parseNumbers(&temp, parse);
			instructions.push(temp);
		} else {
			size = stoi(line);
		}
	}
	input.close();
	return size ;
}

void runProgram(vector<Instruction> &instructions) {
	for(Instruction i : instructions) {

	}
}

int main(int argc, char *argv[]) {
	vector<Instruction> instructions;
	int size = parseInput(argc, input_file, &instructions);
	PriorityQueue x
}
