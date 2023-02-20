#ifndef GLOBAL_H
#define GLOBAL_H

#include <string>
#include <unordered_map>

#define DEBUG_PRINT false

// The vehicle information as defined in the instruction
typedef struct Vehicle {
  Vehicle(int speed, float batteryCapacity, float timeToCharge,
          float engergyUse, int passengerCount, float probOfFault) {
    m_speed = speed;
    m_batteryCapacity = batteryCapacity;
    m_timeToCharge = timeToCharge;
    m_engergyUse = engergyUse;
    m_passengerCount = passengerCount;
    m_probOfFault = probOfFault;
  }

  Vehicle() {}

  Vehicle(const Vehicle& v) {
    m_speed = v.m_speed;
    m_batteryCapacity = v.m_batteryCapacity;
    m_timeToCharge = v.m_timeToCharge;
    m_engergyUse = v.m_engergyUse;
    m_passengerCount = v.m_passengerCount;
    m_probOfFault = v.m_probOfFault;
  }

  int m_speed;              // unit: mph
  float m_batteryCapacity;  // unit: kWh
  float m_timeToCharge;     // unit: hour
  float m_engergyUse;       // unit: kWh/mile
  int m_passengerCount;
  float m_probOfFault;  // unit: number/hour
} Vehicle_t;

enum Company { Alpha, Bravo, Charlie, Delta, Echo };

extern std::unordered_map<Company, Vehicle> VehicleTemplate;

extern std::unordered_map<Company, std::string> CompanyName;

// This map keeps the company value for each vehicle.
extern std::unordered_map<int, Company> vehicleIdToCompany;

#endif