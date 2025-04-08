import random

n = int(input())

def write_to_file(filename, content):
    with open(filename, 'w') as f:
        f.write(content)


def random_string(n):
    return ''.join(random.choice(list('abcdefghijklmnopqrstuvwxyz')) for _ in range(n))


write_to_file('text.txt', random_string(n))
