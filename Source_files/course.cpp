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
 * @return Vector with the course classes
 */
vector<class1> course::get_classes() const{
    return classes;
}

/**Gets the course name.
 * Time complexity. O(1)
 * @returns String with the Course name
 */
string course::get_course_name() const{
    return course_code;
}

/**Gets the course grade (1,2,3).
 * Time complexity. O(1)
 * @returns Course grade
 */
int course::get_course_grade() const {
    return classes[0].get_class_grade();
}

/**Gets a specific class. Return a boolean confirming if the class exists.
 * Time complexity. O(n)
 * @param cl Class we want to get (object with limited information)
 * @returns True if the class is part of this course and the information about the class was collected or False otherwise
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
 * @param st Student that we want to obtain the class he is enrolled
 * @returns The class the student is enrolled or a generic class if the student isn´t enrolled into a class
 */
class1 course::get_student_class(const student& st) const{
    class1 dummy {"Dummy"};
    for(const class1& cl: classes){
        if(cl.student_in_class(st))
            return cl;
    }
    return dummy;
}

/**Gets a specific class by reference. Always use get_class before get_class_by_reference.
 * Time complexity. O(n)
 * @param cl Class we want to get
 * @returns Returns the class we wanted to get
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
 * @returns Classes by reference
*/
vector<class1>& course::get_classes_by_ref() {
    return classes;
}

/**Gets the number that are enrolled to the course.
 * Time complexity: O(n)
 * @returns Number of students in a class
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
 * @param classes Vector with the classes we want to set
 */
void course::set_classes(vector<class1> classes){
    this->classes = classes;
}

/**Adds a class to the classes vector.
 * Time complexity: O(1)
 * @param cl Class that we want to add
 */
void course::add_class(const class1& cl) {
    classes.push_back(cl);
}


//auxiliary functions ---------------------------------------------------

/** Changes a specific class schedule.
 *  Time complexity: O(n)
 *  @param cl Class we want to edit
 *  @param time1 New Schedule time
 *  @param class_type Class type we want to change the schedule
 */
void course::edit_class(const class1& cl, const schedule& time1, const string& class_type){
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
* Time complexity: O(n^2)
 * @param st Student we want to check
 * @returns True if the student is enrolled into the course or False otherwise*/
bool course::has_student(const student& st) const{
    for(const class1& cl: classes){
        if(cl.student_in_class(st)) //O(n)
            return true;
    }
    return false;
}


/**Checks if the balance between course classes is not disturbed.
* Time complexity: O(nlog(n)
 * @param cl Class we want to check the balance
 * @returns True if the is according to the rules or False otherwise*/
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
 * @param student_sort_by Student sorting criteria
 * @param class_sort_by Class sorting criteria
 * @param student_sort_option Student sorting order (ascending, descending)
 * @param class_sort_option Class sorting order (ascending, descending)
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
