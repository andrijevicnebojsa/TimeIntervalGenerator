# Koristimo tačan naziv kolone: 'Interval (µs)'

# Kreiranje histograma
plt.figure(figsize=(10, 6))
sns.histplot(simulacija_df["Interval (µs)"], bins=15, kde=True)
plt.title("Slika 23 - Histogram intervala impulsa (1 kHz)")
plt.xlabel("Vremenski interval [µs]")
plt.ylabel("Frekvencija")
plt.grid(True)
plt.tight_layout()
plt.savefig("/mnt/data/slika_6_2_histogram.png")
plt.close()

# Kreiranje boxplot grafikona
plt.figure(figsize=(8, 5))
sns.boxplot(data=simulacija_df, y="Interval (µs)")
plt.title("Slika 24 - Boxplot vremenskih intervala impulsa (1 kHz)")
plt.ylabel("Vremenski interval [µs]")
plt.grid(True)
plt.tight_layout()
plt.savefig("/mnt/data/slika_6_3_boxplot.png")
plt.close()
