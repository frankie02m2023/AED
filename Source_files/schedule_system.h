//
// Created by franc on 22/10/2023.
//

#ifndef TRABALHOAED_SCHEDULE_SYSTEM_H
#define TRABALHOAED_SCHEDULE_SYSTEM_H
#include "interface.h"
#include <stack>

class schedule_system {
public:
    stack<interface> system_changes;
    schedule_system();
    void schedule_system_functions();
    void print_current_schedule_system_data() const;
};


#endif //TRABALHOAED_SCHEDULE_SYSTEM_H
