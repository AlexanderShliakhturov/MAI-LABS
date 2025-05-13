CREATE TABLE owners (
    owner_id SERIAL PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    age INTEGER,
    country VARCHAR(100),
    city VARCHAR(100),
    email VARCHAR(100),
    phone VARCHAR(20),
    registration_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    comment TEXT,
    experimental int

);

CREATE TABLE pets (
    pet_id SERIAL PRIMARY KEY,
    owner_id INTEGER REFERENCES owners(owner_id) ON DELETE CASCADE,
    name VARCHAR(100) NOT NULL,
    breed VARCHAR(100),
    age INTEGER,
    weight NUMERIC(5,2),
    last_vaccination_date DATE
);