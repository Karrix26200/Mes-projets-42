from utils import read_csv
import matplotlib.pyplot as plt

if __name__ == "__main__":
    plt.rcParams.update({'font.size': 5})
    plt.subplots_adjust(hspace=0.42)
    data = read_csv("dataset_train.csv")

    # Initialise data
    courses = list(data.keys())[6:]
    houses = ["Gryffindor", "Slytherin", "Ravenclaw", "Hufflepuff"]

    # Compute means
    mean_mark = dict()
    for course in courses:
        mean_mark[course] = dict()
        for house in houses:
            mean_mark[course][house] = {"count": 0, "sum": 0}

        for house, mark in zip(data["Hogwarts House"], data[course]):
            if mark != "":
                mean_mark[course][house]["count"] += 1
                mean_mark[course][house]["sum"] += float(mark)

    # Show result
    for i, course in enumerate(mean_mark):
        print("\n", course)
        test = mean_mark[course]
        for house in mean_mark[course]:
            mean_mark[course][house] = mean_mark[course][house]["sum"] / mean_mark[course][house]["count"]
        print(mean_mark[course])
        plt.subplot(4,4, i+1)
        plt.title(course)
        plt.bar(test.keys(), test.values(), 1, color='rgby')
    plt.show()