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
bool schedHelper(
  const AvailabilityMatrix&,
  const size_t,
  const size_t,
  DailySchedule&,
  vector<size_t>&,
  size_t, size_t
);

// Add your implementation of schedule() and other helper functions here
bool schedHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<size_t>& shiftsTaken,
    size_t days, 
    size_t shiftsOfDay)
{
    if (days == sched.size()) return true;

    for (size_t worker = 0; worker < avail[days].size(); ++worker)
    {
        if (avail[days][worker] && shiftsTaken[worker] < maxShifts
        && find(sched[days].begin(), sched[days].end(), worker) == sched[days].end()) {

            sched[days][shiftsOfDay] = worker;
            shiftsTaken[worker]++;

            if (shiftsOfDay + 1 == dailyNeed) {
                if (schedHelper(avail, dailyNeed, maxShifts, sched, shiftsTaken, days+1, 0))
                    return true;
            }

            else { 
                if (schedHelper(avail, dailyNeed, maxShifts, sched, shiftsTaken, days, shiftsOfDay+1))
                    return true;
            }

            sched[days][shiftsOfDay] = INVALID_ID;
            shiftsTaken[worker]--;

        }
    }
    return false;   
}



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
    // Add your code below
    size_t days = avail.size();
    size_t shiftsOfDay = avail[0].size();

    // cout << days << " " << shiftsOfDay;

    vector<size_t> shiftsTaken(shiftsOfDay, 0);

    sched.clear();
    sched.resize(days, vector<Worker_T>(dailyNeed, INVALID_ID));

    return schedHelper(avail, dailyNeed, maxShifts, sched, shiftsTaken, 0, 0);
}

