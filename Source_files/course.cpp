//
// Created by lucas on 15/10/2023.
//

#include "course.h"
#include <algorithm>
#include"sorting_options.h"

/**
* @file course.cpp
* @brief Implementation of class course.
*/

//constructor ------------------------------------------------------------
course::course(std::string course) {
    course_code = course;
}

//getters ---------------------------------------------------------------
//complexity for almost all getters: O(1)

/**Gets the classes vector.
 * Time complexity. O(1)
 */
vector<class1> course::get_classes() const{
    return classes;
}

/**Gets the course name.
 * Time complexity. O(1)
 */
string course::get_course_name() const{
    return course_code;
}

/**Gets the course grade (1,2,3).
 * Time complexity. O(1)
 */
int course::get_course_grade() const {
    return classes[0].get_class_grade();
}

/**Gets a specific class. Return a boolean confirming if the class exists.
 * Time complexity. O(n)
 */
bool course::get_class(class1& cl) const {
    auto it = std::find(classes.begin(),classes.end(),cl);
    if(it != classes.end()){
        cl = *it;
    }
    return it != classes.end();
}

/**Gets a specific student class. If it is not found, a generic class("dummy") is returned.
 * Time complexity. O(n^2)
 */
class1 course::get_student_class(student st) const{
    class1 dummy {"Dummy"};
    for(class1 cl: classes){
        if(cl.student_in_class(st))
            return cl;
    }
    return dummy;
}

/**Gets a specific class by reference. Always use get_class before get_class_by_reference.
 * Time complexity. O(n)
 */
class1& course::get_class_by_ref(class1& cl) {
    auto it = std::find(classes.begin(),classes.end(),cl);
    class1 &cl1 = *it;
    if(it != classes.end()){
        return cl1;
    }
    return cl;
}

/**Gets the classes vector by reference.
* Time complexity. O(1)
*/
vector<class1>& course::get_classes_by_ref() {
    return classes;
}

/**Gets the number that are enrolled to the course.
 * Time complexity: O(n)
 */
size_t course::number_of_students() const {
    size_t res = 0;
    for(class1 cl: classes){
        res += cl.get_students().size();
    }
    return res;
}

//setters --------------------------------------------------------------
//complexity for all setters: O(1)

/**Sets the classes vector.
 * Time complexity: O(1).
 */
void course::set_classes(vector<class1> classes){
    this->classes = classes;
}

/**Adds a class to the classes vector.
 * Time complexity: O(1)
 */
void course::add_class(class1 cl) {
    classes.push_back(cl);
}


//auxiliary functions ---------------------------------------------------

/** Changes a specific class schedule.
 *  Time complexity: O(n)
 */
void course::edit_class(class1 cl, schedule time1, string class_type){
    for (class1 &a_class: classes) {
        if (a_class.get_class_name() == cl.get_class_name()) {
            if (class_type == "T") {
                if(a_class.get_T_class().week_day == "Dont Apply"){
                    a_class.set_T_class(time1);
                }
                else{
                    a_class.set_T_class_2(time1);
                }
            } else if (class_type == "TP") {
                a_class.set_TP_class(time1);
            } else {
                a_class.set_PL_class(time1);
            }
        }
    }
}

/**Checks if a student attends to a specific class of the course
* Time complexity: O(n^2) */
bool course::has_student(const student& st) const{
    for(const class1& cl: classes){
        if(cl.student_in_class(st)) //O(n)
            return true;
    }
    return false;
}


/**Checks if the balance between course classes is not disturbed.
* Time complexity: O(nlog(n) */
bool course::check_class_balance(const class1& cl) const {
    vector<class1> copy_classes = classes;
    sort(copy_classes.begin(), copy_classes.end(), compare_class_ocupation);
    size_t min_ocupation = copy_classes[0].get_students().size();
    size_t target_class_ocupation = cl.get_students().size();
    if(target_class_ocupation - min_ocupation > 4){
        return false;
    }
    return true;
}

//Data printer ----------------------------------------------------------

/**Prints all the course data.
 * Time complexity: O(nlog(n))
 */
void course::print_course_data( const string& class_sort_by ,const string& student_sort_by, const string& class_sort_option, const string& student_sort_option) const {
    cout << "----------------------------------------------" << endl;
    cout << "Course Code = " << course_code << endl;
    cout << "Class list for course: " << course_code << endl;
    cout << "\n";
    vector<class1> sorted_classes = classes;
    sorted_classes = sort_class_vector(sorted_classes, class_sort_by, class_sort_option);
    for(class1 aclass : sorted_classes){
        aclass.print_class_data(student_sort_by,student_sort_option);
    }
}

//Operators -----------------------------------------------------------
//complexity for all operators: O(1)
bool course::operator==(const course& other_course) const {

    return other_course.course_code == course_code;
}

bool course::operator!=(const course& other_course) const {
    return  other_course.course_code != course_code;
}

bool course::operator<(const course& other_course) const {

    return course_code < other_course.course_code;
}

void course::operator=(const course &other_course) {
    course_code = other_course.course_code;
    classes = other_course.classes;
}
