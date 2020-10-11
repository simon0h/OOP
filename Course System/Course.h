#include <iostream>
#include <string>
#include <vector>
// #ifndef COURSE_H
// #define COURSE_H

class Student;

class Course {

friend std::ostream& operator<<(std::ostream& os, const Course& rhs);

public:
    Course(const std::string& courseName);

    const std::string& getName() const;

    bool addStudent(Student* student);

    void removeStudentsFromCourse();

private:
    std::string name;
    std::vector<Student*> students;

    bool findStudent(Student* student) const;
};