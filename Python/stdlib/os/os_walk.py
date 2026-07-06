import os

path = '../'
file_loc = os.walk(path)
file_list = []
for path, dirs, files in file_loc:
    for f in files:
        file_list.append(os.path.join(path, f))

print(file_list)