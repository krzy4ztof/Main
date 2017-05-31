#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=MinGW64-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/3577b923/Actor.o \
	${OBJECTDIR}/_ext/3577b923/ActorComponent.o \
	${OBJECTDIR}/_ext/3577b923/ActorFactory.o \
	${OBJECTDIR}/_ext/3577b923/ComponentFactory.o \
	${OBJECTDIR}/_ext/3577b923/RenderComponent.o \
	${OBJECTDIR}/_ext/3577b923/ScriptComponent.o \
	${OBJECTDIR}/_ext/3577b923/TransformComponent.o \
	${OBJECTDIR}/_ext/f54f40c9/Logger.o \
	${OBJECTDIR}/_ext/85083ff8/EventManager.o \
	${OBJECTDIR}/_ext/d8bd05b7/AudioSystem.o \
	${OBJECTDIR}/_ext/d8bd05b7/DataFiles.o \
	${OBJECTDIR}/_ext/d8bd05b7/DebuggingOptions.o \
	${OBJECTDIR}/_ext/d8bd05b7/ErrorCode.o \
	${OBJECTDIR}/_ext/d8bd05b7/GameCodeApp.o \
	${OBJECTDIR}/_ext/d8bd05b7/GameMessages.o \
	${OBJECTDIR}/_ext/d8bd05b7/InitOptions.o \
	${OBJECTDIR}/_ext/d8bd05b7/Macros.o \
	${OBJECTDIR}/_ext/d8bd05b7/PlayerOptions.o \
	${OBJECTDIR}/_ext/d8bd05b7/VideoSystem.o \
	${OBJECTDIR}/_ext/3d10b69c/LinuxCalls.o \
	${OBJECTDIR}/_ext/3d10b69c/LinuxCpuCalls.o \
	${OBJECTDIR}/_ext/3d10b69c/LinuxProcessCalls.o \
	${OBJECTDIR}/_ext/819a3e2b/Cygwin64Calls.o \
	${OBJECTDIR}/_ext/819a3e2b/Cygwin64CpuCalls.o \
	${OBJECTDIR}/_ext/819a3e2b/Cygwin64ProcessCalls.o \
	${OBJECTDIR}/_ext/819a3e2b/Windows32Calls.o \
	${OBJECTDIR}/_ext/819a3e2b/Windows64Calls.o \
	${OBJECTDIR}/_ext/3bb5fc67/BaseGameLogic.o \
	${OBJECTDIR}/_ext/7ebfce64/LuaStateManager.o \
	${OBJECTDIR}/_ext/3ce66fe/GameMain.o \
	${OBJECTDIR}/_ext/3ce66fe/Main.o \
	${OBJECTDIR}/_ext/184af2c2/DelayProcess.o \
	${OBJECTDIR}/_ext/184af2c2/Process.o \
	${OBJECTDIR}/_ext/184af2c2/ProcessManager.o \
	${OBJECTDIR}/_ext/184af2c2/TempTestProcess.o \
	${OBJECTDIR}/_ext/bf3d906f/DefaultResourceLoader.o \
	${OBJECTDIR}/_ext/bf3d906f/IResourceFile.o \
	${OBJECTDIR}/_ext/bf3d906f/IResourceLoader.o \
	${OBJECTDIR}/_ext/bf3d906f/Resource.o \
	${OBJECTDIR}/_ext/bf3d906f/ResourceCache.o \
	${OBJECTDIR}/_ext/bf3d906f/ResourceHandle.o \
	${OBJECTDIR}/_ext/bf3d906f/ResourceZipFile.o \
	${OBJECTDIR}/_ext/bf3d906f/TZipDirFileHeader.o \
	${OBJECTDIR}/_ext/bf3d906f/TZipDirHeader.o \
	${OBJECTDIR}/_ext/bf3d906f/TZipLocalHeader.o \
	${OBJECTDIR}/_ext/bf3d906f/XmlResourceLoader.o \
	${OBJECTDIR}/_ext/bf3d906f/ZipFile.o \
	${OBJECTDIR}/_ext/74aa468b/SaveManager.o \
	${OBJECTDIR}/_ext/3190a5a3/test.o \
	${OBJECTDIR}/_ext/35313a4f/TestClass.o \
	${OBJECTDIR}/_ext/1972f209/HumanView.o \
	${OBJECTDIR}/_ext/1972f209/IGameView.o \
	${OBJECTDIR}/_ext/471e58e5/MemoryPool.o \
	${OBJECTDIR}/_ext/471e58e5/MemoryUsageObject.o \
	${OBJECTDIR}/_ext/471e58e5/MemoryUsageObjectAutoInitMemPool.o \
	${OBJECTDIR}/_ext/471e58e5/NumberUtils.o \
	${OBJECTDIR}/_ext/471e58e5/PrimeSearch.o \
	${OBJECTDIR}/_ext/471e58e5/PropertyTreeUtils.o \
	${OBJECTDIR}/_ext/471e58e5/RandomGenerator.o \
	${OBJECTDIR}/_ext/471e58e5/StringUtils.o \
	${OBJECTDIR}/_ext/da6670a0/WatermillGame.o \
	${OBJECTDIR}/_ext/da6670a0/WatermillLogic.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/watermill.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/watermill.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/watermill ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/3577b923/Actor.o: ../../../source/actors/Actor.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/3577b923
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3577b923/Actor.o ../../../source/actors/Actor.cpp

${OBJECTDIR}/_ext/3577b923/ActorComponent.o: ../../../source/actors/ActorComponent.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/3577b923
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3577b923/ActorComponent.o ../../../source/actors/ActorComponent.cpp

${OBJECTDIR}/_ext/3577b923/ActorFactory.o: ../../../source/actors/ActorFactory.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/3577b923
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3577b923/ActorFactory.o ../../../source/actors/ActorFactory.cpp

${OBJECTDIR}/_ext/3577b923/ComponentFactory.o: ../../../source/actors/ComponentFactory.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/3577b923
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3577b923/ComponentFactory.o ../../../source/actors/ComponentFactory.cpp

${OBJECTDIR}/_ext/3577b923/RenderComponent.o: ../../../source/actors/RenderComponent.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/3577b923
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3577b923/RenderComponent.o ../../../source/actors/RenderComponent.cpp

${OBJECTDIR}/_ext/3577b923/ScriptComponent.o: ../../../source/actors/ScriptComponent.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/3577b923
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3577b923/ScriptComponent.o ../../../source/actors/ScriptComponent.cpp

${OBJECTDIR}/_ext/3577b923/TransformComponent.o: ../../../source/actors/TransformComponent.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/3577b923
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3577b923/TransformComponent.o ../../../source/actors/TransformComponent.cpp

${OBJECTDIR}/_ext/f54f40c9/Logger.o: ../../../source/debugging/Logger.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/f54f40c9
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/f54f40c9/Logger.o ../../../source/debugging/Logger.cpp

${OBJECTDIR}/_ext/85083ff8/EventManager.o: ../../../source/eventManager/EventManager.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/85083ff8
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/85083ff8/EventManager.o ../../../source/eventManager/EventManager.cpp

${OBJECTDIR}/_ext/d8bd05b7/AudioSystem.o: ../../../source/gameInitialization/AudioSystem.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d8bd05b7
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d8bd05b7/AudioSystem.o ../../../source/gameInitialization/AudioSystem.cpp

${OBJECTDIR}/_ext/d8bd05b7/DataFiles.o: ../../../source/gameInitialization/DataFiles.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d8bd05b7
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d8bd05b7/DataFiles.o ../../../source/gameInitialization/DataFiles.cpp

${OBJECTDIR}/_ext/d8bd05b7/DebuggingOptions.o: ../../../source/gameInitialization/DebuggingOptions.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d8bd05b7
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d8bd05b7/DebuggingOptions.o ../../../source/gameInitialization/DebuggingOptions.cpp

${OBJECTDIR}/_ext/d8bd05b7/ErrorCode.o: ../../../source/gameInitialization/ErrorCode.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d8bd05b7
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d8bd05b7/ErrorCode.o ../../../source/gameInitialization/ErrorCode.cpp

${OBJECTDIR}/_ext/d8bd05b7/GameCodeApp.o: ../../../source/gameInitialization/GameCodeApp.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d8bd05b7
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d8bd05b7/GameCodeApp.o ../../../source/gameInitialization/GameCodeApp.cpp

${OBJECTDIR}/_ext/d8bd05b7/GameMessages.o: ../../../source/gameInitialization/GameMessages.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d8bd05b7
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d8bd05b7/GameMessages.o ../../../source/gameInitialization/GameMessages.cpp

${OBJECTDIR}/_ext/d8bd05b7/InitOptions.o: ../../../source/gameInitialization/InitOptions.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d8bd05b7
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d8bd05b7/InitOptions.o ../../../source/gameInitialization/InitOptions.cpp

${OBJECTDIR}/_ext/d8bd05b7/Macros.o: ../../../source/gameInitialization/Macros.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d8bd05b7
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d8bd05b7/Macros.o ../../../source/gameInitialization/Macros.cpp

${OBJECTDIR}/_ext/d8bd05b7/PlayerOptions.o: ../../../source/gameInitialization/PlayerOptions.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d8bd05b7
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d8bd05b7/PlayerOptions.o ../../../source/gameInitialization/PlayerOptions.cpp

${OBJECTDIR}/_ext/d8bd05b7/VideoSystem.o: ../../../source/gameInitialization/VideoSystem.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d8bd05b7
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d8bd05b7/VideoSystem.o ../../../source/gameInitialization/VideoSystem.cpp

${OBJECTDIR}/_ext/3d10b69c/LinuxCalls.o: ../../../source/gameInitialization/linux/LinuxCalls.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/3d10b69c
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3d10b69c/LinuxCalls.o ../../../source/gameInitialization/linux/LinuxCalls.cpp

${OBJECTDIR}/_ext/3d10b69c/LinuxCpuCalls.o: ../../../source/gameInitialization/linux/LinuxCpuCalls.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/3d10b69c
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3d10b69c/LinuxCpuCalls.o ../../../source/gameInitialization/linux/LinuxCpuCalls.cpp

${OBJECTDIR}/_ext/3d10b69c/LinuxProcessCalls.o: ../../../source/gameInitialization/linux/LinuxProcessCalls.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/3d10b69c
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3d10b69c/LinuxProcessCalls.o ../../../source/gameInitialization/linux/LinuxProcessCalls.cpp

${OBJECTDIR}/_ext/819a3e2b/Cygwin64Calls.o: ../../../source/gameInitialization/windows/Cygwin64Calls.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/819a3e2b
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/819a3e2b/Cygwin64Calls.o ../../../source/gameInitialization/windows/Cygwin64Calls.cpp

${OBJECTDIR}/_ext/819a3e2b/Cygwin64CpuCalls.o: ../../../source/gameInitialization/windows/Cygwin64CpuCalls.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/819a3e2b
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/819a3e2b/Cygwin64CpuCalls.o ../../../source/gameInitialization/windows/Cygwin64CpuCalls.cpp

${OBJECTDIR}/_ext/819a3e2b/Cygwin64ProcessCalls.o: ../../../source/gameInitialization/windows/Cygwin64ProcessCalls.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/819a3e2b
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/819a3e2b/Cygwin64ProcessCalls.o ../../../source/gameInitialization/windows/Cygwin64ProcessCalls.cpp

${OBJECTDIR}/_ext/819a3e2b/Windows32Calls.o: ../../../source/gameInitialization/windows/Windows32Calls.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/819a3e2b
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/819a3e2b/Windows32Calls.o ../../../source/gameInitialization/windows/Windows32Calls.cpp

${OBJECTDIR}/_ext/819a3e2b/Windows64Calls.o: ../../../source/gameInitialization/windows/Windows64Calls.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/819a3e2b
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/819a3e2b/Windows64Calls.o ../../../source/gameInitialization/windows/Windows64Calls.cpp

${OBJECTDIR}/_ext/3bb5fc67/BaseGameLogic.o: ../../../source/gameLogic/BaseGameLogic.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/3bb5fc67
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3bb5fc67/BaseGameLogic.o ../../../source/gameLogic/BaseGameLogic.cpp

${OBJECTDIR}/_ext/7ebfce64/LuaStateManager.o: ../../../source/luaScripting/LuaStateManager.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/7ebfce64
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7ebfce64/LuaStateManager.o ../../../source/luaScripting/LuaStateManager.cpp

${OBJECTDIR}/_ext/3ce66fe/GameMain.o: ../../../source/main/GameMain.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce66fe
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce66fe/GameMain.o ../../../source/main/GameMain.cpp

${OBJECTDIR}/_ext/3ce66fe/Main.o: ../../../source/main/Main.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce66fe
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce66fe/Main.o ../../../source/main/Main.cpp

${OBJECTDIR}/_ext/184af2c2/DelayProcess.o: ../../../source/mainLoop/DelayProcess.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/184af2c2
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/184af2c2/DelayProcess.o ../../../source/mainLoop/DelayProcess.cpp

${OBJECTDIR}/_ext/184af2c2/Process.o: ../../../source/mainLoop/Process.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/184af2c2
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/184af2c2/Process.o ../../../source/mainLoop/Process.cpp

${OBJECTDIR}/_ext/184af2c2/ProcessManager.o: ../../../source/mainLoop/ProcessManager.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/184af2c2
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/184af2c2/ProcessManager.o ../../../source/mainLoop/ProcessManager.cpp

${OBJECTDIR}/_ext/184af2c2/TempTestProcess.o: ../../../source/mainLoop/TempTestProcess.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/184af2c2
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/184af2c2/TempTestProcess.o ../../../source/mainLoop/TempTestProcess.cpp

${OBJECTDIR}/_ext/bf3d906f/DefaultResourceLoader.o: ../../../source/resourceCache/DefaultResourceLoader.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/bf3d906f
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/bf3d906f/DefaultResourceLoader.o ../../../source/resourceCache/DefaultResourceLoader.cpp

${OBJECTDIR}/_ext/bf3d906f/IResourceFile.o: ../../../source/resourceCache/IResourceFile.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/bf3d906f
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/bf3d906f/IResourceFile.o ../../../source/resourceCache/IResourceFile.cpp

${OBJECTDIR}/_ext/bf3d906f/IResourceLoader.o: ../../../source/resourceCache/IResourceLoader.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/bf3d906f
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/bf3d906f/IResourceLoader.o ../../../source/resourceCache/IResourceLoader.cpp

${OBJECTDIR}/_ext/bf3d906f/Resource.o: ../../../source/resourceCache/Resource.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/bf3d906f
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/bf3d906f/Resource.o ../../../source/resourceCache/Resource.cpp

${OBJECTDIR}/_ext/bf3d906f/ResourceCache.o: ../../../source/resourceCache/ResourceCache.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/bf3d906f
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/bf3d906f/ResourceCache.o ../../../source/resourceCache/ResourceCache.cpp

${OBJECTDIR}/_ext/bf3d906f/ResourceHandle.o: ../../../source/resourceCache/ResourceHandle.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/bf3d906f
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/bf3d906f/ResourceHandle.o ../../../source/resourceCache/ResourceHandle.cpp

${OBJECTDIR}/_ext/bf3d906f/ResourceZipFile.o: ../../../source/resourceCache/ResourceZipFile.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/bf3d906f
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/bf3d906f/ResourceZipFile.o ../../../source/resourceCache/ResourceZipFile.cpp

${OBJECTDIR}/_ext/bf3d906f/TZipDirFileHeader.o: ../../../source/resourceCache/TZipDirFileHeader.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/bf3d906f
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/bf3d906f/TZipDirFileHeader.o ../../../source/resourceCache/TZipDirFileHeader.cpp

${OBJECTDIR}/_ext/bf3d906f/TZipDirHeader.o: ../../../source/resourceCache/TZipDirHeader.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/bf3d906f
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/bf3d906f/TZipDirHeader.o ../../../source/resourceCache/TZipDirHeader.cpp

${OBJECTDIR}/_ext/bf3d906f/TZipLocalHeader.o: ../../../source/resourceCache/TZipLocalHeader.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/bf3d906f
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/bf3d906f/TZipLocalHeader.o ../../../source/resourceCache/TZipLocalHeader.cpp

${OBJECTDIR}/_ext/bf3d906f/XmlResourceLoader.o: ../../../source/resourceCache/XmlResourceLoader.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/bf3d906f
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/bf3d906f/XmlResourceLoader.o ../../../source/resourceCache/XmlResourceLoader.cpp

${OBJECTDIR}/_ext/bf3d906f/ZipFile.o: ../../../source/resourceCache/ZipFile.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/bf3d906f
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/bf3d906f/ZipFile.o ../../../source/resourceCache/ZipFile.cpp

${OBJECTDIR}/_ext/74aa468b/SaveManager.o: ../../../source/saveManager/SaveManager.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/74aa468b
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/74aa468b/SaveManager.o ../../../source/saveManager/SaveManager.cpp

${OBJECTDIR}/_ext/3190a5a3/test.o: ../../../source/scripts/test.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/3190a5a3
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3190a5a3/test.o ../../../source/scripts/test.cpp

${OBJECTDIR}/_ext/35313a4f/TestClass.o: ../../../source/testClasses/TestClass.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/35313a4f
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/35313a4f/TestClass.o ../../../source/testClasses/TestClass.cpp

${OBJECTDIR}/_ext/1972f209/HumanView.o: ../../../source/userInterface/HumanView.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/1972f209
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1972f209/HumanView.o ../../../source/userInterface/HumanView.cpp

${OBJECTDIR}/_ext/1972f209/IGameView.o: ../../../source/userInterface/IGameView.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/1972f209
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1972f209/IGameView.o ../../../source/userInterface/IGameView.cpp

${OBJECTDIR}/_ext/471e58e5/MemoryPool.o: ../../../source/utilities/MemoryPool.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/471e58e5
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/471e58e5/MemoryPool.o ../../../source/utilities/MemoryPool.cpp

${OBJECTDIR}/_ext/471e58e5/MemoryUsageObject.o: ../../../source/utilities/MemoryUsageObject.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/471e58e5
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/471e58e5/MemoryUsageObject.o ../../../source/utilities/MemoryUsageObject.cpp

${OBJECTDIR}/_ext/471e58e5/MemoryUsageObjectAutoInitMemPool.o: ../../../source/utilities/MemoryUsageObjectAutoInitMemPool.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/471e58e5
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/471e58e5/MemoryUsageObjectAutoInitMemPool.o ../../../source/utilities/MemoryUsageObjectAutoInitMemPool.cpp

${OBJECTDIR}/_ext/471e58e5/NumberUtils.o: ../../../source/utilities/NumberUtils.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/471e58e5
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/471e58e5/NumberUtils.o ../../../source/utilities/NumberUtils.cpp

${OBJECTDIR}/_ext/471e58e5/PrimeSearch.o: ../../../source/utilities/PrimeSearch.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/471e58e5
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/471e58e5/PrimeSearch.o ../../../source/utilities/PrimeSearch.cpp

${OBJECTDIR}/_ext/471e58e5/PropertyTreeUtils.o: ../../../source/utilities/PropertyTreeUtils.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/471e58e5
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/471e58e5/PropertyTreeUtils.o ../../../source/utilities/PropertyTreeUtils.cpp

${OBJECTDIR}/_ext/471e58e5/RandomGenerator.o: ../../../source/utilities/RandomGenerator.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/471e58e5
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/471e58e5/RandomGenerator.o ../../../source/utilities/RandomGenerator.cpp

${OBJECTDIR}/_ext/471e58e5/StringUtils.o: ../../../source/utilities/StringUtils.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/471e58e5
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/471e58e5/StringUtils.o ../../../source/utilities/StringUtils.cpp

${OBJECTDIR}/_ext/da6670a0/WatermillGame.o: ../../../source/watermillGame/WatermillGame.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/da6670a0
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/da6670a0/WatermillGame.o ../../../source/watermillGame/WatermillGame.cpp

${OBJECTDIR}/_ext/da6670a0/WatermillLogic.o: ../../../source/watermillGame/WatermillLogic.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/da6670a0
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/da6670a0/WatermillLogic.o ../../../source/watermillGame/WatermillLogic.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
