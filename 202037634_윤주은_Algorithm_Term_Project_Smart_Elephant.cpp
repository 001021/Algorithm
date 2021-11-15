// Implement by Dynamic Programming
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#define MAX 1024

typedef struct elephant
{
	int weight;
	int iq;
	int index;
} elephant;

void print_lds(elephant* data, int* v, int seq) {
	if (v[seq] > 0) {
		// Get the entire array by moving to the corresponding index while going backward.
		print_lds(data, v, v[seq]);
	}
	printf("%d\n", data[seq].index);
}

// Sorting elephants by weight.
void sort_by_weight(elephant* e, int index) {
	for (int i = 0; i < index; i++) {
		for (int j = 0; j < index; j++) {
			if (e[i].weight < e[j].weight) {
				elephant t = e[i];
				e[i] = e[j];
				e[j] = t;
			}
		}
	}
}


int main() {
	int index = 0;

	elephant e[MAX];

	printf("Type elephant data(weight, IQ) (end to type 0 0)\n");

	// initializing
	while (true) {
		scanf("%d %d", &e[index].weight, &e[index].iq);
		if (e[index].weight == 0) break;
		e[index].index = index + 1;
		index++;		
	}

	sort_by_weight(e, index);

	int seq[MAX]; // Store the length of the longest array
	int V[MAX]; // Actual subsequence
	int max = 0; // Stores the largest number in the seq array

	for (int i = 0; i < index; i++) {
		seq[i] = 1; // Initialize the length of the longest array to 1.
	}

	for (int i = 1; i <= index; i++) {
		for (int j = 1; j < i; j++) {
			// 1. The IQ of the jth elephant is greater than the IQ of the ith elephant, AND
			// 2. The length of the jth LDS + 1 is bigger than the length of the ith LDS, AND
			// 3. The weight of the jth elephant is less than the weight of the ith elephant
			if (e[j].iq > e[i].iq && seq[j] + 1 > seq[i] && e[j].weight < e[i].weight) {
				seq[i] = seq[j] + 1;
				V[i] = j; // Storing index int actual subsequence array
			}
		}
	}

	int max_seq = 1; // Find the LDS

	for (int i = 0; i < index; i++) {
		if (max < seq[i]) {
			max = seq[i];
			max_seq = i;
		}
	}

	printf("%d\n", max);
	print_lds(e, V, max_seq);
	return 0;
}