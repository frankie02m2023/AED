//
// Created by franc on 12/10/2023.
//
#ifndef CLASS1_H
#define CLASS1_H
#include <list>
#include <string>
#include "student.h"
#include "time.h"

class class1{
public:
    class1(string class_name);
    class1(string class_name, time T_class, time TP_class, time PL_class);
    string get_class_name() const;
    time get_T_class() const;
    time get_TP_class() const;
    time get_PL_class() const;
    void set_T_class(const time& T_time);
    void set_TP_class(const time& TP_time);
    void set_PL_class(const time& PL_time);
    void add_students(student st);
private:
    string class_name;
    time T_class;
    time TP_class;
    time PL_class;
    list<student> students;
};

#endif


