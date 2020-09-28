import numpy as np
from utils import csv_to_numpy, predict, normalize, unnormalize

if __name__ == "__main__":
    # Initialisation
    data = csv_to_numpy("data.csv")
    km_list, price_list = data[:,0], data[:,1]
    t0, t1 = 0, 0
    data_mean = 1 / len(data)

    n_km_list, km_decay, km_max = normalize(km_list)
    n_price_list, price_decay, price_max = normalize(price_list)

    # Hyperparameters
    learning_rate = 0.5
    generation = 7

    # Learning loop
    for i in range(generation):
        sum_for_t0 = 0
        sum_for_t1 = 0
        for km, price in zip(n_km_list, n_price_list):
            error = predict(km, t0, t1) - price
            sum_for_t0 += error
            sum_for_t1 += error * km

        # Regression
        t0 -= learning_rate * (data_mean * sum_for_t0)
        t1 -= learning_rate * (data_mean * sum_for_t1)

        # Visualization
        sum_for_t0 *= data_mean
        precision = 1 - abs(sum_for_t0 ** 2)
        print("generation {}: error = {:.2f}, precision = {:.2f}, T0 = {:.2f}, T1 = {:.2f}".format(i, sum_for_t0, precision, t0, t1))

    # Save thetas
    with open("thetas.csv", "w") as text_file:
        text_file.write("t0,t1\n{},{}".format(t0, t1))