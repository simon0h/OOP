#include <iostream>
#include <string>
#include <vector>
// #ifndef STUDENT_H
// #define STUDENT_H

class Course;

class Student {

friend std::ostream& operator<<(std::ostream& os, const Student& rhs);

public:
    Student(const std::string& name);

    const std::string& getName() const;

    bool addCourse(Course* course);

    void removedFromCourse(Course* course);

private:
    std::string name;
    std::vector<Course*> courses;

    bool findCourse(const Course* course) const;
};