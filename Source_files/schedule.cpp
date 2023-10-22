//
// Created by franc on 22/10/2023.
//
#include "schedule.h"
#include <vector>
#include <algorithm>

schedule::schedule(string week_day, float hour, float duration){
    this->week_day = week_day;
    this->hour = hour;
    this->duration = duration;
}

bool schedule::operator<(const schedule& other_schedule) const{
    vector<string> week_days = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    auto it = std::find(week_days.begin(),week_days.end(),week_day);
    int value1 = std::distance(week_days.begin(),it);
    it = std::find(week_days.begin(),week_days.end(),other_schedule.week_day);
    int value2 = std::distance(week_days.begin(),it);
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

bool schedule::operator>(const schedule& other_schedule) const{
    vector<string> week_days = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    auto it = std::find(week_days.begin(),week_days.end(),week_day);
    int value1 = std::distance(week_days.begin(),it);
    it = std::find(week_days.begin(),week_days.end(),other_schedule.week_day);
    int value2 = std::distance(week_days.begin(),it);
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

bool schedule::operator==(const schedule& other_schedule) const{
    return (week_day == other_schedule.week_day) && (hour == other_schedule.hour) && (duration == other_schedule.duration);
}