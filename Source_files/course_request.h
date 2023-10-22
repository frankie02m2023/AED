//
// Created by franc on 22/10/2023.
//

#ifndef TRABALHOAED_COURSE_REQUEST_H
#define TRABALHOAED_COURSE_REQUEST_H
#include "course.h"

class course_request {
   student request_student;
   course target_course;
public:
    course_request(student a_student, course a_course);
    student get_student() const;
    course get_target_course() const;
    virtual bool is_valid_request() const;
};


#endif //TRABALHOAED_COURSE_REQUEST_H
