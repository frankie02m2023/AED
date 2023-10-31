//
// Created by franc on 12/10/2023.
//
#ifndef STUDENT_H
#define STUDENT_H
#include <string>
using namespace std;

/**
*\file student.h
* @brief Definition of class student.
*
 * \class student
 * Where are performed some specific functions related to students.
 * Stores the student name and his number.
 */
class student{
public:
    /** @name Constructors
     *
     */
     ///@{
    student(){};
    student(string student_name, string student_number);
    ///@}

    /** @name Getters
     *
     */
     ///@{
    string get_name() const;
    string get_number() const;
    ///@}

    /** @name Operators
     *
     */
     ///@{
    bool operator==(const student& other_student) const;
    bool operator!=(const student& other_student) const;
    bool operator<(const student& other_student) const;
    bool operator>(const student& other_student) const;
    ///@}

    /** @name Data printers
     *
     */
    void print_student() const;

private:
    string student_name;
    string student_number;
};

#endif
