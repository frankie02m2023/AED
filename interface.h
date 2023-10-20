//
// Created by franc on 20/10/2023.
//

#ifndef TRABALHOAED_INTERFACE_H
#define TRABALHOAED_INTERFACE_H
#include "course.h"


class interface {
public:
    vector<course>courses;
    void read_data_classes_per_uc();
    void read_data_classes();
    void read_data_students_classes();
};


#endif //TRABALHOAED_INTERFACE_H
