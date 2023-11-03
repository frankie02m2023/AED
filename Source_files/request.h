//
// Created by lucas on 30/10/2023.
//

#ifndef TRABALHOAED_REQUEST_H
#define TRABALHOAED_REQUEST_H

#include "course.h"
/**
* @file request.h
* @brief Contains a struct with requests information.
*/
/** Struct with the info used to process the requests.
 *
 */

struct request {
    string request_type;        /**< Type of the request(add, remove, switch).*/
    student target_student;     /**< Information about the student to process. */
    course added_course;        /**< Course where we want to add the student (only for add and switch requests). */
    course removed_course;      /**< Course where we want to remove the student (only for remove and switch requests). */
    class1 added_class;         /**< Class where we want to add the student (only for add and switch requests). */
    class1 removed_class;       /**< Class where we want to remove the student (only for remove and switch requests). */
};

#endif //TRABALHOAED_REQUEST_H
