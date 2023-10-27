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
     course a {"L.EIC001"};
     test.consult_all_students_in_aCourse(a);
    return 0;
}
