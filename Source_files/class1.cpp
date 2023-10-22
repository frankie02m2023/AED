//
// Created by lucas on 15/10/2023.
//

#include <sstream>
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

list<student> class1::get_students() const {
    return students;
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

bool class1::student_in_class(student st) const {
    auto it = std::find(students.begin(), students.end(), st);
    return it != students.end();
}

bool class1::operator==(const class1& other_class1) const {
    return other_class1.class_name == class_name;
}

bool class1::operator!=(const class1& other_class1) const {
    return other_class1.class_name != class_name;
}

string class1::convert_class_to_hour_and_minute_format(schedule class_schedule) const {
    string time_and_duration, start_time_hour, start_time_minute, duration_hours, duration_minutes;
    stringstream ss;
    int class_start_hour = static_cast<int>(class_schedule.hour);
    ss << class_start_hour;
    start_time_hour = ss.str();
    ss.str("");
    ss.clear();
    if(class_start_hour < 10){
        start_time_hour = '0' + start_time_hour;
    }
    int class_start_minute = (class_schedule.hour - class_start_hour) * 60;
    ss << class_start_minute;
    start_time_minute = ss.str();
    ss.str("");
    ss.clear();
    if(class_start_minute < 10){
        start_time_minute = '0' + start_time_minute;
    }
    int class_duration_hours = static_cast<int>(class_schedule.duration);
    ss << class_duration_hours;
    duration_hours = ss.str() + "h ";
    ss.str("");
    ss.clear();
    int class_duration_minutes = (class_schedule.duration - class_duration_hours) * 60;
    ss << class_duration_minutes;
    duration_minutes = ss.str() + "min";
    ss.str("");
    ss.clear();
    if(class_duration_minutes == 0){
        duration_minutes = "";
    }
    time_and_duration = start_time_hour + ':' + start_time_minute + " Duration = " + duration_hours + duration_minutes;
    return time_and_duration;
}

string class1::convert_T_class_to_hour_and_minute_format() const {
    return convert_class_to_hour_and_minute_format(T_class);
}

string class1::convert_TP_class_to_hour_and_minute_format() const {
    return convert_class_to_hour_and_minute_format(TP_class);
}

string class1::convert_PL_class_to_hour_and_minute_format() const {
    return convert_class_to_hour_and_minute_format(PL_class);
}

void class1::print_class_data() const {
    std::cout << "Class name = " << class_name << endl;
    std::cout << "T Class schedule = " << T_class.week_day << " Start time = " << convert_T_class_to_hour_and_minute_format() << endl;
    std::cout << "TP Class schedule = " << TP_class.week_day << " Start time = " << convert_TP_class_to_hour_and_minute_format() << endl;
    std::cout << "PL Class schedule = " << PL_class.week_day << " Start time = " << convert_PL_class_to_hour_and_minute_format() << endl;
    for(const student& s : students){
        s.print_student();
    }
    if(students.empty()){
        std::cout << "There is no student in this class" << endl;
    }
    std::cout <<'\n';
}

