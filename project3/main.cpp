#include <assert.h>
#include <bits/stdc++.h>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
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

typedef struct greedyreturn {
	vector<int> bestset;
	int maxprofit;
} GreedyReturn;

typedef struct node {
	// indexes stored in taken and non_taken relative to sorted array
	vector<int> taken;
	vector<int> not_taken;
	int profit = 0;
	int weight = 0;
	double bound = 0;
} Node;

void parseInput(int argc, char input_file[], vector<KnapsackProblem> &p) {
	if(argc != 4) {
		cout << "Usage: ./submission [input_file] [output_file] [0/1/2]\n";
		exit(0);
	}
	ifstream input(input_file);
	KnapsackProblem temp;
	input >> temp.size >> temp.capacity;
	while(!input.eof()) {
		KnapsackEntry entry;
		for(int i = 0; i < temp.size; i++) {
			input >> entry.weight >> entry.profit;
			entry.ratio = (double)entry.profit / (double)entry.weight;
			entry.index = i+1;
			temp.entries.push_back(entry);
		}
		p.push_back(temp);
		temp.entries.clear();
		input >> temp.size >> temp.capacity;
	}
	//p.pop_back();
	input.close();
}

string print_vector(vector<int> &best_items) {
	stringstream ss;
	sort(best_items.begin(), best_items.end());
	for(int i : best_items) ss << i << " ";
	string ret = ss.str();
	if(ret.length() >= 0) {
		ret.erase(ret.find_last_not_of(" \t\n\r\f\v") + 1);
	}
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

GreedyReturn greed1_algo(KnapsackProblem &p) {
	GreedyReturn ret = {};
	vector<KnapsackEntry> sorted = sort_entries(p.entries);
	int cur_weight = p.capacity;
	for(int i = 0; i < sorted.size(); i++) {
		if(cur_weight - sorted[i].weight >= 0) {
			cur_weight -= sorted[i].weight;
			ret.maxprofit += sorted[i].profit;
			//cout << ret.maxprofit << endl;
			ret.bestset.push_back(sorted[i].index);
		}
		assert(cur_weight >= 0);
	}
	return ret;
}

string knapsack_greed1(KnapsackProblem &p) {
	auto start = chrono::high_resolution_clock::now();
	stringstream output;
	GreedyReturn x = greed1_algo(p);
	auto stop = chrono::high_resolution_clock::now();
	output << p.size << " " << x.maxprofit << " "
	       << (chrono::duration_cast<chrono::nanoseconds>(stop - start).count()) / 1000
		   << " " << print_vector(x.bestset) << '\n';
	return output.str();
}

int* find_pmax(vector<KnapsackEntry> &entries, int capacity) {
	static int pmax[2] = {0, 0};
	for(int i = 0; i < entries.size(); i++) {
		if(entries[i].weight <= capacity) {
			pmax[0] = entries[i].profit;
			pmax[1] = i+1;
		}
	}
	//cout << "profit: " << pmax[0] << " index: " << pmax[1] << endl;
	return pmax;
}

GreedyReturn greed2_algo(KnapsackProblem &p) {
	int *pmax = find_pmax(p.entries, p.capacity);
	GreedyReturn ret = greed1_algo(p);
	if(ret.maxprofit > pmax[0]) {
		return ret;
	}
	ret.maxprofit = pmax[0];
	ret.bestset.clear();
	ret.bestset.push_back(pmax[1]);
	return ret;
}

string knapsack_greed2(KnapsackProblem &p) {
	auto start = chrono::high_resolution_clock::now();
	stringstream output;
	GreedyReturn x = greed2_algo(p);
	auto stop = chrono::high_resolution_clock::now();
	output << p.size << " " << x.maxprofit << " "
	       << (chrono::duration_cast<chrono::nanoseconds>(stop - start).count()) / 1000
		   << " " << print_vector(x.bestset) << '\n';
	return output.str();
}

bool promising(Node x, int capacity, int maxprofit) {
	return (x.weight <= capacity && x.bound > maxprofit) ? true : false;
}

double compute_bound(Node x, vector<KnapsackEntry> sorted, int capacity) {
	double bound = 0;
	//cout << "Not taken: " << print_vector(x.not_taken) << "  Taken: " << print_vector(x.taken) << endl;
	for(int i = 0; i < sorted.size(); i++) {
		for(int j = 0; j < x.not_taken.size(); j++) {
			if(x.not_taken[j] == i) goto CONTINUE;
		}
		if(capacity - sorted[i].weight >= 0) {
			capacity -= sorted[i].weight;
			bound += sorted[i].profit;
			//cout << "capacity: " << capacity << "    bound: " << bound << endl;
		} else {
			bound += (double)capacity * sorted[i].ratio;
			capacity = 0;
			//cout << "capacity: " << capacity << "    bound: " << bound << endl;
			break;
		}
		CONTINUE:
		assert(capacity >= 0);
		//cout << "loop run" << endl;
	}
	return bound;
}

int get_si(int tree_index, int sorted_size) {
	for(int i = 0; i < sorted_size; i++) {
		if((tree_index >= (1<<i+1)-1) &&
		   (tree_index < (1<<(i+2))-1)) {
			return i;
		}
	}
	return -1; // should never happen
}

string knapsack_backtrack(KnapsackProblem &p) {
	auto start = chrono::high_resolution_clock::now();
	stringstream output;
	GreedyReturn x = greed2_algo(p);
	int maxprofit = x.maxprofit;
	vector<int> bestset = x.bestset;
	Node tree[1<<(p.size+1)];
	vector<KnapsackEntry> sorted = sort_entries(p.entries);

	tree[0].profit = 0;
	tree[0].weight = 0;
	tree[0].bound = compute_bound(tree[0], sorted, p.capacity);
	int tree_index = 1;
	int sorted_index = 0;
	int leaf_node_bound = (1<<(p.size+1)) - ceil((double)(1<<(p.size+1))/2.0) - 1;

	for(int i = 1; i < (1<<(p.size+1)); i++) {
		/* Initialize node with parent node info */
		//cout << "node " << tree_index << " child of " << (int)((ceil((double)tree_index/2.0))-1) << endl;
		tree[tree_index] = tree[(int)((ceil((double)tree_index/2.0))-1)];
		sorted_index = get_si(tree_index, sorted.size());
		assert(sorted_index != -1);
		if(tree_index % 2) { // left node
			tree[tree_index].profit += sorted[sorted_index].profit;
			tree[tree_index].weight += sorted[sorted_index].weight;
			tree[tree_index].taken.push_back(sorted_index);
		} else { // right node
			//cout << "\nAdding to not_taken for node " << tree_index <<  "\n";
			tree[tree_index].not_taken.push_back(sorted_index);
		}
		tree[tree_index].bound = compute_bound(tree[tree_index], sorted, p.capacity);
		//cout << "tree_index: " << tree_index << " profit: " << tree[tree_index].profit << " weight: " << tree[tree_index].weight << " bound: " << tree[tree_index].bound; 
		if(tree[tree_index].weight <= p.capacity && tree[tree_index].profit > maxprofit) {
			maxprofit = tree[tree_index].profit;
			/*
			bestset.clear();
			for(int i = 0; i < tree[tree_index].taken.size(); i++) {
				bestset.push_back(sorted[i].index);
			}
			*/
			bestset = tree[tree_index].taken;
			for(int i = 0; i < bestset.size(); i++) {
				bestset[i] = sorted[bestset[i]].index;
			}
		}
		//cout << "   Promising? : " << promising(tree[tree_index], p.capacity, maxprofit) << endl;
		if(promising(tree[tree_index], p.capacity, maxprofit)) {
			if(tree_index < leaf_node_bound) {
				tree_index = tree_index*2 + 1;
				assert(tree_index < (1<<(p.size+1)));
				continue; // continue checking left children, dfs order
			}
		}
		for(;;) {
			int parent = (int)((ceil((double)tree_index/2.0))-1);
			tree_index = parent*2 + 2;
			//cout << "Tree_index:
			if(tree_index >= (1<<(p.size+1))) {
				goto STOP;
			}
			if(tree[tree_index].bound == 0) { // we've found desired node
				break;
			}
			tree_index = parent; // continue searching for non-checked right node in next node
			if(tree_index == 0) goto STOP;
		}
	}
	STOP:
	auto stop = chrono::high_resolution_clock::now();
	output << p.size << " " << maxprofit << " " << fixed << setprecision(2)
	       << (chrono::duration_cast<chrono::nanoseconds>(stop - start).count()) / 1000.0
	       << " " << print_vector(bestset) << '\n';
	return output.str();
}

void runProgram(vector<KnapsackProblem> &p, char filename[], char num[]) {
	ofstream output(filename);
	string result;
	for(KnapsackProblem i : p) {
		if(num[0] == '0') {
			result = knapsack_greed1(i);
		} else if(num[0] == '1') {
			result = knapsack_greed2(i);
		} else if(num[0] == '2') {
			result = knapsack_backtrack(i);
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
	vector<KnapsackEntry> sorted = sort_entries(p[0].entries);
	for(KnapsackEntry i : sorted) {
		cout << "Weight: " << i.weight << " Profit: " << i.profit << " Ratio: " << i.ratio << " Index: " << i.index << endl;
	}
	#endif
}
