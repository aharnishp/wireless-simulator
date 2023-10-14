import numpy as np
import matplotlib.pyplot as plt

# Define the parameters
Pt = 1.0  # Transmitted power
d = np.linspace(0.001, 1, 100)  # Range of distances from 0.001 to 1

# Calculate received power using the formula
Pr = Pt / (4 * np.pi * d**2) * (1 - d**2 / (2 * (4 * np.pi * d**2)))

# Create the plot
plt.figure(figsize=(8, 6))
plt.plot(d, Pr, label='Received Power')
plt.xlabel('Distance (d)')
plt.ylabel('Received Power (Pr)')
plt.title('Received Power vs. Distance')
plt.grid(True)
plt.legend()
plt.show()
