//
// Created by franc on 12/10/2023.
//

#include <string>
using namespace std;

class student{
public:
    student(string student_name, string student_number);
    string get_name();
    string get_number();

private:
    string student_name;
    string student_number;
};
