//Dynamic array and copy control
//Create directory system
//Simon Oh
//ho587
//CS2124 Spring 2019

#include <string>
#include <iostream>
using namespace std;

class Position {
   
    friend ostream& operator<<(ostream& os, const Position& rhs) {
        os << '[' << rhs.title << ',' << rhs.salary << ']';
        return os;
    }

public:
    Position(const string& aTitle, double aSalary): title(aTitle), salary(aSalary) {

    }

    const string& getTitle() const { 
        return title; 
    }
    double getSalary() const { 
        return salary; 
    }
    void changeSalaryTo(double d) { 
        salary = d; 
    }

private:
    string title;
    double salary;
};

class Entry {

    friend ostream& operator<<(ostream& os, const Entry& rhs) {
        os << rhs.name << ' ' << rhs.room
           << ' ' << rhs.phone << ", " << *rhs.pos;
        return os;
    }

public:
    Entry(const string& name, unsigned room, unsigned phone, Position& position): name(name), room(room), phone(phone), pos(&position) {
    
    }

    const string& getName() const { 
        return name; 
    }

    unsigned getRoom() const { 
        return room; 
    }

    unsigned getPhone() const { 
        return phone; 
    }

private:
    string name;
    unsigned room;
    unsigned phone;
    Position* pos;
}; 

class Directory {
    
    friend ostream& operator<<(ostream& os, const Directory& d);

public:
    
    Directory(): size(0), capacity(1), entries(new Entry*[1]) {
    }

    Directory(const Directory& newDirectory): size(newDirectory.size), 
             capacity(newDirectory.capacity), entries(new Entry*[newDirectory.capacity]) {
        cout << "Copying Directory" << endl;
        for (size_t i = 0; i < size; i++) {
            entries[i] = new Entry(*newDirectory.entries[i]);
        }
    }

    Directory& operator=(const Directory& newDirectory) {
        cout << "Assigning Directory" << endl;
        if (this != &newDirectory) {
            cout << "Deleting Directory for the assignment operator" << endl;
            for (size_t i = 0; i < size; i++) {
                cout << "Currently deleting " << entries[i]->getName() << endl;
                delete entries[i];
            }
            delete [] entries;
            size = newDirectory.size;
            capacity = newDirectory.capacity;
            entries = new Entry*[capacity];
            for (size_t i = 0; i < size; i++) {
                entries[i] = new Entry(*newDirectory.entries[i]);
            }
        }
        else {
            cout << "No self assignment pls" << endl;
        }
        return *this;
    }

    unsigned operator[](const string& name) const {
        for (size_t i = 0; i < size; i++) {
            if (entries[i]->getName() == name) {
                return entries[i]->getPhone();
            }
        }
        cerr << "Person does not exist" << endl;
        return 99999999;
    }
    
    void add(const string& name, unsigned room, unsigned ph, Position& pos) {
        if (size == capacity) {
            Entry** newEntries = new Entry*[capacity * 2];
            for (size_t i = 0; i < capacity; i++) {
                newEntries[i] = entries[i];
            }
            entries = newEntries;
            delete [] newEntries;
            capacity *= 2;
        } // if
        entries[size] = new Entry(name, room, ph, pos);
        size++;
    } // add

    ~ Directory() {
        cout << "Deleting Directory..." << endl;
        for (size_t i = 0; i < size; i++) {
            cout << "Currently deleting " << entries[i]->getName() << endl;
            delete entries[i];
        }
        delete [] entries;
    }

private:    
    Entry** entries;
    size_t size;
    size_t capacity;
}; // class Directory

ostream& operator<<(ostream& os, const Directory& d) {
    for (size_t i = 0; i < d.size; i++) {
        os << *d.entries[i] << endl;
        return os;
    }
}

void doNothing(Directory dir) { cout << dir << endl; }

int main() {
    
    // Note that the Postion objects are NOT on the heap.
    Position boss("Boss", 3141.59);
    Position pointyHair("Pointy Hair", 271.83);
    Position techie("Techie", 14142.13);
    Position peon("Peonissimo", 34.79);
    
    // Create a Directory
    Directory d;
    d.add("Marilyn", 123, 4567, boss);
    cout << "d: " << d << endl;

    Directory d2 = d;   // What function is being used??
    d2.add("Gallagher", 111, 2222, techie);
    d2.add("Carmack", 314, 1592, techie);
    cout << "d: " << d << endl;
    cout << "d2: " << d2 << endl;

    cout << "Calling doNothing\n";
    doNothing(d2);
    cout << "Back from doNothing\n";

    Directory d3;
    d3 = d2;

    // Should display 1592
    cout << d2["Carmack"] << endl;
    cout << "End" << endl;
    
} // main
