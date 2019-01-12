//Simon Oh
//Implement Conway's Game of Life

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;

void fillVec(ifstream& file);
vector<string> initialize(string line);
void gameOfLife(vector<vector<string>> cells);
void display(vector<vector<string>> cells);

void open() {
	ifstream textFile("life.txt");
	if (!textFile) {
		cerr << "Could not open the file" << endl;
	}
	fillVec(textFile);
	textFile.close();
}

void fillVec(ifstream& file) {
	vector<vector<string>> cells;
	string line;
	vector<string> emptyLine;
	getline(file, line);
	for (size_t i = 0; i < line.size() + 2; ++i) {
			emptyLine.push_back("");
		}
	cells.push_back(emptyLine);
	cells.push_back(initialize(line));
	while (file >> line) {
		cells.push_back(initialize(line));
	}
	cells.push_back(emptyLine);
	cout << "Initial world" << endl;
	display(cells);
	gameOfLife(cells);
}

vector<string> initialize(string line) {
	string cell;
	vector<string> lineVec;
	lineVec.push_back("");
	for (size_t i = 0; i < line.size(); ++i) {
		cell = line[i];
		lineVec.push_back(cell);
	}
	lineVec.push_back("");
	return lineVec;
}

void gameOfLife(vector<vector<string>> cells) {
	int liveNeighbors;
	for (size_t i = 0; i < 10; ++i) {
		vector<vector<string>> newCells = cells;
		for (size_t j = 1; j < cells.size() - 1; ++j) {
			for (size_t k = 1; k < cells[j].size() - 1; ++k) {
				if (cells[j - 1][k - 1] == "*") {
					++liveNeighbors; 
				}
				if (cells[j - 1][k] == "*") {
					++liveNeighbors; 
				}
				if (cells[j - 1][k + 1] == "*") {
					++liveNeighbors; 
				}
				if (cells[j][k - 1] == "*") {
					++liveNeighbors; 
				}
				if (cells[j][k + 1] == "*") {
					++liveNeighbors; 
				}
				if (cells[j + 1][k - 1] == "*") {
					++liveNeighbors; 
				}
				if (cells[j + 1][k] == "*") {
					++liveNeighbors; 
				}
				if (cells[j + 1][k + 1] == "*") {
					++liveNeighbors; 
				}
				if (cells[j][k] == "*") {
					if (liveNeighbors == 2 || liveNeighbors == 3) {
					}
					else {
						newCells[j][k] = "-";
					}
				}
				else {
					if (liveNeighbors == 3) {
						newCells[j][k] = "*";
					}
				}
				liveNeighbors = 0;
			}
		}
		cout << "Generation: " << i + 1 << endl;
		display(newCells);
		cells = newCells;
	}
}

void display(vector<vector<string>> cells) {
	for (size_t i = 1; i < cells.size() - 1; ++i) {
		for (size_t j = 1; j < cells[i].size() - 1; ++j) {
			cout << cells[i][j];
		}
		cout << endl;
	}
	cout << "===========================" << endl;
}

int main() {
	open();
}







