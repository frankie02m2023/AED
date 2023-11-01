//
// Created by franc on 20/10/2023.
//

#ifndef TRABALHOAED_INTERFACE_H
#define TRABALHOAED_INTERFACE_H
#include <set>
#include "course.h"
#include <queue>
#include "request.h"

/**
 *
* @file interface.h
* @brief Definition of class interface.
*
 *\class interface
 * Where are performed the most important functions in our system.
 * Stores a vector with the courses and a queue with the requests
 */
class interface {
    vector<course>courses;
    queue<request> requests;
    string students_classes_filename;
    string students_requests_filename;
public:
    interface(){};
    /** @name Basic getters
     *
     */
    ///@{
    vector<course> get_courses() const;
    queue<request> get_requests() const;
    string get_students_classes_filename() const;
    string get_students_requests_filename() const;
    ///@}

    /** @name Data readers
     *
     */
    ///@{
    void read_data_classes_per_uc();
    void read_data_classes();
    void read_data_students_classes();
    void read_data_students_requests();
    ///@}

    /** @name Advanced getters
     *
     */
     ///@{
    set<pair<pair<schedule,string>,course>> get_class_schedule(class1 a_class) const;
    set<pair<pair<schedule,string>,course>> get_student_schedule(const student& a_student) const;
    list<student> get_class_students_for_course(class1 a_class, course a_course) const;
    set<student> get_all_students_in_aCourse(course a_course) const;
    set<student> get_all_students_in_aYear(int year) const;
    vector<course> get_all_courses_for_student(const student& a_student) const;
    student get_student(const student& a_student) const;
    size_t number_of_students_in_aYear(int year) const;
    size_t number_of_students_in_anUC(const course& a_course) const;
    size_t number_of_students_in_aClass(const class1& a_class, const course& a_course) const;
    size_t number_of_courses_per_student(const student& a_student) const;
    ///@}

    /** @name Operators
     *
     */
    ///@{
    void operator=(const interface& other_interface);
    ///@}

    /** @name Setters
     *
     */
     ///@{
    void set_students_classes_filename(const string& filename);
    void set_students_requests_filename(const string& filename);
     void set_courses(vector<course>);
     ///@}

     /** @name Request processing functions
      *
      */
     ///@{
     bool can_add_to_class(course& a_course, student& a_student, class1& a_class) const;
    void store_new_request(const request& new_request, const string& new_filename);
    void remove_request(const string& new_filename);
    bool process_request(string& error_message, const string& new_student_filename, const string& new_request_filename);
    bool enroll_student_in_course(student& a_student,course& a_course, class1& a_class, string& error_message);
    bool remove_student_from_course(student& a_student, course& a_course, string& error_message);
    bool switch_student_courses(student& a_student, course& old_course, course& new_course, class1& new_class, string& error_message);
    bool switch_student_classes(student& a_student, course& a_course, class1& old_class, class1& new_class, string& error_message);
    void add_request_to_file(const request& new_request, const string& new_filename);
    void remove_request_from_file(const string& new_request_filename);
    void enroll_student_in_course_in_file(student& a_student, course& a_course, class1& a_class, const string& new_filename);
    void remove_student_from_course_in_file(student& a_student, course& a_course, const string& new_filename);
    void switch_student_courses_in_file(student& a_student, course& old_course, course& new_course, class1& new_class, const string& new_filename);
    void switch_student_classes_in_file(student& a_student, course& a_course, class1& old_class, class1& new_class, const string& filename);
    ///@}

    /** @name Data printers
     *
     */
     ///@{
    void consult_class_schedule(const class1& a_class) const;
    void consult_student_schedule_by_schedule(const student& a_student) const;
    void consult_student_schedule_by_course(const student& a_student) const;
    void consult_students_in_class_and_course(const class1& a_class, const course& a_course,  const string& sortby = "name", const string& sort_option = "ascending") const;
    void consult_all_students_in_aCourse(const course& a_course,  const string& sortby = "name", const string& sort_option  = "ascending") const;
    void consult_all_students_in_aYear(int year,  const string& sortby = "name", const string& sort_option  = "ascending") const;
    void consult_classes_and_courses_occupation_by_year(int year, const string& uc_sort_by = "occupation", const string& class_sort_by = "occupation",
                                                        const string& sorting_uc  = "ascending", const string& sorting_classes  = "ascending");
    void consult_student_requests() const;

    void print_data(const string& uc_sort_by = "name", const string& class_sort_by = "name",const string& student_sort_by = "name",
                    const string& uc_sort_option = "ascending", const string& class_sort_option = "ascending", const string& student_sort_option = "ascending") const;
    ///@}
};


#endif //TRABALHOAED_INTERFACE_H
