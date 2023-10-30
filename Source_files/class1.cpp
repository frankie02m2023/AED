//
// Created by lucas on 15/10/2023.
//

#include <sstream>
#include "class1.h"
#include "sorting_options.h"

short class1::student_capacity = 30;

//constructor --------------------------------------------------
//complexity: O(1)
class1::class1(std::string class_name, schedule T_class, schedule T_class_2, schedule TP_class , schedule PL_class ) {
    this->class_name = class_name;
    this->T_class = T_class;
    this->T_class_2 = T_class_2;
    this->TP_class = TP_class;
    this->PL_class = PL_class;
}


//getters -------------------------------------------------------
//Complexity for all getter: O(1)
schedule class1::get_PL_class() const {
    return PL_class;
}

schedule class1::get_TP_class() const {
    return TP_class;
}

schedule class1::get_T_class() const {
    return T_class;
}

schedule class1::get_T_class_2() const {
    return T_class_2;
}

string class1::get_class_name() const {
    return class_name;
}

list<student> class1::get_students() const {
    return students;
}

int class1::get_class_grade() const{
    return class_name[0] - '0';
}

//setters -----------------------------------------------------
//Complexity for all setter: O(1)
void class1::set_T_class(const schedule& T_time) {
    this->T_class = T_time;
}

void class1::set_T_class_2(const schedule& T_time) {
    this->T_class_2 = T_time;
}

void class1::set_TP_class(const schedule& TP_time) {
    this->TP_class = TP_time;
}

void class1::set_PL_class(const schedule& PL_time) {
    this->PL_class = PL_time;
}

void class1::add_students(const student& st) {
    students.push_back(st);
}

void class1::remove_students(student st) {
    auto it = std::find(students.begin(),students.end(),st);
    students.erase(it);
}

//auxiliary function -------------------------------------------
//complexity O(n)
bool class1::student_in_class(const student& st) const {
    auto it = std::find(students.begin(), students.end(), st);
    return it != students.end();
}

student class1::get_student_in_class(student st) const {
    auto it = std::find(students.begin(),students.end(),st);
    return *it;
}

//operator -----------------------------------------------------
//complexity for all operators: O(1)
bool class1::operator==(const class1& other_class1) const {
    return other_class1.class_name == class_name;
}

bool class1::operator!=(const class1& other_class1) const {
    return other_class1.class_name != class_name;
}

bool class1::operator<(const class1& other_class1) const{
    return class_name < other_class1.class_name;
}


void class1::operator=(const class1& other_class1){
    class_name = other_class1.class_name;
    T_class = other_class1.T_class;
    T_class_2 = other_class1.T_class_2;
    TP_class = other_class1.TP_class;
    PL_class = other_class1.PL_class;
    students = other_class1.students;
}

//functions to convert the time format -------------------------------------------------------------------
//complexity: O(log(n))
string class1::convert_class_to_hour_and_minute_format(const schedule& class_schedule){
    string time_and_duration, start_time_hour, start_time_minute, duration_hours, duration_minutes;
    stringstream ss;

    //get the start hour in the float format from the schedule and convert into string
    int class_start_hour = static_cast<int>(class_schedule.hour);
    ss << class_start_hour;
    start_time_hour = ss.str();

    ss.str("");
    ss.clear();

    //convert the hour into the format '00'
    if(class_start_hour < 10){
        start_time_hour = '0' + start_time_hour;
    }

    //get the start minutes from the schedule and convert into string
    int class_start_minute = (class_schedule.hour - class_start_hour) * 60;
    ss << class_start_minute;
    start_time_minute = ss.str();

    ss.str("");
    ss.clear();

    //convert the start minutes into the format '00'
    if(class_start_minute < 10){
        start_time_minute = '0' + start_time_minute;
    }

    //get duration hour part in the float format and convert it into string
    int class_duration_hours = static_cast<int>(class_schedule.duration);
    ss << class_duration_hours;
    duration_hours = ss.str() + "h ";

    ss.str("");
    ss.clear();

    //get duration minute part and convert it into string
    int class_duration_minutes = (class_schedule.duration - class_duration_hours) * 60;
    ss << class_duration_minutes;
    duration_minutes = ss.str() + "min";

    ss.str("");
    ss.clear();

    //convert the duration minute part into the format '00'
    if(class_duration_minutes == 0){
        duration_minutes = "";
    }

    //joins everything into the format '00:00 Duration = 0h00min'
    time_and_duration = start_time_hour + ':' + start_time_minute + " Duration = " + duration_hours + duration_minutes;
    return time_and_duration;
}

string class1::convert_T_class_to_hour_and_minute_format() const {
    return convert_class_to_hour_and_minute_format(T_class);
}

string class1::convert_T_class2_to_hour_and_minute_format() const {
    return convert_class_to_hour_and_minute_format(T_class_2);
}

string class1::convert_TP_class_to_hour_and_minute_format() const {
    return convert_class_to_hour_and_minute_format(TP_class);
}

string class1::convert_PL_class_to_hour_and_minute_format() const {
    return convert_class_to_hour_and_minute_format(PL_class);
}

//Data printers -----------------------------------------------------------------------------------

//prints all class data
//complexity : O(nlog(n))
void class1::print_class_data(const string& student_sort_by,const string& student_sort_option) const {
    std::cout << "Class name = " << class_name << endl;
    std::cout << "T Class schedule = " << T_class.week_day << " Start time = " << convert_T_class_to_hour_and_minute_format() << endl;
    std::cout << "T Class schedule = " << T_class_2.week_day << " Start time = " << convert_T_class2_to_hour_and_minute_format() << endl;
    std::cout << "TP Class schedule = " << TP_class.week_day << " Start time = " << convert_TP_class_to_hour_and_minute_format() << endl;
    std::cout << "PL Class schedule = " << PL_class.week_day << " Start time = " << convert_PL_class_to_hour_and_minute_format() << endl;

    if(students.empty()){
        std::cout << "There is no student in this class" << endl;
    }
    else{
        list<student> sorted_students = students;
        sorted_students = sort_students_list(sorted_students, student_sort_by, student_sort_option);
        for(const student& s : sorted_students){
            s.print_student();
        }
    }
    std::cout <<'\n';
}

//prints the class schedule
//complexity : O(log(n))
void class1::print_class_schedule() const {
    std::cout << "Class name = " << class_name << endl;
    std::cout << "T Class schedule = " << T_class.week_day << " Start time = " << convert_T_class_to_hour_and_minute_format() << endl;
    std::cout << "T Class 2 schedule = " << T_class_2.week_day << " Start time = " << convert_T_class2_to_hour_and_minute_format() << endl;
    std::cout << "TP Class schedule = " << TP_class.week_day << " Start time = " << convert_TP_class_to_hour_and_minute_format() << endl;
    std::cout << "PL Class schedule = " << PL_class.week_day << " Start time = " << convert_PL_class_to_hour_and_minute_format() << endl;
}

