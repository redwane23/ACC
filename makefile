# --- 1. OS Detection ---
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
    INCLUDES = -I/opt/homebrew/include
    LIB_PATHS = -L/opt/homebrew/lib
    KAFKA_LIBS = -lrdkafkacpp -lrdkafka
else
    INCLUDES =
    LIB_PATHS =
    KAFKA_LIBS = -lrdkafkacpp -lrdkafka -lrt -lpthread
endif

# --- 2. Compiler & Flags ---
CC = gcc
CXX = g++
TARGET = test
BUILD_DIR = build

CFLAGS = -std=c11 -Wall -I. -I./adaptive_mpc_wrapper -I./headers -I./module $(INCLUDES)
CXXFLAGS = -std=c++17 -Wall -I. -I./adaptive_mpc_wrapper -I./headers -I./module $(INCLUDES)
LDFLAGS = -lm $(LIB_PATHS) $(KAFKA_LIBS) -lpthread

# --- 3. Source Discovery (Recursive-style) ---
C_SRCS = $(wildcard *.c) \
         $(wildcard adaptive_mpc_wrapper/*.c) \
         $(wildcard headers/*.c) \
         $(wildcard modules/*.c) 

CPP_SRCS = $(wildcard *.cpp) \
           $(wildcard adaptive_mpc_wrapper/*.cpp) \
           $(wildcard headers/*.cpp) \
           $(wildcard modules/*.cpp)

# This creates object paths that mirror the source folder structure inside build/
C_OBJS = $(C_SRCS:%.c=$(BUILD_DIR)/%.o)
CPP_OBJS = $(CPP_SRCS:%.cpp=$(BUILD_DIR)/%.o)
OBJS = $(C_OBJS) $(CPP_OBJS)

# --- 4. Build Rules ---
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Universal rule for C files (creates subfolders automatically)
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Universal rule for CPP files (creates subfolders automatically)
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: clean
