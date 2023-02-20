#include "Simulator.h"

void Simulator::setDuration(float duration) { m_duration = duration; }

void Simulator::initVehicles(int n) {
  std::vector<int> count(5, 0);
  for (int i = 0; i < n; i++) {
    Company company = (Company)(rand() % 5);
    count[(int)company]++;
    vehicleIdToCompany[i] = company;
    Event vehicleTakeOffEvent;
    vehicleTakeOffEvent.eventType = EVENT_VEHICLE_TAKE_OFF;
    vehicleTakeOffEvent.eventCreateTime = 0;
    vehicleTakeOffEvent.eventHappenTime = 0;
    vehicleTakeOffEvent.vehicleId = i;
    m_timeLine->push(vehicleTakeOffEvent);
  }
  for (int i = 0; i < 5; i++) {
    std::cout << count[i] << " vehicles made by " << CompanyName[(Company)i]
              << " are added to the simulator" << std::endl;
  }
}

void Simulator::launchNewFlight(Event& curEvent) {
  Vehicle curVehicle = VehicleTemplate[vehicleIdToCompany[curEvent.vehicleId]];
  Event vehicleBatteryOutEvent;
  vehicleBatteryOutEvent.eventType = EVENT_VEHICLE_BATTERY_OUT;
  vehicleBatteryOutEvent.eventCreateTime = m_currentTime;
  vehicleBatteryOutEvent.eventHappenTime =
      m_currentTime + curVehicle.m_batteryCapacity /
                          (curVehicle.m_speed * curVehicle.m_engergyUse);
  vehicleBatteryOutEvent.vehicleId = curEvent.vehicleId;

#if DEBUG_PRINT
  std::cout << "Add batteryOut event for vehicle "
            << vehicleBatteryOutEvent.vehicleId
            << ", with event creating time: "
            << vehicleBatteryOutEvent.eventCreateTime
            << " and event happening time: "
            << vehicleBatteryOutEvent.eventHappenTime << std::endl;
#endif

  m_timeLine->push(vehicleBatteryOutEvent);
}

void Simulator::updateFlightData(Event& curEvent) {
  m_dataRecorder.addFlightToVehicle(curEvent.vehicleId,
                                    m_currentTime - curEvent.eventCreateTime);
}

void Simulator::updateChargeData(Event& curEvent) {
  m_dataRecorder.addChageSessionToVehicle(
      curEvent.vehicleId, m_currentTime - curEvent.eventCreateTime);
}

void Simulator::run() {
  // this loop deals with the events happening before the simuation ends
  while (m_timeLine->size()) {
    // If the event to be processed happens after the duration we set, break
    if (m_timeLine->top().eventHappenTime > m_duration) {
      break;
    }

    Event curEvent = m_timeLine->top();
    m_timeLine->pop();
    m_currentTime = curEvent.eventHappenTime;

    if (curEvent.eventType == EVENT_VEHICLE_TAKE_OFF) {
      // launch a new flight for this vehicle
#if DEBUG_PRINT
      std::cout << m_currentTime << ": Process vehicleTakeOffEvent for vehicle "
                << curEvent.vehicleId
                << ", with event creating time: " << curEvent.eventCreateTime
                << " and event happening time: " << curEvent.eventHappenTime
                << std::endl;
#endif
      launchNewFlight(curEvent);
    } else if (curEvent.eventType == EVENT_VEHICLE_BATTERY_OUT) {
      // the flight ends, update the flight information of this vehicle and send
      // it to the charging station
#if DEBUG_PRINT
      std::cout << m_currentTime
                << ": Process vehicleBatteryOutEvent for vehicle "
                << curEvent.vehicleId
                << ", with event creating time: " << curEvent.eventCreateTime
                << " and event happening time: " << curEvent.eventHappenTime
                << std::endl;
#endif
      updateFlightData(curEvent);
      m_chargingStation.addVehicle(curEvent.vehicleId, m_currentTime);
    } else if (curEvent.eventType == EVENT_VEHICLE_END_CHARGE) {
      // this vehicle is fully charged, update the charging session information
      // and launch a new flight for it
#if DEBUG_PRINT
      std::cout << m_currentTime << ": Process vehicleEndCharge for vehicle "
                << curEvent.vehicleId
                << ", with event creating time: " << curEvent.eventCreateTime
                << " and event happening time: " << curEvent.eventHappenTime
                << std::endl;
#endif
      updateChargeData(curEvent);
      m_chargingStation.removeVehicle(curEvent.vehicleId, m_currentTime);
    }
  }

  // this loop deals with the events happening before the simuation ends
  while (m_timeLine->size()) {
    Event curEvent = m_timeLine->top();
    m_timeLine->pop();
    m_currentTime = m_duration;
    if (curEvent.eventType == EVENT_VEHICLE_TAKE_OFF) {
      // no flight needs to be launched, nothing to do here
      continue;
    } else if (curEvent.eventType == EVENT_VEHICLE_BATTERY_OUT) {
      // clear every vehicle that is in flight
      // take the cuurent duration of this flight into account
      // (simutation_end_time - flight_start_time)
#if DEBUG_PRINT
      std::cout << m_currentTime
                << ": Process vehicleBatteryOutEvent for vehicle "
                << curEvent.vehicleId
                << ", with event creating time: " << curEvent.eventCreateTime
                << " and event happening time: " << curEvent.eventHappenTime
                << std::endl;
#endif
      updateFlightData(curEvent);
    } else if (curEvent.eventType == EVENT_VEHICLE_END_CHARGE) {
      // clear every vehicle that is being charged
      // take the cuurent duration of this charge session into account
      // (simutation_end_time - charge_session_start_time)
#if DEBUG_PRINT
      std::cout << m_currentTime << ": Process vehicleEndCharge for vehicle "
                << curEvent.vehicleId
                << ", with event creating time: " << curEvent.eventCreateTime
                << " and event happening time: " << curEvent.eventHappenTime
                << std::endl;
#endif
      updateChargeData(curEvent);
    }
  }
}

void Simulator::printSimulationStatistics() {
  m_dataRecorder.printCurrentStatistics();
}
