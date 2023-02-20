To compile the program, run: g++ DataRecorder.cpp ChargingStation.cpp  Simulator.cpp main.cpp -o simulator
To run the program, run: ./simulator
Set DEBUG_PRINT in Global.h to true to see detailed simulation events. 

TODO:
Instead of setting the vehicle and company in the Global.h, add a FileReader to read the parameters from file.
    So that we can chage the simulation setting without rebuilding the project.
Use derived class and virtual function to avoid multiple if-else statements in the run function of simulator.
    Current cases are fine becase we only have 3 kinds of events.
    
    
Test:
In unit test, I wrote simple code to test the DataRecorder and ChargingStation seprately to make sure they are processing the data correctly.

To verify the whole system works as integration test, I add DEBUG_PRINT flag in the code, which prints detailed behavior and how data flow in the simulator.
I used some simple cases:
1. Only generate one vehicle: to see if the events are processed in the desired order.
2. Only generate two vehicles: to see if the simulator can process events for different vehicles concurrently.
3. Generate 4 vehicles of the same type: to see if the charging station can manage the wait queue correctly.