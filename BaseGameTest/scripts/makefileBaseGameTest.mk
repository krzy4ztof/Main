# http://make.mad-scientist.net/papers/how-not-to-use-vpath/

###################
###	compiler	###
###################
CXX := g++

###################
###	executable	###
###################
progs   := BaseGameTest.exe

root_dir := ..

prog_output_dir := $(root_dir)/settings/make/BaseGameTest/Debug_MinGW64
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
include_dirs += -I"/usr/local/include"

# -g3 debugger level3
CXXFLAGS := -Wall -g3 -MMD -MP $(include_dirs) 

#######################
###	linker flags	###
#######################

LDLIBS := -lBaseGame
LDLIBS += -lfreeglut
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
LDLIBS += -lboost_unit_test_framework-mt

lib_path := -L"../../BaseGame/Debug_MinGW64" 
lib_path += -L"../../../libraries/freeglut/lib/x64"
lib_path += -L"/usr/local/lib"

LDFLAGS := $(lib_path) $(LDLIBS)

###########################
###	pre installation	###
###########################
copy_files := $(prog_output_dir)/freeglut.dll $(prog_output_dir)/watermill.ini

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


$(prog_output_dir)/freeglut.dll: $(root_dir)/../../libraries/freeglut/bin/x64/freeglut.dll
	cp -f $< $@

$(prog_output_dir)/watermill.ini: $(root_dir)/../Watermill/settings/eclipse/Watermill/watermill_release.ini
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


	

	

