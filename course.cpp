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
