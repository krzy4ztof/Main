# http://make.mad-scientist.net/papers/how-not-to-use-vpath/

###################
###	compiler	###
###################
CXX := g++

###################
###	executable	###
###################
progs   := Watermill

root_dir := ../..

prog_output_dir := $(root_dir)/settings/make/Watermill/Debug_Linux_Make
objprog := $(addprefix $(prog_output_dir)/, $(progs))

#######################
### object files	###
#######################
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
# -g3 debugger level3
CXXFLAGS := -Wall -std=c++0x -g3 -MMD -MP

#include_dirs += -I"/mingw64/include/freetype2/"
#CXXFLAGS := -Wall -std=c++0x -g3 -MMD -MP $(include_dirs)

#######################
###	linker flags	###
#######################
LDLIBS := -lBaseGame
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
#LDLIBS += -lglfw3
#LDLIBS += -ljpeg
LDLIBS += -lglfw
#LDLIBS += -lpng16
#LDLIBS += -lfreetype

#GLFW_LIB := `pkg-config --cflags glfw3`

lib_path := -L$(root_dir)/../BaseGame/Debug_Linux_Make
#lib_path += -L"/usr/lib/x86_64-linux-gnu"

LDFLAGS := $(lib_path) $(LDLIBS) 

#$(GLFW_LIB)

###########################
###	pre installation	###
###########################
copy_files :=  $(prog_output_dir)/watermill.ini

###################
###	recipies	###
###################
all: createDir $(objprog)

###################################
###	pre installation receipies	###
###################################
createDir: $(objdir) $(copy_files)

$(objdir):
	mkdir -p $(objdir)

$(prog_output_dir)/watermill.ini: $(root_dir)/settings/eclipse/Watermill/watermill_release.ini
	cp -f $< $@

#######################
###	force receipies	###
#######################
cleanExe:
	rm -f $(objprog)

###########################
###	compile receipies	###
###########################
$(objdir)/%.o : %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@
	
$(objprog): $(addprefix $(objdir)/, $(objects)) 
	$(CXX) $^ $(LDFLAGS) -o $@

#######################
###	clean receipe	###
#######################
clean:
	rm -rf $(prog_output_dir)/* 

force: createDir cleanExe $(objprog)

#######################
###	debug receipies	###
#######################
.PHONY: debugPrint debugPrint2

#SHOW Link.o
#g++ -L../../BaseGame/scripts/obj -L../../../libraries/freeglut/lib/x64 -L/mingw64/lib -L/mingw64/x86_64-w64-mingw32/lib -L/usr/local/lib -lBaseGame5 -lfreeglut -lpsapi -lopengl32 -llua -lboost_system-mt -lboost_filesystem-mt -lboost_locale-mt -lboost_log-mt -lboost_thread-mt -lboost_log_setup-mt -lboost_iostreams-mt
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
	@echo 'SHOW Link.o';
	@echo $(LINK.o);
	@echo;
	@echo 'SHOW COMPILE.c';
	@echo $(COMPILE.c);
	@echo;
	@echo 'SHOW COMPILE.cpp';
	@echo $(COMPILE.cpp);
	@echo;
