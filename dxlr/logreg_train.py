from ft_math import math_standardize
from utils import read_csv
import numpy as np
import random
import copy
import sys
import os

houses = np.array(["Gryffindor", "Slytherin", "Ravenclaw", "Hufflepuff"])

def get_dataset(data, courses, stdz_data=None):
    dataset = copy.deepcopy(data)

    # Clean data
    base_key = list(dataset.keys())
    for course in base_key:
        if course not in courses:
            del dataset[course]

    # All to float and none to mean of his house mark for a given feature
    for course in dataset:
        # Get sum, count and set to None
        houses_means = dict()
        for i, (mark, house) in enumerate(zip(dataset[course], data["Hogwarts House"])):
            if mark != "":
                dataset[course][i] = float(mark)
                if house not in houses_means:
                    houses_means[house] = {"sum": 0, "count": 0}
                houses_means[house]["sum"] += dataset[course][i]
                houses_means[house]["count"] += 1
            else:
                dataset[course][i] = None
            
        # Computes houses means
        for house in houses_means:
            houses_means[house] = houses_means[house]["sum"] / houses_means[house]["count"]
            
        # Apply meanx
        for i, (mark, house) in enumerate(zip(dataset[course], data["Hogwarts House"])):
            if mark is None:
                dataset[course][i] = houses_means[house]

    # Standardization
    if stdz_data is None:
        stdz_data = dict()
        for course in courses:
            dataset[course], v_min, v_max, mean, std = math_standardize(dataset[course])
            stdz_data[course] = {"min": v_min, "max": v_max, "mean": mean, "std": std}
    else:
        for course in courses:
            dataset[course], v_min, v_max, mean, std = math_standardize(dataset[course], stdz_data[course]["min"], stdz_data[course]["max"], stdz_data[course]["mean"], stdz_data[course]["std"])

    # Dict to numpy
    dataset = np.array(list(dataset.values()), dtype=np.float32)
    # Numpy transpose because we want iterate on row
    dataset = dataset.transpose()

    return dataset, stdz_data

def predict(dataset, weigths, activation_fnc="sigmoid"):
    y = np.zeros((dataset.shape[0], weigths.shape[0], weigths.shape[1]))
    for i in range(dataset.shape[0]):
        y[i] = weigths * dataset[i]
    y = np.sum(y, axis=2) / dataset.shape[0] # Reduce mean
    if activation_fnc == "sigmoid":
        y =  1 / (1 + np.exp(-y))
    elif activation_fnc == "relu":
        y[y < 0] = 0
    elif activation_fnc == "softplus":
        y = np.log(1 + np.exp(y))
    elif activation_fnc == "gauss":
        y = np.exp((-y)**2)
    elif activation_fnc == "heaviside":
        y[y < 0.5] = 0
        y[y >= 0.5] = 1
    elif activation_fnc == "none":
        pass
    else:
        print("Error: no activation function")
        exit(1)
    return y 

def get_real(dataset_houses, houses):
    y_real = np.zeros((len(dataset_houses), houses.shape[0]))
    houses = np.array(houses)
    house_list = np.array(dataset_houses)
    for i in range(houses.shape[0]):
        y_real[:, i] = house_list[:] == houses[i]
    return y_real

def learn(data, courses, generation=100, batch_size=None, learning_rate=0.5, dropout=0, activation_fnc="sigmoid", mute=False):
    base_courses = courses
    dataset, stdz_data = get_dataset(data, courses, stdz_data=None)
    courses = copy.deepcopy(base_courses)

    '''
        La formule demande de faire la moyenne des erreurs des outputs. Donc on a 4 outputs on divie par 4 c'est tout.
    '''
    # Add biase
    courses.append("Bias")
    biases = np.full((dataset.shape[0], 1), 1)
    datasets = np.concatenate((dataset, biases), axis=1)

    # Initialization
    input_number = len(courses)
    weigths = np.random.rand(4, input_number)

    # Shuffle with seed for SGD
    datasets_houses = np.array(data["Hogwarts House"])
    seed = random.randint(0, 30000)
    np.random.seed(seed)
    np.random.shuffle(datasets_houses)
    np.random.seed(seed)
    np.random.shuffle(datasets)

    # Split for stochastic gradient descent
    batch_nbr = int(len(datasets_houses) / batch_size) if batch_size is not None else 1
    datasets_houses = np.array_split(datasets_houses, batch_nbr)
    datasets = np.array_split(datasets, batch_nbr)

    for g in range(generation):
        # For each for stochastic gradient descent
        for bi, (dataset, dataset_houses) in enumerate(zip(datasets, datasets_houses)):
            y_real = get_real(dataset_houses, houses)
            y_prediction = predict(dataset, weigths, activation_fnc)

            errors = y_prediction - y_real            
            # J = feature
            for j in range(weigths.shape[1]):
                mean = (errors.T * dataset[:,j]).T
                mean = np.mean(mean, axis=0)
                dropouts = np.random.rand(mean.shape[0])
                mean[dropouts < dropout] = 0
                weigths[:,j] -= mean * learning_rate

            error = np.mean(np.mean(errors, axis=0))
            accuracy = 1 - (error ** 2)
            if not mute:
                print("Generation: {}/{} | Batch: {}/{} | Error: {:.2f} | Accuracy: {:.2f}".format(g+1, generation, bi+1, batch_nbr, error, accuracy))

    # Save data (courses, stdz_data and weights)
    new_csv = ",".join(courses) + "\n"
    data_list = ["min", "max", "mean", "std"]
    for data_type in data_list:
        new_csv += ",".join([str(stdz_data[key][data_type]) for key in stdz_data]) + ",\n"
    for house in weigths:
        new_csv += ",".join([str(weigth) for weigth in house]) + "\n"
    f = open("train_data.csv", "w")
    f.write(new_csv)
    f.close()

    '''
        Save data csv look like this:
            feature_0,  feature_n...,
            min_0,
            max_0,
            mean_0,
            std_0,
            weigth_00,
            weigth_01,
            weigth_02,
            weigth_03,
    '''

def main():
    # Parse dataset path parameter
    dataset_path = "dataset_train.csv"
    if len(sys.argv) == 2:
        dataset_path = sys.argv[1]
    if not os.path.exists(dataset_path):
        print("Can't find dataset", dataset_path)
        exit(1)

    # Dataset to read
    data = read_csv(dataset_path)
    # Features I choose to train
    courses = ["Astronomy", "Herbology", "Defense Against the Dark Arts", "Ancient Runes"]
    courses += ["Divination", "Muggle Studies", "History of Magic", "Transfiguration", "Charms", "Flying"]
    
    # Hyperparameter
    generation = 1
    learning_rate = 0.5
    dropout = 0.1
    batch_size = 32
    activation_fnc = "sigmoid"
    learn(data=data, courses=courses, generation=generation, batch_size=batch_size, learning_rate=learning_rate, dropout=dropout, activation_fnc=activation_fnc, mute=False)
        
if __name__ == "__main__":
    main()