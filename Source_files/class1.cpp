//
// Created by lucas on 15/10/2023.
//

#include <sstream>
#include "class1.h"
#include "sorting_options.h"
/**
* @file class1.cpp
* @brief Implementation of class class1.
*/
short class1::student_capacity = 30;

//constructor --------------------------------------------------
// Time complexity: O(1)
class1::class1(std::string class_name, schedule T_class, schedule T_class_2, schedule TP_class , schedule PL_class ) {
    this->class_name = class_name;
    this->T_class = T_class;
    this->T_class_2 = T_class_2;
    this->TP_class = TP_class;
    this->PL_class = PL_class;
}


//getters -------------------------------------------------------
//Complexity for all getter: O(1)

/** Gets the PL class schedule.
 * Time complexity: O(1)
 * @returns PL class schedule
 */
schedule class1::get_PL_class() const {
    return PL_class;
}

/** Gets the TP class schedule.
 * Time complexity: O(1)
 * @returns TP class schedule
 */
schedule class1::get_TP_class() const {
    return TP_class;
}

/** Gets the T class schedule.
 * Time complexity: O(1)
 * @returns T class schedule
 */
schedule class1::get_T_class() const {
    return T_class;
}

/** Gets the T_2 class schedule.
 * Time complexity: O(1)
 * @returns T_class_2 schedule
 */
schedule class1::get_T_class_2() const {
    return T_class_2;
}

/** Gets the class name.
 * Time complexity: O(1)
 * @return class name
 */
string class1::get_class_name() const {
    return class_name;
}

/** Gets the students list.
 * Time complexity: O(1)
 * @returns List of students that are enrolled into the class
 */
list<student> class1::get_students() const {
    return students;
}

/** Gets the grade of the class (1,2,3).
 * Time complexity: O(1)
 * @returns Class grade
 */
int class1::get_class_grade() const{
    return class_name[0] - '0';
}

//setters -----------------------------------------------------
//Complexity for all setter: O(1)

/** Sets the T Schedule.
 * Time complexity: O(1)
 * @param T_time New schedule
 */
void class1::set_T_class(const schedule& T_time) {
    this->T_class = T_time;
}

/** Sets the T_2 Schedule.
 * Time complexity: O(1)
 * * @param T_time New schedule
 */
void class1::set_T_class_2(const schedule& T_time) {
    this->T_class_2 = T_time;
}

/** Sets the TP Schedule.
 * Time complexity: O(1)
 * * @param TP_time New schedule
 */
void class1::set_TP_class(const schedule& TP_time) {
    this->TP_class = TP_time;
}

/** Sets the PL Schedule.
 * Time complexity: O(1)
 * * @param PL_time New schedule
 */
void class1::set_PL_class(const schedule& PL_time) {
    this->PL_class = PL_time;
}

/** Adds student to the students list.
 * Time complexity: O(1)
 * @param st Student that will be added
 */
void class1::add_students(const student& st) {
    students.push_back(st);
}

/** Removes student from student list.
 * Time complexity: O(n)
 * @param st Student that will be removed
 */
void class1::remove_students(const student& st) {
    auto it = std::find(students.begin(),students.end(),st);
    students.erase(it);
}

//auxiliary function -------------------------------------------
//complexity O(n)
/** Checks if a student belongs to the class.
 * Time complexity: O(n)
 * @param st Student we want to check
 * @returns True if the student is in this class or False otherwise
 */
bool class1::student_in_class(const student& st) const {
    auto it = std::find(students.begin(), students.end(), st);
    return it != students.end();
}

/**Gets a  specific student in the students list.
 * Time complexity: O(n)
 * @param st student we want to get (Object only with some information)
 * @returns Student with all the information
 */
student class1::get_student_in_class(const student& st) const {
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

/** Converts the time format from a simple float format to the string format '00:00'.
* Time complexity: O(log(n))
 * @param class_schedule Schedule for a specific class
 * @returns String with the pretended hour and minute format*/
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

/** Converts the T time format from a simple float format to the string format '00:00'.
* Time complexity: O(log(n))
 * @returns String with the pretended hour and minute format*/
string class1::convert_T_class_to_hour_and_minute_format() const {
    return convert_class_to_hour_and_minute_format(T_class);
}

/** Converts the T_2 time format from a simple float format to the string format '00:00'.
* Time complexity: O(log(n))
 * @returns String with the pretended hour and minute format*/
string class1::convert_T_class2_to_hour_and_minute_format() const {
    return convert_class_to_hour_and_minute_format(T_class_2);
}

/** Converts the TP time format from a simple float format to the string format '00:00'.
* Time complexity: O(log(n))
 * @returns String with the pretended hour and minute format*/
string class1::convert_TP_class_to_hour_and_minute_format() const {
    return convert_class_to_hour_and_minute_format(TP_class);
}

/** Converts the PL time format from a simple float format to the string format '00:00'.
* Time complexity: O(log(n))
 * @returns String with the pretended hour and minute format*/
string class1::convert_PL_class_to_hour_and_minute_format() const {
    return convert_class_to_hour_and_minute_format(PL_class);
}

//Data printers -----------------------------------------------------------------------------------

/**Prints all class data.
*Time complexity : O(nlog(n))
 * @param student_sort_by Student sorting criteria
 * @param student_sort_option Student sorting order (ascending, descending)*/
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

/**Prints the class schedule.
*Time complexity : O(log(n))*/
void class1::print_class_schedule() const {
    std::cout << "Class name = " << class_name << endl;
    if(T_class.week_day != "Dont Apply"){
        std::cout << "T Class schedule = " << T_class.week_day << " Start time = " << convert_T_class_to_hour_and_minute_format() << endl;
    }
    if(T_class_2.week_day != "Dont Apply"){
        std::cout << "T Class schedule = " << T_class_2.week_day << " Start time = " << convert_T_class2_to_hour_and_minute_format() << endl;
    }
    if(TP_class.week_day != "Dont Apply"){
        std::cout << "TP Class schedule = " << TP_class.week_day << " Start time = " << convert_TP_class_to_hour_and_minute_format() << endl;
    }
    if(PL_class.week_day != "Dont Apply"){
        std::cout << "PL Class schedule = " << PL_class.week_day << " Start time = " << convert_PL_class_to_hour_and_minute_format() << endl;
    }
}

