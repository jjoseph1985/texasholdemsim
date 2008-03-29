#ifndef SIMTIME_H_INCLUDED
#define SIMTIME_H_INCLUDED

#include <string>
#include <cstring>
#include <ctime>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>


/* Wrapper class for useful time functions */

using namespace std;

class SimTime
{
    public:
                 SimTime();
        string   GetCurrentTime2();
        string   GetCurrentDate();
        string   GetSimTime();
        string   SimTimeDiff();
        void     Update();

        void     TimerStart();
        void     TimerStop();
        string   TimerDiff();

    private:
        // Sim Time
        clock_t  startSimTime;
        clock_t  currentSimTime;
        int      simSubSec;
        int      simSec;
        int      simMin;

        // Time & Date
        time_t   t;
        struct   tm* currentTime;
        string   strCurrentTime;
        string   strCurrentDate;

        // Timer
        clock_t  timerStart;
        clock_t  timerStop;
        clock_t  timerDiff;

        char     buffer[20];
/*
        int     sec;
        int     min;
        int     hour;
        int     month;
        int     day;
        int     year;
*/
};

#endif // SIMTIME_H_INCLUDED
