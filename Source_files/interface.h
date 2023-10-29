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
#include "request.h"


class interface {
    vector<course>courses;
    queue<request> requests;
public:
    vector<course> get_courses() const;
    queue<request> get_requests() const;
    void read_data_classes_per_uc();
    void read_data_classes();
    void read_data_students_classes();
    set<pair<pair<schedule,string>,course>> get_class_schedule(class1 a_class) const;
    set<pair<pair<schedule,string>,course>> get_student_schedule(const student& a_student) const;
    set<student> get_class_students_for_all_courses(class1 a_class) const;
    list<student> get_class_students_for_course(class1 a_class, course a_course) const;
    set<student> get_all_students_in_aCourse(course a_course) const;
    set<student> get_all_students_in_aYear(int year) const;
    vector<course> get_all_courses_for_student(const student& a_student) const;
    student get_student(const student& a_student) const;
    size_t number_of_students_in_aYear(int year) const;
    size_t number_of_students_in_anUC(const course& a_course) const;
    size_t number_of_students_in_aClass(const class1& a_class, const course& a_course) const;
    size_t number_of_courses_per_student(const student& a_student) const;
    void consult_class_schedule(const class1& a_class) const;
    void consult_student_schedule_by_schedule(const student& a_student) const;
    void consult_student_schedule_by_course(const student& a_student) const;
    void consult_students_in_class(const class1& a_class) const;
    void consult_students_in_class_and_course(const class1& a_class, const course& a_course) const;
    void consult_all_students_in_aCourse(const course& a_course) const;
    void consult_all_students_in_aYear(int year) const;
    bool can_add_to_class(course& a_course, student& a_student, class1& a_class) const;
    void store_new_request(const request& new_request);
    void process_request(string& error_message);
    bool enroll_student_in_course(student& a_student,course& a_course, class1& a_class, string& error_message);
    bool remove_student_from_course(student& a_student, course& a_course, string& error_message);
    bool switch_student_courses(student& a_student, course& old_course, course& new_course, class1& new_class, string& error_message);
    bool switch_student_classes(student& a_student, course& a_course, class1& old_class, class1& new_class, string& error_message);
    void print_data() const;
    void set_courses(vector<course>);
};


#endif //TRABALHOAED_INTERFACE_H
