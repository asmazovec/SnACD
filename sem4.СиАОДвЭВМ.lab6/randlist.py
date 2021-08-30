import random

size = 1000000
max_ = 10000000000000
with open(f'{size}_{random.randint(0,100)}', 'a') as f:
    for i in range(size - 1):
        f.write(str(random.randint(0, max_)) + "\n")
    f.write(str(random.randint(0, max_)))
