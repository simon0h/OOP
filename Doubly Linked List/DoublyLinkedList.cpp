//Doubly linked lists
//Simon Oh
//ho587
//CS2124 Spring 2019

#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

class List {

struct Node;

friend ostream& operator<< (ostream& os, const List& list);

public:

	class Iterator;

	List(): listSize(0) {
		headSentinel = new Node();
		tailSentinel = new Node();
		headSentinel->next = tailSentinel;
		tailSentinel->prev = headSentinel;
	}

	int size() const {
		return listSize;
	}

	int front() const {
		return (headSentinel->next)->num;
	}

	int& front() {
		return (headSentinel->next)->num;
	}

	Iterator& begin() {
		Iterator* begin = new Iterator(headSentinel->next);
		return *begin;
	}

	int back() const {
		return (tailSentinel->prev)->num;
	}

	int& back() {
		return (tailSentinel->prev)->num;
	}

	Iterator& end() {
		Iterator* end = new Iterator(tailSentinel);
		return *end;
	}

	void push_back(int i) {
		Node* node = new Node(i, tailSentinel->prev, tailSentinel);
		tailSentinel->prev->next = node;
		tailSentinel->prev = node;
		listSize++;
	}

	void push_front(int i) {
		Node* node = new Node(i, headSentinel, headSentinel->next);
		headSentinel->next->prev = node;
		headSentinel->next = node;
		listSize++;
	}

	void pop_back() {
		if (tailSentinel->prev != headSentinel) {
			Node* toDelete = tailSentinel->prev;
			tailSentinel->prev->prev->next = tailSentinel;
			tailSentinel->prev = tailSentinel->prev->prev;
			listSize --;
			delete toDelete;
		}
	}

	void pop_front() {
		if (tailSentinel->prev != headSentinel) {
			Node* toDelete = headSentinel->next;
			headSentinel->next->next->prev = headSentinel;
			headSentinel->next = headSentinel->next->next;
			listSize --;
			delete toDelete;
		}
	}

	void clear() {
		while (listSize) {
        	pop_back();
    	}
	}

	int operator[](int i) const {
		Node* currNode = headSentinel->next;
		for (size_t j = 0; j < i; j++) {
			currNode = currNode->next;
		}
		return currNode->num;
	}

	int& operator[](int i) {
		Node* currNode = headSentinel->next;
		for (size_t j = 0; j < i; j++) {
			currNode = currNode->next;
		}
		return currNode->num;
	}

	class Iterator {

	friend bool operator==(const Iterator& lhs, const Iterator& rhs);
	friend class List;

	public:
		Iterator(Node* node): node(node) {
			
		}

		Iterator& operator++() {
			node = node->next;
			return *this;
		}

		Iterator& operator--() {
			node = node->prev;
			return *this;
		}

		int operator*() {
			return node->num;
		}

	private:
		Node* node;
	};

	Iterator& insert(Iterator& iter, int i) {
		if (iter == begin()) {
			push_front(i);
		}
		else if (iter == end()) {
			push_back(i);
		}
		else {
			Node* currNode = iter.node;
			Node* nextNode = (iter.node)->next;
			Node* toInsert = new Node(i, currNode, nextNode);
			currNode->next = toInsert;
			nextNode->prev = toInsert;
			listSize++;
		}
		return ++iter;
	}

	Iterator& erase(Iterator& iter) {
		Node* nextNode = (iter.node)->next;
		Node* prevNode = (iter.node)->prev;
		prevNode->next = nextNode;
		nextNode->prev = prevNode;
		listSize--;
		delete iter.node;
		return ++iter;
	}

private:

	Node* headSentinel;
	Node* tailSentinel;
	int listSize;

	struct Node {

		Node(int i = -1, Node* prev = nullptr, Node* next = nullptr): prev(prev), next(next), num(i) {

		}

		Node* prev;
		Node* next;
		int num;
	};

};

ostream& operator<<(ostream& os, const List& list) {
	if (list.headSentinel->next == list.tailSentinel) {
		os << "Empty list" << endl;
	}
	else {
		List::Node* currNode = (list.headSentinel)->next; 
		while (currNode != list.tailSentinel) {
			os << currNode->num << " ";
			currNode = currNode->next;
		}
	}
	return os;
}

bool operator==(const List::Iterator& lhs, const List::Iterator& rhs) {
	if (lhs.node == rhs.node) {
		return true;
	}
	return false;
}

bool operator!=(const List::Iterator& lhs, const List::Iterator& rhs) {
	if (lhs == rhs) {
		return false;
	}
	return true;
}

// Task 1
void printListInfo(const List& myList) {
        cout << "size: " << myList.size()
             << ", front: " << myList.front()
             << ", back(): " << myList.back()
             << ", list: " << myList << endl;
}

// The following should not compile. Check that it does not.
// void changeFrontAndBackConst(const List& theList){
//     theList.front() = 17;
//     theList.back() = 42;
// }

void changeFrontAndBack(List& theList){
    theList.front() = 17;
    theList.back() = 42;
}

//Task 4
void printListSlow(const List& myList) {
    for (size_t i = 0; i < myList.size(); ++i) {
        cout << myList[i] << ' ';
    }
    cout << endl;
}   

int main() {

    // Task 1
    cout << "\n------Task One------\n";
    List myList;
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "Pushing back " << i*i << endl;
        myList.push_back(i*i);
        printListInfo(myList);
    }
    myList.pop_back();
    printListInfo(myList);
    cout << "===================\n";
    
    cout << "Modify the first and last items, and display the results\n";
    changeFrontAndBack(myList);
    printListInfo(myList);
    cout << "===================\n";

    cout << "Remove the items with pop_back\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_back();
    }
    cout << "===================\n";
    cout << "Empty list: ";
    printListInfo(myList);

    // Task 2
    cout << "\n------Task Two------\n";
    cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "Pushing front " << i*i << endl;
        myList.push_front(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_front\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_front();
    }
    cout << "===================\n";

    // Task 3
    cout << "\n------Task Three------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i*i);
    }
    printListInfo(myList);
    cout << "Now clear\n";
    myList.clear();
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "===================\n";

    // Task 4
    cout << "\n------Task Four------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    cout << "Display elements with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Add one to each element with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
    cout << "And print it out again with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Now calling a function, printListSlow, to do the same thing\n";
    printListSlow(myList);
    cout << "Finally, for this task, using the index operator to modify\n"
         << "the data in the third item in the list\n"
         << "and then using printListSlow to display it again\n";
    myList[2] = 42;
    printListSlow(myList);

    // Task 5
    cout << "\n------Task Five------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    printListInfo(myList);
    cout << "Now display the elements in a ranged for\n";
    for (int x : myList) cout << x << ' ';
    cout << endl;
    cout << "And again using the iterator type directly:\n";
    for (List::Iterator iter = myList.begin(); iter != myList.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
    
    // Task 6
    cout << "\n------Task Six------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Filling an empty list with insert at begin(): "
         << "i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) {
    	myList.insert(myList.begin(), i*i);
    }
    printListInfo(myList);
	cout << "Filling an empty list with insert at differnt spot: " << endl;
	List::Iterator iter = myList.begin();
	++iter;
	++iter;
	for (int i = 0; i < 10; ++i) myList.insert(iter, 100);
    printListInfo(myList);
    cout << "===================\n";

    // Task 7
    cout << "\n------Task Seven------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    cout << "Erasing the elements in the list, starting from the beginning\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.erase(myList.begin());
    }
    printListInfo(myList);
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    List::Iterator iter2 = myList.begin();
	++iter2;
	++iter2;
	cout << "Erasing the third in the list\n";
	myList.erase(iter2);
	printListInfo(myList);
    cout << "===================\n";
}
