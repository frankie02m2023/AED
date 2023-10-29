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

    //auxiliary functions
    class1& get_class_by_ref(class1& cl);
    vector<class1>& get_classes_by_ref();
    bool has_student(student st) const;
    void edit_class(class1 cl, schedule time1, string class_type);
    bool check_class_balance(const class1& cl) const;

    //operators
    bool operator==(const course& other_course) const;
    bool operator!=(const course& other_course) const;
    bool operator<(const course& other_course) const;
    void operator=(const course& other_course);

    //data printer
    void print_course_data() const;

private:
    string course_code;
    vector<class1> classes;
};

bool compare_class_ocupation(const class1& cl1, const class1& cl2);

#endif