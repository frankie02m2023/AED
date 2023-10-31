//
// Created by franc on 22/10/2023.
//
// Each Interface function should be called here inside a system function with the same name
// The interface function should be associated to the interface that is on top of the system stack
// in case it is a read only
// or apllied to a new interface function if it changes the system interface in any way
<<<<<<< HEAD

=======

>>>>>>> 1efb7d863adaadba0b7ab09ed2a7f24deee88aa3
#include "schedule_system.h"

/**
* @file schedule_system.cpp
* @brief Implementation of class schedule_system.
*/

schedule_system::schedule_system() {
    interface start_interface;
    start_interface.read_data_classes_per_uc();
    start_interface.read_data_classes();
    start_interface.read_data_students_classes();
    start_interface.read_data_students_requests();
    system_changes.push((start_interface));
    number_of_request_changes = 0;
    number_of_student_data_changes = 0;
}

/** Consults the given class schedule.
 * Time complexity : O(nlog(n))
 *
 */
void schedule_system::consult_class_schedule(class1 a_class) const {
    system_changes.top().consult_class_schedule(a_class);
}

/** Consults the given student schedule.
* Time complexity: O(n^3)
 */
void schedule_system::consult_student_schedule(student a_student) const {
    system_changes.top().consult_student_schedule_by_course(a_student);
}

/** Consults students in a given class and course.
 *  Time complexity: O(nlog(n))
 */
void schedule_system::consult_students_in_class_and_course(class1 a_class, course a_course, string sortby, string sort_option) const{
    system_changes.top().consult_students_in_class_and_course(a_class,a_course,sortby, sort_option);
}

/** Consults all the student in a given course.
* Time complexity: O(n^2) */
void schedule_system::consult_all_students_in_aCourse(course a_course, const string& sort_by, const string& sort_option) const{
    system_changes.top().consult_all_students_in_aCourse(a_course,sort_by,sort_option);
}

/** Consults all the students in a given year.
 * Time complexity: O(n^3)
 */
void schedule_system::consult_all_students_in_aYear(int year, const string& sort_by, const string& sort_option) const{
    system_changes.top().consult_all_students_in_aYear(year,sort_by,sort_option);
}

/** Consults the occupation of all courses and classes in a given year.
 * Time complexity: O(n^2log(n))
 */
void schedule_system::consult_classes_and_courses_occupation_by_year(int year, const string& uc_sort_by, const string& class_sort_by,const string& sorting_uc, const string& sorting_classes){
    system_changes.top().consult_classes_and_courses_occupation_by_year(year,uc_sort_by,class_sort_by,sorting_uc,sorting_classes);
}

/** Stores new requests into the requests queue in the interface that is on top of the stack.
 * Time complexity: O(1)
 */
void schedule_system::store_new_request(const request &new_request) {
    interface new_system_iteration = system_changes.top();
    number_of_request_changes++;
    string new_request_filename = "students_requests.csv" + to_string(number_of_request_changes);
    new_system_iteration.store_new_request(new_request,new_request_filename);
    system_changes.push(new_system_iteration);
}

/** Processes the request in front of the queue and stores the changes into the system_changes stack.
* Time complexity: O(n^3) */
void schedule_system::process_request(std::string &error_message) {
    interface new_system_iteration = system_changes.top();
    string new_data_change_filename,new_request_filename;
    new_request_filename = "students_requests.csv" + to_string(number_of_request_changes);
    number_of_request_changes++;
    new_data_change_filename = "classes_students.csv" + to_string(number_of_student_data_changes + 1);
    if(new_system_iteration.process_request(error_message,new_data_change_filename,new_request_filename)){
        number_of_student_data_changes++;
    }
    system_changes.push(new_system_iteration);
}

void schedule_system::undo_system_changes() {
    string old_student_data_filename = system_changes.top().get_students_classes_filename();
    string old_requests_filename = system_changes.top().get_students_requests_filename();
    system_changes.pop();
    if(system_changes.top().get_students_classes_filename() != old_student_data_filename){
        string old_student_data_path = "../Data_files/" + old_student_data_filename;
        std::filesystem::path oldStudentDataPath(old_student_data_path);
        if (std::filesystem::exists(oldStudentDataPath)) {
            std::filesystem::remove(oldStudentDataPath);
        }
    }
    if(system_changes.top().get_students_classes_filename() != old_requests_filename){
        string old_requests_path = "../Data_files/" + old_requests_filename;
        std::filesystem::path oldRequestsPath(old_requests_path);
        if (std::filesystem::exists(oldRequestsPath)) {
            std::filesystem::remove(oldRequestsPath);
        }
    }
}

/**Controls the flow of the program according to the users instructions.
* Time complexity varies depending on the functions that are called: between O(n) and O(n^3)*/
    void schedule_system::schedule_system_functions(){
        std::cout << "Write 1 in the terminal if you wish to read data in the system" << endl;
        std::cout << "Write 2 in the terminal if you wish to add a request into the system" << endl;
        std::cout << "Type here:  " ;
        char option;
        std::cin >> option;
        std::cout << endl;

        if(option == '1'){
            std::cout << "Please type the number associated with the action you wish to perform: " << endl;
            std::cout << "1. Consult a given class's timetable" << endl;
            std::cout << "2. Consult a given student's timetable" << endl;
            std::cout << "3. Consult all the students enrolled in a given class and course" << endl;
            std::cout << "4. Consult all the students enrolled in a given course" << endl;
            std::cout << "5. Consult all the students who are at a given grade" << endl;
            std::cout << "6. Consult detailed information about all the courses and classes in a given year" << endl;
            cin >> option;

            if(option == '1'){
                string class_name;
                cout << "Please write the name of the class whose schedule you wish to consult: ";
                cin >> class_name;
                cout << endl;
                class1 target_class(class_name);
                consult_class_schedule(target_class);
            }

            else if(option == '2'){
                string student_name, student_number;
                cout << "Please write the name and number of the student whose schedule you wish to consult: ";
                cin >> student_name;
                cout << " ";
                cin >> student_number;
                cout << endl;
                student target_student(student_name, student_number);
                system_changes.top().consult_student_schedule_by_schedule(target_student);
            }

            else if(option == '3'){
                string class_name, course_code;
                cout << "Please write the name of the class you wish to check:";
                cin >> class_name;
                cout << "Please write the name of the course you wish to check: ";
                cin >> course_code;
                cout << endl;
                class1 target_class(class_name);
                course target_course(course_code);
                //consult_students_in_class_and_course(target_class, target_course);
            }

            else if(option == '4'){
                string course_name;
                char sorting_option;
                char sorting_order;
                cout << "Please write the name of the course you wish to check:" << endl;
                cin >> course_name;
                course target_course(course_name);
                cout << "Please select the number associated with the sorting criteria you wish to choose:" << endl;
                cout << "1. Name" << endl;
                cout << "2. Number" << endl;
                cout << "3. No sorting preference" << endl;
                cin  >> sorting_option;
                cout << endl;
                cout << "Please select how wish to order the list of students based on your sorting criteria:" << endl;
                cout << "1. Ascending";
                cout << "2. Descending";
                cin >> sorting_order;
                if(sorting_option == '1' || sorting_option == '3'){
                    if(sorting_order == '1'){
                        consult_all_students_in_aCourse(target_course,"name","ascending");
                    }
                    else if(sorting_order == '2'){
                        consult_all_students_in_aCourse(target_course,"name","descending");
                    }
                }
                else if(sorting_option == '2'){
                    if(sorting_order == '1'){
                        consult_all_students_in_aCourse(target_course,"number","ascending");
                    }
                    else if(sorting_order == '2'){
                        consult_all_students_in_aCourse(target_course,"number","descending");
                    }
                }
            }
            else if(option == '5'){
                string target_year;
                int target_grade;
                char sorting_option;
                char sorting_order;
                cout << "Please write the number associated with the grade you wish to check: ";
                cin >> target_year;
                cout << '\n';
                target_grade = stoi(target_year);
                cout << "Please select the number associated with the sorting criteria you wish to choose:" << endl;
                cout << "1. Student name" << endl;
                cout << "2. Student number" << endl;
                cout << "3. No sorting preference" << endl;
                cin  >> sorting_option;
                cout << endl;
                cout << "Please select how wish to order the list of students based on your sorting criteria:" << endl;
                cout << "1. Ascending";
                cout << "2. Descending";
                cin >> sorting_order;
                if(sorting_option == '1' || sorting_option == '3'){
                    if(sorting_order == '1'){
                        consult_all_students_in_aYear(target_grade,"name","ascending");
                    }
                    else if(sorting_order == '2'){
                        consult_all_students_in_aYear(target_grade,"name","descending");
                    }
                }
                else if(sorting_option == '2'){
                    if(sorting_order == '1'){
                        consult_all_students_in_aYear(target_grade,"number","ascending");
                    }
                    else if(sorting_order == '2'){
                        consult_all_students_in_aYear(target_grade,"number","descending");
                    }
                }
            }
            else if(option == '6'){
                string year;
                int grade;
                string sorting_class_option,sorting_class_order,sorting_course_option,sorting_course_order;
                cout << "Please write the number of the grade you wish to check:";
                cin >> year;
                grade = stoi(year);
                cout << "Please select the number associated with the sorting criteria you wish to choose:" << endl;
                cout << "1. Course Name" << endl;
                cout << "2. Course occupation" << endl;
                cout << "3. No sorting preference" << endl;
                cin  >> sorting_course_option;
                cout << endl;
                cout << "Please select how wish to order the list of courses based on your sorting criteria:" << endl;
                cout << "1. Ascending" << endl;
                cout << "2. Descending" << endl;
                cin >> sorting_course_order;
                cout << "Please select the number associated with the sorting criteria you wish to choose:" << endl;
                cout << "1. Class Name" << endl;
                cout << "2. Class Occupation" << endl;
                cout << "3. No sorting preference" << endl;
                cin  >> sorting_class_option;
                cout << endl;
                cout << "Please select how wish to order the list of classes based on your sorting criteria:" << endl;
                cout << "1. Ascending" << endl;
                cout << "2. Descending" << endl;
                cin >> sorting_class_order;
                cout << endl;
                if(sorting_course_option == "1"){
                    sorting_course_option = "name";
                }
                else if (sorting_course_option == "2" || sorting_course_option == "3"){
                    sorting_course_option = "occupation";
                }
                if(sorting_course_order == "1"){
                    sorting_course_order = "ascending";
                }
                else if(sorting_course_order == "2"){
                    sorting_course_order = "descending";
                }
                if(sorting_class_option == "1"){
                    sorting_class_option = "name";
                }
                else if (sorting_class_option == "2" || sorting_class_option == "3"){
                    sorting_class_option = "occupation";
                }
                if(sorting_class_order == "1"){
                    sorting_class_order = "ascending";
                }
                else if(sorting_class_order == "2"){
                    sorting_class_order = "descending";
                }
                consult_classes_and_courses_occupation_by_year(grade,sorting_course_option,sorting_class_option,sorting_course_order,sorting_class_order);
                cout << sorting_class_option;
            }

        }
        else if(option == '2'){
            string student_number, added_course, removed_course, added_class, removed_class;
            struct request new_request;
            std::cout << "Please enter your student number : ";
            cin >> student_number;
            std::cout << "Please type the number associated with the request you wish to make: " << endl;
            std::cout << "1. Enroll in a new course" << endl;
            std::cout << "2. Drop out of a course" << endl;
            std::cout << "3. Swap one of your courses for a new one" << endl;
            std::cout << "4. Swap classes for a specific course" << endl;
            cin >> option;
            if(option == '1'){
                std::cout << "Please enter the name of the course you wish to enroll in: ";
                cin >> added_course;
                std::cout << "Please enter the name of the class you wish to enroll in: ";
                cin >> added_class;
                new_request.request_type = "add course";
                new_request.added_course = added_course;
                new_request.added_class = added_class;
                store_new_request(new_request);
            }
            else if(option == '2'){
                std::cout << "Please enter the name of the course you wish to drop out of: ";
                cin >> removed_course;
                new_request.request_type = "remove course";
                new_request.removed_course = removed_course;
                store_new_request(new_request);
            }
            else if(option == '3'){
                std::cout << "Please enter the name of the course you wish to enroll in: ";
                cin >> added_course;
                std::cout << "Please enter the name of the course you wish to drop out of: ";
                cin >> removed_course;
                std::cout << "Please enter the name of the class you wish to enroll in: ";
                cin >> added_class;
                new_request.request_type = "switch courses";
                new_request.added_course = added_course;
                new_request.removed_course = removed_course;
                new_request.added_class = added_class;
                store_new_request(new_request);
            }
            else if(option == '4'){
                std::cout << "Please enter the name of the course for which you desire to swap class: ";
                cin >> added_course;
                std::cout << "Please enter the name of the class you wish to enroll in: ";
                cin >> added_class;
                std::cout << "Please enter the name of the class you wish to leave : ";
                cin >> removed_class;
                new_request.request_type = "switch classes";
                new_request.added_course = added_course;
                new_request.added_class = added_class;
                new_request.removed_class = removed_class;
                store_new_request(new_request);
            }
        }
    }

    /**Prints all the data into the interface that is on top of the stack.
    * Time Complexity : O(n^2log(n)) */
void schedule_system::print_current_schedule_system_data() const {
    system_changes.top().print_data();
}