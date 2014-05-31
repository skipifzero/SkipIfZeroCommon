CC = clang++
#Add "-g" to enable debugging.
DEBUG =
LFLAGS = -Wall -std=c++11 -pthread -O3 -o $(DEBUG)
TEST_LFLAGS = -Wall -std=c++11 -pthread -O0 -o $(DEBUG)
CFLAGS = -Wall -std=c++11 -pthread -O3 -c -o $(DEBUG)

# Subdirectories
SFZ_SUB = sfz/
MATH_SUB = math/

# Source paths
SRC_DIR = src/
SRC_SFZ_DIR = $(SRC_DIR)$(SFZ_SUB)
SRC_SFZ_MATH_DIR = $(SRC_SFZ_DIR)$(MATH_SUB)

TEST_DIR = tests/
TEST_SFZ_DIR = $(TEST_DIR)$(SFZ_SUB)
TEST_SFZ_MATH_DIR = $(TEST_SFZ_DIR)$(MATH_SUB)

BUILD_DIR = build/

OBJS =

# Binaries
MAIN_BIN = $(BUILD_DIR)MainBin.out
#TESTS_BIN = $(BUILD_DIR)Tests.out

$(MAIN_BIN): $(OBJS) $(SRC_DIR)Main.cpp $(SRC_SFZ_DIR)Math.hpp $(SRC_SFZ_MATH_DIR)Vector.hpp $(SRC_SFZ_MATH_DIR)Vector.inl $(SRC_SFZ_MATH_DIR)MathUtils.hpp
	mkdir -p $(BUILD_DIR)
	$(CC) $(LFLAGS) $@ $(SRC_DIR)Main.cpp $(OBJS)
	@echo ""


# Test binaries
$(BUILD_DIR)MathUtils_Tests.out: $(MAIN_BIN) $(OBJS) $(TEST_SFZ_MATH_DIR)MathUtils_Tests.cpp
	mkdir -p $(BUILD_DIR)
	$(CC) $(TEST_LFLAGS) $@ $(TEST_SFZ_MATH_DIR)MathUtils_Tests.cpp
	@echo ""

$(BUILD_DIR)Vector_Tests.out: $(MAIN_BIN) $(OBJS) $(TEST_SFZ_MATH_DIR)Vector_Tests.cpp
	mkdir -p $(BUILD_DIR)
	$(CC) $(TEST_LFLAGS) $@ $(TEST_SFZ_MATH_DIR)Vector_Tests.cpp
	@echo ""


#$(TESTS_BIN): $(MAIN_BIN) $(OBJS) $(TEST_DIR)catch.hpp $(TEST_DIR)Tests.cpp $(TEST_SFZ_MATH_DIR)Vector_Tests.inl $(TEST_SFZ_MATH_DIR)MathUtils_Tests.inl
#	mkdir -p $(BUILD_DIR)
#	$(CC) $(TEST_LFLAGS) $@ $(TEST_DIR)Tests.cpp $(OBJS) 
#	@echo ""


# Compilation units
# $(BUILD_DIR)Main.o: $(SRC_DIR)Main.cpp $(SRC_SFZ_DIR)Math.hpp $(SRC_SFZ_MATH_DIR)VectorN.hpp $(SRC_SFZ_MATH_DIR)VectorN.inl
#	mkdir -p $(BUILD_DIR)
#	$(CC) $(CFLAGS) $@ $<


# Commands
# Builds the project
all: $(MAIN_BIN)

# Builds and runs the project
run: all
	./$(MAIN_BIN)

# Builds and runs tests
tests: all $(BUILD_DIR)MathUtils_Tests.out $(BUILD_DIR)Vector_Tests.out
	@echo "Running MathUtils tests"
	./$(BUILD_DIR)MathUtils_Tests.out
	@echo "Running Vector tests"
	./$(BUILD_DIR)Vector_Tests.out

# Cleans the project from built files
clean:
	$(RM) -r $(BUILD_DIR)