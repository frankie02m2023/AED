//
// Created by franc on 12/10/2023.
//

#ifndef TIME_H
#define TIME_H

#include <string>
using namespace std;

class schedule{
public:
    //constructors
    schedule(){};
    schedule(string week_day, float hour, float duration);

    //member variables
    string week_day;
    float hour;
    float duration;

    //operators
    bool operator<(const schedule& other_schedule) const;
    bool operator>(const schedule& other_schedule) const;
    bool operator==(const schedule& other_schedule) const;
};
//auxiliary function
bool overlapping_schedule(const schedule& schedule1, const schedule &schedule2);
#endif