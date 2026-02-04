#include "control_object.h"

ControlObject::ControlObject(double K, double T, double xi)
    : K_obj(K), T_obj(T), xi(xi) {}

void ControlObject::setInitialConditions(double initial_y, double initial_dy) {
    y = initial_y;
    dy = initial_dy;
}

double ControlObject::update(double u, double dt) {
    double ddy = (-y - 2.0 * xi * T_obj * dy + K_obj * u) / (T_obj * T_obj);
    dy += ddy * dt;
    y += dy * dt;
    return y;
}

double ControlObject::getY() const {
    return y;
}