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
<<<<<<< HEAD
# -g3 debugger level3
CXXFLAGS := -Wall -std=c++0x -g3 -MMD -MP 
=======

# boost
include_dirs := -I/home/krzysztof/home/utils/boost_1_67_0


#include_dirs := -I"/c/Users/Krzysztof/home/myImportantFiles/projects/git/Main/BaseGame/source" 
#include_dirs += -I"/c/Users/Krzysztof/home/myImportantFiles/projects/git/libraries/freeglut/include"
#include_dirs += -I"/mingw64/include"
#include_dirs += -I"/mingw64/x86_64-w64-mingw32/include"
#include_dirs += -I"/usr/local/include"

# -g3 debugger level3
#CXXFLAGS := -Wall -g3 -MMD -MP $(include_dirs) 
#CXXFLAGS := -Wall -std=c++0x -g3 -MMD -MP 

#CXXFLAGS := -Wall -std=c++0x -g3 -MMD -MP 
CXXFLAGS := -Wall -std=c++0x -g3 -MMD -MP $(include_dirs) 

>>>>>>> master

#######################
###	linker flags	###
#######################

LDLIBS := -lfreeglut
LDLIBS += -lpsapi
LDLIBS += -lopengl32
LDLIBS += -llua
LDLIBS += -lboost_system-mt
LDLIBS += -lboost_filesystem-mt
LDLIBS += -lboost_locale-mt
LDLIBS += -lboost_log-mt
LDLIBS += -lboost_thread-mt
LDLIBS += -lboost_log_setup-mt
LDLIBS += -lboost_iostreams-mt

<<<<<<< HEAD
LDFLAGS := $(LDLIBS)
=======
#boost
lib_path := -L/home/krzysztof/home/utils/boost_1_67_0/stage/lib

#lib_path += -L"../../../libraries/freeglut/lib/x64"
#lib_path += -L"/mingw64/lib"
#lib_path += -L"/mingw64/x86_64-w64-mingw32/lib"
#lib_path += -L"/usr/local/lib"

LDFLAGS := $(lib_path) $(LDLIBS)
#LDFLAGS := $(LDLIBS)

>>>>>>> master

###################
###	recipies	###
###################
<<<<<<< HEAD
=======

#all: debugPrint $(objprog)
>>>>>>> master
all: createDir $(objprog)

###################################
###	pre installation receipies	###
###################################

createDir: $(objdir)
<<<<<<< HEAD
=======
#	mkdir -p $(objdir)
#	cp ../../../libraries/freeglut/bin/x64/freeglut.dll $(lib_output_dir)
#	cp ../settings/eclipse/Watermill/watermill_release_short2.ini $(lib_output_dir)/watermill.ini
>>>>>>> master

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

<<<<<<< HEAD
=======
#SHOW COMPILE.cpp
#g++ -Wall -MMD -MP -I../BaseGame/source -I../BaseGame/source/gameInitialization -I../BaseGame/source/gameInitialization/linux -I../BaseGame/source/gameInitialization/windows -I/c/Users/Krzysztof/home/myImportantFiles/projects/git/libraries/freeglut/include -I/mingw64/include -I/mingw64/x86_64-w64-mingw32/include -I/usr/local/include -c


>>>>>>> master
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
<<<<<<< HEAD
=======


>>>>>>> master
