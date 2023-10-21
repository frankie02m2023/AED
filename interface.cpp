//
// Created by franc on 20/10/2023.

#include "interface.h"
#include "schedule.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>





void interface::read_data_classes_per_uc() {
    string file, line;
    file = "classes_per_uc.csv";
    ifstream open_file;
    open_file.open(file);
    bool is_trash = true;
    if (!open_file.is_open()) {
        std::cerr << "Error: Unable to open the CSV file." << std::endl;
        // Exit the function
    }
    while(getline(open_file, line)){
        if(!is_trash){
            auto it1 = line.find_first_of(',');
            course new_course(line.substr(0,it1));
            auto it = std::find(courses.begin(), courses.end(),new_course);
            if(it == courses.end()){
                courses.push_back(new_course);
            }
            class1 new_class(line.substr(it1 + 1));
            courses[courses.size() - 1].add_class(new_class);
        }
        else{
            is_trash = false;
        }
    }
}

void interface::read_data_classes() {
    string file, line;
    file = "classes.csv";
    ifstream open_file(file);
    string day_of_the_week, class_type;
    int class_time, class_duration;
    struct schedule time1;
    getline(open_file, line); //dummy

    while (getline(open_file, line)) {
        //get couse
        auto it = line.find_first_of(',');
        course course1(line.substr(0, it));
        line = line.substr(it+1);

        //get class
        it = line.find_first_of(',');
        class1 class_in_line(line.substr(0, it));
        line = line.substr(it+1);

        //get days of the week
        it = line.find_first_of(',');
        day_of_the_week = line.substr(0, it);
        line = line.substr(it+1);

        //get class time
        it = line.find_first_of(',');
        class_time = std::stoi(line.substr(0, it));
        line = line.substr(it+1);

        //get class duration
        it = line.find_first_of(',');
        class_duration = std::stoi(line.substr(0, it));
        line = line.substr(it+1);

        //get class type
        it = line.find_first_of(',');
        class_type = line.substr(0, it);
        for (course &a_course: courses) {
            if (a_course == course1) {
                time1.hour = class_time;
                time1.duration = class_duration;
                time1.week_day = day_of_the_week;
               a_course.edit_class(class_in_line, time1, class_type);
            }

        }
    }
}

void interface::print_data() const{
    cout << "Printing data for the entire system" << endl;
    for(course a_course : courses){
        a_course.print_course_data();
    }
}
