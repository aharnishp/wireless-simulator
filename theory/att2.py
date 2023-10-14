import numpy as np
import matplotlib.pyplot as plt
import sympy as sp

# Define symbolic variables
d_symbolic = sp.Symbol('d')
Pt_symbolic = sp.Symbol('Pt')

# Define the formula
received_power_formula = Pt_symbolic / (4 * np.pi * d_symbolic**2) * (1 - d_symbolic**2 / (2 * (4 * np.pi * d_symbolic**2)))

# Compute the power series expansion
power_series = sp.series(received_power_formula, d_symbolic, n=3).removeO()

# Define values
Pt_value = 1.0
d_values = np.linspace(0.001, 1, 100)

# Calculate received power using the power series expansion
Pr_values = [float(power_series.subs({d_symbolic: d_val, Pt_symbolic: Pt_value})) for d_val in d_values]

# Create the plot
plt.figure(figsize=(8, 6))
plt.plot(d_values, Pr_values, label='Received Power (Approx.)')
plt.xlabel('Distance (d)')
plt.ylabel('Received Power (Pr)')
plt.title('Received Power vs. Distance (Approximation)')
plt.grid(True)
plt.legend()
plt.show()
