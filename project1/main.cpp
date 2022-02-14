#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define ENABLE_TESTING 0

using namespace std;

typedef struct card {
	string name;
	int price;
} Card;

void parseInput(int argc, char **argv, vector<Card> &market, vector<vector<Card>> &vendor, vector<int> &budgets) {
	if(argc != 5) {
		cout << "Usage: program1 -m <market-price-file> -p <price-list-file>\n";
		exit(0);
	}
	ifstream mp_file(argv[2]);
	int num = 0;
	mp_file >> num;
	Card temp;
	while(mp_file >> temp.name >> temp.price) {
		market.push_back(temp);
	}
	mp_file.close();

	ifstream pl_file(argv[4]);
	string line;
	bool firstRun = true;
	int n = 0;
	int i = 0;
	while(getline(pl_file, line)) {
		if(line.find_first_of("0123456789") != 0) {
			stringstream parse(line);
			while(parse >> temp.name >> temp.price);
			vendor[i].push_back(temp);
		} else {
			vendor.push_back(vector<Card>());
			stringstream parse(line);
			parse >> n >> n;
			budgets.push_back(n);
			if(!firstRun) i++;
			else firstRun = false;
		}
	}
	pl_file.close();
}

void errorCheck(vector<Card> &market, vector<vector<Card>> &vendor) {
	for(vector<Card> v : vendor) {
		for(Card c : v) {
			for(int i = 0; i < market.size(); i++) {
				if(c.name == market[i].name) {
					break;
				} else if(i == market.size() - 1) {
					cout << "Error: card with name \"" << c.name << "\" not found in market file\n";
					exit(0);
				}
			}
		}
	}
}

int moneySum(vector<Card> &v) {
	int ret = 0;
	for(Card e : v)
		ret += e.price;
	return ret;
}

int findProfit(vector<Card> &S, vector<Card> &market) {
	int ret = 0;
	for(Card x : S) {
		for(Card m : market) {
			if(x.name == m.name) { // grabs first match
				ret += m.price;
				break;
			}
		}
	}
	return ret;
}

bool bitSet(int i, int j) {
	return (1U << j) & i;
}

string print_card_vector(vector<Card> &M) {
	stringstream ret;
	for(Card x : M)
		ret << x.name << endl;
	return ret.str();
}

string computeMaxProfit(vector<Card> &market, vector<Card> &vendor, const int budget) {
	auto start = chrono::high_resolution_clock::now();
	stringstream output;
	int maxProfit = 0;
	vector<Card> S;
	vector<Card> M;
	if(moneySum(vendor) <= budget) {
		M = vendor;
		maxProfit = findProfit(M, market);
		goto DONE;
	}
	for(int i = 0; i < (1 << vendor.size()); i++) {
		S.clear();
		for(int j = 0; j < vendor.size(); j++)
			if(bitSet(i, j)) S.push_back(vendor[j]);
		if(moneySum(S) <= budget && findProfit(S, market) > maxProfit) {
			maxProfit = findProfit(S, market);
			M = S;
		}
	}
	DONE:
	auto stop = chrono::high_resolution_clock::now();
	output << market.size() << " " << maxProfit << " " << M.size() << " "
	       << chrono::duration_cast<chrono::seconds>(stop - start).count()
		   << "\n" << print_card_vector(M);
	return output.str();
}

void runComputeMaxProfit(vector<Card> &market, vector<vector<Card>> &vendor, vector<int> &budgets) {
	ofstream output("output.txt");
	for(int i = 0; i < vendor.size(); i++)
		output << computeMaxProfit(market, vendor[i], budgets[i]);
	output.close();
}

int main(int argc, char *argv[]) {
	vector<Card> market;
	vector<vector<Card>> vendor;
	vector<int> budgets;
	parseInput(argc, argv, market, vendor, budgets);
	errorCheck(market, vendor);
	runComputeMaxProfit(market, vendor, budgets);
	#if ENABLE_TESTING
	cout << "Market Prices:\n";
	for(int i = 0; i < market.size(); i++) {
		cout << market[i].name << " " << market[i].price << endl;
	}
	cout << "\n";
	for(int i = 0; i < vendor.size(); i++) {
		cout << "Sample " << i << " with budget " << budgets[i] << ":\n";
		for(int j = 0; j < vendor[i].size(); j++) {
			cout << vendor[i][j].name << " " << vendor[i][j].price << endl;
		}
	}
	#endif
}
