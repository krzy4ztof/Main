# http://make.mad-scientist.net/papers/how-not-to-use-vpath/

###################
###	compiler	###
###################
CXX := g++

###############
###	library	###
###############
progs := libBaseGame.a

root_dir := ../..
lib_output_dir := ${root_dir}/Debug_Linux_Make

objprog := $(addprefix $(lib_output_dir)/, $(progs))

#######################
### object files	###
#######################
root_source := $(root_dir)/source

full_objects := $(shell find $(root_source) -name "*.cpp")
cpp_objects := $(notdir $(full_objects))
objects := $(cpp_objects:%.cpp=%.o)

objdir := $(lib_output_dir)/make_obj

###################
###	cpp files	###
###################
source_dir_all := $(shell find $(root_source) -type d)
VPATH := $(source_dir_all)

#######################
###	compiler flags	###
#######################
# -g3 debugger level3
include_dirs += -I"/mingw64/include/freetype2/"

#CXXFLAGS := -Wall -std=c++0x -g3 -MMD -MP 
CXXFLAGS := -Wall -std=c++0x -g3 -MMD -MP $(include_dirs) 

###################
###	recipies	###
###################
all: createDir $(objprog)

force: createDir $(objprog)

###################################
###	pre installation receipies	###
###################################
createDir: $(objdir)

$(objdir):
	mkdir -p $(objdir)

###########################
###	compile receipies	###
###########################
$(objdir)/%.o : %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(objprog): $(addprefix $(objdir)/, $(objects))
	ar -r $@ $^

#######################
###	clean receipe	###
#######################

clean:
	rm -rf $(lib_output_dir)/*
	
#######################
###	debug receipies	###
#######################
.PHONY: debugPrint2 debugPrint

debugPrint:
	@echo 'SHOW full_objects';
	@echo $(full_objects);
	@echo;
	@echo 'SHOW cpp_objects';
	@echo $(cpp_objects);
	@echo;
	@echo 'SHOW objects';
	@echo $(objects);
	@echo;
	@echo 'SHOW source_dir_all';
	@echo $(source_dir_all);
	@echo;
	@echo 'SHOW VPATH';
	@echo $(VPATH);
	@echo;


debugPrint2:
	@echo 'SHOW Link.opp';
	@echo $(LINK.opp);
	@echo;
	@echo 'SHOW Link.o';
	@echo $(LINK.o);
	@echo;
	@echo 'SHOW objects';
	@echo $(objects);
	@echo;	
	@echo 'SHOW VPATH';
	@echo $(VPATH);
	@echo;	
	@echo 'SHOW Link.o';
	@echo $(LINK.o);
	@echo;
	@echo 'SHOW COMPILE.c';
	@echo $(COMPILE.c);
	@echo;
	@echo 'SHOW COMPILE.cpp';
	@echo $(COMPILE.cpp);
	@echo;
