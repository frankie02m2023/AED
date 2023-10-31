//
// Created by lucas on 27/10/2023.
//

#ifndef TRABALHOAED_SORTING_OPTIONS_H
#define TRABALHOAED_SORTING_OPTIONS_H

#include "student.h"
#include "course.h"
#include "class1.h"
#include "interface.h"
/** Functions used to sort the data structures in the other files*/

/** @name Student compare options
 *
 */
 ///@{
bool sort_student_name(const student& st1, const student& st2);
bool sort_student_name_reverse(const student& st1, const student& st2);
bool sort_student_number(const student& st1, const student& st2);
bool sort_student_number_reverse(const student& st1, const student& st2);
///@}

/** @name Course compare options
 *
 */
 ///@{
bool sort_course_name(const course& c1, const course& c2);
bool sort_course_name_reverse(const course& c1, const course& c2);
bool sort_course_occupation(const course& c1, const course& c2);
bool sort_course_occupation_reverse(const course& c1, const course& c2);
///@}

/** @name Class compare options
 */
 ///@{
bool sort_class_name(const class1& cl1, const class1& cl2);
bool sort_class_name_reverse(const class1& cl1, const class1& cl2);
bool sort_class_occupation(const class1& cl1, const class1& cl2);
bool sort_class_occupation_reverse(const class1& cl1, const class1& cl2);
bool class_schedule_sort(const pair<pair<schedule,string>,course>& s1, const pair<pair<schedule,string>,course>& s2);
bool compare_class_ocupation(const class1& cl1, const class1& cl2);
///@}


/** @name Sorting functions
 */
 ///@{
list <student> sort_students_list(list<student> sorted_students, const string& sortby, const string& sort_option );
vector<course> sort_course_vector(vector<course> sorted_courses, const string& sortby, const string& sort_option);
vector<class1> sort_class_vector(vector<class1> sorted_classes, const string& sortby, const string& sort_option);
///@}

#endif //TRABALHOAED_SORTING_OPTIONS_H
