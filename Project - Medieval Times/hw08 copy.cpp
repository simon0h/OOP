//Simon Oh
//N19471254
//Homework 8
//Linked lists

#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Polynomial {

struct Node;

friend ostream& operator << (ostream& os, const Polynomial& poly);
friend bool operator == (const Polynomial& lhs, const Polynomial& rhs);

public:
	Polynomial(const vector<int>& vec = {0}): degrees(vec.size() - 1) { //Default constructor creates a polynomial of zero degrees if no parameters are passed
		createLinkedList(vec);
	}

	Polynomial(const Polynomial& rhs): degrees(rhs.degrees) {
		head = new Node();
		Node* toCopy = rhs.head->next;
		Node* currNode = head;
		while (toCopy->next) {
			Node *newNode = new Node(toCopy->num); //Creates a new node
			currNode->next = newNode; //And link the previous node to the next node
			currNode = newNode;
			toCopy = toCopy->next;
		}
		Node *newNode = new Node(toCopy->num); //Since size_t is always greater than -1, this is for the last element
		currNode->next = newNode;
	}

	int getDegrees() const {
		return degrees;
	}

	void createLinkedList(const vector<int>& vec) {
		head = new Node();
		Node* currNode = head;
		for (size_t i = vec.size() - 1; i > 0; i--) {
			Node *newNode = new Node(vec[i]);
			currNode->next = newNode;
			currNode = newNode;
		}
		Node *newNode = new Node(vec[0]); //Since size_t is always greater than -1, this is for the last element
		currNode->next = newNode;
	}

	int evaluate(int x) {
		int answer = head->next->num; //Because the 0th degree is just a number with no variables, it is the default value for the answer to be returned
		int degrees = 2; //Degrees start at two because int passed will be powered only if the power degree is greater than or equal to two
		Node* next = head->next->next; //Skips the 0th degree because it is just an integer
		while(next) {
			int powered = x;
			for (size_t i = 2; i < degrees; i++) { //Makes sure that the int passed will be powered only if the power degree is greater than or equal to two
				powered *= x;
			}
			powered *= next->num;
			answer += powered;
			degrees++;
			next = next->next;
		}
		return answer;
	} 

	Polynomial& operator=(const Polynomial& rhs) {
		if (&rhs != this) {
			Node* next = head->next;
			Node* toDelete = head;
			while (next) {
				delete toDelete;
				toDelete = next;
				next = next->next;
			}
			delete toDelete;
			head = new Node();
			Node* toCopy = rhs.head->next;
			Node* currNode = head;
			while (toCopy->next) {
				Node *newNode = new Node(toCopy->num);
				currNode->next = newNode;
				currNode = newNode;
				toCopy = toCopy->next;
			}
			Node *newNode = new Node(toCopy->num); //To copy over the last element
			currNode->next = newNode;
			return *this;
		}
	}

	Polynomial& operator+=(const Polynomial& rhs) {
		Node* currNode = head->next;
		Node* rhsCurrNode = (rhs.head)->next;
		int biggerDegree;
		if (degrees > rhs.degrees) {
			biggerDegree = degrees;
		}
		else {
			biggerDegree = rhs.degrees;
		}
		for (size_t i = 0; i < biggerDegree + 1; i++) {
			currNode->num += rhsCurrNode->num;
			if (!(currNode->next)) { 
				currNode->next = new Node; //Creates a new node with num = 0 to add to the correct degree
				currNode = currNode->next;
				rhsCurrNode = rhsCurrNode->next;
			}
			else if (!(rhsCurrNode->next)) {
				return *this;
			}
			else {
				currNode = currNode->next;
				rhsCurrNode = rhsCurrNode->next;
			}
		}
		return *this;
	}

	~Polynomial() {
		Node* next = head->next;
		Node* toDelete = head;
		while (next) {
			delete toDelete;
			toDelete = next;
			next = next->next;
		}
		delete toDelete; 
	}

private:
	int degrees;
	Node* head;

	struct Node {
		Node(int num = -10): num(num), next(nullptr) {

		}
		int num;
		Node* next;
	};
};

ostream& operator << (ostream& os, const Polynomial& poly) {
	string toReturn;
	int i = 1;
	Polynomial::Node* next = (poly.head)->next;
	toReturn += to_string(next->num);
	while (next->next) {
		next = next->next;
		if (next->num != 1 && next->num != 0) {
			if (i == 1) {
				toReturn = to_string(next->num) + "x + " + toReturn;
			}
			else {
				toReturn = to_string(next->num) + "x^" + to_string(i) + " + " + toReturn;
			}
		}
		else if (next->num == 1) {
			if (i == 1) {
				toReturn = "x + " + toReturn;
			}
			else {
				toReturn = "x^" + to_string(i) + " + " + toReturn;
			}
		}
		i++;
		//next = next->next;
	}
	os << toReturn;
	return os;
}

bool operator == (const Polynomial& lhs, const Polynomial& rhs) {
	Polynomial::Node* lhsNode = (lhs.head)->next;
	Polynomial::Node* rhsNode = (rhs.head)->next;
	while (lhsNode) {
		if (lhsNode->num != rhsNode->num) {
			return false;
		}
		lhsNode = lhsNode->next;
		rhsNode = rhsNode->next;
	}
	return true;
}

bool operator != (const Polynomial& lhs, const Polynomial& rhs) {
	return !(lhs == rhs);
}

Polynomial operator + (const Polynomial& lhs, const Polynomial& rhs) {
	Polynomial toReturn = rhs;
	if (rhs.getDegrees() > lhs.getDegrees()) {
		toReturn += lhs;
	}
	else {
		toReturn = lhs;
		toReturn += rhs;
	}
	return toReturn;
}

void doNothing(Polynomial temp) {}

void towers(int n, int start = 0, int target = 1, int spare = 2) {
	if (n > 1) {
		towers (n - 1 , start, spare, target);
	}
	cout << "Moving disk " << n << " to peg " << target << endl;
	if (n > 1) {
		towers (n - 1 , spare, target, start);
	}
}

int main() {

	//towers(3);
	
    Polynomial p1({17});                 // 17
    Polynomial p2({1, 2});               // x + 2
    Polynomial p3({-1, 5});              // -1x + 5
    Polynomial p4({5, 4, 3, 2, 1});      // 5x^4 + 4x^3 + 3x^2 + 2x + 1
    Polynomial has_a_zero({4, 0, 1, 7}); // 4x^3 + x + 7
	
    cout << "p1: " << p1 << endl;
    cout << "p2: " << p2 << endl;
    cout << "p3: " << p3 << endl;
    cout << "p4: " << p4 << endl;
    cout << "has_a_zero: " << has_a_zero << endl;
    cout << "p2 + p3: " << (p2+p3) << endl; 
    cout << "p2 + p4: " << (p2+p4) << endl; 
    cout << "p4 + p2: " << (p4+p2) << endl;

    Polynomial p5(p4);
    cout << "p5: " << p5 << endl; 
    p5 += p3;
    cout << "p5 += p3: " << p5 << endl;  

    cout << "Calling doNothing(p5)" << endl;
    doNothing(p5);
    cout << "p5: " << p5 << endl;

    Polynomial p6;
    cout << "p6: " << p6 << endl;
    cout << boolalpha;  // Causes bools true and false to be printed that way.
    cout << "(p4 != p6) is " << (p4 != p6) << endl;
    p6 = p4;
    p4 += p6;
    cout << "p4: " << p4 << endl;
    cout << "p6: " << p6 << endl;
    cout << boolalpha;
    cout << "(p4 == p6) is " << (p4 == p6) << endl;

    Polynomial p7({5, 4, 3, 2, 1});
    cout << "p4 != p7 is " << (p4 != p7) << endl;

    int x = 5;
    cout << "Evaluating p1 at " << x << " yields: " << p1.evaluate(x) << endl;
    cout << "Evaluating p2 at " << x << " yields: " << p2.evaluate(x) << endl;
	
    Polynomial p8({3, 2, 1});           // 3x^2 + 2x + 1
    cout << "p8: " << p8 << endl;
    cout << "Evaluating p8 at " << x << " yields: " << p8.evaluate(5) << endl;
    cout << "p4: " << p4 << endl;
    cout << "Evaluating p4 at " << x << " yields: " << p4.evaluate(5) << endl;

    cout << boolalpha;
    cout << "(p1 == p2) is " << (p1 == p2) << endl;
    cout << "(p1 != p2) is " << (p1 != p2) << endl;

	/*=================================================================
	NEW TEST CODE - test if cleaning the leading 0s
	===================================================================*/

	Polynomial p8({ 1, 1 });
	Polynomial p9({ -1, 1 });
	Polynomial p10({ 0, 0, 2 });
	//p8 + p9 tests if += does the cleanup()
	//p10 tests if constructor does the cleanup()
	cout << "((p8 + p9) == p10) is " << ((p8 + p9) == p10) << endl;
}


