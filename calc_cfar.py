# Use python to calculate the CFAR threshold for different PFA values
# GNSS-SDR uses the quantile of an Exponential or Chi-Square distribution.
# Actually, the grid is magnitude squared, so it's exponentially distributed for noise.
# P(max(X_1..X_N) > T * mean) = 1 - (1 - exp(-T))^N = pfa
# So (1 - exp(-T))^N = 1 - pfa
# 1 - exp(-T) = (1 - pfa)^(1/N)
# exp(-T) = 1 - (1 - pfa)^(1/N)
# T = -ln(1 - (1 - pfa)^(1/N))

import math

N = 8184 # effective FFT size

for pfa in [0.1, 0.01, 0.001, 0.0001, 0.00001, 0.9]:
    T = -math.log(1 - (1 - pfa)**(1/N))
    print(f"PFA={pfa}: Threshold={T:.4f}")
