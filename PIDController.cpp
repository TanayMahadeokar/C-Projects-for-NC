// Furnace Simulation using basic PID controller

#include<iostream>
#include<cmath>
#include<chrono>
#include<thread>

using namespace std;
using namespace chrono;

// PID Controller class
class PIDController {
    private:
       double Kp, Ki, Kd;  // PID gains
       double prevError, integral;
       double dt;

    public:
       // Constructor
       PIDController(double Kp, double Ki, double Kd, double dt): Kp(Kp), Ki(Ki), Kd(Kd), dt(dt), prevError(0), integral(0){}

       // Compute PID output 
       double compute (double setpoint, double currentTemp){
        double error = setpoint - currentTemp;
        integral += error * dt;
        double derivative = (error - prevError) / dt;
        prevError = error;

       // PID output
         double output = Kp * error + Ki * integral + Kd * derivative;
         return output;
       }
};

    // Furnace Simulation
    double simulationFurnace (double power, double currentTemp) {
        double coolingRate = 0.02;  // Heat loss Factor
        double HeatingFactor = 0.1;  // How much power affect tempearture

        return currentTemp + HeatingFactor * power - coolingRate * (currentTemp - 25);
    }

int main(){
    // Initialize PID controller (Tuning: adjust Kp, Ki, Kd)
    PIDController pid(2.0, 0.5, 0.1, 1.0);

    // Simulation Parameters
    double setpoint = 800.0;  // Target Furnace Temperature
    double temperature = 25;  // Initial room Temperature
    double power = 0.0;  // Initial Heating power

    // Real time loop for 100 iterations
    for (int i = 0; i < 100; i++){
        power = pid.compute(setpoint, temperature);

        // Constrain power to a range (0 to 100%)
        power = max(0.0, min(100.0, power));

        // Simulate Furnace Heating
        temperature = simulationFurnace(power, temperature);

        // Print the Result
        cout << "Time " << i << " sec | Temp: " << temperature << " c | Power: " << power << " %\n";
    }

    return 0;
}