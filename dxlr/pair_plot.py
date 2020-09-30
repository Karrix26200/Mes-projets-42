from utils import read_csv
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
if __name__ == "__main__":
    data = read_csv("dataset_train.csv")
    courses = list(data.keys())[6:]

    df = pd.DataFrame.from_dict(data)
    df = df.drop(columns = ["Index", "First Name", "Last Name", "Birthday", "Best Hand"])
    for i, course in enumerate(courses):
        df[course] = pd.to_numeric(df[course], downcast="float")
        print("Row", i, course)
    sns.pairplot(df, hue="Hogwarts House")
    plt.show()

'''
    On regarde l'histograme de chaque features, celle isolant au moins une feature d'une autre sont selectionné
    Comme on a pu l'observer sur scatter_plot, Astronomy vs Defense against sont EXACTEMENT la meme features. On peut penser qu'il faut en garder qu'un, mais non, il faut utiliser les 2, les doublons ameliorent la precision.
    Ensuite en regarde les histogrames, on garde que celles qui isolent au moins une feature(couleur). Les doublons peuvent etre utilsé tous les 2 pour ameliorer la precisions:
    
    A | ACCURACY | 10 features | Sensé etre la meilleur solution
    1 et 3 (doublon d'isolement)
    2
    4
    5
    6
    7 et 8 (doublon d'isolement)
    11
    12

    B | ACCURACY | 4 features | INSTABLE (pour montrer la facon de penser)
    4, 5, 7, 11
    Divination, Muggle Studies, History of Magic, Charms

    C | ACCURACY | 4 features --> Meilleur ratio nbr_features / accuracy (On utilise une logique d'elimination entre astro, herbo et runes. Le doublon Defense permet d'affiner la precision mais ca reste un doublon)
    1 et 3, 2, 6 (Elles s'isolent entre elles)
    Astro, Defense, Herbo, Runes

    On peut faire pareil juste avec Astro + Herbo mais moins precis mais plus rapide à entrainer

    Il faut garder en tete que plus on prend de feature isolantes, plus le model sera précis. Si on prend juste les 2 features, ca va marcher, mais moins précis. Plus on prend de feature, plus on est précis mais plus le model met du temps a apprendre
'''
