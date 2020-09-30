import numpy as np
from utils import read_csv
from logreg_train import predict, get_dataset, houses
import os
import sys

if __name__ == "__main__":
    # Parse dataset path parameter
    dataset_path = "dataset_test.csv"
    if len(sys.argv) == 2:
        dataset_path = sys.argv[1]
    if not os.path.exists(dataset_path):
        print("Can't find dataset", dataset_path)
        exit(1)

    # Import courses, stdz_data and weights
    path = "train_data.csv"
    if not os.path.exists(path):
        print("Can't find", path)
        exit(1)
    other_data = read_csv(path)
    stdz_data = dict()
    courses = list(other_data.keys())
    base_courses = courses[:-1]
    data_list = ["min", "max", "mean", "std"]
    weigths = np.zeros((4, len(courses)))
    # Extract standardization data
    for course in base_courses:
        stdz_data[course] = dict()
        for i, data_type in enumerate(data_list):
            stdz_data[course][data_type] = float(other_data[course][i])
    # Extract weigths
    for c, course in enumerate(courses):
        for i in range(4):
            weigths[i][c] = float(other_data[course][i+4])
        
    # Post initialization
    data = read_csv(dataset_path)
    dataset, stdz_data = get_dataset(data, base_courses, stdz_data=stdz_data)

    # Add biase
    biases = np.full((dataset.shape[0], 1), 1)
    dataset = np.concatenate((dataset, biases), axis=1)

    y_prediction = predict(dataset, weigths)
    new_csv = "Index,Hogwarts House\n"
    for i, pred in enumerate(y_prediction):
        new_csv += str(i) + "," + houses[np.argmax(pred)] + "\n"
    f = open("houses.csv", "w")
    f.write(new_csv)
    f.close()