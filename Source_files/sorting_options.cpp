//
// Created by lucas on 27/10/2023.
//

#include "sorting_options.h"

/**
* \file sorting_options.cpp
* @brief Implementation of sort functions and sort options.
*/

//student compare options ---------------------------------------------------
//complexity for all compares : O(1)

/** Functions used to compare the students
 */
 ///@{
bool sort_student_name(const student& st1, const student& st2){
    return st1.get_name() < st2.get_name();
}

/** Functions used to compare the students
 */
bool sort_student_name_reverse(const student& st1, const student& st2) {
    return st1.get_name() > st2.get_name();
}

/** Functions used to compare the students
 */
bool sort_student_number(const student& st1, const student& st2){
    return st1.get_number() < st2.get_number();
}

/** Functions used to compare the students
 */
bool sort_student_number_reverse(const student& st1, const student& st2){
    return st1.get_number() > st2.get_number();
}
///@}

//course compare options ----------------------------------------------------
//complexity for almost all compares : O(1)

/**Functions used to compare the courses
 */
 ///@{
bool sort_course_name(const course& c1, const course& c2){
    return c1.get_course_name() < c2.get_course_name();
}

/**Functions used to compare the courses
 */
bool sort_course_name_reverse(const course& c1, const course& c2){
    return c1.get_course_name() > c2.get_course_name();
}

//complexity for occupation compares: O(n)
/**Functions used to compare the courses
 */
bool sort_course_occupation(const course& c1, const course& c2){
    size_t c1_occupation = c1.number_of_students();
    size_t c2_occupation = c2.number_of_students();
    return c1_occupation < c2_occupation;
}

/**Functions used to compare the courses
 */
bool sort_course_occupation_reverse(const course& c1, const course& c2){
    size_t c1_occupation = c1.number_of_students();
    size_t c2_occupation = c2.number_of_students();
    return c1_occupation > c2_occupation;
}
///@}


//class compare options ---------------------------------------------------------
//complexity for non compare function: O(1)
/** Functions used to compare classes
 *
 */
 ///@{
bool sort_class_name(const class1& cl1, const class1& cl2){
    return cl1.get_class_name() < cl2.get_class_name();
}

/** Functions used to compare classes
 *
 */
bool sort_class_name_reverse(const class1& cl1, const class1& cl2){
    return cl1.get_class_name() > cl2.get_class_name();
}

//complexity for occupation functions: O(n)
/** Functions used to compare classes
 *
 */
bool sort_class_occupation(const class1& cl1, const class1& cl2){
    size_t cl1_occupation = cl1.get_students().size();
    size_t cl2_occupation = cl2.get_students().size();
    return cl1_occupation < cl2_occupation;
}

/** Functions used to compare classes
 *
 */
bool sort_class_occupation_reverse(const class1& cl1, const class1& cl2){
    size_t cl1_occupation = cl1.get_students().size();
    size_t cl2_occupation = cl2.get_students().size();
    return cl1_occupation > cl2_occupation;
}

//complexity: O(1)
/** Functions used to compare classes
 *
 */
bool class_schedule_sort(const pair<pair<schedule,string>,course>& s1, const pair<pair<schedule,string>,course>& s2){
    return s1.second < s2.second;
}

//O(1)
/** Functions used to compare classes
 *
 */
bool compare_class_ocupation(const class1& cl1, const class1& cl2){
    size_t cl1_occupation = cl1.get_students().size();
    size_t cl2_occupation = cl2.get_students().size();
    return cl1_occupation < cl2_occupation;
}
///@}

//sorting functions ----------------------------------------------------------------
//complexity: O(nlog(n))
/** Sorts a list of students with various sort options.
 * Time complexity: O(nlog(n))
 * @param sorted_students List with students that will be sorted
 * @param sortby Sorting criteria
 * @param sort_option Sorting order
 */
list<student> sort_students_list(list<student> sorted_students, const string& sortby, const string& sort_option ){
    if(sortby == "name"){
        if(sort_option == "ascending") {
            sorted_students.sort(sort_student_name);
        }
        else if(sort_option == "descending"){
            sorted_students.sort(sort_student_name_reverse);
        }
    }
    else if(sortby == "number"){
        if(sort_option == "ascending"){
            sorted_students.sort(sort_student_number);
        }
        else if(sort_option == "descending"){
            sorted_students.sort(sort_student_number_reverse);
        }
        else{
            cout << "invalid sorting option" << endl;
        }
    }
    else{
        cout << "can´t sort by " << sortby << endl;
    }
    return sorted_students;
}

/** Sorts a vector of courses with various sort options.
 * Time complexity: O(nlog(n))
 * * @param sorted_courses Vector with courses that will be sorted
 * @param sortby Sorting criteria
 * @param sort_option Sorting order
 */
vector<course> sort_course_vector(vector<course> sorted_courses, const string& sortby, const string& sort_option){
    if(sortby == "name") {
        if (sort_option == "ascending") {
            sort(sorted_courses.begin(), sorted_courses.end(), sort_course_name);
        } else if (sort_option == "descending") {
            sort(sorted_courses.begin(), sorted_courses.end(), sort_course_name_reverse);
        } else {
            cout << "Not a valid option for course sorting. Using default setting";
        }
    }
    else if(sortby == "occupation"){
        if(sort_option == "ascending"){
            sort(sorted_courses.begin(), sorted_courses.end(), sort_course_occupation);
        }
        else if(sort_option == "descending"){
            sort(sorted_courses.begin(), sorted_courses.end(), sort_course_occupation_reverse);
        }
        else{
            cout << "Not a valid option for course sorting. Using default setting";
        }
    }
    return sorted_courses;
}

/** Sorts a vector of classes with various sort options.
 * Time complexity: O(nlog(n))
 * * @param sorted_classes Vector with classes that will be sorted
 * @param sortby Sorting criteria
 * @param sort_option Sorting order
 */
vector<class1> sort_class_vector(vector<class1> sorted_classes, const string& sortby, const string& sort_option){
    if(sortby == "name") {
        if (sort_option == "ascending") {
            sort(sorted_classes.begin(), sorted_classes.end(), sort_class_name);
        } else if (sort_option == "descending") {
            sort(sorted_classes.begin(), sorted_classes.end(), sort_class_name_reverse);
        } else {
            cout << "Not a valid option for course sorting. Using default setting";
        }
    }
    else if(sortby == "occupation"){
        if(sort_option == "ascending"){
            sort(sorted_classes.begin(), sorted_classes.end(), sort_class_occupation);
        }
        else if(sort_option == "descending"){
            sort(sorted_classes.begin(), sorted_classes.end(), sort_class_occupation_reverse);
        }
        else{
            cout << "Not a valid option for course sorting. Using default setting";
        }
    }
    return sorted_classes;
}
