CC = gcc
CXX = g++
# Added -I./adaptive_mpc_wrapper to CFLAGS and CXXFLAGS
CFLAGS = -std=c11 -Wall -I. -I./adaptive_mpc_wrapper -I./headers
CXXFLAGS = -std=c++11 -Wall -I. -I./adaptive_mpc_wrapper -I./headers
TARGET = test
BUILD_DIR = build
LDFLAGS = -lm   # Link math library for MPC calculations

# 1. Update source paths to adaptive_mpc_wrapper
C_SRCS = $(wildcard *.c) \
         $(wildcard adaptive_mpc_wrapper/*.c) \
         $(wildcard headers/*.c)      

CPP_SRCS = $(wildcard *.cpp) \
           $(wildcard adaptive_mpc_wrapper/*.cpp) \
           $(wildcard headers/*.cpp)       

C_OBJS = $(addprefix $(BUILD_DIR)/, $(notdir $(C_SRCS:.c=.o)))
CPP_OBJS = $(addprefix $(BUILD_DIR)/, $(notdir $(CPP_SRCS:.cpp=.o)))
OBJS = $(C_OBJS) $(CPP_OBJS)

$(TARGET): $(OBJS) | $(BUILD_DIR)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# --- Rules ---

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# 2. Updated rule for adaptive_mpc_wrapper C files
$(BUILD_DIR)/%.o: adaptive_mpc_wrapper/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: headers/%.c | $(BUILD_DIR)    
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 3. Updated rule for adaptive_mpc_wrapper CPP files
$(BUILD_DIR)/%.o: adaptive_mpc_wrapper/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: headers/%.cpp | $(BUILD_DIR)  
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: clean