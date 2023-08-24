# Compiler settings
CC = g++
CXXFLAGS = -std=c++14 -I. -DICE_CPP11_MAPPING

# Makefile settings
APPNAME = frontend
EXT = .cpp
SRCDIR = ./src
SRCDIR_TAIWIND_CONFIG = ./TailwindConfig/src
OBJDIR = ./src/obj

# Linking lib
LDFLAGS =  -lwthttp -lwt -lwtdbo -lIce++11 -lpthread -lssl -lcrypto -lboost_filesystem -lboost_regex

# Runtime lib
RLIB = --docroot . -c ./wt_config.xml --http-address 0.0.0.0 --http-port 9090


############## Creating variables #############
SRC = $(wildcard $(SRCDIR)/*$(EXT)) 
SRC_TAILWIND_CONFIG = $(wildcard $(SRCDIR_TAIWIND_CONFIG)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o) $(SRC_TAILWIND_CONFIG:$(SRCDIR_TAIWIND_CONFIG)/%$(EXT)=$(OBJDIR)/%.o)
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

$(OBJDIR)/%.o: $(SRCDIR_TAIWIND_CONFIG)/%$(EXT)
	$(CC) $(CXXFLAGS) -o $@ -c $<
	

################## Run #################
run:
	./$(APPNAME) $(RLIB)

runTrace:
	./$(APPNAME) --Ice.Trace.Network=2 $(RCMD) $(RLIB)

dbg:
	gdb ./$(APPNAME)

.PHONY: gen_obj_dir
gen_obj_dir:
	mkdir -p $(OBJDIR)

################### Cleaning rules ###################
# Cleans complete project
.PHONY: clean
clean:
	$(RM) $(APPNAME) $(DEP) $(OBJ)

cleanDependencies:
	$(RM) $(DEP)

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

################### Display variables ###################
echo:
	@echo $(DEP)