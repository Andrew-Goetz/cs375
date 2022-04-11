#include <assert.h>
#include <bits/stdc++.h>
#include <chrono>
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
	double ratio;
	int index;
} KnapsackEntry;

typedef struct problem {
	vector<KnapsackEntry> entries;
	int size;
	int capacity;
} KnapsackProblem;

void parseInput(int argc, char input_file[], vector<KnapsackProblem> &p) {
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
			entry.ratio = (double)entry.profit / (double)entry.weight;
			entry.index = i+1;
			temp.entries.push_back(entry);
		}
		p.push_back(temp);
		temp.entries.clear();
	}
	p.pop_back();
	input.close();
}

string print_vector(vector<int> &best_items) {
	stringstream ss;
	sort(best_items.begin(), best_items.end());
	for(int i : best_items) ss << i << " ";
	string ret = ss.str();
	assert(ret.length());
	ret.pop_back();
	return ret;
}

vector<KnapsackEntry> sort_entries(vector<KnapsackEntry> sorted) {
	for(int i = 0; i < sorted.size(); ++i) {
		for(int j = i + 1; j < sorted.size(); ++j) {			
			if(sorted[i].ratio < sorted[j].ratio) {
				KnapsackEntry tmp = sorted[i];
				sorted[i] = sorted[j];
				sorted[j] = tmp;
			}
		}
	}
	return sorted;
}

string knn_greed1(KnapsackProblem &p) {
	auto start = chrono::high_resolution_clock::now();
	stringstream output;
	int max_profit = 0;
	vector<int> best_items;
	vector<KnapsackEntry> sorted = sort_entries(p.entries);
	int cur_weight = p.capacity;
	for(int i = 0; i < sorted.size(); i++) {
		if(cur_weight - sorted[i].weight >= 0) {
			cur_weight -= sorted[i].weight;
			max_profit += sorted[i].profit;
			best_items.push_back(sorted[i].index);
		}
		assert(cur_weight >= 0);
	}
	auto stop = chrono::high_resolution_clock::now();
	output << p.size << " " << max_profit << " "
	       << chrono::duration_cast<chrono::seconds>(stop - start).count()
		   << " " << print_vector(best_items) << '\n';
	return output.str();
}

string knn_greed2(KnapsackProblem &p) {
	auto start = chrono::high_resolution_clock::now();
	stringstream output;
	int max_profit = 0;
	vector<int> best_items;

	auto stop = chrono::high_resolution_clock::now();
	output << p.size << " " << max_profit << " "
	       << chrono::duration_cast<chrono::seconds>(stop - start).count()
		   << print_vector(best_items) << '\n';
	return output.str();
}

string knn_backtrack(KnapsackProblem &p) {
	auto start = chrono::high_resolution_clock::now();
	stringstream output;
	int max_profit = 0;
	vector<int> best_items;

	auto stop = chrono::high_resolution_clock::now();
	output << p.size << " " << max_profit << " "
	       << chrono::duration_cast<chrono::seconds>(stop - start).count()
		   << print_vector(best_items) << '\n';
	return output.str();
}

void runProgram(vector<KnapsackProblem> &p, char filename[], char num[]) {
	ofstream output(filename);
	string result;
	for(KnapsackProblem i : p) {
		if(num[0] == '0') {
			result = knn_greed1(i);
		} else if(num[0] == '1') {
			result = knn_greed2(i);
		} else if(num[0] == '2') {
			result = knn_backtrack(i);
		}
		output << result;
	}
	output.close();
}

int main(int argc, char *argv[]) {
	vector<KnapsackProblem> p;
	parseInput(argc, argv[1], p);
	runProgram(p, argv[2], argv[3]);
	#if ENABLE_TESTING
	for(KnapsackProblem i : p) {
		cout << "Size: " << i.size << "    Capacity: " << i.capacity << endl;
		for(KnapsackEntry k : i.entries) {
			cout << k.weight << " " << k.profit << " ratio: " << k.ratio << endl;
		}
		cout << endl;
	}

	vector<KnapsackEntry> sorted = sort_entries(p[1].entries);
	for(KnapsackEntry i : sorted) {
		cout << "Weight: " << i.weight << "Profit: " << i.profit << "Ratio: " << i.ratio << "Index: " << i.index << endl;
	}
	#endif
}
