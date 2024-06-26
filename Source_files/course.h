#ifndef COURSE_H
#define COURSE_H
#include <string>
#include <vector>
#include "class1.h"
using namespace std;

/**
* @file course.h
* @brief Definition of class course.
 *
 *\class course
 * Where are performed specific functions related to the courses.
 *  Stores the course code and a vector with his classes.
 */
class course{
public:
    /** @name Constructors
     *
     */
     ///@{
    course(){};
    course(string course);
    ///@}

    /** @name Getters
     *
     */
     ///@{
    string get_course_name() const;
    vector<class1> get_classes() const;
    bool get_class(class1& cl) const;
    int get_course_grade() const;
    class1 get_student_class(const student& st) const;
    size_t number_of_students() const;
    ///@}

    /** @name Setters
     *
     */
     ///@{
    void set_classes(vector<class1> classes);
    void add_class(const class1& cl);
    ///@}

    /** @name Auxiliary functions
     *
     */
     ///@{
    class1& get_class_by_ref(class1& cl);
    vector<class1>& get_classes_by_ref();
    bool has_student(const student& st) const;
    void edit_class(const class1& cl, const schedule& time1, const string& class_type);
    bool check_class_balance(const class1& cl) const;
    ///@}

    /**@name Operators
     *
     */
     ///@{
    bool operator==(const course& other_course) const;
    bool operator!=(const course& other_course) const;
    bool operator<(const course& other_course) const;
    void operator=(const course& other_course);
    ///@}

    /**@name Data printer
     *
     */
     ///@{
    void print_course_data( const string& class_sort_by ,const string& student_sort_by, const string& class_sort_option, const string& student_sort_option) const;
    ///@}

private:
    string course_code;
    vector<class1> classes;
};

#endif