# http://make.mad-scientist.net/papers/how-not-to-use-vpath/

###################
###	compiler	###
###################
CXX := g++

###################
###	executable	###
###################
progs   := Watermill.exe
#progs   := libWatermill.a


root_dir := ..
prog_output_dir := $(root_dir)/settings/make/Debug_MinGW64
#lib_output_dir := ${root_dir}/Debug_MinGW64
objprog := $(addprefix $(prog_output_dir)/, $(progs))
#objprog := $(addprefix $(lib_output_dir)/, $(progs))

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
#include_dirs += -I"/c/Users/Krzysztof/home/myImportantFiles/projects/git/libraries/freeglut/include"
#include_dirs += -I"/usr/local/include"
include_dirs += -I"/mingw64/include/freetype2/"

# -g3 debugger level3
CXXFLAGS := -Wall -g3 -MMD -MP $(include_dirs) 

#######################
###	linker flags	###
#######################
# -lWatermillBase MUST be included before -lBaseGame
# when -lBaseGame is included before -lWatermillBase then undefined reference errors occur
LDLIBS := -lWatermillBase
LDLIBS += -lBaseGame
#LDLIBS += -lWatermillBase
#LDLIBS += -lfreeglut
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
LDLIBS += -lglfw3
LDLIBS += -ljpeg
LDLIBS += -lglew32
LDLIBS += -lpng16
LDLIBS += -lfreetype

lib_path := -L$(root_dir)/../WatermillBase/settings/make/Debug_MinGW64
lib_path += -L$(root_dir)/../BaseGame/settings/make/Debug_MinGW64
#lib_path += -L"../../WatermillBase/Debug_MinGW64" 
#lib_path += -L"../../../libraries/freeglut/lib/x64"
lib_path += -L"/usr/local/lib"

LDFLAGS := $(lib_path) $(LDLIBS)

###########################
###	pre installation	###
###########################
#copy_files := $(prog_output_dir)/libzstd.dll $(prog_output_dir)/freeglut.dll $(prog_output_dir)/watermill.ini
copy_files := $(prog_output_dir)/libzstd.dll $(prog_output_dir)/watermill.ini


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
#$(objprog): $(addprefix $(objdir)/, $(objects))
#	ar -r $@ $^


#######################
###	clean receipe	###
#######################

clean:
	rm -rf $(prog_output_dir)/* 
#	rm -rf $(objdir)/*

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


	

	

