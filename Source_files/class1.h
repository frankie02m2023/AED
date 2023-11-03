//
// Created by franc on 12/10/2023.
//
#ifndef CLASS1_H
#define CLASS1_H
#include <algorithm>
#include <list>
#include <string>
#include <iostream>
#include "student.h"
#include "schedule.h"


/**
 *\file class1.h
 * @brief Definition of class class1.
 *
 *\class class1
 * Where are performed specific functions related to the classes.
 * Stores the name of the class, its schedule and a list of students that are registered in this class.
 */

class class1{
public:
    /** @name Constructors
     *
     */
     ///@{
    class1(){};
    class1(string class_name, schedule T_class = {"Dont Apply",0, 0 },schedule T_class_2 = {"Dont Apply", 0, 0}, schedule TP_class = {"Dont Apply",0, 0 }, schedule PL_class = {"Dont Apply",0, 0 });
    ///@}

    /**static variable determining the maximum number of students allowed in any class
     *
     */
    static short student_capacity;


    /** @name Getters
     *
     */
     ///@{
    string get_class_name() const;
    schedule get_T_class() const;
    schedule get_T_class_2() const;
    schedule get_TP_class() const;
    schedule get_PL_class() const;
    list<student> get_students() const;
    int get_class_grade() const;
    ///@}

    /** @name Setters
     *
     */
     ///@{
    void set_T_class(const schedule& T_time);
    void set_T_class_2(const schedule& T_time);
    void set_TP_class(const schedule& TP_time);
    void set_PL_class(const schedule& PL_time);
    void add_students(const student& st);
    void remove_students(const student& st);
    ///@}

    /** @name Operators
     *
     */
     ///@{
    bool operator==(const class1& other_class1) const;
    bool operator!=(const class1& other_class1) const;
    bool operator<(const class1& other_class1) const;
    void operator=(const class1& other_class1);
    ///@}

    /** @name Functions to convert the time format
     *
     */
     ///@{
    static string convert_class_to_hour_and_minute_format(const schedule& class_schedule);
    string convert_T_class_to_hour_and_minute_format() const;
    string convert_T_class2_to_hour_and_minute_format() const;
    string convert_TP_class_to_hour_and_minute_format() const;
    string convert_PL_class_to_hour_and_minute_format() const;
    ///@}

    /** @name Auxiliary functions
     *
     */
     ///@{
    bool student_in_class(const student& st) const;
    student get_student_in_class(const student& st) const;
    ///@}

    /** @name data printers
     *
     */
     ///@{
    void print_class_data(const string& student_sort_by, const string& student_sort_option) const;
    void print_class_schedule() const;
    ///@}

private:
    string class_name;
    schedule T_class;
    schedule T_class_2;
    schedule TP_class;
    schedule PL_class;
    list<student> students;
};

#endif


