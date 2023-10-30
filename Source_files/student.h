//
// Created by franc on 12/10/2023.
//
#ifndef STUDENT_H
#define STUDENT_H

#include <string>
using namespace std;

class student{
public:
    //constructors
    student(){};
    student(string student_name, string student_number);

    //getters
    string get_name() const;
    string get_number() const;

    //operators
    bool operator==(const student& other_student) const;
    bool operator!=(const student& other_student) const;
    bool operator<(const student& other_student) const;
    bool operator>(const student& other_student) const;

    //data printers
    void print_student() const;

private:
    string student_name;
    string student_number;
};

#endif
