//
// Created by franc on 12/10/2023.
//

#ifndef TIME_H
#define TIME_H

#include <string>
using namespace std;
/**
* @file schedule.h
* @brief Definition of class schedule.

 *\class schedule
 * Where are performed specific functions related to the schedules.
 * Stores the week_day, hour and duration of a class.
 */

class schedule{
public:
    /** @name Constructors
     *
     */
     ///@{
    schedule(){};
    schedule(string week_day, float hour, float duration);
    ///@}

    /** @name Member Variables
     *
     */
     ///@{
    string week_day;
    float hour;
    float duration;
    ///@}

    /** @name Operators
     *
     */
     ///@{
    bool operator<(const schedule& other_schedule) const;
    bool operator>(const schedule& other_schedule) const;
    bool operator==(const schedule& other_schedule) const;
    ///@}
};

/** @name auxiliary function
 *
 */
bool overlapping_schedule(const schedule& schedule1, const schedule &schedule2);
#endif