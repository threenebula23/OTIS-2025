#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>         
#include "pid.h"
#include "control_object.h"

int main() {
    double K_pid = 10.0;
    double Ti = 0.1;
    double Td = 0.05;
    double Ts = 0.008;

    double K_obj = 3.0;
    double T_obj = 0.1;
    double xi = 1.0;

    double initial_object_temperature = 150.0;   // Начальная температура объекта
    double target_temperature        = 133.0;    // Целевая температура (к которой стремится график)
    double ramp_start_temperature    = -199.0;   // Начало линейной рампы уставки
    double transition_duration       = 7.0;      // Длительность рампы, с

    double sim_time = 10.0;                      // Общее время моделирования (увеличено)

    PID pid(K_pid, Ti, Td, Ts);
    ControlObject obj(K_obj, T_obj, xi);
    obj.setInitialConditions(initial_object_temperature, 0.0);   

    auto steps = static_cast<int>(sim_time / Ts);
    std::vector<double> time(steps), setpoint(steps), y_out(steps), u_out(steps), e_out(steps);

    std::ofstream output("simulation_results.csv");
    output << "time,setpoint,y,u,e\n";

    double current_setpoint;

    for (int k = 0; k < steps; ++k) {
        time[k] = k * Ts;

        // Линейная рампа уставки
        if (time[k] <= transition_duration) {
            current_setpoint = ramp_start_temperature +
                               (target_temperature - ramp_start_temperature) / transition_duration * time[k];
        } else {
            current_setpoint = target_temperature;
        }

        double e = current_setpoint - obj.getY();
        double u = pid.compute(e);
        obj.update(u, Ts);

        double current_y = obj.getY();

        setpoint[k] = current_setpoint;
        y_out[k]    = current_y;
        u_out[k]    = u;
        e_out[k]    = e;

        output << time[k] << "," << current_setpoint << "," << current_y
               << "," << u << "," << e << "\n";
    }

    output.close();

    std::cout << "Моделирование завершено. Результаты сохранены в simulation_results.csv\n";
    std::cout << "Запуск визуализации...\n";

    std::system("python vizualize.py");  

    return 0;
}