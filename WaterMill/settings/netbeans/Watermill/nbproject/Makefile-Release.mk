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
CND_PLATFORM=MinGW-Windows
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
	${OBJECTDIR}/_ext/d8bd05b7/AudioSystem.o \
	${OBJECTDIR}/_ext/d8bd05b7/DataFiles.o \
	${OBJECTDIR}/_ext/d8bd05b7/ErrorCode.o \
	${OBJECTDIR}/_ext/d8bd05b7/GameCodeApp.o \
	${OBJECTDIR}/_ext/d8bd05b7/VideoSystem.o \
	${OBJECTDIR}/_ext/3d10b69c/LinuxCalls.o \
	${OBJECTDIR}/_ext/819a3e2b/Cygwin64Calls.o \
	${OBJECTDIR}/_ext/819a3e2b/Windows32Calls.o \
	${OBJECTDIR}/_ext/819a3e2b/Windows64Calls.o \
	${OBJECTDIR}/_ext/3ce66fe/Main.o \
	${OBJECTDIR}/_ext/35313a4f/TestClass.o


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

${OBJECTDIR}/_ext/d8bd05b7/AudioSystem.o: ../../../source/gameInitialization/AudioSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/d8bd05b7
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d8bd05b7/AudioSystem.o ../../../source/gameInitialization/AudioSystem.cpp

${OBJECTDIR}/_ext/d8bd05b7/DataFiles.o: ../../../source/gameInitialization/DataFiles.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/d8bd05b7
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d8bd05b7/DataFiles.o ../../../source/gameInitialization/DataFiles.cpp

${OBJECTDIR}/_ext/d8bd05b7/ErrorCode.o: ../../../source/gameInitialization/ErrorCode.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/d8bd05b7
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d8bd05b7/ErrorCode.o ../../../source/gameInitialization/ErrorCode.cpp

${OBJECTDIR}/_ext/d8bd05b7/GameCodeApp.o: ../../../source/gameInitialization/GameCodeApp.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/d8bd05b7
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d8bd05b7/GameCodeApp.o ../../../source/gameInitialization/GameCodeApp.cpp

${OBJECTDIR}/_ext/d8bd05b7/VideoSystem.o: ../../../source/gameInitialization/VideoSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/d8bd05b7
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d8bd05b7/VideoSystem.o ../../../source/gameInitialization/VideoSystem.cpp

${OBJECTDIR}/_ext/3d10b69c/LinuxCalls.o: ../../../source/gameInitialization/linux/LinuxCalls.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/3d10b69c
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3d10b69c/LinuxCalls.o ../../../source/gameInitialization/linux/LinuxCalls.cpp

${OBJECTDIR}/_ext/819a3e2b/Cygwin64Calls.o: ../../../source/gameInitialization/windows/Cygwin64Calls.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/819a3e2b
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/819a3e2b/Cygwin64Calls.o ../../../source/gameInitialization/windows/Cygwin64Calls.cpp

${OBJECTDIR}/_ext/819a3e2b/Windows32Calls.o: ../../../source/gameInitialization/windows/Windows32Calls.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/819a3e2b
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/819a3e2b/Windows32Calls.o ../../../source/gameInitialization/windows/Windows32Calls.cpp

${OBJECTDIR}/_ext/819a3e2b/Windows64Calls.o: ../../../source/gameInitialization/windows/Windows64Calls.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/819a3e2b
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/819a3e2b/Windows64Calls.o ../../../source/gameInitialization/windows/Windows64Calls.cpp

${OBJECTDIR}/_ext/3ce66fe/Main.o: ../../../source/main/Main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce66fe
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce66fe/Main.o ../../../source/main/Main.cpp

${OBJECTDIR}/_ext/35313a4f/TestClass.o: ../../../source/testClasses/TestClass.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/35313a4f
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/35313a4f/TestClass.o ../../../source/testClasses/TestClass.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/watermill.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
