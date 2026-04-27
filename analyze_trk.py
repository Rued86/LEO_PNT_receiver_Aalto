import h5py
import numpy as np

try:
    with h5py.File('tracking_dump0.mat', 'r') as mat:
        cn0 = np.array(mat['CN0_SNV_dB_Hz']).flatten()
        doppler = np.array(mat['carrier_doppler_hz']).flatten()
        
        print(f"Total tracking samples: {len(cn0)}")
        print(f"Initial Doppler: {doppler[0]:.2f} Hz")
        print(f"Mid Doppler: {doppler[len(doppler)//2]:.2f} Hz")
        print(f"Final Doppler: {doppler[-1]:.2f} Hz")
        
        # Find where CN0 drops below 25
        drops = np.where(cn0 < 25.0)[0]
        if len(drops) > 0:
            print(f"First drop below 25 dB-Hz at sample: {drops[0]}")
            
except Exception as e:
    print(f"Error reading dump: {e}")
