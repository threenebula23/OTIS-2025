#ifndef CONTROL_OBJECT_H
#define CONTROL_OBJECT_H

class ControlObject {
private:
    double y = 0.0;
    double dy = 0.0;
    double K_obj;
    double T_obj;
    double xi;

public:
    ControlObject(double K, double T, double xi);

    /**
     * @brief Установка начальных условий объекта
     * @param initial_y Начальная температура объекта
     * @param initial_dy Начальная производная (обычно 0)
     */
    void setInitialConditions(double initial_y, double initial_dy = 0.0);

    double update(double u, double dt);
    double getY() const;
};

#endif