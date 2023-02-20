#include "DataRecorder.h"

void DataRecorder::addFlightToVehicle(int vehicleId, float flightTime) {
  if (m_statisticsByVehicle.count(vehicleId) == 0) {
    m_statisticsByVehicle[vehicleId] = VehicleStats_t();
  }
  m_statisticsByVehicle[vehicleId].flightTime += flightTime;
  m_statisticsByVehicle[vehicleId].numOfFlights++;
}

void DataRecorder::addChageSessionToVehicle(int vehicleId,
                                            float chargeSessionTime) {
  if (m_statisticsByVehicle.count(vehicleId) == 0) {
    m_statisticsByVehicle[vehicleId] = VehicleStats_t();
  }
  m_statisticsByVehicle[vehicleId].chargeSessionTime += chargeSessionTime;
  m_statisticsByVehicle[vehicleId].numOfChargeSessions++;
}

void DataRecorder::printCurrentStatistics() {
  m_statisticsByCompany.clear();

  for (auto vs : m_statisticsByVehicle) {
    Company company = vehicleIdToCompany[vs.first];
    if (m_statisticsByCompany.count(company) == 0) {
      m_statisticsByCompany[company] = vs.second;
    } else {
      m_statisticsByCompany[company].flightTime += vs.second.flightTime;
      m_statisticsByCompany[company].numOfFlights += vs.second.numOfFlights;
      m_statisticsByCompany[company].chargeSessionTime +=
          vs.second.chargeSessionTime;
      m_statisticsByCompany[company].numOfChargeSessions +=
          vs.second.numOfChargeSessions;
    }
  }

  for (auto cs : m_statisticsByCompany) {
    std::cout << "Company Name: " << CompanyName[cs.first] << std::endl;
    std::cout << "average flight time per flight: "
              << cs.second.flightTime / cs.second.numOfFlights << std::endl;
    std::cout << "average distance traveled per flight: "
              << cs.second.flightTime * VehicleTemplate[cs.first].m_speed /
                     cs.second.numOfFlights
              << std::endl;
    std::cout << "average time charging per charge session: "
              << cs.second.chargeSessionTime / cs.second.numOfChargeSessions
              << std::endl;
    std::cout << "total number of faults: "
              << cs.second.flightTime * VehicleTemplate[cs.first].m_probOfFault
              << std::endl;
    std::cout << "total number of passenger miles: "
              << cs.second.flightTime * VehicleTemplate[cs.first].m_speed *
                     VehicleTemplate[cs.first].m_passengerCount
              << std::endl;
    std::cout << "----------------------------------------------------------"
              << std::endl;
  }
}