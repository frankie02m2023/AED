//
// Created by franc on 20/10/2023.
//
#include "schedule_system.h"

int main(){
    schedule_system system;
    class1 test_class("1LEIC05");
    system.system_changes.top().consult_class_schedule(test_class);
    return 0;
}
