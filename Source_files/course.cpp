//
// Created by lucas on 15/10/2023.
//

#include "course.h"
#include <algorithm>

course::course(std::string course) {
    course_code = course;
}

vector<class1> course::get_classes() const{
    return classes;
}

void course::set_classes(vector<class1> classes){
    this->classes = classes;
}

string course::get_course_name() const{
    return course_code;
}

void course::add_class(class1 cl) {
    classes.push_back(cl);
}

void course::edit_class(class1 cl, schedule time1, string class_type){
    for (class1 &a_class: classes) {
        if (a_class.get_class_name() == cl.get_class_name()) {
            if (class_type == "T") {
                a_class.set_T_class(time1);
            } else if (class_type == "TP") {
                a_class.set_TP_class(time1);
            } else {
                a_class.set_PL_class(time1);
            }
        }
    }
}

void course::print_course_data() const {
    cout << "----------------------------------------------" << endl;
    cout << "Course Code = " << course_code << endl;
    cout << "Class list for course: " << course_code << endl;
    cout << "\n";
    for(class1 aclass : classes){
        aclass.print_class_data();
    }
}

bool course::get_class(class1& cl) const {
    auto it = std::find(classes.begin(),classes.end(),cl);
    if(it != classes.end()){
        cl = *it;
    }
    return it != classes.end();
}


//TODO
bool course::has_student(student st) const{
    return true;
}

//TODO
class1 course::get_student_class(student st) const{}


bool course::operator==(const course& other_course) const {

    return other_course.course_code == course_code;
}

bool course::operator!=(const course& other_course) const {
    return  other_course.course_code != course_code;
}

bool course::operator<(const course& other_course) const {

    return course_code < other_course.course_code;
}
