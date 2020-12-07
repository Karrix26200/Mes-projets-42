import os
from os import listdir
from os.path import isfile, join

if __name__ == "__main__":
    mypath = "test"
    onlyfiles = [f for f in listdir(mypath) if isfile(join(mypath, f))]
    print(onlyfiles)
    for filen in onlyfiles:
        cnt = open(mypath + "/" + filen, 'r').read()
        cnt = "python3 " + cnt[2:]
        print(cnt)
        os.system(cnt)