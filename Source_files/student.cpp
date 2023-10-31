//
// Created by lucas on 15/10/2023.
//
#include <iostream>
#include "student.h"

/**
*\file student.cpp
*@brief Implementation of class student.
*/

//constructor
//complexity: O(1)
student::student(string student_name, string student_number){
    this->student_name = student_name;
    this->student_number = student_number;
}

//getters----------------------------------------------------------
//complexity for all getters: O(1)
/** Gets the name of the student.
 * Time complexity: O(1)
 */
string student::get_name() const {
    return student_name;
}

/**Gets the number of the student.
 * Time complexity: O(1)
 */
string student::get_number() const {
    return student_number;
}

//operators ----------------------------------------------------------
//complexity for all operators: O(1)
bool student::operator==(const student& other_student) const{
    return other_student.student_number == student_number;
}

bool student::operator!=(const student& other_student) const{
    return other_student.student_number != student_number;
}

bool student::operator<(const student& other_student) const{
    return student_number < other_student.student_number;
}

bool student::operator>(const student& other_student) const{
    return student_number > other_student.student_number;
}

//data printer----------------------------------------------------------

/** Prints the information of the sutudent.
 * Time complexity: O(1)
 */
void student::print_student() const {
    std::cout << "name: " << student_name << ", Number: " << student_number << endl;
}
