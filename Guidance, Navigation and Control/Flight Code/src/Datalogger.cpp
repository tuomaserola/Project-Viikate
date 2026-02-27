#include "Datalogger.h"
#include "SD.H"
#include "SPI.h"
#include "Constants.h"


DataLogger::DataLogger(bool logFlightData){
    logFlightData_ = logFlightData;
}

void DataLogger::initialize(){
    pinMode(Constants::CS_PIN, OUTPUT);
    SD.begin(Constants::CS_PIN);

    if (SD.exists("flight.csv")) {SD.remove("flight.csv");} // Remove old flight data
    if (SD.exists("eventLog.txt")) {SD.remove("eventLog.txt");} // Remove old event log
   
    auto FDF = SD.open("flight.csv", FILE_WRITE); // FDF = Flight Data File
    if (FDF){ // Writing headers
        FDF.println("timeMs,altitude,verticalVelocity,accelZ,rotatZ,accelMagnitude,rbfRemoved");
        FDF.close();
    }
   
    auto EDF = SD.open("eventLog.txt", FILE_WRITE); // Event Data File
    if (EDF) {
        EDF.println("--- LOG START ---");
        EDF.close();
    }
}

bool DataLogger::logFlightData(const FlightData& data){
    auto FDF = SD.open("flight.csv", FILE_WRITE); // Flight Data File
    if (FDF){
        FDF.print(data.timeMs);
        FDF.print(",");
        FDF.print(data.altitude);
        FDF.print(",");
        FDF.print(data.verticalVelocity);
        FDF.print(",");
        FDF.print(data.accelZ);
        FDF.print(",");
        FDF.print(data.rotatZ);
        FDF.print(",");
        FDF.print(data.accelMagnitude);
        FDF.print(",");
        FDF.println(data.rbfRemoved);
        FDF.close();
        return true;
    }
    else {return false;}

};


// bool Datalogger::logState(){} // Format: "Time, Status of flight, Additional information like "Parachute deployed" "
