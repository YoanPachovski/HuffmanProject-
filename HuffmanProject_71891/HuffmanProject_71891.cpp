// HuffmanProject_71891.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "Encoding.h"
#include "Decoding.h"

using namespace std;

void menu()
{
	string forTyping;
	cout << "Write a word you want to compress and must be atleast 2 symbols:";
	ofstream MyFile("FileToCompress.txt");
	string newWord;
	cin >> newWord;
	MyFile << newWord;
	MyFile.close();
	/*std::ofstream ofs;            // Ако искаш декомпресирания файл от преди да се изчисти 
	ofs.open("FileToDecompress.txt", std::ofstream::out | std::ofstream::trunc); 
	ofs.close();*/
	cout << "Menu Options:" << endl;
	cout << "encode: encodes the word from the file and saves it to FileToDecompress.txt" << endl;
	cout << "decode: decodes the decimal numbers from FileToDecompress.txt and prints it on the console" << endl;
	cout << "debug: prints the decimal numbers needed for decoding" << endl;
	cout << "powerOfComp: prints the bits from the starting word , the encoded one and the bits saved in the proccess:" << endl;
	cout << "changeWord: Write new sentence or word you want to encode" << endl;
	cout << "help: prints the menu options" << endl;
	cout << "exit: exits the program" << endl;
	while (forTyping!="exit")
	{
		cin >> forTyping;
		if (forTyping=="encode")
		{
			encode("FileToCompress.txt");
			cout << endl;
		}
		else if (forTyping == "decode")
		{
			decode("FileToDecompress.txt");
			cout << endl;
		}
		else if (forTyping == "debug")
		{
			debug("FileToCompress.txt");
			cout << endl;
			cout << endl;
		}
		else if (forTyping == "powerOfComp")
		{
			powerOfCompression("FileToCompress.txt");
			cout << endl;
		}
		else if (forTyping == "changeWord")
		{
			cout << "Write a new word you want to compress:";
			ofstream MyFile("FileToCompress.txt");
			string newWord;
			cin >> newWord;
			MyFile << newWord;
			MyFile.close();
		}
		else if (forTyping == "help")
		{
			cout << "Menu Options:" << endl;
			cout << "encode: encodes the word from the file and saves it to FileToDecompress.txt" << endl;
			cout << "decode: decodes the decimal numbers from FileToDecompress.txt and prints it on the console" << endl;
			cout << "debug: prints the decimal numbers needed for decoding" << endl;
			cout << "powerOfComp: prints the bits from the starting word , the encoded one and the bits saved in the proccess:" << endl;
			cout << "changeWord: Write new sentence or word you want to encode" << endl;
			cout << "help: prints the possible actions you can make" << endl;
			cout << "exit: exits the program" << endl;
			cout << endl;
		}
    }
}
int main()
{
	menu();
}
