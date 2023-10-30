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
    void consult_all_students_in_aCourse(course a_course, const string& sort_by = "name", const string& sort_option ="ascending") const;
    void consult_all_students_in_aYear(int year,  const string& sortby = "name", const string& sort_option  = "ascending") const;
    void consult_classes_and_courses_occupation_by_year(int year, const string& uc_sort_by = "occupation", const string& class_sort_by = "occupation",const string& sorting_uc  = "ascending", const string& sorting_classes  = "ascending");
    void store_new_request(const request& new_request);
    void process_request(string& error_message);
    void print_current_schedule_system_data() const;
};


#endif //TRABALHOAED_SCHEDULE_SYSTEM_H
