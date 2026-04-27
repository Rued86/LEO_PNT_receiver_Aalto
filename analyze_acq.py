import h5py
import numpy as np

# Load the first acquisition dump
with h5py.File('acq_dump_G_1C_ch_0_1_sat_2.mat', 'r') as mat:
    print("Keys:", list(mat.keys()))
    
    threshold = np.array(mat['threshold']).item()
    test_statistic = np.array(mat['test_statistic']).item()
    positive_acq = np.array(mat['positive_acq']).item()
    doppler_max = np.array(mat['doppler_max']).item()
    doppler_step = np.array(mat['doppler_step']).item()
    
    print(f"Positive Acq: {positive_acq}")
    print(f"Threshold: {threshold:.4f}")
    print(f"Test Statistic: {test_statistic:.4f}")
    print(f"Doppler Max: {doppler_max}")
    print(f"Doppler Step: {doppler_step}")



# Let's also check the pfa threshold if available, though it might not be in the MAT file
