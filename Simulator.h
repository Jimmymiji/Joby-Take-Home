#ifndef SIMILATOR_H
#define SIMILATOR_H

#include <functional>
#include <memory>
#include <queue>

#include "ChargingStation.h"
#include "DataRecorder.h"
#include "Event.h"
#include "Global.h"

// It controls the overall behavior of the simulation system.
// The main idea here is to process each event by the time each event happens
// and make different reaction to different event type
class Simulator {
 private:
  DataRecorder
      m_dataRecorder;  // It records data and generates statistics report
  ChargingStation
      m_chargingStation;  // It controls distribution of chargers and maintains
                          // vehicles who needs to charge
  std::shared_ptr<
      std::priority_queue<Event, std::vector<Event>,
                          std::function<bool(const Event&, const Event&)>>>
      m_timeLine;  // It sorts event by its eventHappenTime in ascending order
  float m_currentTime;
  float m_duration;  // The duration of this simulation, unit: hour

 public:
  Simulator() {
    auto comp = [](const Event& a, const Event& b) {
      return a.eventHappenTime > b.eventHappenTime;
    };
    m_timeLine = std::make_shared<
        std::priority_queue<Event, std::vector<Event>,
                            std::function<bool(const Event&, const Event&)>>>(
        comp);
    m_currentTime = 0;
    m_chargingStation = ChargingStation(3, m_timeLine);
  }

  void setDuration(float duration);

  // It adds n vehicles from given list of companies into the simulator and
  // launch a new flight for each vehicle
  void initVehicles(int n);

  void launchNewFlight(Event& curEvent);

  void updateFlightData(Event& curEvent);

  void updateChargeData(Event& curEvent);

  void run();

  void printSimulationStatistics();
};

#endif