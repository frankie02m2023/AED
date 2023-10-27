//
// Created by lucas on 15/10/2023.
//

#include "course.h"
#include <algorithm>
#include"sorting_options.h"

//constructor ------------------------------------------------------------
course::course(std::string course) {
    course_code = course;
}

//getters ---------------------------------------------------------------
vector<class1> course::get_classes() const{
    return classes;
}

string course::get_course_name() const{
    return course_code;
}

int course::get_course_grade() const {
    return classes[0].get_class_grade();
}

bool course::get_class(class1& cl) const {
    auto it = std::find(classes.begin(),classes.end(),cl);
    if(it != classes.end()){
        cl = *it;
    }
    return it != classes.end();
}

class1 course::get_student_class(student st) const{
    class1 dummy {"Dummy"};
    for(class1 cl: classes){
        if(cl.student_in_class(st))
            return cl;
    }
    return dummy;
}

size_t course::number_of_students() const {
    size_t res = 0;
    for(class1 cl: classes){
        res += cl.get_students().size();
    }
    return res;
}

//setters --------------------------------------------------------------
void course::set_classes(vector<class1> classes){
    this->classes = classes;
}

void course::add_class(class1 cl) {
    classes.push_back(cl);
}

//auxiliary functions ---------------------------------------------------
void course::edit_class(class1 cl, schedule time1, string class_type){
    for (class1 &a_class: classes) {
        if (a_class.get_class_name() == cl.get_class_name()) {
            if (class_type == "T") {
                if(a_class.get_T_class().week_day == "Dont Apply"){
                    a_class.set_T_class(time1);
                }
                else{
                    a_class.set_T_class_2(time1);
                }
            } else if (class_type == "TP") {
                a_class.set_TP_class(time1);
            } else {
                a_class.set_PL_class(time1);
            }
        }
    }
}

bool course::has_student(const student& st) const{
    for(const class1& cl: classes){
        if(cl.student_in_class(st))
            return true;
    }
    return false;
}

//Data printer ----------------------------------------------------------
void course::print_course_data( const string& class_sort_by ,const string& student_sort_by, const string& class_sort_option, const string& student_sort_option) const {
    cout << "----------------------------------------------" << endl;
    cout << "Course Code = " << course_code << endl;
    cout << "Class list for course: " << course_code << endl;
    cout << "\n";
    vector<class1> sorted_classes = classes;
    sorted_classes = sort_class_vector(sorted_classes, class_sort_by, class_sort_option);
    for(class1 aclass : sorted_classes){
        aclass.print_class_data(student_sort_by,student_sort_option);
    }
}

//Operators -----------------------------------------------------------
bool course::operator==(const course& other_course) const {

    return other_course.course_code == course_code;
}

bool course::operator!=(const course& other_course) const {
    return  other_course.course_code != course_code;
}

bool course::operator<(const course& other_course) const {

    return course_code < other_course.course_code;
}
