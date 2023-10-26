//
// Created by franc on 20/10/2023.
//
#include "schedule_system.h"

int main(){
    /*
    schedule_system system;
    system.schedule_system_functions();
     */
     interface test;
     test.read_data_classes_per_uc();
     test.read_data_classes();
     test.read_data_students_classes();
     student test_student {"Ludovico", "202071557"};
     test.consult_student_schedule(test_student);
    return 0;
}
