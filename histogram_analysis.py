# Reimport and rerun everything after kernel reset
import numpy as np
import pandas as pd

# Definišemo frekvencije za test: 1 Hz, 10 Hz, 100 Hz
frequencies = [1, 10, 100]
num_pulses = 20  # Manje impulsa zbog dužih intervala kod manjih frekvencija

# Simulacija sa jitter-om ±2 µs za sve frekvencije
results = []

for freq in frequencies:
    period_us = 1_000_000 / freq
    jitter = np.random.normal(loc=0, scale=2, size=num_pulses)
    timestamps_us = np.cumsum(np.full(num_pulses, period_us) + jitter)
    intervals_us = np.diff(np.insert(timestamps_us, 0, 0))
    devijacija = ((intervals_us - period_us) / period_us) * 100

    for i in range(num_pulses):
        results.append({
            "Frekvencija (Hz)": freq,
            "Impuls": i + 1,
            "Interval (µs)": intervals_us[i],
            "Devijacija (%)": devijacija[i]
        })

df_all = pd.DataFrame(results)

# Statistička analiza po frekvencijama
summary = df_all.groupby("Frekvencija (Hz)")["Interval (µs)"].agg(
    Srednja_vrednost="mean",
    Standardna_devijacija="std",
    Maksimalno_odstupanje=lambda x: np.max(np.abs(x - x.mean()))
).reset_index()

import ace_tools as tools; tools.display_dataframe_to_user(name="Statistička analiza po frekvencijama", dataframe=summary)
