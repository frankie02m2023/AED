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
     //test.consult_all_students_in_aYear(1, "name", "descending");
     //class1 cl {"1LEIC02"};
     //course c {"L.EIC001"};
     //test.consult_students_in_class_and_course(cl, c, "number", "ascending");
     //test.consult_classes_and_courses_occupation_by_year(1,"name","name", "descending", "descending");
     test.print_data("name", "name", "number", "descending", "descending", "descending");
    return 0;
}
