#ifndef CHARGINGSTATION_H
#define CHARGINGSTATION_H

#include <deque>
#include <functional>
#include <memory>
#include <queue>
#include <unordered_map>
#include <vector>

#include "Event.h"
#include "Global.h"

// This class maintains a queue for vehicles waiting for the chargers and
// distributes chargers to vehicle
class ChargingStation {
 private:
  std::deque<int> m_waitQueue;  // the queue of vehicle who waits to be charged,
                                // it keeps the vehicle id
  std::vector<int>
      m_chargers;  // it keeps the chargers, chargers[i] means which vehicle is
                   // using this charger, it will be -1 if it is available
  std::unordered_map<int, float>
      vehicleEntryTime;  // it keeps the charge session beginning time for each
                         // vehicle
  std::shared_ptr<
      std::priority_queue<Event, std::vector<Event>,
                          std::function<bool(const Event&, const Event&)>>>
      m_timeLine;

  int m_numOfCharger;  // total number of chargers in this station

 public:
  ChargingStation() {}

  ChargingStation(
      int n,
      std::shared_ptr<
          std::priority_queue<Event, std::vector<Event>,
                              std::function<bool(const Event&, const Event&)>>>
          timeLine) {
    m_numOfCharger = n;
    m_timeLine = timeLine;
    m_chargers = std::vector<int>(n, -1);
  }

  // This functions adds a vehicle to the charge station
  // if there is an available charger, this vehicle will be charged, and an
  // event of type EVENT_VEHICLE_END_CHARGE will be put into the timeLine queue
  // if all chargers are occupied, this vehicle will be put in the m_waitQueue
  void addVehicle(int vehicleId, float entryTime);

  // This functions removes the vehicle from the charge station when it is fully
  // charged It will put an event of type EVENT_VEHICLE_TAKE_OFF into the
  // timeLine queue, which means this vehicle can be launched for a new flight
  // Then it will assign the available charger to a waiting vehicle (if any) and
  // put an event of type EVENT_VEHICLE_END_CHARGE into the timeLine queue
  void removeVehicle(int vehicleId, float currentTime);
};

#endif