#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *swap1, int *swap2);
int bubbleSort(int arr[], int n);
int selectionSort(int arr[], int n);
int heapSort(int arr[], int n);
void heapify(int arr[], int n, int i);
void printToFile(FILE *fp, int arr[], int size);

int main() {

	FILE *fp = fopen("random.txt", "r");

	FILE *bubbleOut = fopen("bubble.txt", "w");
	FILE *selectionOut = fopen("selection.txt", "w");
	FILE *heapOut = fopen("heap.txt", "w");

	FILE *comparison = fopen("comparison.txt", "w");

	int arrBubble[50000];
	int arrSelection[50000];
	int arrHeap[50000];

	if (fp == NULL) {
		printf("failed to open random.txt, maybe try $ make genrand\n");
		exit(100);
	}

	int data;
	int i = 0;

	while (fscanf(fp, "%d", &data) == 1) {
		arrBubble[i] = data;
		arrSelection[i] = data;
		arrHeap[i] = data;
		i++;
	}

	
	int bubbleLoops = bubbleSort(arrBubble, 50000);
	int selectionLoops = selectionSort(arrSelection, 50000);
	int heapLoops = heapSort(arrHeap, 50000);

	printToFile(bubbleOut, arrBubble, i);
	printToFile(selectionOut, arrSelection, i);
	printToFile(heapOut, arrHeap, i);

	fprintf(comparison, "%12s\t%12s\t%12s\n%12d\t%12d\t%12d\n", "Bubble", "Selection", "Heap", bubbleLoops, selectionLoops, heapLoops);

}

void swap(int *swap1, int *swap2) {

	int temp = *swap1;
	*swap1 = *swap2;
	*swap2 = temp;

}

int bubbleSort(int arr[], int n) { 

	int loops = 0;

	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (arr[j] > arr[j+1]) 
			swap(arr + j, arr + j + 1);
			loops++;
		}
	}

	return loops;

}

int selectionSort(int arr[], int n) {

	int loops = 0;

	for (int i = 0; i < n-1; i++) {

		int min_idx = i; 

		for (int j = i+1; j < n; j++) {
			if (arr[j] < arr[min_idx]) {
				min_idx = j;
				loops++;
			}
		}

		swap(arr + min_idx, arr + i); 

	}

	return loops;
	
}

int heapSort(int arr[], int n) {

	int loops = 0;

	for (int i = n / 2 - 1; i >=0; i--) {
		heapify(arr, n, i);
		loops++;
	}

	for (int i = n - 1; i >= 0; i--) {
		swap(arr, arr + i);
		heapify(arr, i, 0);
		loops++;
	}

	return loops;

}

void heapify(int arr[], int n, int i) {

	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if (l < n && arr[l] > arr[largest]) largest = l;

	if (r < n && arr[r] > arr[largest]) largest = r;

	if (largest != i) {
		swap(arr + i, arr + largest);
		heapify(arr, n, largest);
	}

}

void printToFile(FILE *fp, int arr[], int size) {

	for (int i = 0; i < size; i++) fprintf(fp, "%d\n", arr[i]);

}