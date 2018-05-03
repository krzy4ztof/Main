# http://make.mad-scientist.net/papers/how-not-to-use-vpath/

###################
###	compiler	###
###################
<<<<<<< HEAD
=======

>>>>>>> master
CXX := g++

###################
###	executable	###
###################
<<<<<<< HEAD
=======

>>>>>>> master
progs   := Watermill

root_dir := ../..

prog_output_dir := $(root_dir)/settings/make/Watermill/Debug_Linux_Make
<<<<<<< HEAD
=======
#prog_output_dir := $(root_dir)/settings/eclipse/Watermill/Debug_MinGW64
>>>>>>> master
objprog := $(addprefix $(prog_output_dir)/, $(progs))

#######################
### object files	###
#######################
<<<<<<< HEAD
=======

>>>>>>> master
sourcedir := $(root_dir)/source/

#objects = Main.o GameMain.o WatermillGame.o WatermillLogic.o
full_objects := $(shell find $(sourcedir) -name *.cpp)
cpp_objects := $(notdir $(full_objects))
objects := $(cpp_objects:%.cpp=%.o)

objdir := $(prog_output_dir)/make_obj

###################
###	cpp files	###
###################
source_dir_all := $(shell find $(sourcedir) -type d)
VPATH = $(source_dir_all)

#######################
###	compiler flags	###
#######################
<<<<<<< HEAD
# -g3 debugger level3
CXXFLAGS := -Wall -std=c++0x -g3 -MMD -MP

#######################
###	linker flags	###
#######################
LDLIBS := -lBaseGame
=======

#include_dirs := -I"../../BaseGame/source" 
#include_dirs += -I"../../../libraries/freeglut/include"
#include_dirs += -I"/mingw64/include"
#include_dirs += -I"/mingw64/x86_64-w64-mingw32/include"
#include_dirs += -I"/usr/local/include"

# -g3 debugger level3
#CXXFLAGS := -Wall -std=c++0x -g3 -MMD -MP $(include_dirs) 
CXXFLAGS := -Wall -std=c++0x -g3 -MMD -MP


#######################
###	linker flags	###
#######################

#pthread
#dl

#glut
#(link to \usr\lib\x86_64-linux-gnu\libglut.a)
#GL
#(link to \usr\lib\x86_64-linux-gnu\libGL.so)
#GLU
#(link to \usr\lib\x86_64-linux-gnu\libGLU.a)


#lua
#(link to \usr\local\lib\liblua.a)


#-lBaseGame -llua -lglut -lGL -lGLU -lboost_system -lboost_filesystem -lboost_locale -lboost_log -lboost_thread -lboost_log_setup -lboost_iostreams -lpthread -ldl 

LDLIBS := -lBaseGame
#LDLIBS += -lfreeglut
#LDLIBS += -lpsapi
#LDLIBS += -lopengl32
>>>>>>> master
LDLIBS += -llua
LDLIBS += -lglut
LDLIBS += -lGL
LDLIBS += -lGLU
LDLIBS += -lboost_system
LDLIBS += -lboost_filesystem
LDLIBS += -lboost_locale
LDLIBS += -lboost_log
LDLIBS += -lboost_thread
LDLIBS += -lboost_log_setup
LDLIBS += -lboost_iostreams
LDLIBS += -lpthread
LDLIBS += -ldl

lib_path := -L$(root_dir)/../BaseGame/Debug_Linux_Make
<<<<<<< HEAD

LDFLAGS := $(lib_path) $(LDLIBS)

###########################
###	pre installation	###
###########################
=======
#lib_path += -L"$(root_dir)/../../libraries/freeglut/lib/x64"
#lib_path += -L"/mingw64/lib"
#lib_path += -L"/mingw64/x86_64-w64-mingw32/lib"

#lua
#lib_path += -L"/usr/local/lib"

#libdl.so
#lib_path += -L"/usr/lib/x86_64-linux-gnu"



#/usr/bin/ld: //usr/local/lib/liblua.a(loadlib.o): undefined reference to symbol 'dlclose@@GLIBC_2.2.5'
#makefileWatermillLinux.mk:146: recipe for target '../../settings/make/Watermill/Debug_Linux/Watermill' failed
#/usr/lib/x86_64-linux-gnu/libdl.so: error adding symbols: DSO missing from command line
#collect2: error: ld returned 1 exit status
#make: *** [../../settings/make/Watermill/Debug_Linux/Watermill] Error 1


#/usr/bin/ld: //usr/local/lib/liblua.a(loadlib.o): undefined reference to symbol 'dlclose@@GLIBC_2.2.5'
#/usr/lib/gcc/x86_64-linux-gnu/5/../../../x86_64-linux-gnu/libdl.so: error adding symbols: DSO missing from command line
#collect2: error: ld returned 1 exit status
#makefileWatermillLinux.mk:153: recipe for target '../../settings/make/Watermill/Debug_Linux/Watermill' failed
#make: *** [../../settings/make/Watermill/Debug_Linux/Watermill] Error 1

LDFLAGS := $(lib_path) $(LDLIBS)


### DEFAULT CDT BUILD

#g++ -std=c++0x -I/home/krzysztof/home/projects/Main/BaseGame -I/usr/local/include -O0 -g3 -Wall -c -fmessage-length=0 -o source/main/GameMain.o ../../../../source/main/GameMain.cpp 

#g++ -L/home/krzysztof/home/projects/Main/BaseGame -L/home/krzysztof/home/projects/Main/BaseGame/Debug_Linux -L/usr/local/lib -o Watermill 
#source/main/GameMain.o source/main/Main.o source/watermillGame/WatermillGame.o source/watermillGame/WatermillLogic.o 
#-lBaseGame -llua -lglut -lGL -lGLU -lboost_system -lboost_filesystem -lboost_locale -lboost_log -lboost_thread -lboost_log_setup -lboost_iostreams -lpthread -ldl 

### MAKE BUILD
# g++ ../../settings/make/Watermill/Debug_Linux_Make/make_obj/WatermillGame.o ../../settings/make/Watermill/Debug_Linux_Make/make_obj/WatermillLogic.o 
# ../../settings/make/Watermill/Debug_Linux_Make/make_obj/Main.o ../../settings/make/Watermill/Debug_Linux_Make/make_obj/GameMain.o -
# L../../../BaseGame/Debug_Linux_Make 
#-lBaseGame -lglut -lGL -lGLU -ldl -lpthread -llua -lboost_system -lboost_filesystem -lboost_locale -lboost_log -lboost_thread -lboost_log_setup -lboost_iostreams 
#-o ../../settings/make/Watermill/Debug_Linux_Make/Watermill




###########################
###	pre installation	###
###########################

#copy_files := $(prog_output_dir)/freeglut.dll $(prog_output_dir)/watermill.ini
>>>>>>> master
copy_files :=  $(prog_output_dir)/watermill.ini

###################
###	recipies	###
###################
<<<<<<< HEAD
all: createDir $(objprog)
=======

all: createDir $(objprog)
#all: debugPrint createDir $(objprog)
>>>>>>> master

###################################
###	pre installation receipies	###
###################################
<<<<<<< HEAD
=======

>>>>>>> master
createDir: $(objdir) $(copy_files)

$(objdir):
	mkdir -p $(objdir)

<<<<<<< HEAD
=======

#$(prog_output_dir)/freeglut.dll: $(root_dir)/../../libraries/freeglut/bin/x64/freeglut.dll
#	cp -f $< $@
	

>>>>>>> master
$(prog_output_dir)/watermill.ini: $(root_dir)/settings/eclipse/Watermill/watermill_release.ini
	cp -f $< $@

###########################
###	compile receipies	###
###########################
<<<<<<< HEAD
=======


>>>>>>> master
$(objdir)/%.o : %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@
	
$(objprog): $(addprefix $(objdir)/, $(objects)) 
	$(CXX) $^ $(LDFLAGS) -o $@

#######################
###	clean receipe	###
#######################
<<<<<<< HEAD
clean:
	rm -rf $(prog_output_dir)/* 
=======

clean:
	rm -rf $(prog_output_dir)/* 
#	rm -rf $(objdir)/*
>>>>>>> master

#######################
###	debug receipies	###
#######################
<<<<<<< HEAD
.PHONY: debugPrint debugPrint2

=======



.PHONY: debugPrint debugPrint2


#SHOW Link.o
#g++ -L../../BaseGame/scripts/obj -L../../../libraries/freeglut/lib/x64 -L/mingw64/lib -L/mingw64/x86_64-w64-mingw32/lib -L/usr/local/lib -lBaseGame5 -lfreeglut -lpsapi -lopengl32 -llua -lboost_system-mt -lboost_filesystem-mt -lboost_locale-mt -lboost_log-mt -lboost_thread-mt -lboost_log_setup-mt -lboost_iostreams-mt
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
<<<<<<< HEAD
=======
	
	
	
>>>>>>> master

debugPrint2:
	@echo 'SHOW Link.o';
	@echo $(LINK.o);
	@echo;
	@echo 'SHOW COMPILE.c';
	@echo $(COMPILE.c);
	@echo;
	@echo 'SHOW COMPILE.cpp';
	@echo $(COMPILE.cpp);
	@echo;


	

	

