CXX			:= g++
CXX_FLAGS	:= -std=c++17

BIN			:= bin
SRC			:= src
EXECUTABLE	:= main
CHILD 		:= child
BUILD		:= ./build


run: ./build/main_exe
	export LD_LIBRARY_PATH=./build/; \
	./build/main_exe
# export LD_LIBRARY_PATH=./build/ - Переменная окружения, показывающая, где искать библиотеку

build_fir: clean  lib1
	$(CXX) $(CXX_FLAGS) ./src/main_static.cpp -o ./build/main_exe -L./build -lMyLib1

# -L - директория, где искать библиотеку - указываем конкретную библиотеку
# -l - флаг перед именем библиотеки
# -o - имя выходного файла
#  -ldl - линковка с библиотекой динамической загрузки 

build_sec: clean lib2
	$(CXX) $(CXX_FLAGS) ./src/main_static.cpp -o ./build/main_exe -L./build -lMyLib2 

build_both: clean lib1 lib2
	$(CXX) $(CXX_FLAGS) ./src/main_dynamic.cpp -o ./build/main_exe -L./build -ldl


lib1: ./src/lib1.cpp
	$(CXX) $(CXX_FLAGS) -o ./build/libMyLib1.so -shared -fPIC ./src/lib1.cpp

# -shared - создание библиотеки вместо исполняемого файла
# -fPIC - position independnent code - загрузка кода в любую область памяти

lib2: $(SRC)/lib2.cpp
	$(CXX) $(FALAGS) -o ./build/libMyLib2.so -shared -fPIC ./src/lib2.cpp

clean:
	rm -f $(BUILD)/*.o $(BUILD)/*.so $(BUILD)/*_exe



