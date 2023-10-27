#ifndef COURSE_H
#define COURSE_H
#include <string>
#include <vector>
#include "class1.h"
using namespace std;

class course{
public:
    course(){};
    course(string course);
    string get_course_name() const;
    vector<class1> get_classes() const;
    void set_classes(vector<class1> classes);
    void add_class(class1 cl);
    bool get_class(class1& cl) const;
    bool has_student(student st) const;
    int get_course_grade() const;
    class1 get_student_class(student st) const;
    bool operator==(const course& other_course) const;
    bool operator!=(const course& other_course) const;
    bool operator<(const course& other_course) const;
    void edit_class(class1 cl, schedule time1, string class_type);
    void print_course_data() const;
    size_t number_of_students() const;

private:
    string course_code;
    vector<class1> classes;
};

#endif