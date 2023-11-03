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

/**
* @file interface.cpp
* @brief Implementation of class interface.
*/

//----------------------------------------------------------------------------------------
//Basic getters

/** Gets the courses. Time complexity: O(1)
 *  @return Vector with the courses */
vector<course> interface::get_courses() const {
    return courses;
}

/** Gets the requests. Time complexity: O(1)
 *  @returns Queue with the requests*/
queue<request> interface::get_requests() const {
    return requests;
}

/** Gets the name of the file where information about students is stored. Time complexity: O(1)
 *  @returns String with the name of the file were are stored the most recent students information
 *  */
string interface::get_students_classes_filename() const {
    return students_classes_filename;
}

/** Gets the name of the file where student requests are stored. Time complexity: O(1)
 *   @returns String with the name of the file were are stored the most recent requests
 *   */
string interface::get_students_requests_filename() const {
    return students_requests_filename;
}

//--------------------------------------------------------------------------------------
//Data readers (from files)

/**Reads data from the file "classes_per_uc.csv"
    * and organizes the data into the correct data structures.
    * Time complexity: O(n^2).*/

void interface::read_data_classes_per_uc() {
    string file, line;
    file = "../Data_files/classes_per_uc.csv";
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
    open_file.close();
}

/**Reads data from the file "classes.csv"
    *and organizes the data into the correct data structures.
    * Time complexity: O(n^2). */
void interface::read_data_classes() {
    string file, line;
    file = "../Data_files/classes.csv";
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
    open_file.close();
}

/**Reads data from the file "students_classes.csv"
    * and organizes the data into the correct data structures.
    * Time complexity : O(n^3). */
void interface::read_data_students_classes() {
    ifstream f("../Data_files/students_classes.csv");
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
    f.close();
}

/** Reads the data from students_requests.csv
 *  and organizes the data into the correct data structures.
 *  Time complexity: O(n)
 */
void interface::read_data_students_requests(){
    string file,line;
    string target_student_name,target_student_number,request_type;
    request new_request,reset_new_request;
    file = "../Data_files/students_requests.csv";
    ifstream open_file(file);
    while(getline(open_file,line)){
        //get the student number
        auto it = line.find_first_of(',');
        target_student_number = line.substr(0,it);
        line = line.substr(it + 1);

        //get the student name
        it = line.find_first_of(',');
        target_student_name = line.substr(0,it);

        //create a new student object and add it to the request
        student target_student(target_student_name,target_student_number);
        new_request.target_student = target_student;
        line = line.substr(it + 1);

        //get the type of request and add it to the request
        it = line.find_first_of(',');
        request_type = line.substr(0,it);
        new_request.request_type = request_type;
        line = line.substr(it + 1);

        //process the  type of request
        if(request_type == "add course"){
            it = line.find_first_of(',');
            //add the course and class to the request
            course added_course(line.substr(0,it));
            new_request.added_course = added_course;
            line = line.substr(it + 1);
            class1 added_class(line);
            new_request.added_class = added_class;
        }

        else if(request_type == "remove course"){
            //add the course to remove to the request
            course removed_course(line);
            new_request.removed_course = removed_course;
        }

        else if(request_type == "switch courses"){
            it = line.find_first_of(',');
            //add the course the student want to move, the class and the course he was before
            course added_course(line.substr(0,it));
            new_request.added_course = added_course;
            line = line.substr(it + 1);
            it = line.find_first_of(',');
            class1 added_class(line.substr(0,it));
            new_request.added_class = added_class;
            line = line.substr(it + 1);
            course removed_course(line);
            new_request.removed_course = removed_course;
        }

        else if(request_type == "switch classes"){
            it = line.find_first_of(',');
            //add the course, the class the student want to move and the class he was before
            course added_course(line.substr(0,it));
            new_request.added_course = added_course;
            line = line.substr(it + 1);
            it = line.find_first_of(',');
            class1 added_class(line.substr(0,it));
            new_request.added_class = added_class;
            line = line.substr(it + 1);
            class1 removed_class(line);
            new_request.removed_class = removed_class;
        }

        //Puts the new request in the requests queue
        requests.push(new_request);
        new_request = reset_new_request;
    }
    open_file.close();
}

//----------------------------------------------------------------------------------------------------------------
//Operators


void interface::operator=(const interface &other_interface) {
    courses = other_interface.get_courses();
    requests = other_interface.get_requests();
    students_classes_filename = other_interface.get_students_classes_filename();
    students_requests_filename = other_interface.get_students_requests_filename();
}

//----------------------------------------------------------------------------------------------------------------
//Advanced getters

/**Gets a specific course from the courses vector
 *  Time complexity: O(n)
 *  @param a_course The course we wan to get (object only contains the name of the course)
 *  @return The course with all the information
 */
course interface::get_course_from_courses(const course &a_course) const {
    course target_course;
    for(const course& c : courses){
        if(a_course == c){
            target_course = c;
            return c;
        }
    }
}

/**Gets a specific class schedule.
   * Time complexity : O(nlog(n)).
   *  @param a_class Class that we want to get the schedule
   * @Returns A set with the schedule information (pair with the course and a pair with the schedule and the class type)*/
set<pair<pair<schedule,string>,course>> interface::get_class_schedule(class1 a_class) const{
    set<pair<pair<schedule,string>,course>> class_schedule; //schedule for each class
    class1 a_class_copy = a_class;
    string class_type;

    for(const course& a_course : courses){
        if(a_course.get_course_grade() == a_class.get_class_grade()) {
            if (a_course.get_class(a_class)) {
                if (a_class.get_T_class().week_day != "Dont Apply") {
                    class_type = "T";
                    class_schedule.insert(make_pair(make_pair(a_class.get_T_class(), class_type), a_course)); //O(log(N))
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

/**Gets a specific student schedule.
 * Time complexity: O(nlog(n))
 * @param a_student Student that we want to get the schedule
 * @returns A set with the schedule information (pair with the course and a pair with the schedule and the class type) */
set<pair<pair<schedule,string>,course>> interface::get_student_schedule(const student& a_student) const {
    set<pair<pair<schedule,string>,course>> student_schedule;
    class1 aux_class;
    string class_type;
    for(const course& a_course : courses){
        if(a_course.has_student(a_student)){
            aux_class = a_course.get_student_class(a_student);
            if(aux_class.get_T_class().week_day != "Dont Apply"){
                class_type = "T";
                student_schedule.insert(make_pair(make_pair(aux_class.get_T_class(),class_type),a_course));
            }
            if(aux_class.get_T_class_2().week_day != "Dont Apply"){
                class_type = "T";
                student_schedule.insert(make_pair(make_pair(aux_class.get_T_class_2(),class_type),a_course));
            }
            if(aux_class.get_TP_class().week_day != "Dont Apply"){
                class_type = "TP";
                student_schedule.insert(make_pair(make_pair(aux_class.get_TP_class(),class_type),a_course));
            }
            if(aux_class.get_PL_class().week_day != "Dont Apply"){
                class_type = "PL";
                student_schedule.insert(make_pair(make_pair(aux_class.get_PL_class(),class_type),a_course));
            }
        }
    }
    return student_schedule;
}


/**Gets the students in a class for a specific course.
    * Time complexity: O(n).
    *  @param a_class Class from were we want to get the student
    * @param a_course Course from were we want to access the class to obtain the students
    * @returns List of students that belong to that class/course*/
list<student> interface::get_class_students_for_course(class1 a_class, course a_course) const{
    list<student> students;
    auto it = std::find(courses.begin(), courses.end(), a_course);
    a_course = *it;
    if(a_course.get_class(a_class)){ //O(n)
        return a_class.get_students();
    }
    return students;
}

/**Gets all the students in a course.
* Time complexity : O(n^2).
 *  @param a_course Course from were we want to get the students
 * @returns Set of students (because we don´t want repeated students) that belong to the course*/
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

/**Gets all the students in a year.
    * Time complexity: O(n^3).
    * @param year Year from were we want to get the students
    * @returns Set of students (because we don´t want repeated students) that belong to the year*/
set<student> interface::get_all_students_in_aYear(int year) const {
    set<student> students;

    for(const course& a_course : courses ){
        if(a_course.get_course_grade() != year){
            continue;
        }
        set<student> aux = get_all_students_in_aCourse(a_course); //O(n^2)
        students.insert(aux.begin(), aux.end());
    }

    return students;
}

/** Gets all the courses a student is part of.
 *  Time complexity: O(n^3)
 *  @param a_student Student that we want to get the courses
 *  @returns Vector with the courses the student is enrolled*/
vector<course> interface::get_all_courses_for_student(const student &a_student) const {
    vector<course> student_courses;
    for(const course& a_course : courses){
        if(a_course.has_student(a_student)){ //O(n^2)
            student_courses.push_back(a_course);
        }
    }
    return student_courses;
}

/** Gets a specific student info.
 *  Time complexity: O(n^3)
 *  @param a_student Student we want to obtain the information (student object with only some information)
 *  @returns Student with the complete information
 */
student interface::get_student(const student& a_student) const{
    class1 student_class;
    student student_info;
    for(course a_course : courses){
        if(a_course.has_student(a_student)){
            student_class = a_course.get_student_class(a_student);
            student_info = student_class.get_student_in_class(a_student);
            break;
        }
    }
    return student_info;
}

/**Gets the number of students in a class.
    * Time complexity: O(n)
    * @param a_class Class from were we want to obtain the number of students
    * @param a_course Course from were we want to consult the class to obtain the number of students
    * @returns Number of students*/
size_t interface::number_of_students_in_aClass(const class1& a_class, const course& a_course) const {
    return get_class_students_for_course(a_class, a_course).size();
}

/**Gets the number of students in a year.
    * Time complexity: O(n^3).
    *  @param year Year from were we want to obtain the number of students
    * @returns Number of students*/
size_t interface::number_of_students_in_aYear(int year) const {
    return get_all_students_in_aYear(year).size();
}

/**Gets the number of students in a course(Uc).
    * Time complexity: O(n^2).
    * @param a_course course from were we want to obtain the number of students
    * @returns Number of students*/
size_t interface::number_of_students_in_anUC(const course& a_course) const {
    return get_all_students_in_aCourse(a_course).size();
}
/** Gets the number of courses for a specific student
 *  Time complexity: O(n^3)
 *   @param a_student Student from were we want to obtain the number of courses he is enrolled
   * @returns Number of courses
 */
size_t interface::number_of_courses_per_student(const student &a_student) const {
    return get_all_courses_for_student(a_student).size();
}

/** Checks if a student is in this interface.
 *  Time complexity: O(n^3)
 *   @param a_student Student we want to check
 *  @returns False if the student isn´t in the system and True if it is present in the system
 */
bool interface:: has_student(const student& a_student) const{
    for(course a_course : courses){
        if(a_course.has_student(a_student)){
            return true;
        }
    }
    return false;
}


//---------------------------------------------------------------------------------------------
//Data printers

/**Prints the given class schedule ordered by schedule.
    * Time complexity: O(nlog(n)).
    * @param a_class Class we want to consult the schedule*/
void interface::consult_class_schedule_by_schedule(const class1 &a_class) const {
    set<pair<pair<schedule,string>,course>> class_schedule = get_class_schedule(a_class); //O(nlog(n))
    cout << "Schedule for class " << a_class.get_class_name() << ':' << endl;
    auto it = class_schedule.begin();
    string week_day = "";
    while(it != class_schedule.end()){
        if(it->first.first.week_day != week_day){
            cout << '\n';
            week_day = it->first.first.week_day;
            cout << week_day << endl;
        }
        cout << "Course " << it->second.get_course_name() << " - "  << it->first.second << " Class " << " Start time = " << class1::convert_class_to_hour_and_minute_format(it->first.first) << endl;
        it++;
    }
}


/**Prints the given class schedule ordered by course.
    * Time complexity: O(nlog(n)).
    * @param a_class Class we want to consult the schedule*/
void interface::consult_class_schedule_by_course(const class1& a_class) const {
    set<pair<pair<schedule,string>,course>> class_schedule = get_class_schedule(a_class); //O(nlog(n))

    //convert to vector, so we can order the way we want (by course instead of schedule)
    vector<pair<pair<schedule,string>,course>> class_schedule_ordered = {class_schedule.begin(), class_schedule.end()}; //O(N)
    sort(class_schedule_ordered.begin(), class_schedule_ordered.end(), class_schedule_sort); //O(nlog(n))

    cout << "Schedule for class " << a_class.get_class_name() << ':' << endl;

    string prev = ""; //auxiliary variable
    for(auto it = class_schedule_ordered.begin(); it != class_schedule_ordered.end(); it++){    //O(n)

        //checks if is the schedule corresponds to the same course
        if(prev != it->second.get_course_name()) {
            cout << '\n';
            cout << "-----------------------------------------------------" << endl;
            cout << "Course " << it->second.get_course_name() << endl;
            cout << '\n';
            prev = it->second.get_course_name();
        }

        //the schedule of each course is presented ordered by the day of the week and day
        cout << "Class " << it->first.second << " Schedule = " << it->first.first.week_day << " " << class1::convert_class_to_hour_and_minute_format(it->first.first) << endl;//O(log(n))
    }
}

/** Consult a specific student schedule ordered by the schedules
 *  Time complexity: O(nlog(n))
 *  @param a_student Student we want to get the schedule
 */
void interface::consult_student_schedule_by_schedule(const student &a_student) const {
    set<pair<pair<schedule,string>,course>> student_schedule = get_student_schedule(a_student);
    cout << "Schedule for student " << a_student.get_name() << ", number " << a_student.get_number() <<":" << endl;
    auto it = student_schedule.begin();
    string week_day = "";
    while(it != student_schedule.end()){
        cout << "----------------------------------------------------------------------" << endl;
        cout << "Course " << it->second.get_course_name() << endl;
        cout << "Class " << it->first.second << " Schedule = " << it->first.first.week_day << " " << class1::convert_class_to_hour_and_minute_format(it->first.first) << endl;
        cout << '\n';
        it++;
    }
}

/**Prints the student schedule.
    * Time complexity: O(n^3).
    *  @param a_student Student we want to get the schedule*/
void interface::consult_student_schedule_by_course(const student& a_student) const{
    cout << "Schedule for student " << a_student.get_name() << ", number " << a_student.get_number() <<":" << endl;

    for(const course& c: courses){
        if(c.has_student(a_student)){ //O(n^2)
           class1 cl = c.get_student_class(a_student);
           cout << '\n';
           cout << "---------------------------" << endl;
           cout << "Course: " << c.get_course_name() << endl;
           cout << '\n';
           cl.print_class_schedule();
        }
    }
}

/**Prints the students in a given class.
    * Time complexity: O(nlog(n)).
    * @param a_class Class from were we want to get the student
    * @param a_course Course from were we want to access the class to get the student
    * @param sortby Determines the sorting criteria
    * @param sort_option Determines the sorting order(ascending, descending)*/
void interface::consult_students_in_class_and_course(const class1& a_class, const course& a_course, const string& sortby, const string& sort_option) const{
    list<student> students = get_class_students_for_course(a_class,a_course);   //O(n)
    list<student> sorted_students {students.begin(), students.end()};   //O(n)

    sorted_students = sort_students_list(sorted_students, sortby, sort_option); //O(nlog(n))

    if(!students.empty()){
        cout << "------------------------------------------------------------------------------" << endl;
        cout << "List of students for class " << a_class.get_class_name() << " in course " << a_course.get_course_name() << ':' << endl;
        for(const student& a_student : sorted_students){
            a_student.print_student();
        }
    }
    else{
        cout << "Your input class does not exist in your input course! Please try again." << endl;
    }
}

/**Prints all the students in a course.
    * Time complexity: O(n^2).
    * @param a_course Course from were we want to get the student
    * @param sortby Determines the sorting criteria
    * @param sort_option Determines the sorting order(ascending, descending)*/
void interface::consult_all_students_in_aCourse(const course& a_course, const string& sortby, const string& sort_option) const {
    set<student> students = get_all_students_in_aCourse(a_course); //O(n^2)
    list<student> sorted_students {students.begin(), students.end()}; //O(n)

    sorted_students = sort_students_list(sorted_students, sortby, sort_option); //O(nlog(n))

    cout << "----------------------------------------------------------------------------------" << endl;
    cout << "List of students in course " << a_course.get_course_name() <<":" << endl;
    cout <<'\n';
    for (const student& a_student : sorted_students){
        cout <<"Name: " << a_student.get_name() << ' ' << "Number: " << a_student.get_number() << endl;
    }
}

/**Prints all the students in a year.
    * Time complexity: O(n^3).
    * @param year Year from were we want to get the students
    * @param sortby Determines the sorting criteria
    * @param sort_option Determines the sorting order(ascending, descending)*/
void interface::consult_all_students_in_aYear(int year, const string& sortby, const string& sort_option) const {
    set<student> students = get_all_students_in_aYear(year); //O(n^3)
    list<student> sorted_students {students.begin(), students.end()};

    sorted_students = sort_students_list(sorted_students, sortby, sort_option);

    cout << "----------------------------------------------------------------------------------" << endl;
    cout << "List of students in year " << year << ":" << endl;
    cout << '\n';
    for(const student& a_student: sorted_students){
        cout <<"Name: " << a_student.get_name() << ' ' << "Number: " << a_student.get_number() << endl;
    }
}

/**Prints the data in the entire system.
    * Time complexity: O(n^2log(n)).
    * @param uc_sort_by Uc sorting criteria
    * @param class_sort_by Class sorting criteria
    * @param student_sort_by Student sorting criteria
    * @param uc_sort_option Uc sorting order
    * @param class_sort_option Class sorting order
    * @param student_sort_option Student sorting order*/
void interface::print_data(const string& uc_sort_by , const string& class_sort_by ,const string& student_sort_by,const string& uc_sort_option, const string& class_sort_option, const string& student_sort_option) const{
    cout << "Printing data for the entire system" << endl;
    vector <course> sorted_courses = courses;
    sorted_courses = sort_course_vector(sorted_courses, uc_sort_by, uc_sort_option); //O(n(log(n))

    for(const course& a_course : sorted_courses){
        a_course.print_course_data(class_sort_by, student_sort_by, class_sort_option, student_sort_option); //O(nlog(n))
    }
}

/**Prints the occupation in every course and class for a specific year.
    * Time complexity: O(n^2log(n)).
    *  @param year Year we want to get the occupation
    * @param uc_sort_by Uc sorting criteria
    * @param class_sort_by Class sorting criteria
    * @param uc_sort_option Uc sorting order
    * @param class_sort_option Class sorting order*/
void interface::consult_classes_and_courses_occupation_by_year(int year , const string& uc_sort_by, const string& class_sort_by, const string& uc_sort_option, const string& class_sort_option) {
    vector<course> sorted_courses = courses;
    sorted_courses = sort_course_vector(sorted_courses, uc_sort_by, uc_sort_option); //O(nlog(n))

    for(const course& c: sorted_courses){
        if(c.get_course_grade() != year){
            continue;
        }

        vector<class1> sorted_classes = c.get_classes();
        sorted_classes = sort_class_vector(sorted_classes, class_sort_by, class_sort_option);//O(nlog(n))

        cout << "------------------------------------------" << endl;
        cout << "Course: " << c.get_course_name() << " occupation: " << c.number_of_students() << endl;
        cout << '\n';

        for(const class1& cl : sorted_classes){
            cout << "Class: " << cl.get_class_name() << " occupation: " << cl.get_students().size() << endl;
        }
        cout << '\n';
    }
}

/**Checks if it is possible to add a student to a given class in a given course.
 * Time complexity: O(nlog(n))
 * @param a_course Course from were the class belongs
 * @param a_class Class we want to check
 * @param a_student Student we wan to add to the class
 * @return True if we are able to add the student to the class or False if we cannot add the student to the class
 */
bool interface::can_add_to_class(course &a_course, student &a_student, class1 &a_class) const {
    course copy_a_course = a_course;
    class1 copy_a_class = a_class;
    // checking if the class is not full
    if(a_class.get_students().size() == class1::student_capacity){
        return false;
    }
    // temporarily adding the student to the class to check if that doesn t break the class balance in the given course
    a_class.add_students(a_student);
    if(!a_course.check_class_balance(a_class)){
        return false;
    }
    // restoring the input class and course objects back to their initial state
    a_course = copy_a_course;
    a_class = copy_a_class;
    // getting the student schedule and checking potential schedule overlaps
    set<pair<pair<schedule,string>,course>> student_schedule = get_student_schedule(a_student); //O(nlog(n))
    class1 comparable_class(" ");
    auto it = student_schedule.begin();
    while(it != student_schedule.end()){
        if(it->second != a_course){
            if(it->first.second == "TP" || it->first.second == "PL"){
                if(overlapping_schedule(it->first.first,a_class.get_TP_class())){
                    return false;
                }
                if(overlapping_schedule(it->first.first,a_class.get_PL_class())){
                    return false;
                }
            }
        }
        it++;
    }
    return true;
}

/**Checks if it is possible to add a student to a given class in a given course (when swapping courses.
* Time complexity: O(nlog(n))
* @param a_course Course from were the class belongs
* @param a_class Class we want to check
 * @param ignorable_course Course we want to ignore during the execution of the function
* @param a_student Student we wan to add to the class
* @return True if we are able to add the student to the class or False if we cannot add the student to the class
*/
bool interface::can_add_to_class_for_course_swap(course& a_course, student& a_student, class1& a_class, course& ignorable_course) const{
    course copy_a_course = a_course;
    class1 copy_a_class = a_class;
    // checking if the class is not full
    if(a_class.get_students().size() == class1::student_capacity){
        return false;
    }
    // temporarily adding the student to the class to check if that doesn t break the class balance in the given course
    a_class.add_students(a_student);
    if(!a_course.check_class_balance(a_class)){
        return false;
    }
    // restoring the input class and course objects back to their initial state
    a_course = copy_a_course;
    a_class = copy_a_class;
    // getting the student schedule and checking potential schedule overlaps
    set<pair<pair<schedule,string>,course>> student_schedule = get_student_schedule(a_student); //O(nlog(n))
    class1 comparable_class(" ");
    auto it = student_schedule.begin();
    while(it != student_schedule.end()){
        if(it->second != ignorable_course){
            if(it->first.second == "TP" || it->first.second == "PL"){
                if(overlapping_schedule(it->first.first,a_class.get_TP_class())){
                    return false;
                }
                if(overlapping_schedule(it->first.first,a_class.get_PL_class())){
                    return false;
                }
            }
        }
        it++;
    }
    return true;
}

/**Consults the requests made to the system.
 *  Time complexity: O(n)
 */
void interface::consult_student_requests() const {
    queue<request> copy_requests = requests;
    struct request current_request;
    while(!copy_requests.empty()){
        current_request = copy_requests.front();
        cout << "Student : ";
        current_request.target_student.print_student();
        if(current_request.request_type == "add course"){
            cout << "Request type : Enrollment in a new course" << endl;
            cout << "Target course : " << current_request.added_course.get_course_name() << endl;
            cout << "Target class : " << current_request.added_class.get_class_name() << endl;
        }
        if(current_request.request_type == "remove course"){
            cout << "Request type : Removal from a course" << endl;
            cout << "Chosen course : " << current_request.removed_course.get_course_name() << endl;
        }
        if(current_request.request_type == "switch courses"){
            cout << "Request type : Switch between two courses" << endl;
            cout << "New course : " << current_request.added_course.get_course_name() << endl;
            cout << "New class : " << current_request.added_class.get_class_name() << endl;
            cout << "Removable course : " << current_request.removed_course.get_course_name() << endl;
        }
        if(current_request.request_type == "switch classes"){
            cout << "Request type : Switch between two classes in a course" << endl;
            cout << "Target course : " << current_request.added_course.get_course_name() << endl;
            cout << "New class : " << current_request.added_class.get_class_name() << endl;
            cout << "Old class : " << current_request.removed_class.get_class_name() << endl;
        }
        cout << endl;
        copy_requests.pop();
    }
}


/**Function that tries to enroll a student in a new course.
 *  Returns true if the enrollment is successful and false if it isn't.
 *  Time complexity: O(n^3)
 *   @param a_student Student we want to enroll
 *  @param a_course Course were we want to enroll the student
 *  @param a_class Class were we want to add the student
 *  @param error_message Message that will be changed if something goes wrong during the execution of the function (it's given by reference)
 *  @returns True if the student is enrolled in a class or False if that isn´t possible
 */

bool interface::enroll_student_in_course(student &a_student, course &a_course, class1& a_class, string& error_message) {
    //Checking if the student has not enrolled in the maximum number of courses
    if(number_of_courses_per_student(a_student) >= 7){ //O(n^3)
        error_message = "Enrollment failed because student is already enrolled in the maximum number of courses possible.";
        return false;
    }
    //accessing the desired course in courses
    auto it = std::find(courses.begin(), courses.end(),a_course);
    if(it == courses.end()){
        error_message = "Course " + a_course.get_course_name() + " does not exist in our system.";
        return false;
    }
    course& added_course = *it;
    course copy_added_course = added_course;
    class1 copy_added_class = a_class;
    student added_student = get_student(a_student);
    if(copy_added_course.has_student(added_student)){
        error_message = "The student is already enrolled in course " + a_course.get_course_name();
        return false;
    }
    //accessing the given class in the given course
    if(copy_added_course.get_class(copy_added_class)) {
        // checking if the enrollment in the given course and class is possible
        if (can_add_to_class(copy_added_course, added_student, copy_added_class)) {
            class1& added_class = added_course.get_class_by_ref(a_class);
            added_class.add_students(added_student);
            return true;
        }
    }
    //if it is not possible to allocate the student to their desired class in the given course
    //the system tries to allocate them to another class in the same course, starting with the classes
    //that have the least amount of students enrolled in them
    error_message = "Student could not be allocated to their desired class.";
    vector<class1> copy_course_classes = added_course.get_classes();
    sort(copy_course_classes.begin(), copy_course_classes.end(), compare_class_ocupation);
    for(class1 cl : copy_course_classes){
        if(can_add_to_class(added_course, added_student , cl)){
            class1& available_class = added_course.get_class_by_ref(cl);
            available_class.add_students(added_student);
            error_message += "Student was instead allocated to class " + available_class.get_class_name() + '.';
            return true;
        }
    }
    error_message = "Enrollment failed because the student could not be allocated to any of the classes available for course " + a_course.get_course_name();
    return false;
}


/**Functions that tries to remove a student from a course.
* Returns true if the removal is successful and false if it isn't
* Time complexity: O(n^2)
 *  @param a_student Student we want to remove
 * @param a_course Course from were we want to remove the student
 * @param error_message Message that will be changed if something goes wrong during the execution of the function (it's given by reference)
 * @returns True if the student is removed from the course or False if the student isn´t enrolled in this course*/
bool interface::remove_student_from_course(student &a_student, course &a_course, string& error_message) {
    //finding the target course in courses
    auto it = std::find(courses.begin(),courses.end(),a_course);
    if(it == courses.end()){
        error_message = "Course " + a_course.get_course_name() + " does not exist in our system.";
        return false;
    }
    course& removable_course = *it;
    //trying to find the students class in the target course and remove him from it
    for(class1 a_class : removable_course.get_classes()){
        if(a_class.student_in_class(a_student)){
            class1& removable_class = removable_course.get_class_by_ref(a_class);
            removable_class.remove_students(a_student);
            return true;
        }
    }
    //if the student could not be found in the given course set an error message and return false
    error_message = "The student is not enrolled in course " + a_course.get_course_name();
    return false;
}

/**Removes student from a given course to enroll him in another one if possible.
* Time complexity: O(n^3)
 * @param a_student Student we want to switch courses
 * @param old_course Course from were we want to remove the student
 * @param new_course Course were we want to add the student
 * @param new_class Class were we want to add the student
 * @param error_message Message that will be changed if something goes wrong during the execution of the function (it's given by reference)
 *  @returns True if the switch is possible or False otherwise*/
bool interface::switch_student_courses(student &a_student, course &old_course, course &new_course, class1& new_class, string& error_message) {
    auto it = std::find(courses.begin(), courses.end(), old_course);
    course old_course_copy = *it;
    if(it == courses.end()){
        error_message = "Course " + old_course.get_course_name() + " does not exist in our system.";
        return false;
    }
    if (!old_course_copy.has_student(a_student)) {
        error_message = "Student is not enrolled in course " + old_course.get_course_name();
        return false;
    }
    //accessing the desired course in courses
    it = std::find(courses.begin(), courses.end(),new_course);
    if(it == courses.end()){
        error_message = "Course " + new_course.get_course_name() + " does not exist in our system.";
        return false;
    }
    course& added_course = *it;
    course copy_added_course = added_course;
    class1 copy_added_class = new_class;
    student added_student = get_student(a_student);
    if(copy_added_course.has_student(added_student)){
        error_message = "The student is already enrolled in course " + added_course.get_course_name();
        return false;
    }
    //accessing the given class in the given course
    if(copy_added_course.get_class(copy_added_class)) {
        // checking if the enrollment in the given course and class is possible
        if (can_add_to_class_for_course_swap(copy_added_course, added_student, copy_added_class,old_course_copy)) {
            class1& added_class = added_course.get_class_by_ref(new_class);
            added_class.add_students(added_student);
            remove_student_from_course(added_student,old_course,error_message);
            return true;
        }
    }
    error_message = "Student could not be allocated to their desired class.";
    vector<class1> copy_course_classes = added_course.get_classes();
    sort(copy_course_classes.begin(), copy_course_classes.end(), compare_class_ocupation);
    for(class1 cl : copy_course_classes){
        if(can_add_to_class_for_course_swap(added_course, added_student , cl, old_course_copy)){
            class1& available_class = added_course.get_class_by_ref(cl);
            available_class.add_students(added_student);
            remove_student_from_course(added_student,old_course,error_message);
            error_message += "Student was instead allocated to class " + available_class.get_class_name() + '.';
            return true;
        }
    }
    error_message = "Could not enroll student in their desired course because the student could not be allocated to any of the classes available for course " + new_course.get_course_name();
    return false;
}

/**Switches students from one class to another in a given course if possible.
* Time complexity: O(n^3)
 * @param a_student Student we want to switch courses
 * @param a_course Course from were we want to execute the switch
 * @param old_class Class were we want to remove the student
 * @param new_class Class were we want to add the student
 * @param error_message Message that will be changed if something goes wrong during the execution of the function (it's given by reference)
 *  @returns True if the switch is possible or False otherwise
 *  */
bool interface::switch_student_classes(student &a_student, course &a_course, class1 &old_class, class1 &new_class, string& error_message) {
    //finding the target course in courses
    auto it = std::find(courses.begin(),courses.end(),a_course);
    if(it == courses.end()){
        error_message = "The target course does not exist in our system.";
        return false;
    }
    course &target_course = *it;
    course copy_target_course = *it;
    student added_student = get_student(a_student);
    //checking if the class the student wants to leave exists
    if(!copy_target_course.get_class(old_class)){
        error_message = old_class.get_class_name() + "does not exist in course " + target_course.get_course_name();
        return false;
    }
    //checking if student is actually a part of the class he wants to leave
    if(!old_class.student_in_class(added_student)){
        error_message = "The student is not enrolled in class " + old_class.get_class_name() + " of course " + target_course.get_course_name();
        return false;
    }
    //checking if the class the student wants to join exists
    if(!copy_target_course.get_class(new_class)){
        error_message = "The class the student wishes to join does not exist in course " + target_course.get_course_name();
        return false;
    }
    //creating a reference to the copy old class
    class1& copy_target_course_old_class = copy_target_course.get_class_by_ref(old_class);
    //removing student from copy of the old class to check if we can add him to the new one after removing him from the one
    copy_target_course_old_class.remove_students(added_student);
    if(!can_add_to_class(copy_target_course,added_student,new_class)){
        error_message = "The student could not be added to their desired class.";
        return false;
    }
    //creating reference to old class and removing student from it
    class1& old_class_ref = target_course.get_class_by_ref(old_class);
    old_class_ref.remove_students(added_student);
    //creating reference to new class and adding student to it
    class1& new_class_ref = target_course.get_class_by_ref(new_class);
    new_class_ref.add_students(added_student);
    return true;
}

/**Processes the request that is at the front of the requests queue.
 * Time complexity: O(n^3)
 * @param new_student_filename File were will be stored the updated students information
 * @param new_request_filename File were will be stored the updated request information
 * @param error_message Message that will be changed if something goes wrong during the execution of the function (it's given by reference)
 *  @returns True if the process is requested correctly or False otherwise
 */
bool interface::process_request(string& error_message, const string& new_student_filename, const string& new_request_filename) {
    if(requests.empty()){
        error_message = "There are no requests left to process in the system!";
        return false;
    }
    // getting the oldest request in our requests queue
    request processed_request = requests.front();
    // removing the request we are about to process from the queue
    requests.pop();
    // removing the request we are about to process from the queue from the file that stores the interface's requests
    // to do so we call the method below that copies the content of the current requests file to a new file except for the line that references the request we are about to process
    remove_request_from_file(new_request_filename);
    // then we associate the interface with the updated requests file
    students_requests_filename = new_request_filename;
    if(!has_student(processed_request.target_student)){
        error_message = "Student who submitted the request does not exist in the system";
        return false;
    }
    if(processed_request.request_type == "add course"){
        if(enroll_student_in_course(processed_request.target_student, processed_request.added_course, processed_request.added_class, error_message)){
            course new_course = get_course_from_courses(processed_request.added_course);
            class1 new_class = new_course.get_student_class(processed_request.target_student);
            enroll_student_in_course_in_file(processed_request.target_student,processed_request.added_course,new_class,new_student_filename);
            students_classes_filename = new_student_filename;
            return true;
        }
    }
    else if(processed_request.request_type == "remove course") {
        if(remove_student_from_course(processed_request.target_student, processed_request.removed_course, error_message)){
            remove_student_from_course_in_file(processed_request.target_student, processed_request.removed_course,new_student_filename);
            students_classes_filename = new_student_filename;
            return true;
        };
    }
    else if(processed_request.request_type == "switch courses") {
        if(switch_student_courses(processed_request.target_student, processed_request.removed_course,processed_request.added_course, processed_request.added_class, error_message)){
            course new_course = get_course_from_courses(processed_request.added_course);
            class1 new_class = new_course.get_student_class(processed_request.target_student);
            switch_student_courses_in_file(processed_request.target_student, processed_request.removed_course,processed_request.added_course, new_class,new_student_filename);
            students_classes_filename = new_student_filename;
            return true;
        }
    }
    else if(processed_request.request_type == "switch classes"){
        if(switch_student_classes(processed_request.target_student, processed_request.added_course, processed_request.removed_class, processed_request.added_class,error_message)){
            switch_student_classes_in_file(processed_request.target_student, processed_request.added_course,processed_request.removed_class, processed_request.added_class,new_student_filename);
            students_classes_filename = new_student_filename;
            return true;
        }
    }
    return false;
}

/**Adds a request to the file "students_requests.csv".
 * Time complexity: O(n)
 * @param new_filename File were the requests will be stored
 * @param new_request Request we are adding to the file
 */
void interface::add_request_to_file(const request &new_request, const string& new_filename) {
    string line,filename_path,new_filename_path,new_line;
    filename_path = "../Data_files/" + students_requests_filename;
    new_filename_path = "../Data_files/" + new_filename;
    // setting several request formats for the different types of requests
    new_line = new_request.target_student.get_number() + ',' + new_request.target_student.get_name() + ',' + new_request.request_type;
    if(new_request.request_type == "add course"){
        new_line += ',' + new_request.added_course.get_course_name() + ',' + new_request.added_class.get_class_name();
    }
    else if(new_request.request_type == "remove course"){
        new_line += ',' + new_request.removed_course.get_course_name();
    }
    else if(new_request.request_type == "switch courses"){
        new_line += ',' + new_request.added_course.get_course_name() + ',' + new_request.added_class.get_class_name() + ',' + new_request.removed_course.get_course_name();
    }
    else if(new_request.request_type == "switch classes"){
        new_line += ',' + new_request.added_course.get_course_name() + ',' + new_request.added_class.get_class_name() + ',' + new_request.removed_class.get_class_name();
    }
    ifstream read_file(filename_path);
    if(!read_file.is_open()){
        std::cerr << "Error: Unable to open the CSV file for reading." << std::endl;
        return;
    }
    // opening the student requests file in write mode
    ofstream write_file(new_filename_path);
    if (!write_file.is_open()) {
        std::cerr << "Error: Unable to open the CSV file for writing." << std::endl;
        return;
    }
    //copying lines from the previous file into the new version
    while(getline(read_file,line)){
        write_file << line << endl;
    }
    // adding the new request to the file using the appropriate format
    write_file << new_line << endl;
    read_file.close();
    write_file.flush();
    write_file.close();
}

/**Removes the top request from the student requests file after a request is processed.
* Time complexity : O(n)
 * @param new_request_filename File were the updated requests information will be stored*/
void interface::remove_request_from_file(const string& new_request_filename) {
    string requests_file,line,new_requests_file;
    requests_file = "../Data_files/" + students_requests_filename;
    new_requests_file = "../Data_files/" + new_request_filename;
    //opening original student requests file
    ifstream read_file(requests_file);
    // opening copy of student requests file
    ofstream write_file(new_requests_file);
    //getting the first line of the file so that oit is not copied to the copy of the student requests file
    getline(read_file,line);
    //copying every line of the original file to the new copy file except the first one
    while(getline(read_file,line)){
        write_file << line << endl;
    }
    //closing both files
    read_file.close();
    write_file.close();
}

/** Creates a new copy of the students file when a student is added to a new course.
 * Time complexity: O(n)
 * @param new_filename File were the updated students info will be stored
 * @param a_student Student that will enroll into the course
 * @param a_course Course that the student wants to enroll
 * @param a_class Class that the student wants to enroll
 */
void interface::enroll_student_in_course_in_file(student &a_student, course &a_course, class1 &a_class, const string& new_filename){
    string students_file,new_students_file,line,target_student_number,target_student_name,copy_line;

    //adding the complete path to the students' file
    students_file = "../Data_files/" + students_classes_filename;
    new_students_file = "../Data_files/" + new_filename;

    // opening current students file in read mode
    ifstream read_file(students_file);

    // opening future students file in write mode
    ofstream write_file(new_students_file);

    //checking to see if they were open successfully
    if (!read_file.is_open() || !write_file.is_open()) {
        cout << "Error: Unable to open files." << endl;
        return;
    }

    bool found_student = false;

    // looping through lines of the file
    while(getline(read_file,line)){
        copy_line = line;
        //getting the number of the student present in each line
        auto it = line.find_first_of(',');
        target_student_number = line.substr(0,it);
        // if it does not match the number of the student we are looking for, we copy the line to the new students file and continue the loop
        // if it does match the number of the target student, but we had already found him we also continue the loop
        if(target_student_number != a_student.get_number() || found_student){
            write_file << line << endl;
            continue;
        }

        // when we find the first line that references our target student we get his name from the line
        line = line.substr(it + 1);
        it = line.find_first_of(',');
        target_student_name = line.substr(0,it);

        // we then add a new line to the new file where we register our target students' enrollment in a new course
        write_file << target_student_number << ',' << target_student_name << ',' << a_course.get_course_name() << ',' << a_class.get_class_name() << endl;

        //then we reset our line variable to its initial value and add the line we just found
        line = copy_line;
        write_file << line << endl;
        found_student = true;
    }

    read_file.close();
    write_file.close();
}

/** Creates a new copy of the students file when a student is removed from a course.
 * Time complexity: O(n)
 * @param a_student Student that will be removed
 * @param a_course Course from were the student will be removed
 * @param new_filename File that will store the updated information
 */
void interface::remove_student_from_course_in_file(student &a_student, course &a_course,const std::string &new_filename) {
    string student_file, new_student_file,line, target_student_number, target_student_name, target_course, aux_line;
    student_file = "../Data_files/" + students_classes_filename;
    new_student_file = "../Data_files/" + new_filename;
    ifstream read_file(student_file);
    ofstream write_file(new_student_file);

    //Loop the lines in the file to find the target student
    while(getline(read_file,line)){
        //Get the student number
        auto it = line.find_first_of(',');
        aux_line = line;
        target_student_number = line.substr(0,it);

        //Confirming if the student in this line is our target student
        //If it isn´t, then we just add it to the new file and continue the loop
        if(target_student_number != a_student.get_number()){
            write_file << line << endl;
            continue;
        }

        //Get student name
        aux_line = aux_line.substr(it + 1);
        it = aux_line.find_first_of(',');
        target_student_name = aux_line.substr(0,it);

        //Get the course were we want to remove the student
        aux_line = aux_line.substr(it + 1);
        it = aux_line.find_first_of(',');
        target_course = aux_line.substr(0,it);

        //Confirming if the course is the one we want to delete the student from
        //if it isn´t, then just add the line to the new file and continue the loop
        if(target_student_number == a_student.get_number() &&  target_course == a_course.get_course_name()){
            continue;
        }
        write_file << line << endl;
    }
    read_file.close();
    write_file.close();
}

/** Creates a new copy of the students file when a student switches courses.
 * Time complexity: O(n)
 * @param a_student Student that will switch courses
 * @param new_class Class that the student will enroll
 * @param new_course Course that the student will enroll
 * @param old_course Course from were the student wants to switch
 * @param new_filename File that will store the updated information
 */
void interface::switch_student_courses_in_file(student &a_student, course &old_course, course &new_course, class1 &new_class, const std::string &new_filename) {
    string students_file,new_students_file,line,target_student_number,target_student_name,target_course,save_line;
    students_file = "../Data_files/" + students_classes_filename;
    new_students_file = "../Data_files/"+ new_filename;
    ifstream read_file(students_file);
    ofstream write_file(new_students_file);

    //Checks if the files opened successfully
    if (!read_file.is_open() || !write_file.is_open()) {
        cout << "Error: Unable to open files." << endl;
        return;
    }

    //Loop the lines in the file
    while(getline(read_file,line)){
        //Gets the student number
        save_line = line;
        auto it = line.find_first_of(',');
        target_student_number = line.substr(0,it);

        //Confirming if the student in this line is our target student
        //If it isn´t, then we just add it to the new file and continue the loop
        if(target_student_number != a_student.get_number()){
            write_file << line << endl;
            continue;
        }

        //Get student name
        line = line.substr(it + 1);
        it = line.find_first_of(',');
        target_student_name = line.substr(0,it);

        //Get the course we want to change
        line = line.substr(it + 1);
        it = line.find_first_of(',');
        target_course = line.substr(0,it);

        //Checks if the course found is the old one
        //If it's the old course then update the new file with the new course
        if(target_course == old_course.get_course_name()){
            write_file << target_student_number << ',' << target_student_name << ',' << new_course.get_course_name() << ',' << new_class.get_class_name() << endl;
            continue;
        }
        line = save_line;
        write_file << line << endl;
    }

    read_file.close();
    write_file.close();
}

/** Creates a new copy of the students file when a student is added to a new class.
 * Time complexity: O(n)
 * @param a_student Student that will switch classes
 * @param new_class Class that the student will enroll
 * @param a_course Course were the changes will be made
 * @param old_class Class from were the student wants to switch
 * @param new_filename File that will store the updated information
 */
void interface::switch_student_classes_in_file(student &a_student, course &a_course, class1 &old_class,class1 &new_class, const std::string &new_filename) {
    string students_file,new_students_file,line,target_student_number,target_student_name,target_course,save_line;
    students_file = "../Data_files/" + students_classes_filename;
    new_students_file = "../Data_files/" +  new_filename;
    ifstream read_file(students_file);
    ofstream write_file(new_students_file);

    //Checks if the files opened successfully
    if (!read_file.is_open() || !write_file.is_open()) {
        cout << "Error: Unable to open files." << endl;
        return;
    }

    //Loop the lines in the file
    while(getline(read_file,line)){
        //Gets the student number
        save_line = line;
        auto it = line.find_first_of(',');
        target_student_number = line.substr(0,it);

        //Confirming if the student in this line is our target student
        //If it isn´t, then we just add it to the new file and continue the loop
        if(target_student_number != a_student.get_number()){
            write_file << line << endl;
            continue;
        }

        //Get the student name
        line = line.substr(it + 1);
        it = line.find_first_of(',');
        target_student_name = line.substr(0,it);

        //Get the target course
        line = line.substr(it + 1);
        target_course = line.substr(0,it);

        //if the course is the one we are seeking then update the new file with the new class
        if(target_course == a_course.get_course_name()){
            write_file << target_student_number << ',' << target_student_name << ',' << target_course << ',' << new_class.get_class_name() << endl;
            continue;
        }
        line = save_line;
        write_file << line << endl;
    }

    read_file.close();
    write_file.close();
}

/**Stores a new request into the requests queue.
 * Time complexity: O(n)
 * @param new_request Request that will be stored
 * @param new_filename File that will store the updated information
 */
void interface::store_new_request(const request &new_request, const string& new_filename) {
    //pushing the new request to the requests' queue
    requests.push(new_request);
    //registering the new request in a new copy of the students requests file with the name equal to the value of string new_filename
    add_request_to_file(new_request,new_filename);
    //making our interface reference the newly updated students file
    students_requests_filename = new_filename;
}

/**Removes a request from the requests queue and from the requests file
 *  Time complexity: O(n)
 *  @param new_filename File from were we want to remove the request
 */
void interface::remove_request(const std::string &new_filename) {
    requests.pop();
    remove_request_from_file(new_filename);
    students_requests_filename = new_filename;
}

//setters --------------------------------------------------------------
/**Sets the courses vector to the given vector of courses
* Time complexity: O(1)
 * @param courses New courses vector*/
void interface::set_courses(vector<course> courses) {
    this->courses = courses;
}

/**Sets the students_classes file name to a new one.
 * Time complexity: O(1)
 * @param filename New name for the students file
 */
void interface::set_students_classes_filename(const std::string &filename) {
    students_classes_filename = filename;
}

/**Sets the students_requests file name to a new one.
 * Time complexity: O(1)
 * @param filename New name for the requests file
 */
void interface::set_students_requests_filename(const std::string &filename) {
    students_requests_filename = filename;
}
