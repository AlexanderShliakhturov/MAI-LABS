import random
import string


def generate_string_with_pattern(total_length, pattern, pattern_count):

    remaining_length = total_length - len(pattern) * pattern_count

    random_part = "".join(
        random.choices(string.ascii_letters + string.digits, k=remaining_length)
    )

    parts = [pattern] * pattern_count + [random_part]
    # print(parts)

    random.shuffle(parts)
    # print(parts)

    result = "".join(parts)

    return result


def save_string_to_file(string, filename):
    with open(filename, "w") as file:
        file.write(string)


total_length = 100000000
pattern = "mynameisalexander"
pattern_count = 5
filename = "input.txt"

generated_string = generate_string_with_pattern(total_length, pattern, pattern_count)
save_string_to_file(generated_string, filename)
