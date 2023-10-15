#ifndef COURSE_H
#define COURSE_H
#include <string>
#include <vector>
#include "class1.h"
using namespace std;

class course{
public:
    course(string course);
    string get_course_name();
    vector<class1> get_classes();
    void add_class();


private:
    string course_code;
    vector<class1> classes;
};

#endif