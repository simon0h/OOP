//Structs, vectors and functions
//Take a chemical formula and break it down
//Simon Oh
//ho587
//CS2124 Spring 2019

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Hydrocarbon {
	vector<string> names;
	int carbons;
	int hydrogens;
};

void openFile(ifstream& file);
void fillHydrocarbons(ifstream& file, vector<Hydrocarbon>& hydrocarbons);
void insertToHydrocarbons(const string& name, int carbons, int hydrogens, vector<Hydrocarbon>& hydrocarbons);
size_t findDuplicate(int carbons, int hydrogens, const vector<Hydrocarbon>& hydrocarbons);
void sort(vector<Hydrocarbon>& hydrocarbons);
void display(const vector<Hydrocarbon>& hydrocarbons);

int main() {
	ifstream file;
	vector<Hydrocarbon> hydrocarbons;
	openFile(file);
	fillHydrocarbons(file, hydrocarbons);
	cout << endl;
	sort(hydrocarbons);
	display(hydrocarbons);
	file.close();
}

void openFile(ifstream& file) {
	string name;
	cout << "Please enter the file name: " << endl;
	cin >> name;
	file.open(name);
	while (!file) {
		file.clear();
		cerr << "Could not open the file" << endl;
		cout << "Please enter the correct file name: " << endl;
		cin >> name;
		file.open(name);
	}
}

void fillHydrocarbons(ifstream& file, vector<Hydrocarbon>& hydrocarbons) {
	string line;
	string name;
	char c;
	int carbons;
	char h;
	int hydrogens;
	while (file >> name >> c >> carbons >> h >> hydrogens) {
		insertToHydrocarbons(name, carbons, hydrogens, hydrocarbons);
	}
}

void insertToHydrocarbons(const string& name, int carbons, int hydrogens, vector<Hydrocarbon>& hydrocarbons) {
	size_t duplicateLoc;
	duplicateLoc = findDuplicate(carbons, hydrogens, hydrocarbons);
	if (duplicateLoc < hydrocarbons.size()) {
		hydrocarbons[duplicateLoc].names.push_back(name);
	}
	else {
		Hydrocarbon hydrocarbon;
		hydrocarbon.names.push_back(name);
		hydrocarbon.carbons = carbons;
		hydrocarbon.hydrogens = hydrogens;
		hydrocarbons.push_back(hydrocarbon);
	}
}

size_t findDuplicate(int carbons, int hydrogens, const vector<Hydrocarbon>& hydrocarbons) {
	size_t location = hydrocarbons.size();
	for (size_t i = 0; i < hydrocarbons.size(); i++) {
		if ((hydrocarbons[i].carbons == carbons) && (hydrocarbons[i].hydrogens == hydrogens)) {
			location = i;
		}
	}
	return location;
}

void sort(vector<Hydrocarbon>& hydrocarbons) {
	Hydrocarbon toSwap;
	int min;
	for (size_t i = 0; i < hydrocarbons.size(); i++) {
		min = i;
		for (size_t j = i + 1; j < hydrocarbons.size(); j++) {
			if ((hydrocarbons[j].carbons <= hydrocarbons[min].carbons) && (hydrocarbons[j].hydrogens < hydrocarbons[min].hydrogens)) {
				min = j;
			}
		}
		toSwap = hydrocarbons[i];
	 	hydrocarbons[i] = hydrocarbons[min];
	 	hydrocarbons[min] = toSwap; 
	}
}

void display(const vector<Hydrocarbon>& hydrocarbons) {
	for (size_t i = 0; i < hydrocarbons.size(); i++) {
		cout << "C" << hydrocarbons[i].carbons << "H" << hydrocarbons[i].hydrogens;
		for (size_t j = 0; j < hydrocarbons[i].names.size(); j++) {
			cout << " " << hydrocarbons[i].names[j] << " ";
		}
		cout << endl;
	}
}


