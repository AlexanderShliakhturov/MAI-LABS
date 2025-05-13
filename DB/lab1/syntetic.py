import psycopg2
from faker import Faker
import random
from datetime import datetime, timedelta
import time
from tqdm import tqdm

# Настройки подключения к БД
DB_CONFIG = {
    "host": "localhost",
    "port": 5433,
    "database": "DB_LAB_1", 
    "user": "user",   
    "password": "password" 
}

RECORDS_COUNT = 5500000
BATCH_SIZE = 1000 

fake = Faker('ru_RU')  

COUNTRIES = ['Россия', 'Беларусь', 'Казахстан', 'Украина', 'США', 'Германия']
BREEDS = ['Британский', 'Персидский', 'Сиамский', 'Мейн-кун', 'Сфинкс', 
          'Лабрадор', 'Овчарка', 'Пудель', 'Бульдог', 'Чихуахуа']
PET_NAMES = ['Барсик', 'Мурка', 'Шарик', 'Тузик', 'Рекс', 'Мухтар', 'Пушок', 'Том', 'Джерри', 'Белка']

def generate_owners_data(count):
    """Генерация данных для таблицы owners"""
    for i in range(count):
        registration_date = fake.date_time_between(start_date='-5y', end_date='now')
        yield (
            fake.name(),
            random.randint(18, 80),
            random.choice(COUNTRIES),
            fake.city(),
            fake.email(),
            fake.phone_number(),
            registration_date,
            fake.text(max_nb_chars=100) if random.random() > 0.3 else None,
            i + 1
        )

def generate_pets_data(owner_ids):
    """Генерация данных для таблицы pets"""
    for owner_id in owner_ids:
        yield (
            owner_id,
            random.choice(PET_NAMES),
            random.choice(BREEDS),
            random.randint(1, 15),
            round(random.uniform(1.0, 50.0), 2),
            fake.date_between(start_date='-2y', end_date='today') if random.random() > 0.2 else None
        )

def insert_data_batch(conn, cursor, table, data_generator, batch_size):
    """Вставка данных батчами"""
    batch = []
    total = 0
    for record in data_generator:
        batch.append(record)
        if len(batch) >= batch_size:
            try:
                if table == 'owners':
                    args_str = ','.join(cursor.mogrify("(%s,%s,%s,%s,%s,%s,%s,%s,%s)", x).decode('utf-8') for x in batch)
                    cursor.execute(f"INSERT INTO owners (name, age, country, city, email, phone, registration_date, comment, experimental) VALUES {args_str}")
                elif table == 'pets':
                    args_str = ','.join(cursor.mogrify("(%s,%s,%s,%s,%s,%s)", x).decode('utf-8') for x in batch)
                    cursor.execute(f"INSERT INTO pets (owner_id, name, breed, age, weight, last_vaccination_date) VALUES {args_str}")
                conn.commit()
                total += batch_size
                print(f'Batch with size of {batch_size} was inserted', 'total = ', total)
                batch = []
            except Exception as e:
                conn.rollback()
                print(f"Ошибка при вставке: {e}")
                break
            
    if batch:
        try:
            if table == 'owners':
                args_str = ','.join(cursor.mogrify("(%s,%s,%s,%s,%s,%s,%s,%s,%s)", x).decode('utf-8') for x in batch)
                cursor.execute(f"INSERT INTO owners (name, age, country, city, email, phone, registration_date, comment, experimental) VALUES {args_str}")
            elif table == 'pets':
                args_str = ','.join(cursor.mogrify("(%s,%s,%s,%s,%s,%s)", x).decode('utf-8') for x in batch)
                cursor.execute(f"INSERT INTO pets (owner_id, name, breed, age, weight, last_vaccination_date) VALUES {args_str}")
            conn.commit()
        except Exception as e:
            conn.rollback()
            print(f"Ошибка при вставке остатка: {e}")

def main():
    try:
        conn = psycopg2.connect(**DB_CONFIG)
        cursor = conn.cursor()
        
        print("Генерация и вставка данных владельцев...")
        start_time = time.time()
        
        owners_gen = generate_owners_data(RECORDS_COUNT)
        insert_data_batch(conn, cursor, 'owners', owners_gen, BATCH_SIZE)
        
        owners_time = time.time() - start_time
        print(f"Вставка {RECORDS_COUNT} владельцев завершена за {owners_time:.2f} сек")
        
        print("Получение ID владельцев для связей...")
        cursor.execute("SELECT owner_id FROM owners")
        owner_ids = [row[0] for row in cursor.fetchall()]
        
        print("Генерация и вставка данных животных...")
        start_time = time.time()
        
        # Вставка животных
        pets_gen = generate_pets_data(owner_ids)
        insert_data_batch(conn, cursor, 'pets', pets_gen, BATCH_SIZE)
        
        pets_time = time.time() - start_time
        print(f"Вставка {RECORDS_COUNT} животных завершена за {pets_time:.2f} сек")
        
    except Exception as e:
        print(f"Ошибка: {e}")
    finally:
        if conn:
            conn.close()

if __name__ == "__main__":
    main()