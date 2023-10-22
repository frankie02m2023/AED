//
// Created by franc on 12/10/2023.
//

#ifndef TIME_H
#define TIME_H

#include <string>
using namespace std;

class schedule{
public:
    schedule(){};
    schedule(string week_day, float hour, float duration);
    string week_day;
    float hour;
    float duration;
    bool operator<(const schedule& other_schedule) const;
    bool operator>(const schedule& other_schedule) const;
    bool operator==(const schedule& other_schedule) const;
};

#endif