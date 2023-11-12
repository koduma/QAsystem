import shutil
import os

for i in range(52000, 56001, 1):
    print(i)
    path = str(i)+"_q.txt"
    is_file = os.path.isfile(path)
    if is_file:
        new_path = shutil.move(str(i)+"_q.txt","dir14")
        new_path = shutil.move(str(i)+"_a.txt","dir14")