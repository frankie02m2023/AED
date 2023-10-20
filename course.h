#ifndef COURSE_H
#define COURSE_H
#include <string>
#include <vector>
#include "class1.h"
using namespace std;

class course{
public:
    course();
    course(string course);
    string get_course_name() const;
    vector<class1> get_classes() const;
    void add_class(class1 cl);
    bool operator==(const course& other_course) const;
    void edit_class(class1 cl, schedule time1, string class_type);
    void print_course_data() const;

private:
    string course_code;
    vector<class1> classes;
};

#endif