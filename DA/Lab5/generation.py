import random
import string

def generate_random_string(n):
    random_string = ''.join(random.choice(string.ascii_lowercase) for _ in range(n))
    return random_string

def write_to_file(filename, content):
    with open(filename, 'w') as f:
        f.write(content)

def extract_random_slice(s):
    start = random.randint(0, len(s) - 1)
    end = random.randint(start + 1, len(s))
    return s[start:end]


n = 10

random_string = generate_random_string(n)

write_to_file('text.txt', random_string)

random_slice = extract_random_slice(random_string)

write_to_file('patterns.txt', random_slice)