import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('simulation_results.csv')

plt.figure(figsize=(14, 7))

plt.plot(df['time'], df['setpoint'], 'b-', label='Уставка (setpoint)', linewidth=2.5)
plt.plot(df['time'], df['y'], 'r-', label='Выход объекта (y)', linewidth=2)
plt.plot(df['time'], df['u'] * 0.5, 'g-', label='Управление u (×0.5)', linewidth=1.8)  # умножаем, чтобы масштабы были сопоставимы
plt.plot(df['time'], df['e'], 'm--', label='Ошибка e', linewidth=1.5)

plt.grid(True, linestyle='--', alpha=0.7)
plt.legend(loc='upper right')
plt.title('Результаты моделирования ПИД-регулятора')
plt.xlabel('Время, с')
plt.ylabel('Значение')
plt.tight_layout()

plt.show()