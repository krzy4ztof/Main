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
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/source/gameInitialization/AudioSystem.o \
	${OBJECTDIR}/source/gameInitialization/DataFiles.o \
	${OBJECTDIR}/source/gameInitialization/ErrorCode.o \
	${OBJECTDIR}/source/gameInitialization/GameCodeApp.o \
	${OBJECTDIR}/source/gameInitialization/VideoSystem.o \
	${OBJECTDIR}/source/main/Main.o \
	${OBJECTDIR}/source/testClasses/TestClass.o


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
LDLIBSOPTIONS=-L../../libraries/glut-3.7.6-bin -L../../libraries/freeglut/lib -lfreeglut -lopengl32 -Wl,--subsystem,windows

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/watermill.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/watermill.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/watermill ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/source/gameInitialization/AudioSystem.o: source/gameInitialization/AudioSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/gameInitialization
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../libraries/boost_1_60_0 -I../../libraries/glut-3.7.6-bin -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/gameInitialization/AudioSystem.o source/gameInitialization/AudioSystem.cpp

${OBJECTDIR}/source/gameInitialization/DataFiles.o: source/gameInitialization/DataFiles.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/gameInitialization
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../libraries/boost_1_60_0 -I../../libraries/glut-3.7.6-bin -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/gameInitialization/DataFiles.o source/gameInitialization/DataFiles.cpp

${OBJECTDIR}/source/gameInitialization/ErrorCode.o: source/gameInitialization/ErrorCode.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/gameInitialization
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../libraries/boost_1_60_0 -I../../libraries/glut-3.7.6-bin -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/gameInitialization/ErrorCode.o source/gameInitialization/ErrorCode.cpp

${OBJECTDIR}/source/gameInitialization/GameCodeApp.o: source/gameInitialization/GameCodeApp.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/gameInitialization
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../libraries/boost_1_60_0 -I../../libraries/glut-3.7.6-bin -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/gameInitialization/GameCodeApp.o source/gameInitialization/GameCodeApp.cpp

${OBJECTDIR}/source/gameInitialization/VideoSystem.o: source/gameInitialization/VideoSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/gameInitialization
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../libraries/boost_1_60_0 -I../../libraries/glut-3.7.6-bin -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/gameInitialization/VideoSystem.o source/gameInitialization/VideoSystem.cpp

${OBJECTDIR}/source/main/Main.o: source/main/Main.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/main
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../libraries/boost_1_60_0 -I../../libraries/glut-3.7.6-bin -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/main/Main.o source/main/Main.cpp

${OBJECTDIR}/source/testClasses/TestClass.o: source/testClasses/TestClass.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/testClasses
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../libraries/boost_1_60_0 -I../../libraries/glut-3.7.6-bin -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/testClasses/TestClass.o source/testClasses/TestClass.cpp

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
