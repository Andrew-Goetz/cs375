#include <algorithm>
#include <assert.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "PriorityQueue.h"

using namespace std;

#define ENABLE_TESTING 0

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

void parseNumbers(Instruction &temp, stringstream &parse) {
	if(temp.instr == "findContestant" || temp.instr == "showLocation") {
		parse >> temp.k;
		temp.p = -1;
	} else if(temp.instr == "insertContestant" || temp.instr == "earnPoints" || temp.instr == "losePoints") {
		parse >> temp.k >> temp.p;
	} else if(temp.instr == "eliminateWeakest" || temp.instr == "showContestants" ||
		      temp.instr == "showHandles" || temp.instr == "crownWinner") {
		temp.k = -1;
		temp.p = -1;
	} else {
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
			stringstream parse(removeSymbols(line));
			parse >> temp.instr;
			parseNumbers(temp, parse);
			instructions.push_back(temp);
		} else {
			size = stoi(line);
		}
	}
	input.close();
	return size;
}

void runInstruction(PriorityQueue &q, Instruction &i) {
	/* tfw no reflection in C++ */
	q.output << i.instr;
	if(i.k != -1) q.output << " <" << i.k << ">";
	if(i.p != -1) q.output << " <" << i.p << ">";
	q.output << endl;
	if(i.instr == "findContestant") { // k
		assert(i.p == -1);
		q.findContestant(i.k);
	} else if(i.instr == "showLocation") { // k
		assert(i.p == -1);
		q.showLocation(i.k);
	} else if(i.instr == "insertContestant") { // k, p
		q.insertContestant(i.k, i.p);
	} else if(i.instr == "earnPoints") { // k, p
		q.earnPoints(i.k, i.p);
	} else if(i.instr == "losePoints") { // k, p
		q.losePoints(i.k, i.p);		
	} else if(i.instr == "eliminateWeakest") { // void
		assert(i.k == -1 && i.p == -1);
		q.eliminateWeakest(false);
	} else if(i.instr == "showContestants") { // void
		assert(i.k == -1 && i.p == -1);
		q.showContestants();
	} else if(i.instr == "showHandles") { // void
		assert(i.k == -1 && i.p == -1);
		q.showHandles();
	} else if(i.instr == "crownWinner") { // void
		assert(i.k == -1 && i.p == -1);
		q.crownWinner();
	} else {
		cout << "Error: invalid operation name in input file, the program will now exit.\n";
		exit(0);
	}
	
}

void runProgram(vector<Instruction> &instructions, int size, char output_file[]) {
	PriorityQueue q(size, output_file);
	for(Instruction i : instructions) {
		runInstruction(q, i);
	}
}

int main(int argc, char *argv[]) {
	vector<Instruction> instructions;
	int size = parseInput(argc, argv[1], instructions);
	runProgram(instructions, size, argv[2]);

	#if ENABLE_TESTING
	cout << size << endl;
	for(Instruction i : instructions) {
		cout << i.instr << " " << i.k << " " << i.p << endl;
	}
	#endif
}
