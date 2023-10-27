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

int course::get_course_grade() const {
    return classes[0].get_class_grade();
}
//TODO
bool course::has_student(student st) const{
    for(class1 cl: classes){
        if(cl.student_in_class(st))
            return true;
    }
    return false;
}

//TODO
class1 course::get_student_class(student st) const{
    class1 dummy {"Dummy"};
    for(class1 cl: classes){
        if(cl.student_in_class(st))
            return cl;
    }
    return dummy;
}


bool course::operator==(const course& other_course) const {

    return other_course.course_code == course_code;
}

bool course::operator!=(const course& other_course) const {
    return  other_course.course_code != course_code;
}

bool course::operator<(const course& other_course) const {

    return course_code < other_course.course_code;
}

bool compare_class_ocupation(class1 cl1, class1 cl2){
    if(cl1.get_students().size() <= cl2.get_students().size()){
        return true;
    }
    return false;
}

//Checking if the balance between course classes is not disturbed
bool course::check_class_balance() const {
    vector<class1> copy_classes = classes;
    sort(copy_classes.begin(), copy_classes.end(), compare_class_ocupation);
    size_t min_ocupation = copy_classes[0].get_students().size();
    size_t max_ocupation = copy_classes[copy_classes.size()].get_students().size();
    if(max_ocupation - min_ocupation > 4){
        return false;
    }
    return true;
}

bool course::can_add_student_to_class(class1 &cl, student& st) {
    vector<class1> copy_course_classes = classes;
    class1 copy_a_class = cl;
    if(cl.get_students().size() == class1::student_capacity){
        return false;
    }
    cl.add_students(st);
    if(!check_class_balance()){
        return false;
    }
    // need to get student schedule
    classes = copy_course_classes;
    cl = copy_a_class;
    return true;
}
