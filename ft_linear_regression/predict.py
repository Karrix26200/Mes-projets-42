import numpy as np
from utils import csv_to_numpy, predict, normalize, unnormalize

def one_normalize(value, decay, vmax):
    return (value - decay) / vmax

def one_unnormalize(value, decay, vmax):
    return value * vmax + decay

def is_number(s):
    try: 
        float(s)
        return True
    except ValueError:
        return False

if __name__ == "__main__":
    data = csv_to_numpy("data.csv")
    km_list, price_list = data[:,0], data[:,1]

    thetas = csv_to_numpy("thetas.csv")
    t0, t1 = thetas[0], thetas[1]

    useless, km_decay, km_max = normalize(data[:,0])
    useless, price_decay, price_max = normalize(data[:,1])

    while True:
        km = input("Enter your km: ")
        if not is_number(km):
            print("Please enter number")
        else:
            n_km = one_normalize(float(km), km_decay, km_max)
            n_predicted_price = predict(n_km, t0, t1)
            predicted_price = one_unnormalize(n_predicted_price, price_decay, price_max)
            print("For {} km, price is {}".format(km, predicted_price))