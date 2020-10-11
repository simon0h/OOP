#include <iostream>
#include <string>
#include <vector>
#include "Course.h"
#include "Student.h"

Course::Course(const std::string& courseName): name(courseName) {

}

const std::string& Course::getName() const {
    return name;
}

bool Course::addStudent(Student* student) {
    if (findStudent(student)) {
        return false;
    }
    else {
        students.push_back(student);
        return true;
    }
}

void Course::removeStudentsFromCourse() {
    std::cout << "NAME: " << name << std::endl;
    size_t size = students.size() - 1;
    for (size_t i = 0; i < students.size(); i++) {
        students[size - i]->removedFromCourse(this);
        students.pop_back();
    }
}

bool Course::findStudent(Student* student) const {
    for (size_t i = 0; i < students.size(); i++) {
        if (students[i] ==  student) {
            return true;
        }
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const Course& rhs) {
    os << rhs.name << ": ";
    if (rhs.students.size() > 0) {
        for (size_t i = 0; i < rhs.students.size(); i++) {
            os << rhs.students[i]->getName();
            if (i < rhs.students.size() - 1) {
                os << ", ";
            }
        }
    }
    else {
        os << "No Students";
    }
    return os;
}