//Simon Oh
//N19471254
//Homework 8
//Linked lists

#include <string>
#include <iostream>
#include <vector>
#include "hw08_polynomial.h"
using namespace std;

#ifndef HW08_POLYNOMIAL_H
#define HW08_POLYNOMIAL_H

Polynomial::Polynomial(const vector<int>& vec): degrees(vec.size() - 1) { //Default constructor creates a polynomial of zero degrees if no parameters are passed
	createLinkedList(vec);
}

Polynomial::Polynomial(const Polynomial& rhs): degrees(rhs.degrees) {
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

int Polynomial::getDegrees() const {
	return degrees;
}

void Polynomial::createLinkedList(const vector<int>& vec) {
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

int Polynomial::evaluate(int x) {
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

Polynomial& Polynomial::operator=(const Polynomial& rhs) {
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
	return *this;
}

Polynomial& Polynomial::operator+=(const Polynomial& rhs) {
	Node* currNode = head->next;
	Node* rhsCurrNode = (rhs.head)->next;
	int biggerDegree = rhs.degrees;
	if (degrees > rhs.degrees) {
		biggerDegree = degrees;
	}
	for (size_t i = 0; i < biggerDegree + 1; i++) {
		currNode->num += rhsCurrNode->num;
		if (!(currNode->next)) { 
			currNode->next = new Node(0); //Creates a new node with num = 0 to add to the correct degree
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

Polynomial::~Polynomial() {
	Node* next = head->next;
	Node* toDelete = head;
	while (next) {
		delete toDelete;
		toDelete = next;
		next = next->next;
	}
	delete toDelete; 
}

Polynomial::Node::Node(int num): num(num), next(nullptr) {

}

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
		else {

		}
		i++;
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

#endif