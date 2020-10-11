#include <iostream>
#include <string>
#include <vector>
// #ifndef REGISTRAR_H
// #define REGISTRAR_H

class Course;
class Student;

class Registrar {

friend std::ostream& operator<<(std::ostream& os, const Registrar& rhs);

public:
    Registrar() {

    }

    bool addCourse(const std::string& name);

    bool addStudent(const std::string& name);

    bool enrollStudentInCourse(const std::string& studentName, const std::string& courseName);

    bool cancelCourse(const std::string& courseName);

    void purge();

private:
    size_t findStudent(const std::string& name) const;

    size_t findCourse(const std::string& name) const;

    std::vector<Course*> courses;
    std::vector<Student*> students;
};