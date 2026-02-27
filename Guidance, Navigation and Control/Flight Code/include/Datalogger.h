#ifndef DATALOGGER
#define DATALOGGER

#include "FlightData.h"
#include "string.h"

class DataLogger{
    public:
        DataLogger(bool logFlightData = true);
        void initialize();
        bool logFlightData(const FlightData& data);
        // bool logState()

    private: 
        bool logFlightData_ = true; // Not used for now
};



#endif