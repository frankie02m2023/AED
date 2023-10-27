//
// Created by franc on 22/10/2023.
//

#ifndef TRABALHOAED_SCHEDULE_SYSTEM_H
#define TRABALHOAED_SCHEDULE_SYSTEM_H
#include "interface.h"
#include <stack>

class schedule_system {
public:
    stack<interface> system_changes;
    schedule_system();
    void schedule_system_functions();
    void consult_class_schedule(class1 a_class) const;
    void consult_student_schedule(student a_student) const;
    void consult_students_in_class_and_course(class1 a_class, course a_course, string sortby, string sort_option) const;
    void consult_students_in_class(class1 a_class) const;
    void print_current_schedule_system_data() const;
};


#endif //TRABALHOAED_SCHEDULE_SYSTEM_H
