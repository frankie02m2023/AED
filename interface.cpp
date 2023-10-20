//
// Created by franc on 20/10/2023.

#include "interface.h"
#include "time.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>





void interface::read_data_classes_per_uc() {
    string file, line;
    file = "classes_per_uc.csv";
    ifstream open_file(file);
    while(getline(open_file, line)){
        auto it1 = line.find_first_of(',');
        course new_course(line.substr(0,it1));
        auto it = std::find(courses.begin(), courses.end(),new_course);
        if(it == courses.end()){
            courses.push_back(new_course);
        }
        class1 new_class = line.substr(it1);
        new_course.add_class(new_class);
    }
}

void interface::read_data_classes() {
    string file, line;
    file = "classes.csv";
    ifstream open_file(file);
    string day_of_the_week, class_type;
    float class_time, class_duration;
    struct time time1;
    while (getline(open_file, line)) {
        auto it = line.find_first_of(',');
        course course1(line.substr(0, it));
        line = line.substr(it);
        it = line.find_first_of(',');
        class1 class_in_line(line.substr(0, it));
        line = line.substr(it);
        it = line.find_first_of(',');
        day_of_the_week = line.substr(0, it);
        line = line.substr(it);
        it = line.find_first_of(',');
        class_time = std::stoi(line.substr(0, it));
        line = line.substr(it);
        it = line.find_first_of(',');
        class_duration = std::stoi(line.substr(0, it));
        line = line.substr(it);
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

