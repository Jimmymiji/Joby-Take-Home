#ifndef DATARECORDER_H
#define DATARECORDER_H

#include <stdio.h>

#include <iostream>
#include <memory>
#include <unordered_map>

#include "Global.h"

typedef struct VehicleStats {
  float flightTime;  // Total flight time, unit: hour
  int numOfFlights;
  float chargeSessionTime;  // Total charge session time (wating time + charging
                            // time), unit: hour
  int numOfChargeSessions;
} VehicleStats_t;

// This class is responsible for keeping and computing the staticstis during the
// simulation
class DataRecorder {
 private:
  std::unordered_map<int, VehicleStats_t>
      m_statisticsByVehicle;  // It records the vechicle flight status for each
                              // vehicle
  std::unordered_map<Company, VehicleStats_t>
      m_statisticsByCompany;  // It records the total vechicle flight status for
                              // all vehicles of the same company

 public:
  // This function updates the vehicle status about flightTime and number of
  // flights of the given vehicle
  void addFlightToVehicle(int vehicleId, float flightTime);

  // This function updates the vehicle status about chargeSessionTime and number
  // of charge session of the given vehicle
  void addChageSessionToVehicle(int vehicleId, float chargeSessionTime);

  // This function prints out the vehicle status for each company, which gives
  // the information required by the instruction.
  void printCurrentStatistics();
};

#endif