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
 */
#include "schedule_system.h"

int main(){
    schedule_system system;
    system.schedule_system_functions();
    return 0;
}
