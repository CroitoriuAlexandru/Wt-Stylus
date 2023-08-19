# Compiler settings
CC = g++
CXXFLAGS = -std=c++14 -I. -DICE_CPP11_MAPPING

# Makefile settings
APPNAME = app
EXT = .cpp
SRCDIR = ./src
OBJDIR = ./src/obj
DBONAME = test.db
# Linking lib
LDFLAGS =  -lpthread -lboost_filesystem -lboost_regex

# Runtime lib
RLIB = 


############## Creating variables #############
SRC = $(wildcard $(SRCDIR)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)
DEP = $(OBJ:$(OBJDIR)/%.o=$(OBJDIR)/%.d)

########################################################################
####################### Targets beginning here #########################
########################################################################

all: $(APPNAME)

# Builds the app
$(APPNAME): $(OBJ) 
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Creates the dependecy rules
$(OBJDIR)/%.d: $(SRCDIR)/%$(EXT)
	@$(CXX) $(CXXFLAGS) $< -MM -MT $(@:.d=.o) >$@

$(OBJDIR)/%.d: $(SRCDIR_TAIWIND_CONFIG)/%$(EXT)
	@$(CXX) $(CXXFLAGS) $< -MM -MT $(@:.d=.o) >$@

# Includes all .h files
-include $(DEP)

# Building rule for .o files and its .c/.cpp in combination with all .h
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT) 
	$(CC) $(CXXFLAGS) -o $@ -c $<

################## Run #################
run:
	./$(APPNAME) $(RLIB)

dbg:
	gdb ./$(APPNAME)

################### Cleaning rules ###################
# Cleans complete project
.PHONY: clean
clean:
	$(RM) $(APPNAME) $(DEP) $(OBJ) $(DBONAME) 

################### Display variables ###################
displayVariables:
	@echo $(SRC)
	@echo $(OBJ)
	@echo $(DEP)

################### Tailwind commands ###################
startTailwind: buildTailwindModules
	cd resources/themes/tailwind && npx tailwindcss -i ./src/input.css -o ./dist/tailwind.css --watch


buildTailwindModules:
ifneq ("$(wildcard ./resources/tailwind/node_modules)","")
	@echo "Tailwind modules already installed"
else
	@echo "Installing Tailwind modules"
	cd resources/themes/tailwind && npm install
endif
	