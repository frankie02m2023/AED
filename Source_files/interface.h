//
// Created by franc on 20/10/2023.
//

#ifndef TRABALHOAED_INTERFACE_H
#define TRABALHOAED_INTERFACE_H
#include "course.h"
#include <queue>
#include "course_request.h"
#include "course_class_request.h"


class interface {
    vector<course>courses;
    queue<course_request> requests;
public:
    vector<course> get_courses() const;
    queue<course_request> get_requests() const;
    void read_data_classes_per_uc();
    void read_data_classes();
    void read_data_students_classes();
    void consult_class_schedule(class1 a_class) const;
    void consult_student_schedule(student a_student) const;
    void print_data() const;
};


#endif //TRABALHOAED_INTERFACE_H
