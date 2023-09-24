#pragma once
#include "pch.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void printArray(int arr[], int n, vector<string> &codes) {
	int i;
	for (i = 0; i < n; ++i)
	{
		//cout << arr[i];
	}
	ostringstream os;
	for (i = 0; i < n; ++i) {
		os << arr[i];
	}
	string str(os.str());
	codes.push_back(str);
	//cout << "\n";
}
struct MinHeapNode
{
	char data;
	int frequancy;
	struct MinHeapNode *left, *right;
};
struct MinHeap
{
	int size;
	int capacity;
	struct MinHeapNode** arr;
};
struct MinHeapNode *newNode(char data, int frequancy)
{
	struct MinHeapNode *temp = (struct MinHeapNode *)malloc(sizeof(struct MinHeapNode));
	temp->left = temp->right = NULL;
	temp->data = data;
	temp->frequancy = frequancy;

	return temp;
};
struct MinHeap *createMinH(int capacity)
{
	struct MinHeap *minHeap = (struct MinHeap *)malloc(sizeof(struct MinHeap));
	minHeap->size = 0;
	minHeap->capacity = capacity;
	minHeap->arr = (struct MinHeapNode **)malloc(minHeap->capacity * sizeof(struct MinHeapNode *));
	return minHeap;
}
void swapMinHeapNodes(struct MinHeapNode **a, struct MinHeapNode **b)
{
	struct MinHeapNode *temp = *a;
	*a = *b;
	*b = temp;
}
void minHeaptify(struct MinHeap *minHeap, int idx)
{
	int smallest = idx;
	int left = 2 * idx + 1;
	int right = 2 * idx + 2;

	if (left < minHeap->size && minHeap->arr[left]->frequancy < minHeap->arr[smallest]->frequancy)
		smallest = left;

	if (right < minHeap->size && minHeap->arr[right]->frequancy < minHeap->arr[smallest]->frequancy)
		smallest = right;
	if (smallest != idx)
	{
		swapMinHeapNodes(&minHeap->arr[smallest], &minHeap->arr[idx]);
		minHeaptify(minHeap, smallest);
	}
}
int checkIfSizeOne(struct MinHeap *minHeap)
{
	return(minHeap->size == 1);
}
struct MinHeapNode *extractMinHeap(struct MinHeap *minHeap) {
	struct MinHeapNode *temp = minHeap->arr[0];
	minHeap->arr[0] = minHeap->arr[minHeap->size - 1];

	--minHeap->size;
	minHeaptify(minHeap, 0);

	return temp;
}
void insertMinHeap(struct MinHeap *minHeap, struct MinHeapNode *minHeapNode) {
	++minHeap->size;
	int i = minHeap->size - 1;

	while (i && minHeapNode->frequancy < minHeap->arr[(i - 1) / 2]->frequancy) {
		minHeap->arr[i] = minHeap->arr[(i - 1) / 2];
		i = (i - 1) / 2;
	}

	minHeap->arr[i] = minHeapNode;
}
void buildMinHeap(struct MinHeap *minHeap) {
	int n = minHeap->size - 1;
	int i;

	for (i = (n - 1) / 2; i >= 0; --i)
		minHeaptify(minHeap, i);
}
int isLeaf(struct MinHeapNode *root) {
	return !(root->left) && !(root->right);
}
struct MinHeap *createAndBuildMinHeap(char item[], int freq[], int size) {
	struct MinHeap *minHeap = createMinH(size);

	for (int i = 0; i < size; ++i)
		minHeap->arr[i] = newNode(item[i], freq[i]);

	minHeap->size = size;
	buildMinHeap(minHeap);

	return minHeap;
}
struct MinHeapNode *buildHfTree(char item[], int freq[], int size) {
	struct MinHeapNode *left, *right, *top;
	struct MinHeap *minHeap = createAndBuildMinHeap(item, freq, size);

	while (!checkIfSizeOne(minHeap)) {
		left = extractMinHeap(minHeap);
		right = extractMinHeap(minHeap);
		top = newNode('$', left->frequancy + right->frequancy);
		top->left = left;
		top->right = right;
		insertMinHeap(minHeap, top);
	}
	return extractMinHeap(minHeap);
}
void printHuffmanCodes(struct MinHeapNode *root, int arr[], int top, vector<string> &codes, vector<char> &characters) {
	if (root->left) {
		arr[top] = 0;
		printHuffmanCodes(root->left, arr, top + 1, codes, characters);
	}

	if (root->right) {
		arr[top] = 1;
		printHuffmanCodes(root->right, arr, top + 1, codes, characters);
	}
	if (isLeaf(root)) {
		//cout << root->data << " | ";
		printArray(arr, top, codes);
		characters.push_back(root->data);
	}
}
void HuffmanCodes(char item[], int freq[], int size, vector<string> &codes, vector<char> &characters) {
	struct MinHeapNode *root = buildHfTree(item, freq, size);
	int arr[100], top = 0;
	printHuffmanCodes(root, arr, top, codes, characters);
}