//
// Created by franc on 12/10/2023.
//
#ifdef CLASS1_H
#define CLASS1_H
#include <list>
#include <string>
#include "student.h"
#include "time.h"

class class1{
public:
    class1(string class_name, time T_class, time TP_class, time PL_class);
    string get_class_name() const;
    time get_T_class() const;
    time get_TP_class() const;
    time get_PL_class() const;
private:
    string class_name;
    time T_class;
    time TP_class;
    time PL_class;
    list<student> students;
};

#endif


