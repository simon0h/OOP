//Inheritance
//Use inhertiance to model different types of printed materials like books, magazines, etc
//Simon Oh
//ho587
//CS2124 Spring 2019

#include <string>
#include <iostream>
#include <vector>
using namespace std;

class PrintedMaterial {
public:
	PrintedMaterial(unsigned pages): numOfPages(pages) {

	}

	virtual void displayNumPages() const = 0;

private:
	unsigned numOfPages;
};

void PrintedMaterial::displayNumPages() const {
	cout << numOfPages << endl;
}

class Magazine : public PrintedMaterial {
public:
	Magazine(unsigned pages): PrintedMaterial(pages) {

	}

	void displayNumPages() const {
		cout << "Magazine pages: ";
		PrintedMaterial::displayNumPages();
	}

private:
};

class Book : public PrintedMaterial {
public:
	Book(unsigned pages): PrintedMaterial(pages) {

	}

	void displayNumPages() const {
		cout << "Book pages: ";
		PrintedMaterial::displayNumPages();
	}

private:
};

class TextBook : public Book {
public:
	TextBook(unsigned pages, unsigned index): Book(pages), numOfIndexPages(index) {

	}
	
	void displayNumPages() const { 
		cout << "Textbook pages: "; 
		PrintedMaterial::displayNumPages();
		cout << "Textbook indexes: " << numOfIndexPages << endl; 

	}

private:
	unsigned numOfIndexPages;
};

class Novel : public Book {
public:
	Novel(unsigned pages): Book(pages) {

	}

	void displayNumPages() const {
		cout << "Novel pages: ";
		PrintedMaterial::displayNumPages();
	}

private:
};

int main() {
	TextBook t(5430, 23);
	Novel n(213);
	Magazine m(6);

	// as direct method calls
	cout << "\nEach will now be asked directly,\n"
	     << "using the dot member operator to\n"
	     << "display its number of pages:\n";
	t.displayNumPages();
	n.displayNumPages();
	m.displayNumPages();

	PrintedMaterial* pmPtr;
	pmPtr = &t;
	pmPtr->displayNumPages();


	// Storing generic objects in a vector 
	cout << "\nNow we'll use a container. Yea!!!\n";
	vector<PrintedMaterial*> allThemPrinties;
	allThemPrinties.push_back(&t);
	allThemPrinties.push_back(&n);
	allThemPrinties.push_back(&m);
	for(size_t ndx=0; ndx < allThemPrinties.size(); ++ ndx ) 
	{
		allThemPrinties[ndx]->displayNumPages();
	}
}







