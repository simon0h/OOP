//Simon Oh
//N19471254
//Homework 8
//Linked lists

#include <string>
#include <iostream>
#include <vector>

class Polynomial {

struct Node;

friend std::ostream& operator << (std::ostream& os, const Polynomial& poly);
friend bool operator == (const Polynomial& lhs, const Polynomial& rhs);

public:
	Polynomial(const std::vector<int>& vec = {0});

	Polynomial(const Polynomial& rhs);

	int getDegrees() const;

	void createLinkedList(const std::vector<int>& vec);

	int evaluate(int x);

	Polynomial& operator=(const Polynomial& rhs);

	Polynomial& operator+=(const Polynomial& rhs);

	~Polynomial();

private:
	int degrees;
	Node* head;

	struct Node {
		Node(int num = -10);
		int num;
		Node* next;
	};
};

std::ostream& operator << (std::ostream& os, const Polynomial& poly);

bool operator == (const Polynomial& lhs, const Polynomial& rhs);

bool operator != (const Polynomial& lhs, const Polynomial& rhs);

Polynomial operator + (const Polynomial& lhs, const Polynomial& rhs);