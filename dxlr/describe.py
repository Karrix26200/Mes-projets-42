from utils import read_csv
from ft_math import math_count, math_mean, math_min, math_max, math_std, math_percentile


if __name__ == "__main__":
    data = read_csv("dataset_train.csv")
    # Clean data
    courses = list(data.keys())[6:]
    base_keys = list(data.keys())
    for course in base_keys:
        if course not in courses:
            del data[course]

    fnc_dict = {
        "Count": [math_count],
        "Mean": [math_mean],
        "Std": [math_std],
        "Min": [math_min],
        "25%": [math_percentile, 0.25],
        "50%": [math_percentile, 0.50],
        "75%": [math_percentile, 0.75],
        "Max": [math_max]
    }

    # All to float
    for feature in data:
        data[feature] = [i for i in data[feature] if i != ""]
        for i in range(len(data[feature])):
            data[feature][i] = float(data[feature][i])

    # Compute functions
    res_dict = dict()
    for feature in data:
        res_dict[feature] = dict()
        for fnc_key in fnc_dict:
            if len(fnc_dict[fnc_key]) == 1:
                res_dict[feature][fnc_key] = fnc_dict[fnc_key][0](data[feature])
            else:
                res_dict[feature][fnc_key] = fnc_dict[fnc_key][0](data[feature], fnc_dict[fnc_key][1])

    # Init len saver
    len_saver = [0] * (math_count(list(data.keys())) + 1)

    # Add first col
    padding = 2
    lens = []
    for fnc_key in fnc_dict:
        lens.append(len(fnc_key))
    len_saver[0] = math_max(lens) + padding

    # Add other cols
    for i, feature in enumerate(res_dict):
        lens = [len(feature)]
        for fnc_key in res_dict[feature]:
            lens.append(len("{:.2f}".format(res_dict[feature][fnc_key])))
        len_saver[i+1] = math_max(lens) + padding

    # Print it
    header = [""] + list(data.keys())
    res_str = ""
    for i, elem in enumerate(header):
        if i == 0:
            res_str += elem.ljust(len_saver[i])
        else:
            res_str += elem.rjust(len_saver[i])
    print(res_str)

    for fnc_key in fnc_dict:
        res_str = fnc_key.ljust(len_saver[0])
        for i, feature in enumerate(res_dict):
            res_str += "{:.2f}".format(res_dict[feature][fnc_key]).rjust(len_saver[i+1])
        print(res_str)