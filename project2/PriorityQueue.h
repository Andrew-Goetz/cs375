#ifndef PRIORITY_QUEUE_H
#define PRIOTIRY_QUEUE

#include <fstream>
#include <vector>

using namespace std;

typedef struct contestant {
	int id;
	int score;
} Contestant;

class PriorityQueue {
	private:
		vector<Contestant> heap;
		vector<int> handle;
		ofstream output;
		int n;
		void minHeapify(int index);
	public:
		PriorityQueue(int size, char output_file[]);
		void findContestant(int k);
		void insertContestant(int k, int s);
		void eliminateWeakest(void);
		void earnPoints(int k, int p);
		void losePoints(int k, int p);
		void showContestants(void);
		void showHandles(void);
		void showLocation(int k);
		void crownWinner(void);
};

#endif
