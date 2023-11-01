//
// Created by franc on 20/10/2023.
//

/**
 * @file main.cpp
 * @brief This file contains the main function of the project.
 *
 * \mainpage Description
 * This project consists in a set of classes and functions that allow the user to interact with a simple schedule system.
 * With this simple system, you can access information about the students, classes and courses. You can also request
 * changes to the system, for example, add a student to a class, move a student to another class or remove it from that class.
 *
 * \subsection Instructions How to use
 * You will be asked to choose an option. All the options will appear on the screen with a number near them.
 * Then, just type the number corresponding to the option you want to execute.
 * @warning <b> You need to use C++ 17 or above to run the program appropriately <b>
 */
#include <filesystem>
#include "schedule_system.h"

void renaming_files_for_future_use(){
    std::filesystem::path data_files_directory("../Data_files");
    string filename_beginning;
    for(const std::filesystem::directory_entry data_file : std::filesystem::directory_iterator(data_files_directory)){
        auto it = filename_beginning.find_first_of('.');
        filename_beginning = filename_beginning.substr(0,it);
        if(filename_beginning == "students_classes"){
            std::filesystem::rename(data_file,"students_classes.csv");
        }
        else if(filename_beginning == "students_requests"){
            std::filesystem::rename(data_file,"students_requests.csv");
        }
    }
}

int main(){
    schedule_system system;
    system.schedule_system_functions();
    renaming_files_for_future_use();
    return 0;
}
