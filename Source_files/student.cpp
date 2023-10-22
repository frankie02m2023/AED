//
// Created by lucas on 15/10/2023.
//
#include <iostream>
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

bool student::operator==(const student& other_student) const{
    return other_student.student_number == student_number;
}

bool student::operator!=(const student& other_student) const{
    return other_student.student_number != student_number;
}

void student::print_student() const {
    std::cout << "name: " << student_name << ", Number: " << student_number << endl;
}
