//
// Created by lucas on 27/10/2023.
//


//Sorting options -------------------------------------
#include "sorting_options.h"

//student compare options ---------------------------------------------------
//complexity for all compares : O(1)
bool sort_student_name(const student& st1, const student& st2){
    return st1.get_name() < st2.get_name();
}

bool sort_student_name_reverse(const student& st1, const student& st2) {
    return st1.get_name() > st2.get_name();
}

bool sort_student_number(const student& st1, const student& st2){
    return st1.get_number() < st2.get_number();
}

bool sort_student_number_reverse(const student& st1, const student& st2){
    return st1.get_number() > st2.get_number();
}

//course compare options ----------------------------------------------------
//complexity for almost all compares : O(1)
bool sort_course_name(const course& c1, const course& c2){
    return c1.get_course_name() < c2.get_course_name();
}

bool sort_course_name_reverse(const course& c1, const course& c2){
    return c1.get_course_name() > c2.get_course_name();
}

//complexity for occupation compares: O(n)
bool sort_course_occupation(const course& c1, const course& c2){
    size_t c1_occupation = c1.number_of_students();
    size_t c2_occupation = c2.number_of_students();
    return c1_occupation < c2_occupation;
}

bool sort_course_occupation_reverse(const course& c1, const course& c2){
    size_t c1_occupation = c1.number_of_students();
    size_t c2_occupation = c2.number_of_students();
    return c1_occupation > c2_occupation;
}


//class compare options ---------------------------------------------------------
//complexity for non compare function: O(1)
bool sort_class_name(const class1& cl1, const class1& cl2){
    return cl1.get_class_name() < cl2.get_class_name();
}

bool sort_class_name_reverse(const class1& cl1, const class1& cl2){
    return cl1.get_class_name() > cl2.get_class_name();
}

//complexity for occupation functions: O(n)
bool sort_class_occupation(const class1& cl1, const class1& cl2){
    size_t cl1_occupation = cl1.get_students().size();
    size_t cl2_occupation = cl2.get_students().size();
    return cl1_occupation < cl2_occupation;
}

bool sort_class_occupation_reverse(const class1& cl1, const class1& cl2){
    size_t cl1_occupation = cl1.get_students().size();
    size_t cl2_occupation = cl2.get_students().size();
    return cl1_occupation > cl2_occupation;
}

//complexity: O(1)
bool class_schedule_sort(const pair<pair<schedule,string>,course>& s1, const pair<pair<schedule,string>,course>& s2){
    return s1.second < s2.second;
}

//O(1)
bool compare_class_ocupation(const class1& cl1, const class1& cl2){
    size_t cl1_occupation = cl1.get_students().size();
    size_t cl2_occupation = cl2.get_students().size();
    return cl1_occupation < cl2_occupation;
}


//sorting functions ----------------------------------------------------------------
//complexity: O(nlog(n))
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

//complexity: O(nlog(n))
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

//complexity: O(nlog(n))
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
