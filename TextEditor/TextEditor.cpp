#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int length = 26;
string* arr = new string[10];
string sentence = "\0";
string mid = "";
int index = 0;

void saveinfiles();
void EnterData();
bool AutoCompletion();

void  DataSavingIntoFile();
void GettingDataFromFile();
void Document();
string getHalf(string data) {

	string phrase = "";

	for (int i = 0; i < data.length(); i++) {

		if (data[i] != ' ') {
			phrase += data[i];
		}

		if (data[i + 1] == data.length()) {
			return phrase;
		}
		else if (data[i + 1] == ' ') {
			sentence = sentence + " " + phrase;
			phrase = "";
		}

	}


	return phrase;
}


bool AutoCompletion() {

	char data;

	system("cls");



	cout << sentence << " " << mid;



	cout << "\t" << "[ ";

	for (int i = 0; i < 10; i++) {

		if (arr[i] == "\0") {
			break;
		}

		cout << arr[i] << " , ";
	}

	cout << "]";

	cout << endl << endl;



	cout << "Enter your word ";
	cin >> data;



	if (data == '/') {

		if (index < 9 && arr[index + 1] != "\0") {

			index++;

			mid = arr[index];

		}
		else {
			index = 0;
			mid = arr[index];
		}



		AutoCompletion();

	}


	else if (data == ';') {

		sentence = sentence + " " + arr[index];

		return true;
	}
	else if (data == '=') {
		return false;
	}

}

void DataSavingIntoFile() {

	ofstream output("Output.txt");

	if (output.is_open()) {

		output << sentence << ".";

		output.close();

		cout << endl << "File Saved Successfull !" << endl << endl;
	}

}

void GettingDataFromFile() {

	sentence = "";

	ifstream inputFile("Output.txt");

	char c;

	if (inputFile.is_open()) {

		inputFile.get(c);

		while (!inputFile.eof()) {

			sentence += c;
			inputFile.get(c);

			if (inputFile.eof()) {
				break;
			}

		}
	}

	inputFile.close();

}

char getCharacterFromIndex(int Position) {

	char alphabets = 'a';

	for (int i = 0; i < Position; i++) {

		alphabets++;

	}

	return alphabets;

}
void Document() {

	bool carryOn = true;

	do {

		system("cls");


		cout << sentence << " ";



		EnterData();


		carryOn = AutoCompletion();

	} while (carryOn);

}


int getIndexFromChar(char alphabet) {

	char smallAlphabet = 'a', capitalAlphabet = 'A';


	for (int i = 0; i < length; i++) {

		if (alphabet == smallAlphabet++ || alphabet == capitalAlphabet++) {
			return i;
		}
	}
}


class Node {

public:

	bool isfull = false;
	Node* children[26];

	Node() {

		for (int i = 0; i < 26; i++) {
			children[i] = NULL;
		}

		isfull = false;
	}

};

class TriTree {

public:

	Node* root;

	TriTree() {
		root = new Node();
	}

	void insertion(string phrase) {

		Node* temp = root;

		for (int i = 0; i < phrase.length(); i++) {

			char alphabet = phrase[i];

			if (temp->children[getIndexFromChar(alphabet)] == NULL) {
				temp->children[getIndexFromChar(alphabet)] = new Node();

			}

			temp = temp->children[getIndexFromChar(alphabet)];

		}

		temp->isfull = true;

	}

	string* getSuggestions(string alphabet) {

		string* ArrayOfAlphabets = new string[10];



		for (int i = 0; i < 10; i++) {
			ArrayOfAlphabets[i] = "\0";
		}

		int index = 0;

		Node* current = root;

		for (int i = 0; i < alphabet.length(); i++) {

			char letter = alphabet[i];

			if (current->children[getIndexFromChar(letter)] == NULL) {
				return ArrayOfAlphabets;
			}

			current = current->children[getIndexFromChar(letter)];

		}

		for (int i = 0; i < length; i++) {

			if (current->children[i] != NULL) {

				if (current->children[i]->isfull) {

					if (index > 9) {
						return ArrayOfAlphabets;
					}

					ArrayOfAlphabets[index++] = alphabet + getCharacterFromIndex(i);

				}
				else {

					Node* middlenode = current->children[i];

					for (int j = 0; j < length; j++) {

						if (middlenode->children[j] != NULL) {

							if (middlenode->children[j]->isfull) {

								if (index > 9) {
									return ArrayOfAlphabets;
								}

								ArrayOfAlphabets[index++] = alphabet + getCharacterFromIndex(i) + getCharacterFromIndex(j);
							}

						}

					}

				}
			}
		}

		return ArrayOfAlphabets;

	}

}
trieTree;

void EnterData() {

	mid = "";
	cin.ignore();
	cin.clear();
	getline(cin, mid);

	mid = getHalf(mid);

	arr->clear();
	arr = trieTree.getSuggestions(mid);
	index = 0;

}

//////// hufman ///

struct SNode {

	int data;
	SNode* next;

	SNode() {
		data = 0;
		next = NULL;
	}

};

class Mystack {

	SNode* top = NULL;

public:

	Mystack() {
		top = NULL;
	}

	bool is_empty() {

		if (top == NULL)
			return true;
		else
			return false;
	}

	void push(int num) {

		SNode* newNode = new SNode;
		newNode->data = num;
		newNode->next = top;
		top = newNode;
	}

	int pop() {

		int num = -1;
		if (is_empty()) {
			cout << "STACK IS FULL" << endl;
		}
		else {
			SNode* temp = new SNode;
			temp = top;
			num = top->data;
			top = top->next;
			delete temp;
			temp = nullptr;
		}
		return num;
	}

}myObj;

struct qNode {

	int frequency;
	char data = NULL;
	int weight;
	qNode* left;
	qNode* right;
	qNode* parent;
	qNode* next;

};

qNode* qObj = new qNode;

class Queue {

	qNode* front;
	qNode* rear;
	int count = 0;

public:

	Queue() {
		front = NULL;
		rear = NULL;
	}

	bool empty() {
		if (front == NULL)
			return true;
		else
			return false;
	}
	int nodeCount() {
		return count;
	}
	void enqueue(qNode* root) {
		qNode* temp = new qNode;
		temp = root;
		if (empty()) {
			rear = temp;
			front = temp;
			++count;
		}
		else {
			int count1 = 0;
			qNode* curr = front;
			while (curr != NULL) {
				if (curr->data == temp->data && temp->data != '@') {
					curr->frequency += 1;
					++count1;
				}
				curr = curr->next;
			}
			if (count1 == 0) {
				rear->next = temp;
				rear = temp;
				++count;
			}
			sort();
		}
	}
	void sort() //priority queue setting
	{
		if (empty()) {
			cout << "QUEUE IS EMPTY" << endl;
			return;
		}
		else {
			qNode* temp;
			qNode* current;
			temp = front;
			while (temp->next) {
				current = temp->next;
				while (current) {
					if (temp->frequency > current->frequency) {
						swap(current->data, temp->data);
						swap(current->frequency, temp->frequency);
						swap(current->left, temp->left);
						swap(current->parent, temp->parent);
						swap(current->right, temp->right);
					}
					current = current->next;
				}
				temp = temp->next;
			}
		}
	}
	qNode* dequeue() {
		qNode* temp = new qNode;
		if (empty()) {
			cout << "QUEUE is empty" << endl;
		}
		else {
			--count;
			temp = front;
			front = front->next;
		}
		return temp;
	}
	void Q_display() //in case of queue display
	{
		if (empty()) {
			cout << "QUEUE IS EMPTY" << endl;
		}
		else {
			qNode* curr;
			curr = front;
			cout << "The data in the queue: " << endl;
			while (curr != NULL) {
				if (curr->data != '@')
					cout << curr->data << " : " << curr->frequency << " : " << curr->weight << endl;
				curr = curr->next;
			}
		}
	}
};

bool sPush(qNode* root, char key) //push 0 and 1 according to left and right 
{
	if (root != NULL) {
		if (root->data == key) {
			return true;
		}

		if (sPush(root->right, key)) {
			myObj.push(1);
			return true;
		}
		else if (sPush(root->left, key)) {
			myObj.push(0);
			return true;
		}
	}
	return false;
}

void encodeinggg(Queue obj) {

	qNode* root;
	qNode* Left;
	qNode* Right;

	while (obj.nodeCount() != 1) // when the final tree is formed in the queue
	{
		root = new qNode;
		Left = new qNode;
		Right = new qNode;
		Left = obj.dequeue();
		Right = obj.dequeue();
		Left->next = NULL;
		Right->next = NULL;
		Left->weight = 0;
		Right->weight = 1;
		root->data = '@';
		root->left = Left;
		root->right = Right;
		Left->parent = root;
		Right->parent = root;
		root->parent = NULL;
		root->frequency = Left->frequency + Right->frequency;
		root->weight = -1;
		root->next = NULL;
		obj.enqueue(root);
		qObj = root;
	}

	saveinfiles();
}

string decoderrr(string str, qNode* root) {

	qNode* current = root;
	int x = str.length();
	string decodedstring = "";
	for (int i = 0; i < x; ++i) {
		if (str[i] == '0' && current->left != NULL)
			current = current->left;
		else if (str[i] == '1' && current->right != NULL)
			current = current->right;
		if (current->left == NULL && current->right == NULL) {
			decodedstring += current->data;
			current = root;
		}
	}

	return decodedstring;
}

void encoderrrrrText() {

	Queue ObjQ;

	for (int i = 0; i < sentence.length(); i++) {

		qNode* temp = new qNode; //making one noded trees
		temp->data = sentence[i];
		temp->frequency = 1;
		temp->left = NULL;
		temp->right = NULL;
		temp->weight = -1;
		temp->next = NULL;
		ObjQ.enqueue(temp);


	}
	encodeinggg(ObjQ);

}

void saveinfiles() {

	ofstream encode;
	encode.open("File.txt");

	if (!encode) {
		cout << "ENCODER: FILE NOT CREATED" << endl;
	}
	else {

		for (int i = 0; i < sentence.length(); i++) {

			sPush(qObj, sentence[i]);
			while (!myObj.is_empty()) {
				int en = myObj.pop();
				encode << en;
			}
		}

	}
	encode.close();

	cout << endl << endl << "ENCRYPTED FILE SAVED WITH NAME \"OUTPUT.TXT\" " << endl << endl;
	system("pause");
}

void decoderrText() {

	if (qObj->data != NULL) {

		string encodedText = "";

		ifstream inputFile("File.txt");

		char character;

		if (inputFile) {

			inputFile.get(character);

			while (!inputFile.eof()) {

				encodedText = encodedText + character;
				inputFile.get(character);

				if (inputFile.eof()) {
					break;
				}

			}
		}

		inputFile.close();
		sentence = decoderrr(encodedText, qObj);


	}
	else {
		system("cls");
		cout << "Root Not Found !" << endl << endl;
		system("pause");
	}

}


////


int main() {



	string line;
	ifstream input("dictionary.txt");

	if (input.is_open()) {

		while (getline(input, line)) {

			trieTree.insertion(line);
		}
		input.close();
	}


	int choice = 0;
	do {


		system("cls");
		cout << "                      DICTIONARY                      " << endl << endl;

		cout << "PRESS 1 TO ENTER DATA IN FILE" << endl;
		cout << "PRESS 2 TO SHOW ALL THE PREVIOUS DATA SAVED IN FILE" << endl;
		cout << "PRESS 3 TO TERMINATE THE PROGRAM" << endl << endl;

		cout << "ENTER YOUR COICE      ";
		cin >> choice;

		switch (choice) {
		case 1:
			Document();
			break;
		case 2:
			decoderrText();
			Document();
			break;
		case 3:
			cout << "program is quit" << endl;
			break;
		default:
			cout << "invalid input" << endl;
			break;
		}

		encoderrrrrText();

	} while (choice != 3);

	system("pause");
	return 0;
}