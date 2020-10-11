#include <iostream>
#include <string>
#include <vector>
#include "Registrar.h"
#include "Student.h"
#include "Course.h"

bool Registrar::addCourse(const std::string& name) {
        if (findCourse(name) == courses.size()) {
            Course* coursePtr = new Course(name);
            courses.push_back(coursePtr);
            return true;
        }
        else {
            std::cout << "This course already exists" << std::endl;
            return false;
        }
    }

bool Registrar::addStudent(const std::string& name) {
    if (findStudent(name) == students.size()) {
        Student* studentPtr = new Student(name);
        students.push_back(studentPtr);
        return true;
    }
    else {
        std::cout << "This student already exists" << std::endl;
        return false;
    }
}

bool Registrar::enrollStudentInCourse(const std::string& studentName, const std::string& courseName) {
    size_t studentLoc = findStudent(studentName);
    size_t courseLoc = findCourse(courseName);
    if (studentLoc == students.size()) {
        std::cout << studentName << " does not exist" << std::endl;
        return false;
    }
    if (courseLoc == courses.size()) {
        std::cout << courseName << " does not exist" << std::endl;
        return false;
    }
    Course* course = courses[courseLoc];
    Student* student = students[studentLoc];
    return(course->addStudent(student) && student->addCourse(course));
}

bool Registrar::cancelCourse(const std::string& courseName) {
    size_t courseLoc = findCourse(courseName);
    if (courseLoc == courses.size()) {
        std::cout << courseName << " does not exist" << std::endl;
        return false;
    }
    else {
        courses[courseLoc]->removeStudentsFromCourse();
        delete courses[courseLoc];
        courses[courseLoc] = courses.back();
        courses.pop_back();
        return true;
    }
}

void Registrar::purge() {
    for (size_t i = 0; i < courses.size(); i++) {
        delete courses[i];
    }
    courses.clear();
    for (size_t j = 0; j < students.size(); j++) {
        delete students[j];
    }
    students.clear();
}

size_t Registrar::findStudent(const std::string& name) const {
        for (size_t i = 0; i < students.size(); i++) {
            if (students[i]->getName() ==  name) {
                return i;
            }
        }
        return students.size();
    }

size_t Registrar::findCourse(const std::string& name) const {
    for (size_t i = 0; i < courses.size(); i++) {
        if (courses[i]->getName() ==  name) {
            return i;
        }
    }
    return courses.size();
}

std::ostream& operator<<(std::ostream& os, const Registrar& rhs) {
    os << "Registrar's Report" << std::endl;
    os << "Courses: " << std::endl;
    for (size_t i = 0; i < rhs.courses.size(); i++) {
        os << *rhs.courses[i] << std::endl;
    }
    os << "Students: " << std::endl;
    for (size_t j = 0; j < rhs.students.size(); j++) {
        os << *rhs.students[j] << std::endl;
    }
    return os;
}



