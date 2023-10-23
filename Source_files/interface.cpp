//
// Created by franc on 20/10/2023.

#include "interface.h"
#include "schedule.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <utility>
#include <functional>


vector<course> interface::get_courses() const {
    return courses;
}

queue<course_request> interface::get_requests() const {
    return requests;
}

void interface::read_data_classes_per_uc() {
    string file, line;
    file = "classes_per_uc.csv";
    ifstream open_file;
    open_file.open(file);

    if (!open_file.is_open()) {
        std::cerr << "Error: Unable to open the CSV file." << std::endl;
        // Exit the function
    }

    getline(open_file, line); //dummy

    //gets the course and class from the file
    while(getline(open_file, line)){
        //get course
        size_t it1 = line.find_first_of(',');
        course new_course(line.substr(0,it1));

        //confirm if we have already inserted the course
        auto it = std::find(courses.begin(), courses.end(),new_course);
        if(it == courses.end()){
            courses.push_back(new_course);
        }

        //get and insert the new_class
        class1 new_class(line.substr(it1 + 1));
        courses[courses.size() - 1].add_class(new_class);
    }
}

void interface::read_data_classes() {
    string file, line;
    file = "classes.csv";
    ifstream open_file(file);

    if (!open_file.is_open()) {
        std::cerr << "Error: Unable to open the CSV file." << std::endl;
        // Exit the function
    }

    string day_of_the_week, class_type;
    float class_time, class_duration;
    struct schedule time1;
    getline(open_file, line); //dummy

    while (getline(open_file, line)) {
        //get class
        auto it = line.find_first_of(',');
        class1 class_in_line(line.substr(0, it));
        line = line.substr(it+1);

        //get course
        it = line.find_first_of(',');
        course course1(line.substr(0, it));
        line = line.substr(it+1);

        //get days of the week
        it = line.find_first_of(',');
        day_of_the_week = line.substr(0, it);
        line = line.substr(it+1);

        //get class time
        it = line.find_first_of(',');
        class_time = std::stof(line.substr(0, it));
        line = line.substr(it+1);

        //get class duration
        it = line.find_first_of(',');
        class_duration = std::stof(line.substr(0, it));
        line = line.substr(it+1);

        //get class type
        it = line.find_first_of(',');
        class_type = line.substr(0, it);

        //insert values in correct place
        for (course& a_course: courses) {
            if (a_course == course1) {
                time1.hour = class_time;
                time1.duration = class_duration;
                time1.week_day = day_of_the_week;
               a_course.edit_class(class_in_line, time1, class_type);
            }

        }
    }
}

void interface::read_data_students_classes() {
    ifstream f("students_classes.csv");
    string line;

    if (!f.is_open()) {
        std::cerr << "Error: Unable to open the CSV file." << std::endl;
        // Exit the function
    }

    getline(f,line); //dummy

    while(getline(f,line)){
        //get student number
        string student_number;
        size_t s = line.find_first_of(',');
        student_number = line.substr(0, s);
        line = line.substr(s+1);

        //get student name
        string student_name;
        s = line.find_first_of(',');
        student_name = line.substr(0, s);
        line = line.substr(s+1);

        //get ucCode
        string Uccode;
        s = line.find_first_of(',');
        Uccode = line.substr(0, s);
        line = line.substr(s+1);

        //get Classcode
        string class_code;
        s = line.find_first_of(',');
        class_code = line.substr(0, s);
        line = line.substr(s+1);

        //create a new student
        student new_student {student_name, student_number};

        //place student in correct uc and class
        for(course& c: courses){
            if(c.get_course_name() == Uccode){
                vector<class1> classes = c.get_classes();
                for(class1& cl: classes){
                    if(cl.get_class_name() == class_code){
                        cl.add_students(new_student);
                        c.set_classes(classes);
                        break;
                    }
                }
            }
        }
    }
}


//TODO
//Loop through courses and use course::has_class to check if a given course has the class you are looking for
//If it does use course::get_class to get access to the class
//Create a set of pairs where the first pair element is a course and the second is each class schedule
set<pair<pair<schedule,string>,course>> interface::get_class_schedule(class1 a_class) const{
    set<pair<pair<schedule,string>,course>> class_schedule;
    class1 a_class_copy = a_class;
    string class_type;
    for(course a_course : courses){
        if(a_course.get_class(a_class)){
            if(a_class.get_T_class().week_day != "Dont Apply"){
                class_type = "T";
                class_schedule.insert(make_pair(make_pair(a_class.get_T_class(),class_type),a_course));
            }
            if(a_class.get_T_class_2().week_day != "Dont Apply"){
                class_type = "T";
                class_schedule.insert(make_pair(make_pair(a_class.get_T_class_2(),class_type),a_course));
            }
            if(a_class.get_TP_class().week_day != "Dont Apply"){
                class_type = "TP";
                class_schedule.insert(make_pair(make_pair(a_class.get_TP_class(),class_type),a_course));
            }
            if(a_class.get_PL_class().week_day != "Dont Apply"){
                class_type = "PL";
                class_schedule.insert(make_pair(make_pair(a_class.get_PL_class(),class_type),a_course));
            }
        }
        a_class = a_class_copy;
    }
    return class_schedule;
}

//TODO
void interface::consult_class_schedule(class1 a_class) const {
    set<pair<pair<schedule,string>,course>> class_schedule = get_class_schedule(a_class);
    auto it = class_schedule.begin();
    cout << "Schedule for class " << a_class.get_class_name() << ':' << endl;
    while(it != class_schedule.end()){
        cout << "Course " << it->second.get_course_name() << endl;
        cout << "Class " << it->first.second << " Schedule = " << it->first.first.week_day << " " << class1::convert_class_to_hour_and_minute_format(it->first.first) << endl;
        it++;
    }
}

//TODO
//Loop through courses and check if the given student is in course by using course::has_student
//If it does use course::get_student_class to access his scheduled classes for the course
//Create a set of pairs where the first pair element is a course and the second are the students' schedules for the different courses
void interface::consult_student_schedule(student a_student) const{}

void interface::print_data() const{
    cout << "Printing data for the entire system" << endl;
    for(course a_course : courses){
        a_course.print_course_data();
    }
}
