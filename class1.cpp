//
// Created by lucas on 15/10/2023.
//

#include "class1.h"

class1::class1(std::string class_name, schedule T_class, schedule TP_class , schedule PL_class ) {
    this->class_name = class_name;
    this->T_class = T_class;
    this->TP_class = TP_class;
    this->PL_class = PL_class;
}

schedule class1::get_PL_class() const {
    return PL_class;
}

schedule class1::get_TP_class() const {
    return TP_class;
}

schedule class1::get_T_class() const {
    return T_class;
}

string class1::get_class_name() const {
    return class_name;
}

void class1::set_T_class(const schedule& T_time) {
    this->T_class = T_time;
}

void class1::set_TP_class(const schedule& TP_time) {
    this->TP_class = TP_time;
}

void class1::set_PL_class(const schedule& PL_time) {
    this->PL_class = PL_time;
}

void class1::add_students(student st) {
    students.push_back(st);
}

void class1::print_class_data() const {
    std::cout << "Class name = " << class_name << endl;
    std::cout << "T Class schedule = " << T_class.week_day << " Start time - " <<  T_class.hour << " Duration - " << T_class.duration << endl;
    std::cout << "TP Class schedule = " << TP_class.week_day << " Start time - " <<  TP_class.hour << " Duration - " << TP_class.duration << endl;
    std::cout << "PL Class schedule = " << PL_class.week_day << " Start time - " <<  PL_class.hour << " Duration - " << PL_class.duration << endl;
    for(const student& s : students){
        s.print_student();
    }
    if(students.empty()){
        std::cout << "There is no student in this class" << endl;
    }
    std::cout <<'\n';
}

