//
// Created by franc on 22/10/2023.
//
//Each Interface function should be called here inside a system function with the same name
//The interface function should be associated to the interface that is on top of the system stack
// in case it is a read only
// or apllied to a new interface function if it changes the system interface in any way
#include "schedule_system.h"

schedule_system::schedule_system() {
    interface start_interface;
    start_interface.read_data_classes_per_uc();
    start_interface.read_data_classes();
    start_interface.read_data_students_classes();
    system_changes.push((start_interface));
}

void schedule_system::consult_class_schedule(class1 a_class) const {
    system_changes.top().consult_class_schedule(a_class);
}

void schedule_system::consult_student_schedule(student a_student) const {
    system_changes.top().consult_student_schedule_by_course(a_student);
}

void schedule_system::consult_students_in_class_and_course(class1 a_class, course a_course) const {
    system_changes.top().consult_students_in_class_and_course(a_class,a_course);
}

void schedule_system::consult_students_in_class(class1 a_class) const{
    system_changes.top().consult_students_in_class(a_class);
}

void schedule_system::store_new_request(const request &new_request) {
    system_changes.top().store_new_request(new_request);
}

void schedule_system::process_request(std::string &error_message) {
    interface new_system_iteration = system_changes.top();
    new_system_iteration.process_request(error_message);
    system_changes.push(new_system_iteration);
}

//Controls the flow of the program according to the users instructions
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
        std::cout << "4. Consult all the students enrolled in a given class" << endl;
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
            consult_students_in_class_and_course(target_class, target_course);
        }

        else if(option == '4'){
            string class_name;
            cout << "Please write the name of the class you wish to check: ";
            cin >> class_name;
            cout << endl;
            class1 target_class(class_name);
            consult_students_in_class(target_class);
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

void schedule_system::print_current_schedule_system_data() const {
    system_changes.top().print_data();
}