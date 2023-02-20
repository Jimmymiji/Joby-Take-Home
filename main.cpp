#include "Simulator.h"

// This map keeps the Vechicle information for each type of vehicle.
std::unordered_map<Company, Vehicle> VehicleTemplate = {
    {Alpha, Vehicle(120, 320, 0.6, 1.6, 4, 0.25)},
    {Bravo, Vehicle(100, 100, 0.2, 1.5, 5, 0.1)},
    {Charlie, Vehicle(160, 220, 0.8, 2.2, 3, 0.05)},
    {Delta, Vehicle(90, 120, 0.62, 0.8, 2, 0.22)},
    {Echo, Vehicle(30, 150, 0.3, 5.8, 2, 0.61)}};

std::unordered_map<Company, std::string> CompanyName = {
    {Alpha, "Alpha Company"},
    {Bravo, "Bravo Company"},
    {Charlie, "Charlie Company"},
    {Delta, "Delta Company"},
    {Echo, "Echo Company"}};

// This map keeps the company value for each vehicle.
std::unordered_map<int, Company> vehicleIdToCompany = {};

int main() {
  Simulator simulator;
  simulator.setDuration(3.0);
  simulator.initVehicles(20);
  simulator.run();
  simulator.printSimulationStatistics();
  return 0;
}