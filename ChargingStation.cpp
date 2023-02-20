#include "ChargingStation.h"

void ChargingStation::addVehicle(int vehicleId, float entryTime) {
  // update entry time
  vehicleEntryTime[vehicleId] = entryTime;
  // look for available charger
#if DEBUG_PRINT
  std::cout << "Vehicle " << vehicleId << " enters charging station at "
            << entryTime << ". Chargers in the charging station are serving: ";
  for (int c : m_chargers) {
    std::cout << c << " ";
  }
  std::cout << std::endl;
#endif
  for (int i = 0; i < m_numOfCharger; i++) {
    if (m_chargers[i] == -1) {
      // found avaible charger, assign charger
      m_chargers[i] = vehicleId;
      // make prediction on when the charging will end
      Event chargeEndEvent;
      chargeEndEvent.eventType = EVENT_VEHICLE_END_CHARGE;
      chargeEndEvent.vehicleId = vehicleId;
      chargeEndEvent.eventHappenTime =
          entryTime +
          VehicleTemplate[vehicleIdToCompany[vehicleId]].m_timeToCharge;
      chargeEndEvent.eventCreateTime = entryTime;
      m_timeLine->push(chargeEndEvent);
#if DEBUG_PRINT
      std::cout << "Add  chargeEndEvent for vehicle " << vehicleId
                << ", with event creating time: "
                << chargeEndEvent.eventCreateTime
                << " and event happening time: "
                << chargeEndEvent.eventHappenTime << std::endl;
#endif
      return;
    }
  }
  // no available charger found, put the vehicle into waiting list
  m_waitQueue.push_back(vehicleId);

#if DEBUG_PRINT
  std::cout << "Vehicle " << vehicleId << " joins wait queue " << std::endl;
  std::cout << "Wait queue: ";
  for (int c : m_waitQueue) {
    std::cout << c << " ";
  }
  std::cout << std::endl;
#endif
}

void ChargingStation::removeVehicle(int vehicleId, float currentTime) {
#if DEBUG_PRINT
  std::cout << "Vehicle " << vehicleId << " leaves charging station at "
            << currentTime
            << ". Chargers in the charging station are serving: ";
  for (int c : m_chargers) {
    std::cout << c << " ";
  }
  std::cout << std::endl;
#endif

  int chargerIdx = -1;
  // find the charger who is charging this vehicle
  for (int i = 0; i < m_numOfCharger; i++) {
    if (m_chargers[i] == vehicleId) {
      chargerIdx = i;
      m_chargers[i] = -1;
      break;
    }
  }
  // Tell simulator to launch a new flight for this vehicle
  Event vehicleTakeOffEvent;
  vehicleTakeOffEvent.eventType = EVENT_VEHICLE_TAKE_OFF;
  vehicleTakeOffEvent.vehicleId = vehicleId;
  vehicleTakeOffEvent.eventHappenTime = currentTime;
  vehicleTakeOffEvent.eventCreateTime = currentTime;
  m_timeLine->push(vehicleTakeOffEvent);
#if DEBUG_PRINT
  std::cout << "Add vehicleTakeOffEvent for vehicle "
            << vehicleTakeOffEvent.vehicleId << ", with event creating time: "
            << vehicleTakeOffEvent.eventCreateTime
            << " and event happening time: "
            << vehicleTakeOffEvent.eventHappenTime << std::endl;
#endif
  // Assign the new available charger to a waiting vehicle
  if (!m_waitQueue.empty()) {
    int vehicleToStartCharge = m_waitQueue.front();
    m_waitQueue.pop_front();
    m_chargers[chargerIdx] = vehicleToStartCharge;
    // make prediction on when the charging will end
    Event chargeEndEvent;
    chargeEndEvent.eventType = EVENT_VEHICLE_END_CHARGE;
    chargeEndEvent.vehicleId = vehicleToStartCharge;
    chargeEndEvent.eventHappenTime =
        currentTime + VehicleTemplate[vehicleIdToCompany[vehicleToStartCharge]]
                          .m_timeToCharge;
    chargeEndEvent.eventCreateTime = vehicleEntryTime[vehicleToStartCharge];
    m_timeLine->push(chargeEndEvent);

#if DEBUG_PRINT
    std::cout << "Add chargeEndEvent for vehicle " << chargeEndEvent.vehicleId
              << ", with event creating time: "
              << chargeEndEvent.eventCreateTime
              << " and event happening time: " << chargeEndEvent.eventHappenTime
              << std::endl;
    std::cout << "Wait queue: ";
    for (int c : m_waitQueue) {
      std::cout << c << " ";
    }
    std::cout << std::endl;
#endif
  }
}