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
#include"sorting_options.h"
//----------------------------------------------------------------------------------------
//Basic getters
vector<course> interface::get_courses() const {
    return courses;
}

queue<course_request> interface::get_requests() const {
    return requests;
}


//--------------------------------------------------------------------------------------
//Data readers (from files)

//reads data from the file "classes_per_uc.csv"
//and organizes the data into the correct data structures
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

//reads data from the file "classes.csv"
//and organizes the data into the correct data structures
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

//reads data from the file "students_classes.csv"
//and organizes the data into the correct data structures
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



//----------------------------------------------------------------------------------------------------------------
//Advanced getters

//gets a specific class schedule
set<pair<pair<schedule,string>,course>> interface::get_class_schedule(class1 a_class) const{
    set<pair<pair<schedule,string>,course>> class_schedule; //schedule for each class
    class1 a_class_copy = a_class;
    string class_type;

    for(const course& a_course : courses){
        if(a_course.get_course_grade() == a_class.get_class_grade()) {
            if (a_course.get_class(a_class)) {
                if (a_class.get_T_class().week_day != "Dont Apply") {
                    class_type = "T";
                    class_schedule.insert(make_pair(make_pair(a_class.get_T_class(), class_type), a_course));
                }
                if (a_class.get_T_class_2().week_day != "Dont Apply") {
                    class_type = "T";
                    class_schedule.insert(make_pair(make_pair(a_class.get_T_class_2(), class_type), a_course));
                }
                if (a_class.get_TP_class().week_day != "Dont Apply") {
                    class_type = "TP";
                    class_schedule.insert(make_pair(make_pair(a_class.get_TP_class(), class_type), a_course));
                }
                if (a_class.get_PL_class().week_day != "Dont Apply") {
                    class_type = "PL";
                    class_schedule.insert(make_pair(make_pair(a_class.get_PL_class(), class_type), a_course));
                }
            }
            a_class = a_class_copy;
        }
    }
    return class_schedule;
}

//gets the students in a class for a specific course
list<student> interface::get_class_students_for_course(class1 a_class, course a_course) const{
    list<student> students;
    auto it = std::find(courses.begin(), courses.end(), a_course);
    a_course = *it;
    if(a_course.get_class(a_class)){
        return a_class.get_students();
    }
    return students;
}

//gets all the students in a course
set<student> interface::get_all_students_in_aCourse(course a_course) const {
    set<student> students;
    auto it = std::find(courses.begin(), courses.end(), a_course);
    a_course = *it;
    for(const class1& a_class: a_course.get_classes()){
        list<student> aux = get_class_students_for_course(a_class, a_course);
        students.insert(aux.begin(), aux.end());
    }

    return students;
}

//gets all the students in a year
set<student> interface::get_all_students_in_aYear(int year) const {
    set<student> students;

    for(const course& a_course : courses ){
        if(a_course.get_course_grade() != year){
            continue;
        }
        set<student> aux = get_all_students_in_aCourse(a_course);
        students.insert(aux.begin(), aux.end());
    }

    return students;
}

//gets the number of students in a class
size_t interface::number_of_students_in_aClass(const class1& a_class, const course& a_course) const {
    return get_class_students_for_course(a_class, a_course).size();
}

//gets the number of students in a year
size_t interface::number_of_students_in_aYear(int year) const {
    return get_all_students_in_aYear(year).size();
}

//gets the number of students in a course(Uc)
size_t interface::number_of_students_in_anUC(const course& a_course) const {
    return get_all_students_in_aCourse(a_course).size();
}


//---------------------------------------------------------------------------------------------
//Data printers


//prints the given class schedule
void interface::consult_class_schedule(const class1& a_class) const {
    set<pair<pair<schedule,string>,course>> class_schedule = get_class_schedule(a_class);

    //convert to vector, so we can order the way we want (by course instead of schedule)
    vector<pair<pair<schedule,string>,course>> class_schedule_ordered = {class_schedule.begin(), class_schedule.end()};
    sort(class_schedule_ordered.begin(), class_schedule_ordered.end(), class_schedule_sort);

    cout << "Schedule for class " << a_class.get_class_name() << ':' << endl;

    string prev = ""; //auxiliary variable
    for(auto it = class_schedule_ordered.begin(); it != class_schedule_ordered.end(); it++){

        //checks if is the schedule corresponds to the same course
        if(prev != it->second.get_course_name()) {
            cout << '\n';
            cout << "-----------------------------------------------------" << endl;
            cout << "Course " << it->second.get_course_name() << endl;
            cout << '\n';
            prev = it->second.get_course_name();
        }

        //the schedule of each course is presented ordered by the day of the week and day
        cout << "Class " << it->first.second << " Schedule = " << it->first.first.week_day << " " << class1::convert_class_to_hour_and_minute_format(it->first.first) << endl;
    }
}


//prints the student schedule
void interface::consult_student_schedule(const student& a_student) const{
    cout << "Schedule for student " << a_student.get_name() << ", number " << a_student.get_number() <<":" << endl;

    for(const course& c: courses){
        if(c.has_student(a_student)){
           class1 cl = c.get_student_class(a_student);
           cout << '\n';
           cout << "---------------------------" << endl;
           cout << "Course: " << c.get_course_name() << endl;
           cout << '\n';
           cl.print_class_schedule();
        }
    }
}

//prints the students in a given class
void interface::consult_students_in_class_and_course(const class1& a_class, const course& a_course, const string& sortby, const string& sort_option) const{
    list<student> students = get_class_students_for_course(a_class,a_course);
    list<student> sorted_students {students.begin(), students.end()};

    sorted_students = sort_students_list(sorted_students, sortby, sort_option);

    if(!students.empty()){
        cout << "List of students for class " << a_class.get_class_name() << " in course " << a_course.get_course_name() << ':' << endl;
        for(const student& a_student : sorted_students){
            a_student.print_student();
        }
    }
    else{
        cout << "Your input class does not exist in your input course! Please try again." << endl;
    }
}

//prints all the students in a course
void interface::consult_all_students_in_aCourse(const course& a_course, const string& sortby, const string& sort_option) const {
    set<student> students = get_all_students_in_aCourse(a_course);
    list<student> sorted_students {students.begin(), students.end()};

    sorted_students = sort_students_list(sorted_students, sortby, sort_option);

    cout << "Course: " << a_course.get_course_name() << endl;
    cout <<'\n';
    for (const student& a_student : sorted_students){
        cout <<"Name: " << a_student.get_name() << ' ' << "Number: " << a_student.get_number() << endl;
    }
}

//prints all the students in a year
void interface::consult_all_students_in_aYear(int year, const string& sortby, const string& sort_option) const {
    set<student> students = get_all_students_in_aYear(year);
    list<student> sorted_students {students.begin(), students.end()};

    sorted_students = sort_students_list(sorted_students, sortby, sort_option);

    cout << "Year: " << year << endl;
    cout << '\n';
    for(const student& a_student: sorted_students){
        cout <<"Name: " << a_student.get_name() << ' ' << "Number: " << a_student.get_number() << endl;
    }
}

//prints the data in the entire system
void interface::print_data(const string& uc_sort_by , const string& class_sort_by ,const string& student_sort_by,const string& uc_sort_option, const string& class_sort_option, const string& student_sort_option) const{
    cout << "Printing data for the entire system" << endl;
    vector <course> sorted_courses = courses;
    sorted_courses = sort_course_vector(sorted_courses, uc_sort_by, uc_sort_option);

    for(const course& a_course : sorted_courses){
        a_course.print_course_data(class_sort_by, student_sort_by, class_sort_option, student_sort_option);
    }
}

//prints the occupation in every course and class for a specific year
void interface::consult_classes_and_courses_occupation_by_year(int year , const string& uc_sort_by, const string& class_sort_by, const string& uc_sort_option, const string& class_sort_option) {
    vector<course> sorted_courses = courses;
    sorted_courses = sort_course_vector(sorted_courses, uc_sort_by, uc_sort_option);

    for(const course& c: sorted_courses){
        if(c.get_course_grade() != year){
            continue;
        }

        vector<class1> sorted_classes = c.get_classes();
        sorted_classes = sort_class_vector(sorted_classes, class_sort_by, class_sort_option);

        cout << "------------------------------------------" << endl;
        cout << "Course: " << c.get_course_name() << " occupation: " << c.number_of_students() << endl;
        cout << '\n';

        for(const class1& cl : sorted_classes){
            cout << "Class: " << cl.get_class_name() << " occupation: " << cl.get_students().size() << endl;
        }
        cout << '\n';
    }
}
