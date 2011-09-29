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
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/distributedFileSystem/impl/DistributedFileSystemManager.o \
	${OBJECTDIR}/parser/transformer/LowerCaseTransformer.o \
	${OBJECTDIR}/include/impl/Templatizer.o \
	${OBJECTDIR}/parser/PlainTextParser.o \
	${OBJECTDIR}/falcon.o \
	${OBJECTDIR}/parser/WikiParser.o \
	${OBJECTDIR}/include/impl/DeTemplatizer.o \
	${OBJECTDIR}/dictionary/impl/Dictionary.o \
	${OBJECTDIR}/parser/tokenizer/impl/Tokenizer.o \
	${OBJECTDIR}/include/impl/FileManager.o \
	${OBJECTDIR}/parser/filter/StopWordFilter.o \
	${OBJECTDIR}/distributedFileSystem/impl/DistributedFileSystem.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/woot

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/woot: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/woot ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/distributedFileSystem/impl/DistributedFileSystemManager.o: distributedFileSystem/impl/DistributedFileSystemManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/distributedFileSystem/impl
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/distributedFileSystem/impl/DistributedFileSystemManager.o distributedFileSystem/impl/DistributedFileSystemManager.cpp

${OBJECTDIR}/parser/transformer/LowerCaseTransformer.o: parser/transformer/LowerCaseTransformer.cpp 
	${MKDIR} -p ${OBJECTDIR}/parser/transformer
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/parser/transformer/LowerCaseTransformer.o parser/transformer/LowerCaseTransformer.cpp

${OBJECTDIR}/include/impl/Templatizer.o: include/impl/Templatizer.cpp 
	${MKDIR} -p ${OBJECTDIR}/include/impl
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/include/impl/Templatizer.o include/impl/Templatizer.cpp

${OBJECTDIR}/parser/PlainTextParser.o: parser/PlainTextParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/parser
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/parser/PlainTextParser.o parser/PlainTextParser.cpp

${OBJECTDIR}/falcon.o: falcon.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/falcon.o falcon.cpp

${OBJECTDIR}/parser/WikiParser.o: parser/WikiParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/parser
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/parser/WikiParser.o parser/WikiParser.cpp

${OBJECTDIR}/include/impl/DeTemplatizer.o: include/impl/DeTemplatizer.cpp 
	${MKDIR} -p ${OBJECTDIR}/include/impl
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/include/impl/DeTemplatizer.o include/impl/DeTemplatizer.cpp

${OBJECTDIR}/dictionary/impl/Dictionary.o: dictionary/impl/Dictionary.cpp 
	${MKDIR} -p ${OBJECTDIR}/dictionary/impl
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/dictionary/impl/Dictionary.o dictionary/impl/Dictionary.cpp

${OBJECTDIR}/parser/tokenizer/impl/Tokenizer.o: parser/tokenizer/impl/Tokenizer.cpp 
	${MKDIR} -p ${OBJECTDIR}/parser/tokenizer/impl
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/parser/tokenizer/impl/Tokenizer.o parser/tokenizer/impl/Tokenizer.cpp

${OBJECTDIR}/include/impl/FileManager.o: include/impl/FileManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/include/impl
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/include/impl/FileManager.o include/impl/FileManager.cpp

${OBJECTDIR}/parser/filter/StopWordFilter.o: parser/filter/StopWordFilter.cpp 
	${MKDIR} -p ${OBJECTDIR}/parser/filter
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/parser/filter/StopWordFilter.o parser/filter/StopWordFilter.cpp

${OBJECTDIR}/distributedFileSystem/impl/DistributedFileSystem.o: distributedFileSystem/impl/DistributedFileSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/distributedFileSystem/impl
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/distributedFileSystem/impl/DistributedFileSystem.o distributedFileSystem/impl/DistributedFileSystem.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/woot

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
