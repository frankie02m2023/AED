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

/** Gets the courses. Time complexity: O(1)*/
vector<course> interface::get_courses() const {
    return courses;
}

/** Gets the requests. Time complexity: O(1)*/
queue<request> interface::get_requests() const {
    return requests;
}

/** Gets the name of the file where information about students is stored. Time complexity: O(1)*/
string interface::get_students_classes_filename() const {
    return students_classes_filename;
}

/** Gets the name of the file where student requests are stored. Time complexity: O(1)*/
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

/**Reads data from the file "classes.csv"
    *and organizes the data into the correct data structures.
    * Time complexity: O(n^2). */
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

/**Reads data from the file "students_classes.csv"
    * and organizes the data into the correct data structures.
    * Time complexity : O(n^3). */
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
            course added_course(line.substr((0,it)));
            new_request.added_course = added_course;
            line = line.substr(it + 1);
            class1 added_class(line);
            new_request.added_class = added_class;
        }

        else if(request_type == "remove_course"){
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

/**Gets a specific class schedule.
   * Time complexity : O(nlog(n)).*/
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
 * Time complexity: O(nlog(n))*/
set<pair<pair<schedule,string>,course>> interface::get_student_schedule(const student& a_student) const {
    set<pair<pair<schedule,string>,course>> student_schedule;
    class1 aux_class;
    string class_type;
    for(course a_course : courses){
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
    * Time complexity: O(n).*/
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
* Time complexity : O(n^2).*/
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
    * Time complexity: O(n^3).*/
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
 *  Time complexity: O(n^3)*/
vector<course> interface::get_all_courses_for_student(const student &a_student) const {
    vector<course> student_courses;
    for(course a_course : courses){
        if(a_course.has_student(a_student)){ //O(n^2)
            student_courses.push_back(a_course);
        }
    }
    return student_courses;
}

/** Gets a specific student info.
 *  Time complexity: O(n^3)
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
    * Time complexity: O(n)*/
size_t interface::number_of_students_in_aClass(const class1& a_class, const course& a_course) const {
    return get_class_students_for_course(a_class, a_course).size();
}

/**Gets the number of students in a year.
    * Time complexity: O(n^3).*/
size_t interface::number_of_students_in_aYear(int year) const {
    return get_all_students_in_aYear(year).size();
}

/**Gets the number of students in a course(Uc).
    * Time complexity: O(n^2).*/
size_t interface::number_of_students_in_anUC(const course& a_course) const {
    return get_all_students_in_aCourse(a_course).size();
}
/** Gets the number of courses for a specific student
 *  Time complexity: O(n^3)
 */
size_t interface::number_of_courses_per_student(const student &a_student) const {
    return get_all_courses_for_student(a_student).size();
}


//---------------------------------------------------------------------------------------------
//Data printers


/**Prints the given class schedule.
    * Time complexity: O(nlog(n)).*/
void interface::consult_class_schedule(const class1& a_class) const {
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
 */
void interface::consult_student_schedule_by_schedule(const student &a_student) const {
    set<pair<pair<schedule,string>,course>> student_schedule = get_student_schedule(a_student);
    cout << "Schedule for student " << a_student.get_name() << ", number " << a_student.get_number() <<":" << endl;
    auto it = student_schedule.begin();
    while(it != student_schedule.end()){
        cout << "Course " << it->second.get_course_name() << endl;
        cout << "Class " << it->first.second << " Schedule = " << it->first.first.week_day << " " << class1::convert_class_to_hour_and_minute_format(it->first.first) << endl;
        cout << '\n';
        it++;
    }
}

/**Prints the student schedule.
    * Time complexity: O(n^3).*/
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
    * Time complexity: O(nlog(n)).*/
void interface::consult_students_in_class_and_course(const class1& a_class, const course& a_course, const string& sortby, const string& sort_option) const{
    list<student> students = get_class_students_for_course(a_class,a_course);   //O(n)
    list<student> sorted_students {students.begin(), students.end()};   //O(n)

    sorted_students = sort_students_list(sorted_students, sortby, sort_option); //O(nlog(n))

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

/**Prints all the students in a course.
    * Time complexity: O(n^2).*/
void interface::consult_all_students_in_aCourse(const course& a_course, const string& sortby, const string& sort_option) const {
    set<student> students = get_all_students_in_aCourse(a_course); //O(n^2)
    list<student> sorted_students {students.begin(), students.end()}; //O(n)

    sorted_students = sort_students_list(sorted_students, sortby, sort_option); //O(nlog(n))

    cout << "Course: " << a_course.get_course_name() << endl;
    cout <<'\n';
    for (const student& a_student : sorted_students){
        cout <<"Name: " << a_student.get_name() << ' ' << "Number: " << a_student.get_number() << endl;
    }
}

/**Prints all the students in a year.
    * Time complexity: O(n^3).*/
void interface::consult_all_students_in_aYear(int year, const string& sortby, const string& sort_option) const {
    set<student> students = get_all_students_in_aYear(year); //O(n^3)
    list<student> sorted_students {students.begin(), students.end()};

    sorted_students = sort_students_list(sorted_students, sortby, sort_option);

    cout << "Year: " << year << endl;
    cout << '\n';
    for(const student& a_student: sorted_students){
        cout <<"Name: " << a_student.get_name() << ' ' << "Number: " << a_student.get_number() << endl;
    }
}

/**Prints the data in the entire system.
    * Time complexity: O(n^2log(n)).*/
void interface::print_data(const string& uc_sort_by , const string& class_sort_by ,const string& student_sort_by,const string& uc_sort_option, const string& class_sort_option, const string& student_sort_option) const{
    cout << "Printing data for the entire system" << endl;
    vector <course> sorted_courses = courses;
    sorted_courses = sort_course_vector(sorted_courses, uc_sort_by, uc_sort_option); //O(n(log(n))

    for(const course& a_course : sorted_courses){
        a_course.print_course_data(class_sort_by, student_sort_by, class_sort_option, student_sort_option); //O(nlog(n))
    }
}

/**Prints the occupation in every course and class for a specific year.
    * Time complexity: O(n^2log(n)).*/
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

/**Checks if it is possible to add a student to a given class in a given course
 * Time complexity: O(nlog(n))
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
    // getting the student schedule and checking potencial schedule overlaps
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


/**Function that tries to enroll a student in a new course.
 *  Returns true if the enrollment is successful and false if it isn't.
 *  Time complexity: O(n^3)
 */

bool interface::enroll_student_in_course(student &a_student, course &a_course, class1& a_class, string& error_message) {
    //Checking if the student has not enrolled in the maximum number of courses
    if(number_of_courses_per_student(a_student) >= 7){ //O(n^3)
        error_message = "Enrollment failed because student is already enrolled in the maximum number of courses possible.";
        return false;
    }
    //accessing the desired course in courses
    auto it = std::find(courses.begin(), courses.end(),a_course);
    course& added_course = *it;
    course copy_added_course = added_course;
    class1 copy_added_class = a_class;
    student added_student = get_student(a_student);
    if(copy_added_course.has_student(added_student)){
        error_message = "The student is already enrolled in the desired course.";
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
            return true;
        }
    }
    error_message = "Enrollment failed because the student could not be allocated to any of the classes available for course " + a_course.get_course_name();
    return false;
}


/**Functions that tries to remove a student from a course.
* Returns true if the removal is successful and false if it isn't
* Time complexity: O(n^2) */
bool interface::remove_student_from_course(student &a_student, course &a_course, string& error_message) {
    //finding the target course in courses
    auto it = std::find(courses.begin(),courses.end(),a_course);
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
* Time complexity: O(n^3)*/
bool interface::switch_student_courses(student &a_student, course &old_course, course &new_course, class1& new_class, string& error_message) {
    auto it = std::find(courses.begin(), courses.end(), old_course);
    course old_course_copy = *it;

    if (!old_course_copy.has_student(a_student)) {
        error_message = "Student is not enrolled in course " + old_course.get_course_name();
        return false;
    }
    if(!enroll_student_in_course(a_student,new_course,new_class,error_message)){
        return false;
    }
    remove_student_from_course(a_student,old_course,error_message);
    return true;
}

/**Switches students from one class to another in a given course if possible.
* Time complexity: O(n^3) */
bool interface::switch_student_classes(student &a_student, course &a_course, class1 &old_class, class1 &new_class, string& error_message) {
    //finding the target course in courses
    auto it = std::find(courses.begin(),courses.end(),a_course);
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
 */
bool interface::process_request(string& error_message, const string& new_student_filename, const string& new_request_filename) {
    request processed_request = requests.front();
    requests.pop();
    remove_request_from_file(new_request_filename);
    students_requests_filename = new_request_filename;
    if(processed_request.request_type == "add course"){
        if(enroll_student_in_course(processed_request.target_student, processed_request.added_course, processed_request.added_class, error_message)){
            class1 new_class = processed_request.added_course.get_student_class(processed_request.target_student);
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
        if(switch_student_courses(processed_request.target_student, processed_request.added_course,processed_request.removed_course, processed_request.added_class, error_message)){
            class1 new_class = processed_request.added_course.get_student_class(processed_request.target_student);
            switch_student_courses_in_file(processed_request.target_student, processed_request.added_course,processed_request.removed_course, new_class,new_student_filename);
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
        std::cerr << "Error: Unable to open the CSV file for writing." << std::endl;
        return;
    }
    // opening the student requests file in write mode
    ofstream write_file(new_filename_path,ios::app);
    if (!write_file.is_open()) {
        std::cerr << "Error: Unable to open the CSV file for writing." << std::endl;
        return;
    }
    write_file << read_file.rdbuf();
    // adding the new request to the file using the appropriate format
    write_file << new_line << endl;
    read_file.close();
    write_file.close();
}

/**Removes the top request from the student requests file after a request is processed.
* Time complexity : O(n) */
void interface::remove_request_from_file(const string& new_request_filename) {
    string requests_file,line;
    requests_file = "../Data_files/" + students_requests_filename;
    //opening original student requests file
    ifstream read_file(requests_file);
    // opening copy of student requests file
    ofstream write_file(new_request_filename);
    //getting the first line of the file so that oit is not copied to the copy of the student requests file
    getline(read_file,line);
    //copying every line of the original file to the new copy file with the exception of the first one
    while(getline(read_file,line)){
        write_file << line << endl;
    }
    //closing both files
    read_file.close();
    write_file.close();
}

void interface::enroll_student_in_course_in_file(student &a_student, course &a_course, class1 &a_class, const string& new_filename){
    string students_file,new_students_file,line,target_student_number,target_student_name;
    students_file = "../Data_files/" + students_classes_filename;
    new_students_file = new_filename;
    ifstream read_file(students_file);
    ofstream write_file(new_students_file);
    if (!read_file.is_open() || !write_file.is_open()) {
        cout << "Error: Unable to open files." << endl;
        return;
    }
    bool found_student = false;
    while(getline(read_file,line)){
        auto it = line.find_first_of(',');
        target_student_number = line.substr(0,it);
        if(target_student_number != a_student.get_number() || found_student){
            write_file << line << endl;
            continue;
        }
        line = line.substr(it + 1);
        it = line.find_first_of(',');
        target_student_name = line.substr(0,it);
        write_file << target_student_number << ',' << target_student_name << ',' << a_course.get_course_name() << ',' << a_class.get_class_name() << endl;
        found_student = true;
    }
    read_file.close();
    write_file.close();
}

void interface::remove_student_from_course_in_file(student &a_student, course &a_course,const std::string &new_filename) {
    string student_file, new_student_file,line, target_student_number, target_student_name, target_course, aux_line;
    student_file = students_classes_filename;
    new_student_file = new_filename;
    ifstream read_file(student_file);
    ofstream write_file(new_student_file);
    while(getline(read_file,line)){
        auto it = line.find_first_of(',');
        aux_line = line;
        target_student_number = line.substr(0,it);
        if(target_student_number != a_student.get_number()){
            write_file << line << endl;
            continue;
        }
        aux_line = aux_line.substr(it + 1);
        it = aux_line.find_first_of(',');
        target_student_name = aux_line.substr(0,it);
        aux_line = aux_line.substr(it + 1);
        it = aux_line.find_first_of(',');
        target_course = aux_line.substr(0,it);
        if(target_student_number == a_student.get_number() &&  target_course == a_course.get_course_name()){
            continue;
        }
        write_file << line << endl;
    }
}

void interface::switch_student_courses_in_file(student &a_student, course &old_course, course &new_course, class1 &new_class, const std::string &new_filename) {
    string students_file,new_students_file,line,target_student_number,target_student_name,target_course,save_line;
    students_file = "../Data_files/" + students_classes_filename;
    new_students_file = new_filename;
    ifstream read_file(students_file);
    ofstream write_file(new_students_file);
    if (!read_file.is_open() || !write_file.is_open()) {
        cout << "Error: Unable to open files." << endl;
        return;
    }
    while(getline(read_file,line)){
        save_line = line;
        auto it = line.find_first_of(',');
        target_student_number = line.substr(0,it);
        if(target_student_number != a_student.get_number()){
            write_file << line << endl;
            continue;
        }
        line = line.substr(it + 1);
        it = line.find_first_of(',');
        target_student_name = line.substr(0,it);
        line = line.substr(it + 1);
        target_course = line.substr(0,it);
        if(target_course == old_course.get_course_name()){
            write_file << target_student_number << ',' << target_student_name << ',' << new_course.get_course_name() << ',' << new_class.get_class_name() << endl;
            continue;
        }
        line = save_line;
        write_file << line << endl;
    }
}

void interface::switch_student_classes_in_file(student &a_student, course &a_course, class1 &old_class,class1 &new_class, const std::string &new_filename) {
    string students_file,new_students_file,line,target_student_number,target_student_name,target_course,save_line;
    students_file = "../Data_files/" + students_classes_filename;
    new_students_file = new_filename;
    ifstream read_file(students_file);
    ofstream write_file(new_students_file);
    if (!read_file.is_open() || !write_file.is_open()) {
        cout << "Error: Unable to open files." << endl;
        return;
    }
    while(getline(read_file,line)){
        save_line = line;
        auto it = line.find_first_of(',');
        target_student_number = line.substr(0,it);
        if(target_student_number != a_student.get_number()){
            write_file << line << endl;
            continue;
        }
        line = line.substr(it + 1);
        it = line.find_first_of(',');
        target_student_name = line.substr(0,it);
        line = line.substr(it + 1);
        target_course = line.substr(0,it);
        if(target_course == a_course.get_course_name()){
            write_file << target_student_number << ',' << target_student_name << ',' << target_course << ',' << new_class.get_class_name() << endl;
            continue;
        }
        line = save_line;
        write_file << line << endl;
    }
}

/**Stores a new request into the requests queue.
 * Time complexity: O(1)
 */
void interface::store_new_request(const request &new_request, const string& new_filename) {
    requests.push(new_request);
    add_request_to_file(new_request,new_filename);
    students_requests_filename = new_filename;
}

//setters --------------------------------------------------------------
/**Sets the courses vector to the given vector of courses
* Time complexity: O(1)*/
void interface::set_courses(vector<course> courses) {
    this->courses = courses;
}
