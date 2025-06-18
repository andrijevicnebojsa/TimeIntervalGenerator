import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

# Load CSV with impulse timestamps or time errors (single column)
df = pd.read_csv('Simulacija_Impulsa_Etalona.csv')

# Assume the column contains time intervals or timestamps (ns)
time_ns = df.iloc[:, 0].to_numpy()
tau_0 = 1e-6  # Base interval (1 µs), adjust as needed

# Convert to fractional frequency deviation
y = (np.diff(time_ns) - np.mean(np.diff(time_ns))) / np.mean(np.diff(time_ns))

# Allan Deviation
def allan_deviation(y, tau0, max_m=100):
    m_values = np.logspace(0, np.log10(max_m), num=20, dtype=int)
    adev = []
    for m in m_values:
        if 2 * m >= len(y): break
        averaged = np.array([np.mean(y[i:i + m]) for i in range(0, len(y) - m, m)])
        diffs = np.diff(averaged)
        adev.append(np.sqrt(np.mean(diffs ** 2) / 2))
    return m_values[:len(adev)], adev

m_vals, adev_vals = allan_deviation(y, tau_0)

plt.loglog(m_vals * tau_0, adev_vals, marker='o')
plt.title('Allan Deviation')
plt.xlabel('Averaging Time τ (s)')
plt.ylabel('σ(τ)')
plt.grid(True, which='both')
plt.savefig('allan_deviation_plot.png')
plt.show()
