#include <iostream>
#include<string>
#include"HuffmanTree.h"

using namespace std;

int main()
{
	HuffmanTree h;
	string org = "it is test string",
		result = h.encodeString(org);
	
	cout << "The original string: " << org << endl << endl;
	h.showTableCodes();
	cout << "\nThe amount of memory occupied by the original string: " << h.sizeOriginal() << " bits." << endl;
	cout << "\nThe amount of memory occupied by the original string: " << h.sizeEncoded() << " bits." << endl;
	cout << "\nCompression ratio: " << h.compressionRatio() << endl;
	cout << "\nResult after coding: " << result << endl;
	cout << "\nDecoding result: " << h.decodeString(result) << endl;
}