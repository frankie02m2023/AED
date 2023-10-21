//
// Created by franc on 12/10/2023.
//
#ifndef CLASS1_H
#define CLASS1_H
#include <list>
#include <string>
#include <iostream>
#include "student.h"
#include "schedule.h"


class class1{
public:
    class1(string class_name, schedule T_class = {"Dont Apply",0, 0 }, schedule TP_class = {"Dont Apply",0, 0 }, schedule PL_class = {"Dont Apply",0, 0 });
    string get_class_name() const;
    schedule get_T_class() const;
    schedule get_TP_class() const;
    schedule get_PL_class() const;
    list<student> get_students() const;
    void set_T_class(const schedule& T_time);
    void set_TP_class(const schedule& TP_time);
    void set_PL_class(const schedule& PL_time);
    void add_students(student st);
    void print_class_data() const;
private:
    string class_name;
    schedule T_class;
    schedule TP_class;
    schedule PL_class;
    list<student> students;
};

#endif


