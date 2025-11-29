#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool helper(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, std::vector<size_t>& shift, size_t day, size_t n);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    std::vector<size_t> shift(avail[0].size(), 0);

    for (size_t i = 0; i < avail.size(); ++i)
    {
        std::vector<Worker_T> row;

        for (size_t j = 0; j < dailyNeed; ++j)
        {
            row.push_back(static_cast<Worker_T>(0));
        }
        
        sched.push_back(row);
    }

    return helper(avail, dailyNeed, maxShifts, sched, shift, 0, 0);
}

bool helper(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, std::vector<size_t>& shift, size_t day, size_t n)
{
    if (day == avail.size()) return true;

    for (size_t i = 0; i < avail[day].size(); ++i)
    {
        if (avail[day][i] && shift[i] < maxShifts && 
            std::find(sched[day].begin(), sched[day].begin() + n, static_cast<Worker_T>(i)) == sched[day].begin() + n)
        {
            sched[day][n] = static_cast<Worker_T>(i);
            ++shift[i];

            size_t newDay = day;
            size_t newSlot = n + 1;

            if (newSlot == dailyNeed)
            {
                newSlot = 0;
                ++newDay;
            }

            if (helper(avail, dailyNeed, maxShifts, sched, shift, newDay, newSlot)) return true;
            
            --shift[i];
        }
    }

    return false;
}
