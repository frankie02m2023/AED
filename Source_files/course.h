#ifndef COURSE_H
#define COURSE_H
#include <string>
#include <vector>
#include "class1.h"
using namespace std;

class course{
public:
    //constructors
    course(){};
    course(string course);

    //getters
    string get_course_name() const;
    vector<class1> get_classes() const;
    bool get_class(class1& cl) const;
    int get_course_grade() const;
    class1 get_student_class(student st) const;
    size_t number_of_students() const;

    //setters
    void set_classes(vector<class1> classes);
    void add_class(class1 cl);

    //auxiliary
    bool has_student(const student& st) const;
    void edit_class(class1 cl, schedule time1, string class_type);

    //operators
    bool operator==(const course& other_course) const;
    bool operator!=(const course& other_course) const;
    bool operator<(const course& other_course) const;

    //Data printer
    void print_course_data( const string& class_sort_by ,const string& student_sort_by, const string& class_sort_option, const string& student_sort_option) const;

private:
    string course_code;
    vector<class1> classes;
};

#endif