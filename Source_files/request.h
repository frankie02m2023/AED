//
// Created by franc on 27/10/2023.
//

#ifndef TRABALHOAED_REQUEST_H
#define TRABALHOAED_REQUEST_H
#include "course.h"

struct request {
    string request_type;
    student target_student;
    course added_course;
    course removed_course;
    class1 added_class;
    class1 removed_class;
};


#endif //TRABALHOAED_REQUEST_H
