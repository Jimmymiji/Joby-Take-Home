#ifndef EVENT_H
#define EVENT_H

#include <stdio.h>

#include <iostream>
#include <memory>

/*
 * In this project, three kinds of event are used, simulator will have different
 * reaction to differnt kinds of event EVENT_VEHICLE_TAKE_OFF: This event tells
 * the , eventHappenTime and eventCreateTime are the same, which means the
 * beginin of a flight. EVENT_VEHICLE_BATTERY_OUT: This event means an end of
 * flight, eventHappenTime means the ending time of the flight while
 * eventCreateTime means the beginning of the flight. EVENT_VEHICLE_END_CHARGE:
 * This event means a vehicle is done charging, eventHappenTime means the ending
 * time of the charging session while eventCreateTime means the beginning of the
 * charging session.
 */
enum EVENT_TYPE {
  EVENT_VEHICLE_TAKE_OFF,
  EVENT_VEHICLE_BATTERY_OUT,
  EVENT_VEHICLE_END_CHARGE
};

class Event {
 public:
  EVENT_TYPE eventType;
  float eventHappenTime;  // time when event is predicted to happen, unit: hour
  float eventCreateTime;  // time when event is created, unit hour
  int vehicleId;
};

#endif