#include "simtime.h"
#include <iostream>

// Default constructor
SimTime::SimTime()
{
    SimTime::Update();
    startSimTime = clock();
    simSubSec = 0;
    simSec = 0;
    simMin = 0;
}


// Returns the current time in hh:mm:ss
string SimTime::GetCurrentTime2()
{
    SimTime::Update();

    stringstream concat;
    concat << strCurrentTime;

    return concat.str();
}


// Returns the current date in mm/dd/yyyy
string SimTime::GetCurrentDate()
{
    SimTime::Update();

    stringstream concat;
    concat << strCurrentDate;

    return concat.str();
}


// Returns the current simulation time in a nicely formatted manner
string SimTime::GetSimTime()
{
    SimTime::Update();

    stringstream concat;

    if(simSubSec < 100)
        concat << simMin << " min " << simSec << ".0" << simSubSec << " sec" ;
    else
        concat << simMin << " min " << simSec << "." << simSubSec << " sec" ;

    return concat.str();
}


// Starts a millisecond counter
void SimTime::TimerStart()
{
    SimTime::Update();
    timerStart = currentSimTime;
}


// Stops the millisecond counter
void SimTime::TimerStop()
{
    SimTime::Update();
    timerStop = currentSimTime;
}


// Returns the difference between the start & stop time of the millisecond counter
string SimTime::TimerDiff()
{
    timerDiff = timerStart; // - timerStop;

    stringstream concat;
    concat << timerDiff;

    return concat.str();
}


// Updates all the datamembers of the class. (Regets current time values.)
void SimTime::Update()
{
    time(&t);
    currentTime = localtime(&t);

    // Date
    strftime( buffer, 20, "%x", currentTime);
    strCurrentDate.assign(buffer);

    // Time
    strftime( buffer, 20, "%X", currentTime);
    strCurrentTime.assign(buffer);

    // SimTime
    currentSimTime = clock();
    simSubSec = currentSimTime % 1000;
    simSec    = (currentSimTime / 1000) % 60;
    simMin    = (currentSimTime / 60000);

/*
    sec   = currentTime->tm_sec;
    min   = currentTime->tm_min;
    hour  = 1 + (currentTime->tm_hour);
    day   = currentTime->tm_mday;
    month = currentTime->tm_mon;
    year  = 1900 + currentTime->tm_year;

    //cout << sec << "\n";
    //cout << min << "\n";
    //cout << hour << "\n";
*/
}
