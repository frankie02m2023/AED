//
// Created by franc on 20/10/2023.
//

#ifndef TRABALHOAED_INTERFACE_H
#define TRABALHOAED_INTERFACE_H
#include <set>
#include "course.h"
#include <queue>

/**
 * Class interface. Where are performed the most important functions in our system.
 * Stores a vector with the courses and the requests
 */
class interface {
    vector<course>courses;
public:
    /** @name Basic getters
     *
     */
    ///@{
    vector<course> get_courses() const;
    ///@}

    /** @name Data readers
     *
     */
    ///@{
    void read_data_classes_per_uc();
    void read_data_classes();
    void read_data_students_classes();
    ///@}

    /** @name Advanced getters
     *
     */
     ///@{
    set<pair<pair<schedule,string>,course>> get_class_schedule(class1 a_class) const;
    list<student> get_class_students_for_course(class1 a_class, course a_course) const;
    set<student> get_all_students_in_aCourse(course a_course) const;
    set<student> get_all_students_in_aYear(int year) const;
    size_t number_of_students_in_aYear(int year) const;
    size_t number_of_students_in_anUC(const course& a_course) const;
    size_t number_of_students_in_aClass(const class1& a_class, const course& a_course) const;
    ///@}

    /** @name Data printers
     *
     */
     ///@{
    void consult_class_schedule(const class1& a_class) const;
    void consult_student_schedule(const student& a_student) const;
    void consult_students_in_class_and_course(const class1& a_class, const course& a_course,  const string& sortby = "name", const string& sort_option = "ascending") const;
    void consult_all_students_in_aCourse(const course& a_course,  const string& sortby = "name", const string& sort_option  = "ascending") const;
    void consult_all_students_in_aYear(int year,  const string& sortby = "name", const string& sort_option  = "ascending") const;
    void consult_classes_and_courses_occupation_by_year(int year, const string& uc_sort_by = "occupation", const string& class_sort_by = "occupation",
                                                        const string& sorting_uc  = "ascending", const string& sorting_classes  = "ascending");
    void print_data(const string& uc_sort_by = "name", const string& class_sort_by = "name",const string& student_sort_by = "name",
                    const string& uc_sort_option = "ascending", const string& class_sort_option = "ascending", const string& student_sort_option = "ascending") const;
    ///@}
};


#endif //TRABALHOAED_INTERFACE_H
