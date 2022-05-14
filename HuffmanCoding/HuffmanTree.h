#pragma once
#include<iostream>
#include "RBT.h"

class EoHuffmanTree {
public:
	char sym; // Symbol
	int foo; // Frequency of occurrence
	List<bool>* codes;
	EoHuffmanTree* parent;
	EoHuffmanTree* left;
	EoHuffmanTree* right;

	EoHuffmanTree() {
		this->sym = NULL;
		this->foo = 0;
		this->codes = new List<bool>();
		this->parent = NULL;
		this->left = NULL;
		this->right = NULL;
	}
};

class HuffmanTree {
private:
	void analysis(string intial) {
		for (char c : intial) {
			EoList<EoHuffmanTree*>* cur = listLeaf->head;
			bool isHad = 0;

			while (cur != NULL) {
				if (cur->data->sym == c) {
					isHad = 1;
					cur->data->foo += 1;
					break;
				}
				else cur = cur->next;
			}

			if (isHad == 0) {
				EoHuffmanTree* newLeaf = new EoHuffmanTree();
				newLeaf->sym = c;
				newLeaf->foo = 1;
				listLeaf->pushback(newLeaf);
			}
		}
	}

	EoHuffmanTree* minFoo() {
		if (listLeaf->head == NULL) throw logic_error("List leaf is empty!");
		else {

			EoList<EoHuffmanTree*>* cur = listLeaf->head;
			EoList<EoHuffmanTree*>* minFoo = cur;

			while (cur != NULL) {
				if (minFoo->data->foo >= cur->data->foo) minFoo = cur;
				cur = cur->next;
			}

			return minFoo->data;
		}
	}

	void buildTree() {
		if (listLeaf->head == NULL) throw logic_error("List leaf is empty! Can' t build!!!");
		else {
			List<EoHuffmanTree*>* tmp = new List<EoHuffmanTree*>();
			EoList<EoHuffmanTree*>* cur = listLeaf->head;

			while (cur != NULL) {
				tmp->pushback(cur->data);
				cur = cur->next;
			}

			while (listLeaf->head != listLeaf->tail) {
				EoHuffmanTree* min1 = minFoo();
				listLeaf->pop(minFoo());
				EoHuffmanTree* min2 = minFoo();
				listLeaf->pop(minFoo());
				EoHuffmanTree* newNode = new EoHuffmanTree();
				newNode->foo = min1->foo + min2->foo;
				min1->parent = newNode;
				min2->parent = newNode;
				newNode->left = min1;
				newNode->right = min2;
				listLeaf->pushback(newNode);
			}

			root = listLeaf->head->data;
			listLeaf = tmp;
		}
	}

	

public:
	EoHuffmanTree* root;
	List<EoHuffmanTree*>* listLeaf;

	void encode(string intial) {
		HuffmanTree();
		analysis(intial);
		buildTree();

		EoList<EoHuffmanTree*>* cur = listLeaf->head;

		while (cur != NULL) {
			EoHuffmanTree* tmp = cur->data;

			while (tmp->parent != NULL) {
				if (tmp == tmp->parent->left) cur->data->codes->pushfront(1);
				else cur->data->codes->pushfront(0);
				tmp = tmp->parent;
			}

			cur = cur->next;
		}

	}

	string encodeString(string intial) {
		HuffmanTree();
		encode(intial);

		string result;
		size_t rest = intial.length();

		for (char c : intial) {
			EoList<EoHuffmanTree*>* cur = listLeaf->head;
			while (cur != NULL) {
				if (cur->data->sym == c) {
					EoList<bool>* tmp = cur->data->codes->head;
					while (tmp != NULL) {
						if (tmp->data == 1) result += "1";
						else result += "0";
						tmp = tmp->next;
					}
					rest --;
					if (rest != 0) result += " ";
					break;
				}
				else cur = cur->next;
			}
		}
		return result;
	}

	void showTableCodes() {
		if (listLeaf->head == NULL) throw invalid_argument("Nothing coded!");
		else {
			cout << "Encoding table: <'Symbol'- (Frequency of occurrence): Code>\n\n";
			EoList<EoHuffmanTree*>* cur = listLeaf->head;
			while (cur != NULL) {
				cout <<"'" << cur->data->sym << "'" << "- (" << cur->data->foo << "): ";
				EoList<bool>* tmp = cur->data->codes->head;
				while (tmp != NULL) {
					if (tmp->data == 1)  cout << "1";
					else cout << "0";
					tmp = tmp->next;
				}
				cout << endl;
				cur = cur->next;
			}
		}
	}

	size_t sizeOriginal() {
		if (listLeaf->head == NULL) throw invalid_argument("Nothing coded!");
		else return static_cast<size_t>(root->foo) * 8;
	}

	size_t sizeEncoded() {
		if (listLeaf->head == NULL) throw invalid_argument("Nothing coded!");
		else {
			size_t newSize = 0;

			EoList<EoHuffmanTree*>* cur = listLeaf->head;
			while (cur != NULL) {
				newSize += cur->data->foo * cur->data->codes->size;
				cur = cur->next;
			}

			return newSize;
		}
	}

	double compressionRatio() {
		return static_cast<double>(sizeOriginal()) / static_cast<double>(sizeEncoded());
	}

	string decodeString(string encoded) {
		if (listLeaf->head == NULL) throw invalid_argument("Nothing coded!");
		else {
			string decode;
			EoHuffmanTree* cur = root;
			for (char c : encoded) {
				switch (c)
				{
				case '1':
					if (cur->left == NULL) throw invalid_argument("Error codes!");
					else cur = cur->left;
					break;
				case '0':
					if (cur->right == NULL) throw invalid_argument("Error codes!");
					else cur = cur->right;
					break;
				case ' ':
					if (cur->sym == NULL) throw invalid_argument("Error codes!");
					else {
						decode += cur->sym;
						cur = root;
					}
					break;
				default:
					throw invalid_argument("Error codes!");
					
				}
			}
			if (cur->sym == NULL) throw invalid_argument("Error codes!");
			else decode += cur->sym;
			return decode;
		}
	}

	HuffmanTree() {
		this->root = NULL;
		this->listLeaf = new List<EoHuffmanTree*>();
	}
};