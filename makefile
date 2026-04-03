CC = gcc
CXX = g++

# 1. Added Homebrew paths to Flags
CFLAGS = -std=c11 -Wall -I. -I./adaptive_mpc_wrapper -I./headers -I/opt/homebrew/include
CXXFLAGS = -std=c++17 -Wall -I. -I./adaptive_mpc_wrapper -I./headers -I/opt/homebrew/include
TARGET = test
BUILD_DIR = build

# 2. Added Kafka and Math libraries to LDFLAGS
LDFLAGS = -lm -L/opt/homebrew/lib -lrdkafka++ -lrdkafka

C_SRCS = $(wildcard *.c) \
         $(wildcard adaptive_mpc_wrapper/*.c) \
         $(wildcard headers/*.c)      

CPP_SRCS = $(wildcard *.cpp) \
           $(wildcard adaptive_mpc_wrapper/*.cpp) \
           $(wildcard headers/*.cpp)       

C_OBJS = $(addprefix $(BUILD_DIR)/, $(notdir $(C_SRCS:.c=.o)))
CPP_OBJS = $(addprefix $(BUILD_DIR)/, $(notdir $(CPP_SRCS:.cpp=.o)))
OBJS = $(C_OBJS) $(CPP_OBJS)

# 3. Fixed the target rule (Uses Tab now)
$(TARGET): $(OBJS) | $(BUILD_DIR)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# --- Rules ---

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: adaptive_mpc_wrapper/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: headers/%.c | $(BUILD_DIR)    
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: adaptive_mpc_wrapper/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: headers/%.cpp | $(BUILD_DIR)  
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: clean
