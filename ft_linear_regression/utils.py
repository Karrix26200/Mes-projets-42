import numpy as np

def csv_to_numpy(csv_path):
    return np.loadtxt(csv_path, delimiter=',', skiprows=1)

def predict(mileage, t0, t1):
    return t0 + (t1 * mileage)

def normalize(np_arr):
    decay = np.min(np_arr)
    np_arr -= decay
    vmax = np.max(np_arr)
    np_arr /= vmax
    return np_arr, decay, vmax

def unnormalize(np_arr, decay, vmax):
    np_arr *= vmax
    np_arr += decay
    return np_arr