CUDA_ROOT_DIR=/usr/local/cuda
FOLLY_INSTALL_DIR=/tmp/fbcode_builder_getdeps-ZdataZpgera6Zfolly_21ZbuildZfbcode_builder/installed/folly
FMT_INSTALL_DIR=/tmp/fbcode_builder_getdeps-ZdataZpgera6Zfolly_21ZbuildZfbcode_builder/installed/fmt-AS4JqJuYTUiemi53HpVR8Xdlt8rYq3PrJ0361wUyD3s/
CXX = /usr/bin/clang++-10
CXXFLAGS = --std=c++17 -O3 -fPIC -fopenmp -Wall -I$(FOLLY_INSTALL_DIR)/include
LDFLAGS= -fopenmp=libiomp5 -L$(FOLLY_INSTALL_DIR)/lib -L$(FMT_INSTALL_DIR)/lib
LDLIBS= -lstdc++fs -lglog -lfolly -ldouble-conversion -lcrypto -lboost_program_options -ldl -lfmt

# NVCC compiler options:
NVCC=/usr/local/cuda/bin/nvcc
NVCC_FLAGS= -lineinfo -O3 --expt-relaxed-constexpr -ccbin=$(CXX) --std=c++17\
	    -Xcompiler -O3,-fPIC,-fopenmp,-Wall,-Wno-unused-function,-I$(FOLLY_INSTALL_DIR)/include
NVCC_LIBS=

# CUDA library directory:
CUDA_LIB_DIR= -L$(CUDA_ROOT_DIR)/lib64
# CUDA include directory:
CUDA_INC_DIR= -I$(CUDA_ROOT_DIR)/include
# CUDA linking libraries:
CUDA_LINK_LIBS= -lcudart

MKDIR_P = mkdir -p
# Final binary
BIN = ef_bfs 
# Put all auto generated stuff to this build dir.
SRC_DIR = ./src
BUILD_DIR = ./build

# List of all .cpp source files.
CPP = $(wildcard $(SRC_DIR)/*.cpp)
CU = $(wildcard $(SRC_DIR)/*.cu)

# All .o files go to build dir.
OBJ = $(CPP:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o) $(CU:$(SRC_DIR)/%.cu=$(BUILD_DIR)/%.o)

# Gcc/Clang will create these .d files containing dependencies.
DEP = $(OBJ:%.o=%.d)

# Default target named after the binary.
all: directories $(BIN)

directories: ${BUILD_DIR}

${BUILD_DIR}:
	${MKDIR_P} ${BUILD_DIR}

# Actual target of the binary - depends on all .o files.
$(BIN) : $(OBJ)
	$(CXX) $(LDFLAGS) $^ -o $@ $(LDLIBS) $(CUDA_LIB_DIR) $(CUDA_LINK_LIBS)

# Include all .d files
-include $(DEP)

# Build target for every single object file.
# The potential dependency on header files is covered
# by calling `-include $(DEP)`.
$(BUILD_DIR)/%.o : $(SRC_DIR)/%.cpp
# The -MMD flags additionaly creates a .d file with
# the same name as the .o file.
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.cu
# The -MMD flags additionaly creates a .d file with
# the same name as the .o file.
	$(NVCC) $(NVCC_FLAGS) -MMD -c $< -o $@ $(NVCC_LIBS)


.PHONY : clean directories
clean :
	-rm -f $(BIN) $(OBJ) $(DEP)
