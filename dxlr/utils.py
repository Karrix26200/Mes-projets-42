import csv

'''
    TODO:
        - Make option header=True, if not, make 
'''
def read_csv(path, header=True):
    csv_array = dict()
    with open(path) as csvfile:
        spamreader = csv.reader(csvfile, delimiter=',')
        first_line = True
        cols_names = None
        for row in spamreader:
            if first_line:
                cols_names = row if header else range(len(row))
                for col_name in cols_names:
                    csv_array[col_name] = []
            if not (header and first_line):
                for i, col_name in enumerate(cols_names):
                    csv_array[col_name].append(row[i])
            if first_line:
                first_line = False
    return csv_array

# Unit tests
if __name__ == "__main__":
    test = read_csv(path="dataset_train.csv", header=True)
    print(test["First Name"][1])