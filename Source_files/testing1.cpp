//
// Created by franc on 20/10/2023.
//
#include "schedule_system.h"

int main(){
    schedule_system system;
    student target_student("Francisco Magalhães","202007945");
    course added_course("L.EIC012");
    class1 added_class("2LEIC05");
    class1 removed_class("2LEIC04");
    course removed_course("L.EIC002");
    request new_request;
    new_request.target_student = target_student;
    new_request.request_type = "remove course";
    new_request.removed_course = removed_course;
    system.system_changes.top().remove_request_from_file();
    return 0;
}
