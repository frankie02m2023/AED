//
// Created by lucas on 15/10/2023.
//

#include "course.h"

course::course(std::string course) {
    course_code = course;
}

vector<class1> course::get_classes() const {
    return classes;
}

string course::get_course_name() const{
    return course_code;
}

void course::add_class(class1 cl) {
    classes.push_back(cl);
}

// only works if class exists in classes
class1 course::get_class(class1 cl) const {
    for(class1 a_class : classes){
        if(a_class.get_class_name() == cl.get_class_name()){
            return a_class;
        }
    }
}


bool course::operator==(const course& other_course) const {
    return other_course.course_code == course_code;
}
