from sympy import factorint, isprime, gcd
import re

# a = 112085497440388511364493266926808359258182229984346544114566622069335233815379
# factors = factorint(a)
# keys = list(factors.keys()) 

# for key in keys:
#     print(f"{key}, is prime? - {isprime(key)}")

import math

my_num = ('3231700607131100730071487668866995196044410266971548403213034542752465513886789'
    '0893197201411522913463688717960921898019494119559150490921095088154603676330116157751'
    '9389882243892414446062544053019522175727845320789845848089054124702800566882275298157'
    '0891458528568294724106538237972970534050989635694474401020183378096732153297648894573'
    '8432977605032129307390784792137656557063803464019925470552847841201327221399515335410'
    '8529413170012304443972673120111619237653386772637266067057353350363169495575523468370'
    '2272304947722710987286242495369195451210077395191785947268063712817772891541022491483'
    '2056397349155953757360361457')


def extract_b_numbers(file_path):
    with open(file_path, 'r', encoding='utf-8') as file:
        content = file.read()
    
    pattern = r'b\[(\d+)\]\s*=\s*([\d\s]+)(?=\s*b\[\d+\]|$)'
    matches = re.findall(pattern, content, re.MULTILINE)
    matches.sort(key=lambda x: int(x[0]))
    b_numbers = [match[1].replace('\n', '').replace(' ', '').replace('\r', '') for match in matches]
    
    return b_numbers

file_path = 'Лабораторная-2.txt'
b_numbers = extract_b_numbers(file_path)

for i, b in enumerate(b_numbers):
    gcd_val = gcd(int(my_num), int(re.sub(r"[^\d]", "", b)))
    if gcd_val != 1 and i != 30:
        print('ВАРИАНТ  ПЕРВОЕ_ЧИСЛО   is_prime')
        print(i, gcd_val, isprime(gcd_val))
        print("ВТОРОЕ ЧИСЛО   is_prime")
        print(int(my_num)/gcd_val, isprime(int(my_num)/gcd_val))
        break




