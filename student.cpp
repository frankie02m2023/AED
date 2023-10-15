//
// Created by lucas on 15/10/2023.
//
#include "student.h"

student::student(string student_name, string student_number){
    this->student_name = student_name;
    this->student_number = student_number;
}

string student::get_name() const {
    return student_name;
}

string student::get_number() const {
    return student_number;
}
