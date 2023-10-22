//
// Created by franc on 22/10/2023.
//

#include "course_request.h"


course_request::course_request(student a_student, course a_course){
    this->request_student = a_student;
    this->target_course = a_course;
}

student course_request::get_student() const {
    return request_student;
}

course course_request::get_target_course() const {
    return target_course;
}

//TODO
bool course_request::is_valid_request() const{return true;}