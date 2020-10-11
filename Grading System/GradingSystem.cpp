//Design interactive class using association and composition, 
//encasulation and data hiding, delegation, copy control, output operator

//Create a grading system
//Simon Oh
//ho587
//CS2124 Spring 2019

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Section {

friend ostream& operator<<(ostream& os, const Section& s);

private:
	class Student {

	friend ostream& operator<<(ostream& os, const Section::Student& s);

	public:
		Student (const string& name): name(name), grades(14,-1) {

		}

		const string& getName() const {
			return name;
		}

		void addGrade(int grade, int week) {
			grades[week] = grade;
		}

	private:
		string name;
		vector<int> grades;

	};

	class Time {

	friend ostream& operator<<(ostream& os, const Section::Time& t);

	public:
		Time (const string& day, int hour): day(day), hour(hour) {
			convert(hour);
		}

	private:
		string day;
		int hour;
		int normalHour;

		void convert(int hour) {
			if (hour > 12) {
				normalHour = hour - 12;
			}
			else {
				normalHour = hour;
			}
		}
	};

	friend ostream& operator<<(ostream& os, const Section::Time& t) {
		os << "[Day: " << t.day << ", Start time: " << t.normalHour << "], ";
		return os;
	}

	friend ostream& operator<<(ostream& os, const Section::Student& s) {
		os << "Name: " << s.name << ", Grades: ";
		for (size_t i = 0; i < s.grades.size(); i++) {
			os << s.grades[i] << " ";
		}
		return os;
	}

	vector<Student*> students;
	string name;
	Time time;

public:
	Section(const string& name, const string& day, int hour): name(name), time(day, hour) {

	}

	Section(const Section& section):name(section.name), time(section.time) {
		for (size_t i = 0; i < section.students.size();++i){
			students.push_back(new Student(*section.students[i]));
		}
	}

	void addStudent(const string& studentName) {
		Student* student = new Student(studentName);
		students.push_back(student);
	}

	void addGrade(const string& name, int grade, int day) {
		for (size_t i = 0; i < students.size(); i++) {
			if ((students[i]->getName()) == name) {
				students[i]->addGrade(grade, day);
				break;
			}
		}
	}

	~Section() {
		cout << "Section " << name << " is being deleted" << endl;
		for (size_t i = 0; i < students.size(); i++) {
			cout << "Deleting " << students[i]->getName() << endl;; 
			delete students[i];
		}
		students.clear();
	}

};

class LabWorker {

friend ostream& operator<<(ostream& os, const LabWorker& l);

public:
	LabWorker (const string& name): name(name), currSection(nullptr){

	}

	void addSection(Section& section) {
		currSection = &section;
		//hasSection = true;
	}

	void addGrade(const string& name, int grade, int day) {
		currSection->addGrade(name, grade, day - 1);
	}

private:
	string name;
	Section* currSection;
};

ostream& operator<<(ostream& os, const Section& s) {
	os << "Section: " << s.name << ", Time slot: " << s.time << ", Students: ";
	if (s.students.size() > 0) {
		os << "\n";
		for (size_t i = 0; i < s.students.size(); i++) {
			os << *s.students[i] << endl;
		}
	}
	else {
		os << "None" << endl;
	}
	return os;
}

ostream& operator<<(ostream& os, const LabWorker& l) {
	if (l.currSection) {
		os << l.name << " has " << *l.currSection;
	}
	else {
		os << l.name << " does not have a section" << endl;
	}
	return os;
}

// Test code
void doNothing(Section sec) { 
    cout << sec << endl;;
}

int main() {

    cout << "Test 1: Defining a section\n";
    Section secA2("A2", "Tuesday", 16);
    cout << secA2 << endl;

    cout << "\nTest 2: Adding students to a section\n";
    secA2.addStudent("John");
    secA2.addStudent("George");
    secA2.addStudent("Paul");
    secA2.addStudent("Ringo");
    cout << secA2 << endl;

    cout << "\nTest 3: Defining a lab worker.\n";
    LabWorker moe("Moe");
    cout << moe << endl;

    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection(secA2);
    cout << moe << endl;

    cout << "\nTest 5: Adding a second section and lab worker.\n";
    LabWorker jane( "Jane" );
    Section secB3( "B3", "Thursday", 11 );
    secB3.addStudent("Thorin");
    secB3.addStudent("Dwalin");
    secB3.addStudent("Balin");
    secB3.addStudent("Kili");
    secB3.addStudent("Fili");
    secB3.addStudent("Dori");
    secB3.addStudent("Nori");
    secB3.addStudent("Ori");
    secB3.addStudent("Oin");
    secB3.addStudent("Gloin");
    secB3.addStudent("Bifur");
    secB3.addStudent("Bofur");
    secB3.addStudent("Bombur");
    jane.addSection(secB3);
    cout << jane << endl;

    cout << "\nTest 6: Adding some grades for week one\n";
    moe.addGrade("John", 17, 1);  
    moe.addGrade("Paul", 19, 1);  
    moe.addGrade("George", 16, 1);  
    moe.addGrade("Ringo", 7, 1);  
    cout << moe << endl;

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
    moe.addGrade("John", 15, 3);  
    moe.addGrade("Paul", 20, 3);  
    moe.addGrade("Ringo", 0, 3);  
    moe.addGrade("George", 16, 3);  
    cout << moe << endl;

    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
         << "those students (or rather their records?)\n";

    cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
         << "then make sure the following call works properly, i.e. no memory leaks\n";
    doNothing(secA2);
    cout << "Back from doNothing\n\n";

} // main




