//
// Created by franc on 22/10/2023.
//

#ifndef TRABALHOAED_COURSE_CLASS_REQUEST_H
#define TRABALHOAED_COURSE_CLASS_REQUEST_H


#include "course_request.h"

class course_class_request : public course_request{
    class1 target_class;
public:
    course_class_request(student a_student, course a_course, class1 a_class);
    class1 get_target_class() const;
    bool is_valid_request() const override;
};


#endif //TRABALHOAED_COURSE_CLASS_REQUEST_H
