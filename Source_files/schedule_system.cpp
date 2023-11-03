//
// Created by franc on 22/10/2023.
//
// Each Interface function should be called here inside a system function with the same name
// The interface function should be associated to the interface that is on top of the system stack
// in case it is a read only
// or apllied to a new interface function if it changes the system interface in any way

#include <filesystem>
#include <fstream>
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
    start_interface.set_students_classes_filename("students_classes.csv");
    start_interface.set_students_requests_filename("students_requests.csv");
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

/** Consults the requests made to the system.
 *  Time complexity: O(n)
 */
void schedule_system::consult_student_requests() const {
    system_changes.top().consult_student_requests();
}

/** Stores new requests into the requests queue in the interface that is on top of the stack.
 * Time complexity: O(1)
 */
void schedule_system::store_new_request(const request &new_request) {
    //creating a copy of the current system version
    interface new_system_iteration = system_changes.top();
    //incrementing the variable that stores the number of changes made to the requests file during the current system execution
    number_of_request_changes++;
    //using the number_of_request_changes variable to create a new version of the students_requests.csv file with a name different from all the older versions
    string new_request_filename = "students_requests.csv" + to_string(number_of_request_changes);
    //calling the interface member function store_new_request to add the new request to the new interface and associate it with the newest version of the requests file
    new_system_iteration.store_new_request(new_request,new_request_filename);
    //pushing the new system version into the stack that stores the different system iterations
    system_changes.push(new_system_iteration);
}

/**Removes the request in front of the queue from the system, updates the files and adds this changes to the top of the system_changes stack.
 * Time complexity: O(n)
 */
void schedule_system::remove_request() {
    interface new_system_iteration = system_changes.top();
    number_of_request_changes++;
    string new_request_filename = "students_requests.csv" + to_string(number_of_request_changes);
    new_system_iteration.remove_request(new_request_filename);
    system_changes.push(new_system_iteration);
}

/** Processes the request in front of the queue and stores the changes into the system_changes stack.
* Time complexity: O(n^3) */
void schedule_system::process_request(std::string &error_message) {
    // creating a copy of the most recent system version
    interface new_system_iteration = system_changes.top();
    string new_data_change_filename,new_request_filename;

    //incrementing the variable that stores the number of changes made to the requests file during the current system execution
    //we do so to create a new version of the requests file that has a different name from all the older versions
    number_of_request_changes++;

    // setting up the name of the student requests file that will be linked to the new system iteration
    new_request_filename = "students_requests.csv" + to_string(number_of_request_changes);

    // setting up the name of the student classes file that will be linked to the new system iteration if the students request is fulfilled
    new_data_change_filename = "students_classes.csv" + to_string(number_of_student_data_changes + 1);

    //checking if the student request is fulfilled
    //if it is we increment the variable that stores the amount of changes made to the students classes file by one
    //if the request is fulfilled the process_request method in the interface class then creates a new version of the students_classes.csv file reflecting the changes made to the system due to the requests fulfillment
    //the same method also creates a new version of the students_requests.csv file that does not contain the request that is being processed anymore
    if(new_system_iteration.process_request(error_message,new_data_change_filename,new_request_filename)){
        number_of_student_data_changes++;
    }
    //adding the new system iteration or "interface" to the top of the stack that saves system changes
    system_changes.push(new_system_iteration);
}

/**Reverts the last change made to the system.
* That change can be either the submission or the processing of a new a request and the changes that come with it.
 * Time complexity: O(n) */
void schedule_system::undo_system_changes() {
    //getting the names of the data files associated with the current version of the system
    string old_student_data_filename = system_changes.top().get_students_classes_filename();
    string old_requests_filename = system_changes.top().get_students_requests_filename();
    //removing the current version of the system from the stack
    system_changes.pop();
    //deleting files that aren't associated with any version of the system stored in the stack after the undo operation
    //to be simplified tomorrow
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
    void schedule_system::schedule_system_functions() {
    string continue_or_exit;
    while (true) {
        cout << "Type EXIT in the terminal if you wish to close the system or type anything else if you wish to use the system" << endl;
        cout << "Warning : While using the system inserting any invalid input into the terminal will cause the system menu to reset!" << endl;
        cout << "Warning : If you want to add a multi-word name when asked to add your name please separate the two words using '_'" << endl;
        cin >> continue_or_exit;
        if(continue_or_exit == "EXIT"){
            break;
        }
        std::cout << "Write 1 in the terminal if you wish to read data about courses,classes and students in the system"<< endl;
        std::cout << "Write 2 in the terminal if you wish to add a request into the system" << endl;
        std::cout << "Write 3 in the terminal if you wish to consult the requests made to the system" << endl;
        std::cout << "Write 4 in the terminal if you wish to perform admin tasks" << endl;
        std::cout << "Type here:  ";
        char option;
        std::cin >> option;
        std::cout << endl;

        if (option == '1') {
            std::cout << "Please type the number associated with the action you wish to perform: " << endl;
            std::cout << "1. Consult a given class's timetable" << endl;
            std::cout << "2. Consult a given student's timetable" << endl;
            std::cout << "3. Consult all the students enrolled in a given class and course" << endl;
            std::cout << "4. Consult all the students enrolled in a given course" << endl;
            std::cout << "5. Consult all the students who are at a given grade" << endl;
            std::cout << "6. Consult detailed information about all the courses and classes in a given year" << endl;
            cin >> option;

            if (option == '1') {
                string class_name;
                cout << "Please write the name of the class whose schedule you wish to consult: ";
                cin >> class_name;
                cout << endl;
                class1 target_class(class_name);
                consult_class_schedule(target_class);
            } else if (option == '2') {
                string student_name, student_number, sort_option;
                cout << "Please write the name and number of the student whose schedule you wish to consult: " << endl;
                cout << "Name: ";
                cin >> student_name;
                cout << "\n";
                cout << "Number:";
                cin >> student_number;
                cout << endl;
                student target_student(student_name, student_number);
                cout << "Please select the number associated with the sorting criteria you wish to choose" << endl;
                cout <<"1. Course" << endl;
                cout <<"2. Schedule" << endl;
                cin >> sort_option;
                if(sort_option == "1"){
                    consult_student_schedule(target_student);
                }
                else if(sort_option == "2") {
                    system_changes.top().consult_student_schedule_by_schedule(target_student);
                }
            } else if (option == '3') {
                string class_name, course_code;
                cout << "Please write the name of the class you wish to check:";
                cin >> class_name;
                cout << "Please write the name of the course you wish to check: ";
                cin >> course_code;
                cout << endl;
                class1 target_class(class_name);
                course target_course(course_code);
                char sorting_option;
                char sorting_order;
                cout << "Please select the number associated with the sorting criteria you wish to choose:" << endl;
                cout << "1. Name" << endl;
                cout << "2. Number" << endl;
                cout << "3. No sorting preference" << endl;
                cin >> sorting_option;
                cout << endl;
                cout << "Please select how wish to order the list of students based on your sorting criteria:" << endl;
                cout << "1. Ascending" << endl;
                cout << "2. Descending" << endl;
                cin >> sorting_order;
                if (sorting_option == '1' || sorting_option == '3') {
                    if (sorting_order == '1') {
                        consult_students_in_class_and_course(target_class, target_course, "name", "ascending");
                    } else if (sorting_order == '2') {
                        consult_students_in_class_and_course(target_class,target_course, "name", "descending");
                    }
                } else if (sorting_option == '2') {
                    if (sorting_order == '1') {
                        consult_students_in_class_and_course(target_class,target_course, "number", "ascending");
                    } else if (sorting_order == '2') {
                        consult_students_in_class_and_course(target_class,target_course, "number", "descending");
                    }
                }
            } else if (option == '4') {
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
                cin >> sorting_option;
                cout << endl;
                cout << "Please select how wish to order the list of students based on your sorting criteria:" << endl;
                cout << "1. Ascending" << endl;
                cout << "2. Descending" << endl;
                cin >> sorting_order;
                if (sorting_option == '1' || sorting_option == '3') {
                    if (sorting_order == '1') {
                        consult_all_students_in_aCourse(target_course, "name", "ascending");
                    } else if (sorting_order == '2') {
                        consult_all_students_in_aCourse(target_course, "name", "descending");
                    }
                } else if (sorting_option == '2') {
                    if (sorting_order == '1') {
                        consult_all_students_in_aCourse(target_course, "number", "ascending");
                    } else if (sorting_order == '2') {
                        consult_all_students_in_aCourse(target_course, "number", "descending");
                    }
                }
            } else if (option == '5') {
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
                cin >> sorting_option;
                cout << endl;
                cout << "Please select how wish to order the list of students based on your sorting criteria:" << endl;
                cout << "1. Ascending" << endl;
                cout << "2. Descending" << endl;
                cin >> sorting_order;
                if (sorting_option == '1' || sorting_option == '3') {
                    if (sorting_order == '1') {
                        consult_all_students_in_aYear(target_grade, "name", "ascending");
                    }
                    else if (sorting_order == '2') {
                        consult_all_students_in_aYear(target_grade, "name", "descending");
                    }
                    else {
                        cout << endl;
                        continue;
                    }
                }
                else if (sorting_option == '2') {
                    if (sorting_order == '1') {
                        consult_all_students_in_aYear(target_grade, "number", "ascending");
                    }
                    else if (sorting_order == '2') {
                        consult_all_students_in_aYear(target_grade, "number", "descending");
                    }
                    else{
                        cout << endl;
                        continue;
                    }
                }
                else{
                    cout << endl;
                    continue;
                }
            } else if (option == '6') {
                string year;
                int grade;
                string sorting_class_option, sorting_class_order, sorting_course_option, sorting_course_order;
                cout << "Please write the number of the grade you wish to check:";
                cin >> year;
                grade = stoi(year);
                cout << "Please select the number associated with the sorting criteria you wish to choose:" << endl;
                cout << "1. Course Name" << endl;
                cout << "2. Course occupation" << endl;
                cout << "3. No sorting preference" << endl;
                cin >> sorting_course_option;
                cout << endl;
                cout << "Please select how wish to order the list of courses based on your sorting criteria:" << endl;
                cout << "1. Ascending" << endl;
                cout << "2. Descending" << endl;
                cin >> sorting_course_order;
                cout << "Please select the number associated with the sorting criteria you wish to choose:" << endl;
                cout << "1. Class Name" << endl;
                cout << "2. Class Occupation" << endl;
                cout << "3. No sorting preference" << endl;
                cin >> sorting_class_option;
                cout << endl;
                cout << "Please select how wish to order the list of classes based on your sorting criteria:" << endl;
                cout << "1. Ascending" << endl;
                cout << "2. Descending" << endl;
                cin >> sorting_class_order;
                cout << endl;
                if (sorting_course_option == "1") {
                    sorting_course_option = "name";
                }
                else if (sorting_course_option == "2" || sorting_course_option == "3") {
                    sorting_course_option = "occupation";
                }
                else{
                    cout << endl;
                    continue;
                }
                if (sorting_course_order == "1") {
                    sorting_course_order = "ascending";
                }
                else if (sorting_course_order == "2") {
                    sorting_course_order = "descending";
                }
                else{
                    cout << endl;
                    continue;
                }
                if (sorting_class_option == "1") {
                    sorting_class_option = "name";
                }
                else if (sorting_class_option == "2" || sorting_class_option == "3") {
                    sorting_class_option = "occupation";
                }
                else{
                    cout << endl;
                    continue;
                }
                if (sorting_class_order == "1") {
                    sorting_class_order = "ascending";
                }
                else if (sorting_class_order == "2") {
                    sorting_class_order = "descending";
                }
                else{
                    cout << endl;
                    continue;
                }
                consult_classes_and_courses_occupation_by_year(grade, sorting_course_option, sorting_class_option,
                                                               sorting_course_order, sorting_class_order);
                cout << sorting_class_option;
            }
            else{
                cout << endl;
                continue;
            }
            cout << endl;
        }
        else if (option == '2') {
            string student_number, student_name, added_course, removed_course, added_class, removed_class;
            struct request new_request;
            std::cout << "Please enter your student number:";
            cin >> student_number;
            cout << endl;
            std::cout << "Please enter your student name:";
            cin >> student_name;
            cout << endl;
            student target_student(student_name,student_number);
            new_request.target_student = target_student;
            std::cout << "Please type the number associated with the request you wish to make: " << endl;
            std::cout << "1. Enroll in a new course" << endl;
            std::cout << "2. Drop out of a course" << endl;
            std::cout << "3. Swap one of your courses for a new one" << endl;
            std::cout << "4. Swap classes for a specific course" << endl;
            cin >> option;
            cout << endl;
            if (option == '1') {
                std::cout << "Please enter the name of the course you wish to enroll in:";
                cin >> added_course;
                std::cout << "Please enter the name of the class you wish to enroll in:";
                cin >> added_class;
                new_request.request_type = "add course";
                new_request.added_course = added_course;
                new_request.added_class = added_class;
                store_new_request(new_request);
            } else if (option == '2') {
                std::cout << "Please enter the name of the course you wish to drop out of:";
                cin >> removed_course;
                new_request.request_type = "remove course";
                new_request.removed_course = removed_course;
                store_new_request(new_request);
            } else if (option == '3') {
                std::cout << "Please enter the name of the course you wish to enroll in:";
                cin >> added_course;
                std::cout << "Please enter the name of the course you wish to drop out of:";
                cin >> removed_course;
                std::cout << "Please enter the name of the class you wish to enroll in: ";
                cin >> added_class;
                new_request.request_type = "switch courses";
                new_request.added_course = added_course;
                new_request.removed_course = removed_course;
                new_request.added_class = added_class;
                store_new_request(new_request);
            } else if (option == '4') {
                std::cout << "Please enter the name of the course for which you desire to swap class:";
                cin >> added_course;
                std::cout << "Please enter the name of the class you wish to enroll in:";
                cin >> added_class;
                std::cout << "Please enter the name of the class you wish to leave:";
                cin >> removed_class;
                new_request.request_type = "switch classes";
                new_request.added_course = added_course;
                new_request.added_class = added_class;
                new_request.removed_class = removed_class;
                store_new_request(new_request);
            }
            else{
                cout << endl;
                continue;
            }
            cout << endl;
            cout << "Your request was submitted successfully!";
            cout << endl << endl;
        }
        else if(option == '3'){
            consult_student_requests();
            cout << endl;
        }
        else if(option == '4'){
            std::cout << "Please type the number associated with the task you wish to perform:" << endl;
            std::cout << "1.Process the next student request" << endl;
            std::cout << "2.Delete the next student request to be processed" << endl;
            std::cout << "3.Undo the latest changes made to the system (should be used carefully and only as a last resort)" << endl;
            cin >> option;
            if(option == '1'){
                string error_message = "";
                process_request(error_message);
                if(error_message == "" || error_message == "Student could not be allocated to their desired class."){
                    cout << "The request was fulfilled successfully and the according changes were made to the system!" << endl;
                    if(error_message == "Student could not be allocated to their desired class."){
                        cout << "Warning : " + error_message << endl;
                    }
                }
                else{
                    cout << "The request was processed but could not be fulfilled" << endl;
                    cout << "Reason : " + error_message << endl;

                }
            }
            else if(option == '2'){
                remove_request();
                cout << "The request in front of the requests queue was successfully removed from the system" << endl;
            }
            else if(option == '3'){
                std::cout << "Undoing the most recent changes made to the system can lead to an irrecoverable data loss! Are you sure you wish to continue? y or n?" << endl;
                cin >> option;
                if(option == 'y'){
                    undo_system_changes();
                    cout << "The most recent system changes have been reverted";
                }
                else if(option == 'n'){
                    cout << endl;
                    continue;
                }
            }
            else{
                cout << endl;
                continue;
            }
            cout << endl;
        }
    }
    shut_down_system();
}

    /**Prints all the data into the interface that is on top of the stack.
    * Time Complexity : O(n^2log(n))
     * @note This function isn´t used during the execution of the program.
     * Its only purpose is to facilitate the testing of the program.
     * It´s used as an visual alternative to the tests made with the googletest framework*/
void schedule_system::print_current_schedule_system_data() const {
    system_changes.top().print_data();
}

/**Ends current system execution and sets up the next one.
 * Time complexity: O(n)
 */
void schedule_system::shut_down_system() {
    string saved_classes_filename = "classes.csv";
    string saved_classes_ucs_filename = "classes_per_uc.csv";

    //accessing the files linked to the current system version
    string saved_students_filename = system_changes.top().get_students_classes_filename();
    string saved_requests_filename = system_changes.top().get_students_requests_filename();
    std::filesystem::path data_files_directory("../Data_files");

    // looping through all the files in the data_files directory and deleting all the files whose data will not be relevant in the next system execution
    for(const std::filesystem::directory_entry data_file : std::filesystem::directory_iterator(data_files_directory)){
        if(data_file.path().filename() == saved_classes_filename){
            continue;
        }
        else if(data_file.path().filename() == saved_classes_ucs_filename){
            continue;
        }
        else if(data_file.path().filename() == saved_students_filename){
            continue;
        }
        else if(data_file.path().filename() == saved_requests_filename){
            continue;
        }
        std::filesystem::remove(data_file);
    }

    //getting the full path of saved versions of students_classes.csv and students_requests.csv
    saved_students_filename = "../Data_files/" + saved_students_filename;
    saved_requests_filename = "../Data_files/" + saved_requests_filename;


    //changing the names of the saved files to students_classes.csv and students_requests.csv as they will be the first version of those files in the next system execution
    rename(saved_students_filename.c_str(),"../Data_files/students_classes.csv");
    rename(saved_requests_filename.c_str(),"../Data_files/students_requests.csv");


    //not necessary but I think it makes sense to do this
    //emptying the system changes stack
    while(!system_changes.empty()){
        system_changes.pop();
    }

    //resetting the variables that store the number of changes made to the files back to 0
    number_of_student_data_changes = 0;
    number_of_request_changes = 0;
}