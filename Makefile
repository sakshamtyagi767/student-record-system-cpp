CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I include
TARGET   = StudentRecordSystem
SRC      = src/Student.cpp src/RecordManager.cpp src/FileHandler.cpp src/Utils.cpp src/main.cpp
OBJ      = $(SRC:.cpp=.o)

# ─── Build the main executable ─────────────────────────────────────────────────
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ─── Run the program ───────────────────────────────────────────────────────────
run: all
	./$(TARGET)

# ─── Build and run unit tests ─────────────────────────────────────────────────
test:
	$(CXX) $(CXXFLAGS) -o tests/test_runner \
		tests/test_runner.cpp \
		src/Student.cpp src/RecordManager.cpp src/FileHandler.cpp src/Utils.cpp
	./tests/test_runner

# ─── Remove all compiled objects ──────────────────────────────────────────────
clean:
	del /Q src\*.o tests\*.exe StudentRecordSystem.exe 2>nul || true

.PHONY: all run test clean
