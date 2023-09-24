#pragma once
#include "pch.h"
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include "DataForHuffmanTree.h"

using namespace std;

string cutTheString(string &decimalNumbers, string Code)
{
	while (!Code.empty())
	{
		string binaryNum = "";
		binaryNum = Code.substr(0, 8);
		Code.erase(0, 8);
		while (binaryNum.size() < 8)
		{
			binaryNum = binaryNum + '0';
		}
		int number = stoi(binaryNum, 0, 2);
		decimalNumbers = decimalNumbers + to_string(number) + ' ';
	}
	return decimalNumbers;
}
void selectionSort(int a[], int n, char b[]) {
	int i, j, min, temp;
	for (i = 0; i < n - 1; i++) {
		min = i;
		for (j = i + 1; j < n; j++)
			if (a[j] < a[min])
				min = j;
		temp = b[i];
		b[i] = b[min];
		b[min] = temp;
		temp = a[i];
		a[i] = a[min];
		a[min] = temp;
	}
}
void encode(std::string FileName)
{
	string word;
	ifstream MyReadFile(FileName);
	while (getline(MyReadFile, word)) {
		cout << word << endl;
	}
	MyReadFile.close();
	vector<char> arr(word.begin(), word.end());
	map<char, int> countfrequencies;

	for_each(arr.begin(), arr.end(), [&countfrequencies](char& i) { countfrequencies[i]++; });

	std::vector<int> key, value;
	for (std::map<char, int>::iterator it = countfrequencies.begin(); it != countfrequencies.end(); it++) {
		key.push_back(it->first);
		value.push_back(it->second);
	}
	int sizeOfAllArrays = size(key);
	int frequence[100];
	copy(value.begin(), value.end(), frequence);
	char symbols[100];
	copy(key.begin(), key.end(), symbols);
	selectionSort(frequence, sizeOfAllArrays, symbols);
	cout << endl;
	vector<string>codes;
	vector<char> characters;
	HuffmanCodes(symbols, frequence, sizeOfAllArrays, codes, characters);
	for (int i = 0; i < characters.size(); ++i)
	{
		std::cout << characters[i] << '|';
		std::cout << codes[i];
		cout << endl;
	}
	string HuffmanRar = "";
	for (int i = 0; i < word.size(); i++)
	{
		for (int j = 0; j < characters.size(); j++)
		{
			if (word[i] == characters[j])
			{
				HuffmanRar = HuffmanRar + codes[j];
			}
		}
	}
	cout << endl;
	cout << HuffmanRar << std::endl;
	string numbers;
	cutTheString(numbers, HuffmanRar);
	ofstream NewFile("FileToDecompress.txt");
	NewFile << numbers << std::endl;
	for (int i = 0; i < sizeOfAllArrays; ++i)
	{
		NewFile << symbols[i];
	}
	NewFile << endl;
	for (int i = 0; i < sizeOfAllArrays; ++i)
	{
		NewFile << frequence[i];
	}
	NewFile << endl;
	NewFile << sizeOfAllArrays << endl;
	NewFile << HuffmanRar.size();
	NewFile.close();
}
void debug(std::string FileName)
{
	string word;
	ifstream MyReadFile(FileName);

	getline(MyReadFile, word);
	MyReadFile.close();
	vector<char> arr(word.begin(), word.end());
	map<char, int> countfrequencies;

	for_each(arr.begin(), arr.end(), [&countfrequencies](char& i) { countfrequencies[i]++; });

	std::vector<int> key, value;
	for (std::map<char, int>::iterator it = countfrequencies.begin(); it != countfrequencies.end(); it++) {
		key.push_back(it->first);
		value.push_back(it->second);
	}
	int sizeOfAllArrays = size(key);
	int frequence[100];
	copy(value.begin(), value.end(), frequence);
	char symbols[100];
	copy(key.begin(), key.end(), symbols);
	selectionSort(frequence, sizeOfAllArrays, symbols);
	vector<string>codes;
	vector<char> characters;
	HuffmanCodes(symbols, frequence, sizeOfAllArrays, codes, characters);
	string HuffmanRar = "";
	for (int i = 0; i < word.size(); i++)
	{
		for (int j = 0; j < characters.size(); j++)
		{
			if (word[i] == characters[j])
			{
				HuffmanRar = HuffmanRar + codes[j];
			}
		}
	}
	cout << endl;
	string numbers;
	cout << "These are the binary numbers turned into decimal ones: " <<cutTheString(numbers, HuffmanRar);
}
void powerOfCompression(std::string FileName)
{
	string word;
	ifstream MyReadFile(FileName);

	getline(MyReadFile, word);
	MyReadFile.close();
	vector<char> arr(word.begin(), word.end());
	map<char, int> countfrequencies;

	for_each(arr.begin(), arr.end(), [&countfrequencies](char& i) { countfrequencies[i]++; });

	std::vector<int> key, value;
	for (std::map<char, int>::iterator it = countfrequencies.begin(); it != countfrequencies.end(); it++) {
		key.push_back(it->first);
		value.push_back(it->second);
	}
	int sizeOfAllArrays = size(key);
	int frequence[100];
	copy(value.begin(), value.end(), frequence);
	char symbols[100];
	copy(key.begin(), key.end(), symbols);
	selectionSort(frequence, sizeOfAllArrays, symbols);
	cout << endl;
	vector<string>codes;
	vector<char> characters;
	HuffmanCodes(symbols, frequence, sizeOfAllArrays, codes, characters);
	string HuffmanRar = "";
	for (int i = 0; i < word.size(); i++)
	{
		for (int j = 0; j < characters.size(); j++)
		{
			if (word[i] == characters[j])
			{
				HuffmanRar = HuffmanRar + codes[j];
			}
		}
	}
	cout << endl;
	string numbers;
	cutTheString(numbers, HuffmanRar);
	cout << word.size()*8 <<" bits is the size of the starting word" << std::endl;
	cout << HuffmanRar.size() <<" bits is the size of the encoded word" << std::endl;
	int bytesSaved = word.size()*8 - HuffmanRar.size();
	cout << bytesSaved << " bits have been saved by using the Huffman Tree encoding" << std::endl;
}
