# Define the compiler and the linker. The linker must be defined since
# the implicit rule for linking uses CC as the linker. g++ can be
# changed to clang++.
CXX = g++
CC  = $(CXX)

# Generate dependencies in *.d files
DEPFLAGS = -MT $@ -MMD -MP -MF $*.d

# Define preprocessor, compiler, and linker flags. Uncomment the # lines
# if you use clang++ and wish to use libc++ instead of GNU's libstdc++.
# -g is for debugging.
CPPFLAGS = -std=c++17 -I.
#CPPFLAGS = -std=c++17 -I. -I../external
CXXFLAGS =  -O2 -Wall -Wextra -pedantic-errors -Wold-style-cast 
CXXFLAGS += -std=c++17 
CXXFLAGS += -g
CXXFLAGS += $(DEPFLAGS)
LDFLAGS = -g -lstdc++fs
#CPPFLAGS += -stdlib=libc++
#CXXFLAGS += -stdlib=libc++
#LDFLAGS +=  -stdlib=libc++
BIN_DIR := ../bin
EXE_FILES := $(PROGS)

$(BIN_DIR)/%: %
	@mkdir -p $(BIN_DIR)
	mv $< $@
# Targetsm
PROGS = myClient myServer

all: $(PROGS)

# Targets rely on implicit rules for compiling and linking
#testArticle: testArticle.o article.o
myClient: myClient.o connection.o client_commanddecoder.o client_commandhandler.o messagehandler.o logger.o

myServer: myServer.o article.o commandhandler.o connection.o databaseDS.o databaseMS.o databaseserver.o interface.o logger.o messagehandler.o server.o servercommandhandler.o 	
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

install:
	@mkdir -p $(BIN_DIR)
	@mv -f myClient $(BIN_DIR)/myClient
	@mv -f myServer $(BIN_DIR)/myServer

# Phony targets
.PHONY: all test install clean distclean

# Standard clean
clean:
	rm -f *.o $(PROGS)

distclean: clean
	rm *.d


# Include the *.d files
SRC = $(wildcard *.cc)
-include $(SRC:.cc=.d)
