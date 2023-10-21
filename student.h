//
// Created by franc on 12/10/2023.
//
#ifndef STUDENT_H
#define STUDENT_H

#include <string>
using namespace std;

class student{
public:
    student(string student_name, string student_number);
    string get_name() const;
    string get_number() const;
    void print_student() const;

private:
    string student_name;
    string student_number;
};

#endif
