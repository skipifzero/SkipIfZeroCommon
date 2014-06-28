CC = clang++
#Add "-g" to enable debugging.
DEBUG =
LFLAGS = -Wall -Wno-c++11-extensions -std=c++11 -pthread -O3 -o $(DEBUG)
TEST_LFLAGS = -Wall -Wno-c++11-extensions -std=c++11 -pthread -O0 -o $(DEBUG)
CFLAGS = -Wall -Wno-c++11-extensions -std=c++11 -pthread -O3 -c -o $(DEBUG)

# Subdirectories
SFZ_SUB = sfz/
ALGO_SUB = algo/
SFZ_ALGO_SUB = $(SFZ_SUB)$(ALGO_SUB)
MATH_SUB = math/
SFZ_MATH_SUB = $(SFZ_SUB)$(MATH_SUB)
UTIL_SUB = util/
SFZ_UTIL_SUB = $(SFZ_SUB)$(UTIL_SUB)

# Source paths
SRC_DIR = src/
SRC_SFZ_DIR = $(SRC_DIR)$(SFZ_SUB)
SRC_SFZ_ALGO_DIR = $(SRC_DIR)$(SFZ_ALGO_SUB)
SRC_SFZ_MATH_DIR = $(SRC_DIR)$(SFZ_MATH_SUB)
SRC_SFZ_UTIL_DIR = $(SRC_DIR)$(SFZ_UTIL_SUB)

# Test paths
TEST_DIR = tests/
TEST_SFZ_DIR = $(TEST_DIR)$(SFZ_SUB)
TEST_SFZ_ALGO_DIR = $(TEST_DIR)$(SFZ_ALGO_SUB)
TEST_SFZ_MATH_DIR = $(TEST_DIR)$(SFZ_MATH_SUB)
TEST_SFZ_UTIL_DIR = $(TEST_DIR)$(SFZ_UTIL_SUB)

# Build paths
BUILD_DIR = build/
BUILD_SFZ_DIR = $(BUILD_DIR)$(SFZ_SUB)
BUILD_SFZ_ALGO_DIR = $(BUILD_DIR)$(SFZ_ALGO_SUB)
BUILD_SFZ_MATH_DIR = $(BUILD_DIR)$(SFZ_MATH_SUB)
BUILD_SFZ_UTIL_DIR = $(BUILD_DIR)$(SFZ_UTIL_SUB)


# Compilation units
OBJS = $(BUILD_SFZ_ALGO_DIR)SortingPerfTest.o $(BUILD_SFZ_UTIL_DIR)StopWatch.o $(BUILD_SFZ_UTIL_DIR)ScopedThread.o

$(BUILD_SFZ_ALGO_DIR)SortingPerfTest.o: $(SRC_SFZ_ALGO_DIR)SortingPerfTest.cpp $(SRC_SFZ_ALGO_DIR)SortingPerfTest.hpp $(SRC_SFZ_ALGO_DIR)Sorting.hpp $(SRC_SFZ_ALGO_DIR)Sorting.inl $(SRC_SFZ_UTIL_DIR)StopWatch.hpp $(SRC_SFZ_UTIL_DIR)ThreadPool.hpp $(SRC_SFZ_UTIL_DIR)ThreadPool.inl $(SRC_SFZ_UTIL_DIR)BlockingQueue.hpp $(SRC_SFZ_UTIL_DIR)BlockingQueue.inl
	@mkdir -p $(BUILD_SFZ_ALGO_DIR)
	$(CC) $(CFLAGS) $@ $<
	@echo ""

$(BUILD_SFZ_UTIL_DIR)StopWatch.o: $(SRC_SFZ_UTIL_DIR)StopWatch.cpp $(SRC_SFZ_UTIL_DIR)StopWatch.hpp
	@mkdir -p $(BUILD_SFZ_UTIL_DIR)
	$(CC) $(CFLAGS) $@ $<
	@echo ""

$(BUILD_SFZ_UTIL_DIR)ScopedThread.o: $(SRC_SFZ_UTIL_DIR)ScopedThread.cpp $(SRC_SFZ_UTIL_DIR)ScopedThread.hpp
	@mkdir -p $(BUILD_SFZ_UTIL_DIR)
	$(CC) $(CFLAGS) $@ $<
	@echo ""

# Binaries
MAIN_BIN = $(BUILD_DIR)MainBin.out
$(MAIN_BIN): $(OBJS) $(SRC_DIR)Main.cpp $(SRC_SFZ_DIR)Math.hpp $(SRC_SFZ_MATH_DIR)Vector.hpp $(SRC_SFZ_MATH_DIR)Vector.inl $(SRC_SFZ_MATH_DIR)MathConstants.hpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(LFLAGS) $@ $(SRC_DIR)Main.cpp $(OBJS)
	@echo ""

# Test binaries
$(BUILD_DIR)MathConstants_Tests.out: $(MAIN_BIN) $(OBJS) $(TEST_SFZ_MATH_DIR)MathConstants_Tests.cpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(TEST_LFLAGS) $@ $(TEST_SFZ_MATH_DIR)MathConstants_Tests.cpp
	@echo ""

$(BUILD_DIR)Vector_Tests.out: $(MAIN_BIN) $(OBJS) $(TEST_SFZ_MATH_DIR)Vector_Tests.cpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(TEST_LFLAGS) $@ $(TEST_SFZ_MATH_DIR)Vector_Tests.cpp
	@echo ""

$(BUILD_DIR)BlockingQueue_Tests.out: $(MAIN_BIN) $(OBJS) $(TEST_SFZ_UTIL_DIR)BlockingQueue_Tests.cpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(TEST_LFLAGS) $@ $(TEST_SFZ_UTIL_DIR)BlockingQueue_Tests.cpp
	@echo ""

# Commands
# Builds the project
all: $(MAIN_BIN)

# Builds and runs the project
run: all
	./$(MAIN_BIN)

# Builds and runs tests
tests: all $(BUILD_DIR)MathConstants_Tests.out $(BUILD_DIR)Vector_Tests.out $(BUILD_DIR)BlockingQueue_Tests.out
	./$(BUILD_DIR)MathConstants_Tests.out
	./$(BUILD_DIR)Vector_Tests.out
	./$(BUILD_DIR)BlockingQueue_Tests.out

# Cleans the project from built files
clean:
	$(RM) -r $(BUILD_DIR)