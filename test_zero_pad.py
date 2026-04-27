import numpy as np

# Simulate a 1 ms window of a 0.5-ms periodic code
FS = 8184
code_half = np.random.choice([-1, 1], size=FS//2)
rx_signal = np.concatenate([code_half, code_half]) # 1 ms of received signal repeats twice

# 1. Local replica is the full 1 ms (repeats twice)
replica_full = np.concatenate([code_half, code_half])
corr_full = np.abs(np.fft.ifft(np.fft.fft(rx_signal) * np.conj(np.fft.fft(replica_full))))

# 2. Local replica is 0.5 ms padded with zeros
replica_padded = np.concatenate([code_half, np.zeros(FS//2)])
corr_padded = np.abs(np.fft.ifft(np.fft.fft(rx_signal) * np.conj(np.fft.fft(replica_padded))))

print(f"Full replica: Max={np.max(corr_full):.2f}, num peaks={np.sum(corr_full > 0.9*np.max(corr_full))}")
print(f"Padded replica: Max={np.max(corr_padded):.2f}, num peaks={np.sum(corr_padded > 0.9*np.max(corr_padded))}")
