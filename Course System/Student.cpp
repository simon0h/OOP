#include <iostream>
#include <string>
#include <vector>
#include "Course.h"
#include "Student.h"

Student::Student(const std::string& name): name(name) {

}

const std::string& Student::getName() const {
        return name;
    }

bool Student::addCourse(Course* course) {
    if (findCourse(course)) {
        return false;
    }
    else {
        courses.push_back(course);
        return true;
    }
}

void Student::removedFromCourse(Course* course) {
    for (size_t i = 0; i < courses.size(); i++) {
        if (courses[i] == course) {
            courses[i] = courses.back();
            courses.pop_back();
            break;
        }
    }
}
bool Student::findCourse(const Course* course) const {
    for (size_t i = 0; i < courses.size(); i++) {
        if (courses[i] ==  course) {
            return true;
        }
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const Student& rhs) {
    os << rhs.name << ": ";
    if (rhs.courses.size() > 0) {
        for (size_t i = 0; i < rhs.courses.size(); i++) {
            os << rhs.courses[i]->getName();
            if (i < rhs.courses.size() - 1) {
                os << ", ";
            }
        }
    }
    else {
        os << "No Courses";
    }
    return os;
}