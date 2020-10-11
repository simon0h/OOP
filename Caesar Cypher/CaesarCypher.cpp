//Decrypt a text file using Caesar cypher
//Simon Oh
//ho587
//CS2124 Spring 2019

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int getSteps(ifstream& encrypted);
vector<string> fillVector(ifstream& encrypted);
void decrypt(vector<string>& sentences, int steps);
char decryptChar(char a, int steps);
void display(vector<string>& sentences);

void openFile(ifstream& encrypted) {
	encrypted.open("encrypted.txt");
	if (!encrypted) {
		cerr << "Could not open the file" << endl;
	}
}

int getSteps(ifstream& encrypted) {
	int loopSteps;
	int steps;
	while (encrypted >> loopSteps) { //Loop over the file to get the int in the beginning and sets it to steps
		steps = loopSteps;
	}
	encrypted.clear(); //Clears the flag because there is only one int in the file
	return steps;
}

vector<string> fillVector(ifstream& encrypted) {
	string sentence;
	vector<string> sentences;
	while (getline(encrypted, sentence)) {
		sentences.push_back(sentence);
	}
	encrypted.close(); //Close the opened file here because it was not closed in openFile()
	return sentences;
}

void decrypt(vector<string>& sentences, int steps) { //Function for decrypting the whole word
	char toDecrypt;
	for (size_t i = 0; i < sentences.size(); ++i) {
		for (size_t j = 0; j < sentences[i].size(); ++j) { //Loops over a sentence on a indivisual character basis and passes the character to decryptChar
			toDecrypt = decryptChar(sentences[i][j], steps);
			sentences[i][j] = toDecrypt;
		}
	}
}

char decryptChar(char a, int steps) { //Function for decrypting indivisual characters
	int overflow;
	if ((a >= 'a') && (a <= 'z')) { //Checks if the character is lowercase
		if ((a - steps) < 'a') { //Checks if "moving back" the given steps will "overflow"
 			overflow = 'a' - (a - steps); //Overflow is the amount that needs to be wrapped around
			a = '{' - overflow; //Since decrypting goes backwards in the alphabet and because '{'' is the char after 'z', the decrypted char would be '{' minus wrap around amount
		}
		else {
			a -= steps;
		}
	}
	return a;
}

void display(vector<string>& sentences) {
	for (int i = (sentences.size() - 1); i > -1; --i) { //Loops backwards through the vector since the lines are reversed in the file
		cout << sentences[i] << endl;
	}
}

int main() {
	ifstream encrypted;
	int steps;
	vector<string> sentences;
	openFile(encrypted);
	steps = getSteps(encrypted);
	sentences = fillVector(encrypted);
	decrypt(sentences, steps);
	display(sentences);
}

