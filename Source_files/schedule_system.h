//
// Created by franc on 22/10/2023.
//

#ifndef TRABALHOAED_SCHEDULE_SYSTEM_H
#define TRABALHOAED_SCHEDULE_SYSTEM_H
#include "interface.h"
#include <stack>

/**
*\file schedule_system.h
*@brief Definition of class schedule_system.
*/

/**
 *\class schedule_system
 * Where the most important functions from the others classes are called.
 *  Controls the flow of the program.
 *  Stores the changes made into a stack. It also stores the number os student changes and requests.
 */

class schedule_system {
public:
    stack<interface> system_changes;
    int number_of_student_data_changes;
    int number_of_request_changes;
    /** @name Constructor
     *
     */
    schedule_system();

    /** @name system functions
     *
     */
    ///@{
    void schedule_system_functions();
    void consult_class_schedule_by_schedule(const class1& a_class) const;
    void consult_class_schedule_by_course(const class1& a_class) const;
    void consult_student_schedule_by_schedule(const student& a_student) const;
    void consult_student_schedule_by_course(const student& a_student) const;
    void consult_students_in_class_and_course(const class1& a_class, const course& a_course, const string& sortby, const string& sort_option) const;
    void consult_all_students_in_aCourse(const course& a_course, const string& sort_by = "name", const string& sort_option ="ascending") const;
    void consult_all_students_in_aYear(int year,  const string& sortby = "name", const string& sort_option  = "ascending") const;
    void consult_classes_and_courses_occupation_by_year(int year, const string& uc_sort_by = "occupation", const string& class_sort_by = "occupation",const string& sorting_uc  = "ascending", const string& sorting_classes  = "ascending");
    void consult_student_requests() const;
    void store_new_request(const request& new_request);
    void remove_request();
    void process_request(string& error_message);
    void undo_system_changes();
    void shut_down_system();
    ///@}

    /** @name Data printer
     *
     */
    void print_current_schedule_system_data() const;
};


#endif //TRABALHOAED_SCHEDULE_SYSTEM_H
