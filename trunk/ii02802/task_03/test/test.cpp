#include <gtest/gtest.h>
#include "pid.h"
#include "control_object.h"

/**
 * @file test.cpp
 * @brief Модульные тесты для классов PID и ControlObject
 */

TEST(PIDTest, ConstructorCoefficients) {
    double K = 10.0;
    double Ti = 0.1;
    double Td = 0.05;
    double Ts = 0.008;

    PID pid(K, Ti, Td, Ts);

    // Проверяем, что коэффициенты правильно рассчитаны
    double expected_q0 = K * (1.0 + Ts / Ti + Td / Ts);
    double expected_q1 = -K * (1.0 + 2.0 * Td / Ts);
    double expected_q2 = K * (Td / Ts);

    // Т.к. q0,q1,q2 приватные — проверяем через поведение
    double e = 1.0;
    double u1 = pid.compute(e);
    EXPECT_NEAR(u1, expected_q0 * e, 1e-9);

    double e2 = 0.0;
    double u2 = pid.compute(e2);
    EXPECT_NEAR(u2, u1 + expected_q1 * e, 1e-9);
}

TEST(PIDTest, StepResponse) {
    double K = 5.0;
    double Ti = 0.2;
    double Td = 0.04;
    double Ts = 0.01;

    PID pid(K, Ti, Td, Ts);

    double u_sum = 0.0;
    double e = 1.0;

    // 10 шагов с постоянной ошибкой
    for (int i = 0; i < 10; ++i) {
        u_sum += pid.compute(e);
    }

    // Должно быть больше просто пропорциональной части
    EXPECT_GT(u_sum, K * 10.0);
}

TEST(ControlObjectTest, InitialConditions) {
    double K_obj = 3.0;
    double T_obj = 0.1;
    double xi = 1.0;

    ControlObject obj(K_obj, T_obj, xi);

    obj.setInitialConditions(150.0, 0.0);

    EXPECT_DOUBLE_EQ(obj.getY(), 150.0);
}

TEST(ControlObjectTest, StepResponse) {
    double K_obj = 3.0;
    double T_obj = 0.1;
    double xi = 1.0;

    ControlObject obj(K_obj, T_obj, xi);
    obj.setInitialConditions(0.0, 0.0);

    double u = 10.0;
    double dt = 0.008;

    double y_prev = obj.getY();

    for (int i = 0; i < 50; ++i) {
        double y = obj.update(u, dt);
        if (i > 5) {
            EXPECT_GT(y, y_prev);  // должен расти
        }
        y_prev = y;
    }

    // При большом времени должен приближаться к K*u
    EXPECT_NEAR(obj.getY(), K_obj * u, K_obj * u * 0.15);  // ±15% — грубая оценка
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}