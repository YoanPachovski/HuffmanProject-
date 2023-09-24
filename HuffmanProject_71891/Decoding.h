#pragma once
#include "pch.h"
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <sstream>
#include "DataForHuffmanTree.h"

using namespace std;

string convertStrtoArr(string str, string &binaryString)
{
	int str_length = str.length();
	int arr[100] = {};
	int j = 0, i, sum = 0;

	for (i = 0; str[i] != '\0'; i++) {

		if (str[i] == ',')
			continue;
		if (str[i] == ' ') {
			j++;
		}
		else {
			arr[j] = arr[j] * 10 + (str[i] - 48);
		}
	}
	for (i = 0; i <= j; i++) {
		std::string s = std::bitset<8>(arr[i]).to_string();
		binaryString = binaryString + s;

	}
	return binaryString;
}
void popAddedZeros(int huffmanRarSize, string &endcodedString)
{
	while (endcodedString.size() > huffmanRarSize)
	{
		endcodedString.pop_back();
	}
}
string decode_file(char item[], int freq[], int size, string s)
{
	struct MinHeapNode *root = buildHfTree(item, freq, size);
	string ans = "";
	struct MinHeapNode* curr = root;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '0')
			curr = curr->left;
		else
			curr = curr->right;

		if (curr->left == NULL and curr->right == NULL)
		{
			ans += curr->data;
			curr = root;
		}
	}
	// cout<<ans<<endl; 
	return ans + '\0';
}

void decode(string FileName)
{

	std::ifstream f(FileName);
	f.seekg(0, ios::end);
	if (f.tellg() == 0) {
		cout << "File is empty, please use the encode function first" << endl;
		f.close();
	}
	else 
	{
		std::ifstream f(FileName);
		string decimalNumbers;
		string chars;
		string freqForChars;
		string neededSizeForAllArrays;
		string sizeOfHUffManRar;
		if (f.is_open()) {
			getline(f, decimalNumbers);
			getline(f, chars);
			getline(f, freqForChars);
			getline(f, neededSizeForAllArrays);
			getline(f, sizeOfHUffManRar);
		}
		f.close();
		string encodedString;
		convertStrtoArr(decimalNumbers, encodedString);
		stringstream neededSize(neededSizeForAllArrays);
		int sizeNeeded = 0;
		neededSize >> sizeNeeded;
		stringstream huffManRarSize(sizeOfHUffManRar);
		int huffmanRaredSize = 0;
		huffManRarSize >> huffmanRaredSize;
		char items[100];
		int freq[100];
		for (int i = 0; i < sizeNeeded; i++)
		{
			items[i] = chars[i];
		}
		for (int i = 0; i < sizeNeeded; i++)
		{
			stringstream str;
			str << freqForChars[i];
			int x;
			str >> x;
			freq[i] = x;
		}
		popAddedZeros(huffmanRaredSize, encodedString);
		string decodedString = decode_file(items, freq, sizeNeeded, encodedString);
		cout << "\nDecoded Huffman Word:\n" << decodedString << endl;
	}
}