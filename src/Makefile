
# Variables for compiler and configuration flags
CXX = g++
CXXFLAGS = -I/usr/include/tbb -g
LDFLAGS = -ltbb -g

# List all target executables
TARGETS = producer_consumer hello parallel_for  parallel_for_each parallel_qsort parallel_scan parallel_pipe 

# The default rule
all: $(TARGETS)

# FIXED: Turned into a static pattern rule restricted to $(TARGETS)
$(TARGETS): % : %.o
	$(CXX) $^ -o $@ $(LDFLAGS)
	./$@

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Declare non-file targets
.PHONY: all clean

clean:
	rm -rf *.o $(TARGETS)
