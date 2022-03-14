#include <string>
#include <vector>

#include "PriorityQueue.h"

using namespace std;

PriorityQueue::PriorityQueue(int size, char output_file[]) {
	heap(size, -1);
	handle(size, -1);
	output(output_file); // PRINT STUFF TO COUT FOR NOW FOR DEBUGGING
	n = size;
}

void PriorityQueue::findContestant(int k) {
	
}

void PriorityQueue::insertContestant(int k, int s) {
	
}

void PriorityQueue::eliminateWeakest(void) {

}

void PriorityQueue::earnPoints(int k, int p) {

}

void PriorityQueue::losePoints(int k, int p) {

}

void PriorityQueue::showContestants(void) {

}

void PriorityQueue::showHandles(void) {
	for(int k = 0; k < n; k++)
		handle[k] != -1 ?
			cout << "Contestant " << k << " stored in extended heap location " << 
}

void PriorityQueue::showLocation(int k) {

}

void PriorityQueue::crownWinner(void) {

}
