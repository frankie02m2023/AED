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
    //basic getters
    vector<course> get_courses() const;
    queue<course_request> get_requests() const;

    //Data readers (from files)
    void read_data_classes_per_uc();
    void read_data_classes();
    void read_data_students_classes();

    //Advanced getters
    set<pair<pair<schedule,string>,course>> get_class_schedule(class1 a_class) const;
    list<student> get_class_students_for_course(class1 a_class, course a_course) const;
    set<student> get_all_students_in_aCourse(course a_course) const;
    set<student> get_all_students_in_aYear(int year) const;
    size_t number_of_students_in_aYear(int year) const;
    size_t number_of_students_in_anUC(const course& a_course) const;
    size_t number_of_students_in_aClass(const class1& a_class, const course& a_course) const;

    //Data printers
    void consult_class_schedule(const class1& a_class) const;
    void consult_student_schedule(const student& a_student) const;
    void consult_students_in_class_and_course(const class1& a_class, const course& a_course,  string sortby = "name", string sort_option = "ascending") const;
    void consult_all_students_in_aCourse(const course& a_course,  string sortby = "name", string sort_option  = "ascending") const;
    void consult_all_students_in_aYear(int year,  string sortby = "name", string sort_option  = "ascending") const;
    void consult_classes_and_courses_occupation_by_year(int year, const string& uc_sort_by = "occupation", const string& class_sort_by = "occupation",
                                                        const string& sorting_uc  = "ascending", const string& sorting_classes  = "ascending");
    void print_data(const string& uc_sort_by = "name", const string& class_sort_by = "name",const string& student_sort_by = "name",
                    const string& uc_sort_option = "ascending", const string& class_sort_option = "ascending", const string& student_sort_option = "ascending") const;

};


#endif //TRABALHOAED_INTERFACE_H
