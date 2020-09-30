from utils import read_csv
import matplotlib.pyplot as plt

if __name__ == "__main__":
    plt.rcParams.update({'font.size': 5})
    plt.subplots_adjust(hspace=0.42)
    data = read_csv("dataset_train.csv")
    courses = list(data.keys())[6:]

    i = 1
    done = []
    for course in courses:
        for course_2 in courses:
            if course_2 not in done and course != course_2:
                houses = dict()
                for mark, mark_2, house in zip(data[course], data[course_2], data["Hogwarts House"]):
                    if mark != "" and mark_2 != "":
                        if not house in houses:
                            houses[house] = [[],[]]
                        houses[house][0].append(float(mark))
                        houses[house][1].append(float(mark_2))
                colors = list("rgbcmyk")
                plt.subplot(9,9, i)
                i += 1
                print(i, course, course_2)
                for vector in houses.values():
                    plt.scatter(vector[0],vector[1],color=colors.pop(), s=5)
        done.append(course)
    plt.legend(houses.keys())
    plt.show()

    '''
        On peut observer que Astronomy vs Defense against... font une droite donc c'est la meme feature
    '''