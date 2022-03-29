#include <assert.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

#define ENABLE_TESTING 0

typedef struct entry {
	int weight;
	int profit;
} KnapsackEntry;

typedef struct problem {
	vector<KnapsackEntry> entries;
	int size;
	int capacity;
} KnapsackProblem;

void parseInput(int argc, char input_file[], vector<KnapsackProblem> p) {
	if(argc != 4) {
		cout << "Usage: ./submission [input_file] [output_file] [0/1/2]\n";
		exit(0);
	}
	ifstream input(input_file);
	KnapsackProblem temp;
	while(!input.eof()) {
		input >> temp.size >> temp.capacity;
		KnapsackEntry entry;
		for(int i = 0; i < temp.size; i++) {
			input >> entry.weight >> entry.profit;
			temp.entries.push_back(entry);
		}
		p.push_back(temp);
		temp.clear();
	}

	while(input >> temp.weight >> temp.price) {

	}
	input.close();
}

int main(int argc, char *argv[]) {
	vector<KnapsackProblem> p;

	int size = parseInput(argc, argv[1], instructions);
	runProgram(instructions, size, argv[2]);
/*
	#if ENABLE_TESTING
	cout << size << endl;
	for(Instruction i : instructions) {
		cout << i.instr << " " << i.k << " " << i.p << endl;
	}
	#endif
*/
}
