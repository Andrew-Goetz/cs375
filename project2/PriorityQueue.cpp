#include <iostream>
#include <string>
#include <cmath>
#include <vector>

#include "PriorityQueue.h"

using namespace std;

PriorityQueue::PriorityQueue(int size, char output_file[]) {
	n = size+1;
	for(int i = 0; i < n; i++) heap.push_back(Contestant{-1, -1});
	handle(n, -1);
	output(output_file); // PRINT STUFF TO COUT FOR NOW FOR DEBUGGING
}

void PriorityQueue::findContestant(int k) {
	if(handle[k] != -1) {
		cout << "Contestant " << k << " is in the extended heap with score " << heap[handle[k]].score << ".\n";
	} else {
		cout << "Contestant " << k << " is not in the extended heap.\n";
	}
}

void PriorityQueue::insertContestant(int k, int s) {
	for(int i = handle.size(); i <= k; i++) {

	}
	if(handle[k] != -1) {
		cout << "Contestant " << k << " is already in the extended heap: cannot insert.\n";
		return;
	}

	for(int i = 1; i < n; i++) {
		if(heap[i].score == -1) break;
		if(i == n-1) {
			cout << "Contestant " << k << " could not be inserted because the extended heap is full.\n";
			return;
		}
	}

	for(int i = 1; i < (int)floor((double)n/2.0); i++) {
		
	}
	minHeapify(k);
	cout << "Contestant " << k << " inserted with initial score " << s << ".\n";
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
	for(int k = 1; k < n; k++) {
		if(handle[k] != -1) {
			cout << "Contestant " << k << " stored in extended heap location " << handle[k] << ".\n";
		} else {
			cout << "There is no Contestant " << k << " in the extended heap: handle[" << k << "] = -1.\n";
		}
	}
}

void PriorityQueue::showLocation(int k) {

}

void PriorityQueue::crownWinner(void) {

}

void PriorityQueue::minHeapify(int index) {

}
