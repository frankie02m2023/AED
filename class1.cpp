//
// Created by lucas on 15/10/2023.
//

#include "class1.h"

class1::class1(std::string class_name){
    this->class_name = class_name;
}

class1::class1(std::string class_name, time T_class, time TP_class, time PL_class) {
    this->class_name = class_name;
    this->T_class = T_class;
    this->TP_class = TP_class;
    this->PL_class = PL_class;
}

time class1::get_PL_class() const {
    return PL_class;
}

time class1::get_TP_class() const {
    return TP_class;
}

time class1::get_T_class() const {
    return T_class;
}

string class1::get_class_name() const {
    return class_name;
}

void class1::set_T_class(const time& T_time) {
    this->T_class = T_time;
}

void class1::set_TP_class(const time& TP_time) {
    this->TP_class = TP_time;
}

void class1::set_PL_class(const time& PL_time) {
    this->PL_class = PL_time;
}

void class1::add_students(student st) {
    students.push_back(st);
}