//
// Created by franc on 22/10/2023.
//
#include "schedule.h"
#include <vector>
#include <algorithm>

/**
* @file schedule.cpp
* @brief Implementation of class schedule.
*/

//constructor ----------------------------------------------------------
//complexity: O(1)
schedule::schedule(string week_day, float hour, float duration){
    this->week_day = week_day;
    this->hour = hour;
    this->duration = duration;
}


//operators -------------------------------------------------------------
//complexity: O(n)
bool schedule::operator<(const schedule& other_schedule) const{
    //auxiliary vector with the days os the week ordered
    vector<string> week_days = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

    //calculates the position of week_day in the vector and finds its index
    auto it = std::find(week_days.begin(),week_days.end(),week_day);
    int value1 = std::distance(week_days.begin(),it);

    //calculate the position of other_schedule week_day and finds its index
    it = std::find(week_days.begin(),week_days.end(),other_schedule.week_day);
    int value2 = std::distance(week_days.begin(),it);

    //compares the indexes and determines which is the smallest
    if(value1 != value2){
        return value1 < value2;
    }
    if(hour != other_schedule.hour){
        return hour < other_schedule.hour;
    }
    if(duration != other_schedule.duration){
        return duration < other_schedule.duration;
    }
    return false;
}

//complexity: O(n)
bool schedule::operator>(const schedule& other_schedule) const{
    //auxiliary vector with the days os the week ordered
    vector<string> week_days = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

    //calculates the position of week_day in the vector and finds its index
    auto it = std::find(week_days.begin(),week_days.end(),week_day);
    int value1 = std::distance(week_days.begin(),it);

    //calculate the position of other_schedule week_day and finds its index
    it = std::find(week_days.begin(),week_days.end(),other_schedule.week_day);
    int value2 = std::distance(week_days.begin(),it);

    //compares the indexes and determines which is the biggest
    if(value1 != value2){
        return value1 > value2;
    }
    if(hour != other_schedule.hour){
        return hour > other_schedule.hour;
    }
    if(duration != other_schedule.duration){
        return duration > other_schedule.duration;
    }
    return false;
}


//complexity: O(1)
bool schedule::operator==(const schedule& other_schedule) const{
    return (week_day == other_schedule.week_day) && (hour == other_schedule.hour) && (duration == other_schedule.duration);
}

/** Auxiliary function to check if two schedules overlap each other.
* Time Complexity: O(1)
 * @param schedule1 Schedule we want to compare
 * @param schedule2 Schedule we want to compare
 * @returns True if the schedules are overlapping or False otherwise*/
bool overlapping_schedule(const schedule& schedule1, const schedule &schedule2) {
    if(schedule1.week_day == "Dont Apply" || schedule2.week_day == "Dont Apply"){
        return false;
    }
    else{
        if(schedule1.week_day == schedule2.week_day){
            if(schedule1.hour == schedule2.hour){
                return true;
            }
            else{
                schedule earlier_schedule = min(schedule1, schedule2);
                schedule later_schedule = max(schedule1, schedule2);
                if(earlier_schedule.hour + earlier_schedule.duration > later_schedule.hour){
                    return true;
                }
                return false;
            }
        }
        return false;
    }
}