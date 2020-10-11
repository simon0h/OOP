//Linked lists
//Simon Oh
//ho587
//CS2124 Spring 2019

#include <string>
#include <iostream>
#include <vector>
using namespace std;

// Node to be used a part of linked list
struct Node {
	Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
	int data;
	Node* next;
};

// listInsertHead: adds a data item to the beginning of a [possibly empty] list
void listInsertHead(Node*& headPtr, int entry) {
	headPtr = new Node(entry, headPtr);
}

// listClear: frees up all the nodes in a list
void listClear(Node*& headPtr) {
    while (headPtr) {
        Node* next = headPtr->next;
        delete headPtr;
        headPtr = next;
    }
}

Node* listBuild(const vector<int>& vals) {
    Node* result = nullptr;
    for (size_t index = vals.size(); index > 0; --index) {
        listInsertHead(result, vals[index-1]);
    }
    return result;
}

void splice(Node* toAdd, Node* addAfter) {
    Node* addBefore = addAfter->next;
    addAfter->next = toAdd;
    while (addAfter->next) {
        addAfter = addAfter->next;
    }
    addAfter->next = addBefore;
}

Node* isSublist(Node* findThis, Node* findIn) {
    bool matching = false;
    Node* i = findIn;
    Node* t = findThis;
    while (i) {
        if (i->data == t->data) {
            Node* iTemp = i;
            Node* tTemp = t;
            while(iTemp->next && tTemp->next) {
                if (iTemp->data == tTemp->data) {
                    matching = true;
                }
                else {
                    matching = false;
                    break;
                }
                iTemp = iTemp->next;
                tTemp = tTemp->next;
            }
            if (iTemp->data != tTemp->data) {
                matching = false;
            }
            if (matching) {
                return i;
            }
        }
        i = i->next;
    }
    return nullptr;
}

void display(Node* node) {
    while (node->next) {
        cout << node->data << " ";
        node = node->next;
    }
    cout << node->data << " " << endl;
}

int main() {
    Node* first = listBuild({5, 7, 9, 1});
    Node* second = listBuild({6, 3, 2});

    cout << "First linked list: ";
    display(first);

    cout << "Second linked list: ";
    display(second);

    cout << "Getting addAfter" << endl;
    Node* addAfter = first->next; //7

    cout << "Splicing" << endl;
    splice(second, addAfter);

    cout << "Linked list after adding: ";
    display(first);
    display(second);

    cout << "Finding sublist ";
    display(second);
    cout << "in ";
    display(first);
    Node* sub = isSublist(second, first);

    cout << "Sublist" << endl;
    display(sub);

    first = listBuild({1, 2, 3, 2, 3, 2 ,4, 5, 6});
    second = listBuild({2, 3, 2, 4});

    sub = isSublist(second, first);
    display(sub);
}



















