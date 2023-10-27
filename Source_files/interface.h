//
// Created by franc on 20/10/2023.
//

#ifndef TRABALHOAED_INTERFACE_H
#define TRABALHOAED_INTERFACE_H
#include <set>
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
    set<pair<pair<schedule,string>,course>> get_class_schedule(class1 a_class) const;
    set<student> get_class_students_for_all_courses(class1 a_class) const;
    list<student> get_class_students_for_course(class1 a_class, course a_course) const;
    set<student> get_all_students_in_aCourse(course a_course) const;
    set<student> get_all_students_in_aYear(int year) const;
    size_t number_of_students_in_aYear(int year) const;
    size_t number_of_students_in_anUC(const course& a_course) const;
    size_t number_of_students_in_aClass(const class1& a_class, const course& a_course) const;
    void consult_class_schedule(const class1& a_class) const;
    void consult_student_schedule(const student& a_student) const;
    void consult_students_in_class(const class1& a_class) const;
    void consult_students_in_class_and_course(const class1& a_class, const course& a_course,  string sortby, string sort_option) const;
    void consult_all_students_in_aCourse(const course& a_course,  string sortby, string sort_option) const;
    void consult_all_students_in_aYear(int year,  string sortby, string sort_option) const;
    void consult_classes_and_courses_occupation_by_year(int year, string sorting_uc, string sorting_classes);
    void print_data() const;

};


#endif //TRABALHOAED_INTERFACE_H
