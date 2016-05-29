##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug_MinGW64
ProjectName            :=Watermill
ConfigurationName      :=Debug_MinGW64
WorkspacePath          :=C:/home/myImportantFiles/projects/CodeLiteWorkspace
ProjectPath            :=C:/home/myImportantFiles/projects/git/Main/WaterMill/settings/codelite/Watermill
IntermediateDirectory  :=./Debug_MinGW64
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Krzysztof
Date                   :=29/05/2016
CodeLitePath           :="C:/Program Files/CodeLite"
LinkerName             :=C:/msys64/mingw64/bin/g++.exe
SharedObjectLinkerName :=C:/msys64/mingw64/bin/g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="Watermill.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=C:/msys64/mingw64/bin/windres.exe
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)C:/home/myImportantFiles/projects/git/libraries/boost_1_60_0 $(IncludeSwitch)C:/home/myImportantFiles/projects/git/libraries/freeglut/include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)freeglut $(LibrarySwitch)psapi $(LibrarySwitch)opengl32 
ArLibs                 :=  "freeglut" "psapi" "opengl32" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)C:/home/myImportantFiles/projects/git/libraries/freeglut/lib/x64 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := C:/msys64/mingw64/bin/ar.exe rcu
CXX      := C:/msys64/mingw64/bin/g++.exe
CC       := C:/msys64/mingw64/bin/gcc.exe
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := C:/msys64/mingw64/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
Objects0=$(IntermediateDirectory)/AudioSystem.cpp$(ObjectSuffix) $(IntermediateDirectory)/DataFiles.cpp$(ObjectSuffix) $(IntermediateDirectory)/ErrorCode.cpp$(ObjectSuffix) $(IntermediateDirectory)/GameCodeApp.cpp$(ObjectSuffix) $(IntermediateDirectory)/VideoSystem.cpp$(ObjectSuffix) $(IntermediateDirectory)/Main.cpp$(ObjectSuffix) $(IntermediateDirectory)/TestClass.cpp$(ObjectSuffix) $(IntermediateDirectory)/LinuxCalls.cpp$(ObjectSuffix) $(IntermediateDirectory)/Cygwin64Calls.cpp$(ObjectSuffix) $(IntermediateDirectory)/Windows32Calls.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/Windows64Calls.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

PostBuild:
	@echo Executing Post Build commands ...
	copy C:\home\myImportantFiles\projects\git\libraries\freeglut\bin\x64\freeglut.dll Debug_MinGW64
	@echo Done

MakeIntermediateDirs:
	@$(MakeDirCommand) "./Debug_MinGW64"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Debug_MinGW64"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/AudioSystem.cpp$(ObjectSuffix): ../../../source/gameInitialization/AudioSystem.cpp $(IntermediateDirectory)/AudioSystem.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/home/myImportantFiles/projects/git/Main/WaterMill/source/gameInitialization/AudioSystem.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/AudioSystem.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/AudioSystem.cpp$(DependSuffix): ../../../source/gameInitialization/AudioSystem.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/AudioSystem.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/AudioSystem.cpp$(DependSuffix) -MM "../../../source/gameInitialization/AudioSystem.cpp"

$(IntermediateDirectory)/AudioSystem.cpp$(PreprocessSuffix): ../../../source/gameInitialization/AudioSystem.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/AudioSystem.cpp$(PreprocessSuffix) "../../../source/gameInitialization/AudioSystem.cpp"

$(IntermediateDirectory)/DataFiles.cpp$(ObjectSuffix): ../../../source/gameInitialization/DataFiles.cpp $(IntermediateDirectory)/DataFiles.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/home/myImportantFiles/projects/git/Main/WaterMill/source/gameInitialization/DataFiles.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/DataFiles.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/DataFiles.cpp$(DependSuffix): ../../../source/gameInitialization/DataFiles.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/DataFiles.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/DataFiles.cpp$(DependSuffix) -MM "../../../source/gameInitialization/DataFiles.cpp"

$(IntermediateDirectory)/DataFiles.cpp$(PreprocessSuffix): ../../../source/gameInitialization/DataFiles.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/DataFiles.cpp$(PreprocessSuffix) "../../../source/gameInitialization/DataFiles.cpp"

$(IntermediateDirectory)/ErrorCode.cpp$(ObjectSuffix): ../../../source/gameInitialization/ErrorCode.cpp $(IntermediateDirectory)/ErrorCode.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/home/myImportantFiles/projects/git/Main/WaterMill/source/gameInitialization/ErrorCode.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ErrorCode.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ErrorCode.cpp$(DependSuffix): ../../../source/gameInitialization/ErrorCode.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ErrorCode.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ErrorCode.cpp$(DependSuffix) -MM "../../../source/gameInitialization/ErrorCode.cpp"

$(IntermediateDirectory)/ErrorCode.cpp$(PreprocessSuffix): ../../../source/gameInitialization/ErrorCode.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ErrorCode.cpp$(PreprocessSuffix) "../../../source/gameInitialization/ErrorCode.cpp"

$(IntermediateDirectory)/GameCodeApp.cpp$(ObjectSuffix): ../../../source/gameInitialization/GameCodeApp.cpp $(IntermediateDirectory)/GameCodeApp.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/home/myImportantFiles/projects/git/Main/WaterMill/source/gameInitialization/GameCodeApp.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/GameCodeApp.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/GameCodeApp.cpp$(DependSuffix): ../../../source/gameInitialization/GameCodeApp.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/GameCodeApp.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/GameCodeApp.cpp$(DependSuffix) -MM "../../../source/gameInitialization/GameCodeApp.cpp"

$(IntermediateDirectory)/GameCodeApp.cpp$(PreprocessSuffix): ../../../source/gameInitialization/GameCodeApp.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/GameCodeApp.cpp$(PreprocessSuffix) "../../../source/gameInitialization/GameCodeApp.cpp"

$(IntermediateDirectory)/VideoSystem.cpp$(ObjectSuffix): ../../../source/gameInitialization/VideoSystem.cpp $(IntermediateDirectory)/VideoSystem.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/home/myImportantFiles/projects/git/Main/WaterMill/source/gameInitialization/VideoSystem.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/VideoSystem.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/VideoSystem.cpp$(DependSuffix): ../../../source/gameInitialization/VideoSystem.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/VideoSystem.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/VideoSystem.cpp$(DependSuffix) -MM "../../../source/gameInitialization/VideoSystem.cpp"

$(IntermediateDirectory)/VideoSystem.cpp$(PreprocessSuffix): ../../../source/gameInitialization/VideoSystem.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/VideoSystem.cpp$(PreprocessSuffix) "../../../source/gameInitialization/VideoSystem.cpp"

$(IntermediateDirectory)/Main.cpp$(ObjectSuffix): ../../../source/main/Main.cpp $(IntermediateDirectory)/Main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/home/myImportantFiles/projects/git/Main/WaterMill/source/main/Main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Main.cpp$(DependSuffix): ../../../source/main/Main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Main.cpp$(DependSuffix) -MM "../../../source/main/Main.cpp"

$(IntermediateDirectory)/Main.cpp$(PreprocessSuffix): ../../../source/main/Main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Main.cpp$(PreprocessSuffix) "../../../source/main/Main.cpp"

$(IntermediateDirectory)/TestClass.cpp$(ObjectSuffix): ../../../source/testClasses/TestClass.cpp $(IntermediateDirectory)/TestClass.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/home/myImportantFiles/projects/git/Main/WaterMill/source/testClasses/TestClass.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TestClass.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TestClass.cpp$(DependSuffix): ../../../source/testClasses/TestClass.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TestClass.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TestClass.cpp$(DependSuffix) -MM "../../../source/testClasses/TestClass.cpp"

$(IntermediateDirectory)/TestClass.cpp$(PreprocessSuffix): ../../../source/testClasses/TestClass.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TestClass.cpp$(PreprocessSuffix) "../../../source/testClasses/TestClass.cpp"

$(IntermediateDirectory)/LinuxCalls.cpp$(ObjectSuffix): ../../../source/gameInitialization/linux/LinuxCalls.cpp $(IntermediateDirectory)/LinuxCalls.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/home/myImportantFiles/projects/git/Main/WaterMill/source/gameInitialization/linux/LinuxCalls.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/LinuxCalls.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/LinuxCalls.cpp$(DependSuffix): ../../../source/gameInitialization/linux/LinuxCalls.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/LinuxCalls.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/LinuxCalls.cpp$(DependSuffix) -MM "../../../source/gameInitialization/linux/LinuxCalls.cpp"

$(IntermediateDirectory)/LinuxCalls.cpp$(PreprocessSuffix): ../../../source/gameInitialization/linux/LinuxCalls.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/LinuxCalls.cpp$(PreprocessSuffix) "../../../source/gameInitialization/linux/LinuxCalls.cpp"

$(IntermediateDirectory)/Cygwin64Calls.cpp$(ObjectSuffix): ../../../source/gameInitialization/windows/Cygwin64Calls.cpp $(IntermediateDirectory)/Cygwin64Calls.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/home/myImportantFiles/projects/git/Main/WaterMill/source/gameInitialization/windows/Cygwin64Calls.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Cygwin64Calls.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Cygwin64Calls.cpp$(DependSuffix): ../../../source/gameInitialization/windows/Cygwin64Calls.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Cygwin64Calls.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Cygwin64Calls.cpp$(DependSuffix) -MM "../../../source/gameInitialization/windows/Cygwin64Calls.cpp"

$(IntermediateDirectory)/Cygwin64Calls.cpp$(PreprocessSuffix): ../../../source/gameInitialization/windows/Cygwin64Calls.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Cygwin64Calls.cpp$(PreprocessSuffix) "../../../source/gameInitialization/windows/Cygwin64Calls.cpp"

$(IntermediateDirectory)/Windows32Calls.cpp$(ObjectSuffix): ../../../source/gameInitialization/windows/Windows32Calls.cpp $(IntermediateDirectory)/Windows32Calls.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/home/myImportantFiles/projects/git/Main/WaterMill/source/gameInitialization/windows/Windows32Calls.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Windows32Calls.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Windows32Calls.cpp$(DependSuffix): ../../../source/gameInitialization/windows/Windows32Calls.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Windows32Calls.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Windows32Calls.cpp$(DependSuffix) -MM "../../../source/gameInitialization/windows/Windows32Calls.cpp"

$(IntermediateDirectory)/Windows32Calls.cpp$(PreprocessSuffix): ../../../source/gameInitialization/windows/Windows32Calls.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Windows32Calls.cpp$(PreprocessSuffix) "../../../source/gameInitialization/windows/Windows32Calls.cpp"

$(IntermediateDirectory)/Windows64Calls.cpp$(ObjectSuffix): ../../../source/gameInitialization/windows/Windows64Calls.cpp $(IntermediateDirectory)/Windows64Calls.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/home/myImportantFiles/projects/git/Main/WaterMill/source/gameInitialization/windows/Windows64Calls.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Windows64Calls.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Windows64Calls.cpp$(DependSuffix): ../../../source/gameInitialization/windows/Windows64Calls.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Windows64Calls.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Windows64Calls.cpp$(DependSuffix) -MM "../../../source/gameInitialization/windows/Windows64Calls.cpp"

$(IntermediateDirectory)/Windows64Calls.cpp$(PreprocessSuffix): ../../../source/gameInitialization/windows/Windows64Calls.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Windows64Calls.cpp$(PreprocessSuffix) "../../../source/gameInitialization/windows/Windows64Calls.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug_MinGW64/


