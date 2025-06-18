import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

# Parametri simulacije
frequency = 1000  # Frekvencija u Hz (1 kHz)
period_us = 1_000_000 / frequency  # Period u mikrosekundama
num_pulses = 50  # Broj impulsa koji se simuliraju

# Simulacija vremenskih kašnjenja (jitter)
np.random.seed(42)  # Za reproduktivnost
jitter = np.random.normal(loc=0, scale=2, size=num_pulses)  # Jitter ±2 µs
timestamps_us = np.cumsum(np.full(num_pulses, period_us) + jitter)  # Vremenske oznake impulsa

# Izračunavanje vremenskih intervala i devijacija
intervals_us = np.diff(np.insert(timestamps_us, 0, 0))  # Intervali između impulsa
df = pd.DataFrame({
    "Impuls": np.arange(1, num_pulses + 1),
    "Vreme (µs)": timestamps_us,
    "Interval (µs)": intervals_us,
    "Devijacija (%)": ((intervals_us - period_us) / period_us) * 100
})

# Ispisivanje rezultata
print(df)

# Vizuelizacija
plt.figure(figsize=(10, 5))
plt.plot(df["Impuls"], df["Interval (µs)"], marker='o', label='Simulirani intervali')
plt.axhline(y=period_us, color='red', linestyle='--', label='Idealni interval (1000 µs)')
plt.title("Simulacija vremenskih impulsa – 1 kHz izlaz sa jitter-om")
plt.xlabel("Broj impulsa")
plt.ylabel("Trajanje impulsa (µs)")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()
