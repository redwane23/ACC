CC = gcc
CXX = g++                       # C++ compiler
CFLAGS = -std=c11 -Wall -I. -I./mpc_test_grt_rtw
CXXFLAGS = -std=c++11 -Wall -I. -I./mpc_test_grt_rtw   # Flags for C++
TARGET = test
BUILD_DIR = build

# Find all source files
C_SRCS = $(wildcard *.c) $(wildcard mpc_test_grt_rtw/*.c)
CPP_SRCS = $(wildcard *.cpp) $(wildcard mpc_test_grt_rtw/*.cpp)

# Object files go into build directory
C_OBJS = $(addprefix $(BUILD_DIR)/, $(notdir $(C_SRCS:.c=.o)))
CPP_OBJS = $(addprefix $(BUILD_DIR)/, $(notdir $(CPP_SRCS:.cpp=.o)))
OBJS = $(C_OBJS) $(CPP_OBJS)

$(TARGET): $(OBJS) | $(BUILD_DIR)
	$(CXX) $(OBJS) -o $(TARGET)          # Use C++ for linking

# Compile C files from current directory
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile C files from mpc_test_grt_rtw directory
$(BUILD_DIR)/%.o: mpc_test_grt_rtw/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile C++ files from current directory
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile C++ files from mpc_test_grt_rtw directory
$(BUILD_DIR)/%.o: mpc_test_grt_rtw/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: clean