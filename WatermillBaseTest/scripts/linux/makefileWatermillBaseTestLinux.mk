# http://make.mad-scientist.net/papers/how-not-to-use-vpath/

###################
###	compiler	###
###################
CXX := g++

###################
###	executable	###
###################
progs   := WatermillBaseTest

root_dir := ../..

prog_output_dir := $(root_dir)/settings/make/Debug_Linux_Make
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
include_dirs += -I"/usr/include/freetype2/"

# -g3 debugger level3
CXXFLAGS := -Wall -std=c++0x -g3 -MMD -MP $(include_dirs)

#######################
###	linker flags	###
#######################
# -lWatermillBase MUST be included before -lBaseGame
# when -lBaseGame is included before -lWatermillBase then undefined reference errors occur
LDLIBS := -lWatermillBase
LDLIBS += -lBaseGame
LDLIBS += -llua
LDLIBS += -lboost_system
LDLIBS += -lboost_filesystem
LDLIBS += -lboost_locale
LDLIBS += -lboost_log
LDLIBS += -lboost_thread
LDLIBS += -lboost_log_setup
LDLIBS += -lboost_iostreams
LDLIBS += -lboost_unit_test_framework

LDLIBS += -lglfw
LDLIBS += -ljpeg
LDLIBS += -lGLEW
LDLIBS += -lpng16
LDLIBS += -lfreetype

LDLIBS += -lGL

LDLIBS += -lpthread
LDLIBS += -ldl

lib_path := -L$(root_dir)/../WatermillBase/settings/make/Debug_Linux_Make
lib_path += -L$(root_dir)/../BaseGame/settings/make/Debug_Linux_Make
# lib_path += -L"../../../libraries/freeglut/lib/x64"
#lib_path += -L"/usr/local/lib"

LDFLAGS := $(lib_path) $(LDLIBS)

###########################
###	pre installation	###
###########################
#copy_files := $(prog_output_dir)/libzstd.dll $(prog_output_dir)/freeglut.dll $(prog_output_dir)/watermill.ini
#copy_files := $(prog_output_dir)/libzstd.dll  $(prog_output_dir)/watermill.ini
copy_files :=  $(prog_output_dir)/watermill.ini


###################
###	recipies	###
###################
all: createDir $(objprog)

force: createDir cleanExe $(objprog)

###################################
###	pre installation receipies	###
###################################
createDir: $(objdir) $(copy_files)

$(objdir):
	mkdir -p $(objdir)

$(prog_output_dir)/libzstd.dll: $(root_dir)/../../libraries/libzstd/libzstd.dll
	cp -f $< $@

#$(prog_output_dir)/freeglut.dll: $(root_dir)/../../libraries/freeglut/bin/x64/freeglut.dll
#	cp -f $< $@

$(prog_output_dir)/watermill.ini: $(root_dir)/watermill_release.ini
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

#######################
###	debug receipies	###
#######################
.PHONY: debugPrint debugPrint1 debugPrint2

debugPrint:
	@echo 'SHOW sourcedir';
	@echo $(sourcedir);
	@echo;

debugPrint1:
	@echo 'SHOW sourcedir';
	@echo $(sourcedir);
	@echo;
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


	

	

