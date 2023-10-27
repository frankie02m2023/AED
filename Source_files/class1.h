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


class class1{
public:
    //constructor
    class1(string class_name, schedule T_class = {"Dont Apply",0, 0 },schedule T_class_2 = {"Dont Apply", 0, 0}, schedule TP_class = {"Dont Apply",0, 0 }, schedule PL_class = {"Dont Apply",0, 0 });

    //getters
    string get_class_name() const;
    schedule get_T_class() const;
    schedule get_T_class_2() const;
    schedule get_TP_class() const;
    schedule get_PL_class() const;
    list<student> get_students() const;

    //setters
    void set_T_class(const schedule& T_time);
    void set_T_class_2(const schedule& T_time);
    void set_TP_class(const schedule& TP_time);
    void set_PL_class(const schedule& PL_time);
    void add_students(student st);
    int get_class_grade() const;

    //operators
    bool operator==(const class1& other_class1) const;
    bool operator!=(const class1& other_class1) const;
    void operator=(const class1& other_class1);

    //functions to convert the time format
    static string convert_class_to_hour_and_minute_format(schedule class_schedule);
    string convert_T_class_to_hour_and_minute_format() const;
    string convert_T_class2_to_hour_and_minute_format() const;
    string convert_TP_class_to_hour_and_minute_format() const;
    string convert_PL_class_to_hour_and_minute_format() const;

    //auxiliary function
    bool student_in_class(student st) const;

    //data printers
    void print_class_data(const string& student_sort_by, const string& student_sort_option) const;
    void print_class_schedule() const;
private:
    string class_name;
    schedule T_class;
    schedule T_class_2;
    schedule TP_class;
    schedule PL_class;
    list<student> students;
};

#endif


