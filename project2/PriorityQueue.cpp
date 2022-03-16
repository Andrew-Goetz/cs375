#include <assert.h>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

#include "PriorityQueue.h"

using namespace std;

PriorityQueue::PriorityQueue(int size, char output_file[]) {
	n = 0; //number of elements currently in vectors, not including invalid -1 elements
	vector<Contestant> heap(n, Contestant{-1, -1});
	vector<int> handle(n, -1);
	ofstream output(output_file);
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
		handle.push_back(-1); //ensure handle[k] is allocated
	}
	if(handle[k] != -1) {
		cout << "Contestant " << k << " is already in the extended heap: cannot insert.\n";
		return;
	}
	if(n+1 == heap.size()) {
			cout << "Contestant " << k << " could not be inserted because the extended heap is full.\n";
			return;
	}
	n++;
	heap[n].id = k;
	heap[n].score = s;
	handle[k] = n;
	minHeapify(parent(k), true);
	cout << "Contestant " << k << " inserted with initial score " << s << ".\n";
}

void PriorityQueue::eliminateWeakest(void) {
	if(n == 0) {
		cout << "No contestant can be eliminated since the extended heap is empty.\n";
		return;
	}
	cout << "Contestant " << heap[1].id << " with current lowest score " << heap[1].score << " eliminated.\n";
	heapExchange(1, n);
	handle[heap[n].id] = -1;
	heap[n].id = -1;
	heap[n].score = -1;
	n--;
	minHeapify(1, false);
}

void PriorityQueue::earnPoints(int k, int p) {
	if(handle[k] == -1) {
		cout << "Contestant " << k << " is not in the extended heap.\n";
		return;
	}
	heap[handle[k]].score += p;
	minHeapify(handle[k], false);
	cout << "Contestant " << k << "'s score increased by " << p << " points to " << heap[handle[k]].score << ".\n";
}

void PriorityQueue::losePoints(int k, int p) {
	if(handle[k] == -1) {
		cout << "Contestant " << k << " is not in the extended heap.\n";
		return;
	}
	heap[handle[k]].score -= p;
	minHeapify(parent(handle[k]), true);
	cout << "Contestant " << k << "'s score decreased by " << p << " points to " << heap[handle[k]].score << ".\n";
}

void PriorityQueue::showContestants(void) {
	for(int i = 1; i < n; i++) {
		cout << "Contestant " << heap[i].id << " in extended heap location " << i << " with score " << heap[i].score << ".\n";
	}
}

void PriorityQueue::showHandles(void) {
	for(int k = 1; k < n; k++) { //@TODO need question answered about this one
		if(handle[k] != -1) {
			cout << "Contestant " << k << " stored in extended heap location " << handle[k] << ".\n";
		} else {
			cout << "There is no Contestant " << k << " in the extended heap: handle[" << k << "] = -1.\n";
		}
	}
}

void PriorityQueue::showLocation(int k) {
	if(handle[k] == -1) {
		cout << "There is no Contestant " << k << " in the extended heap: handle[" << k << "] = -1.\n";
	} else {
		cout << "Contestant " << k << " stored in extended heap location " << handle[k] << ".\n";
	}
}

void PriorityQueue::crownWinner(void) {
	for(int k = 1; k < n-1; k++) {
		eliminateWeakest();
	}
	assert(heap[1].id != -1 && heap[2].id == -1);
	cout << "Contestant " << heap[1].id << " wins with score " << heap[1].score << "!\n";
}

// assumes value at index i is already in handle vector
void PriorityQueue::minHeapify(int i, bool up) {
	int l = i*2;
	int r = i*2+1;
	assert(l <= n);
	//assert(heap[r].score != -1);

	int min;
	(l <= n && heap[i].score > heap[l].score) ? min = l : min = i;
	if(r <= n && heap[min].score > heap[r].score) min = r;

	if(min != i) {
		heapExchange(i, min);
		up ? minHeapify(parent(min), true) : minHeapify(min, false);
	}
}

void PriorityQueue::heapExchange(int i, int j) {
	handle[heap[i].id] = j;
	handle[heap[j].id] = i;
	Contestant temp = heap[i];
	heap[i] = heap[j];	
	heap[j] = temp;
}

int PriorityQueue::parent(int i) {
	return i != 1 ? (int)floor((double)i/2.0) : 1;
}
