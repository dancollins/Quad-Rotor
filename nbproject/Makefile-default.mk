#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/QuadRotorRevB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/QuadRotorRevB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/FreeRTOS/croutine.o ${OBJECTDIR}/src/FreeRTOS/list.o ${OBJECTDIR}/src/FreeRTOS/queue.o ${OBJECTDIR}/src/FreeRTOS/tasks.o ${OBJECTDIR}/src/FreeRTOS/timers.o ${OBJECTDIR}/src/FreeRTOS/portable/heap_4.o ${OBJECTDIR}/src/FreeRTOS/portable/port.o ${OBJECTDIR}/src/FreeRTOS/portable/port_asm.o ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/low-level/board.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/FreeRTOS/croutine.o.d ${OBJECTDIR}/src/FreeRTOS/list.o.d ${OBJECTDIR}/src/FreeRTOS/queue.o.d ${OBJECTDIR}/src/FreeRTOS/tasks.o.d ${OBJECTDIR}/src/FreeRTOS/timers.o.d ${OBJECTDIR}/src/FreeRTOS/portable/heap_4.o.d ${OBJECTDIR}/src/FreeRTOS/portable/port.o.d ${OBJECTDIR}/src/FreeRTOS/portable/port_asm.o.d ${OBJECTDIR}/src/main.o.d ${OBJECTDIR}/src/low-level/board.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/FreeRTOS/croutine.o ${OBJECTDIR}/src/FreeRTOS/list.o ${OBJECTDIR}/src/FreeRTOS/queue.o ${OBJECTDIR}/src/FreeRTOS/tasks.o ${OBJECTDIR}/src/FreeRTOS/timers.o ${OBJECTDIR}/src/FreeRTOS/portable/heap_4.o ${OBJECTDIR}/src/FreeRTOS/portable/port.o ${OBJECTDIR}/src/FreeRTOS/portable/port_asm.o ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/low-level/board.o


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/QuadRotorRevB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX795F512L
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/FreeRTOS/portable/port_asm.o: src/FreeRTOS/portable/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/FreeRTOS/portable 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/portable/port_asm.o.d 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/portable/port_asm.o.ok ${OBJECTDIR}/src/FreeRTOS/portable/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/src/FreeRTOS/portable/port_asm.o.d" "${OBJECTDIR}/src/FreeRTOS/portable/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/FreeRTOS" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/FreeRTOS/portable" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/low-level" -MMD -MF "${OBJECTDIR}/src/FreeRTOS/portable/port_asm.o.d"  -o ${OBJECTDIR}/src/FreeRTOS/portable/port_asm.o src/FreeRTOS/portable/port_asm.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/src/FreeRTOS/portable/port_asm.o.asm.d",--defsym=__MPLAB_DEBUG=1,--defsym=__ICD2RAM=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include",-I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/FreeRTOS",-I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/FreeRTOS/portable",-I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/low-level"
	
else
${OBJECTDIR}/src/FreeRTOS/portable/port_asm.o: src/FreeRTOS/portable/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/FreeRTOS/portable 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/portable/port_asm.o.d 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/portable/port_asm.o.ok ${OBJECTDIR}/src/FreeRTOS/portable/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/src/FreeRTOS/portable/port_asm.o.d" "${OBJECTDIR}/src/FreeRTOS/portable/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/FreeRTOS" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/FreeRTOS/portable" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/low-level" -MMD -MF "${OBJECTDIR}/src/FreeRTOS/portable/port_asm.o.d"  -o ${OBJECTDIR}/src/FreeRTOS/portable/port_asm.o src/FreeRTOS/portable/port_asm.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/src/FreeRTOS/portable/port_asm.o.asm.d",--gdwarf-2,-I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include",-I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/FreeRTOS",-I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/FreeRTOS/portable",-I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/low-level"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/FreeRTOS/croutine.o: src/FreeRTOS/croutine.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/FreeRTOS 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/croutine.o.d 
	@${FIXDEPS} "${OBJECTDIR}/src/FreeRTOS/croutine.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/FreeRTOS" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/FreeRTOS/portable" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/low-level" -MMD -MF "${OBJECTDIR}/src/FreeRTOS/croutine.o.d" -o ${OBJECTDIR}/src/FreeRTOS/croutine.o src/FreeRTOS/croutine.c   
	
${OBJECTDIR}/src/FreeRTOS/list.o: src/FreeRTOS/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/FreeRTOS 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/list.o.d 
	@${FIXDEPS} "${OBJECTDIR}/src/FreeRTOS/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/FreeRTOS" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/FreeRTOS/portable" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/low-level" -MMD -MF "${OBJECTDIR}/src/FreeRTOS/list.o.d" -o ${OBJECTDIR}/src/FreeRTOS/list.o src/FreeRTOS/list.c   
	
${OBJECTDIR}/src/FreeRTOS/queue.o: src/FreeRTOS/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/FreeRTOS 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/queue.o.d 
	@${FIXDEPS} "${OBJECTDIR}/src/FreeRTOS/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/FreeRTOS" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/FreeRTOS/portable" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/low-level" -MMD -MF "${OBJECTDIR}/src/FreeRTOS/queue.o.d" -o ${OBJECTDIR}/src/FreeRTOS/queue.o src/FreeRTOS/queue.c   
	
${OBJECTDIR}/src/FreeRTOS/tasks.o: src/FreeRTOS/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/FreeRTOS 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/tasks.o.d 
	@${FIXDEPS} "${OBJECTDIR}/src/FreeRTOS/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/FreeRTOS" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/FreeRTOS/portable" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/low-level" -MMD -MF "${OBJECTDIR}/src/FreeRTOS/tasks.o.d" -o ${OBJECTDIR}/src/FreeRTOS/tasks.o src/FreeRTOS/tasks.c   
	
${OBJECTDIR}/src/FreeRTOS/timers.o: src/FreeRTOS/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/FreeRTOS 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/timers.o.d 
	@${FIXDEPS} "${OBJECTDIR}/src/FreeRTOS/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/FreeRTOS" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/FreeRTOS/portable" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/low-level" -MMD -MF "${OBJECTDIR}/src/FreeRTOS/timers.o.d" -o ${OBJECTDIR}/src/FreeRTOS/timers.o src/FreeRTOS/timers.c   
	
${OBJECTDIR}/src/FreeRTOS/portable/heap_4.o: src/FreeRTOS/portable/heap_4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/FreeRTOS/portable 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/portable/heap_4.o.d 
	@${FIXDEPS} "${OBJECTDIR}/src/FreeRTOS/portable/heap_4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/FreeRTOS" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/FreeRTOS/portable" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/low-level" -MMD -MF "${OBJECTDIR}/src/FreeRTOS/portable/heap_4.o.d" -o ${OBJECTDIR}/src/FreeRTOS/portable/heap_4.o src/FreeRTOS/portable/heap_4.c   
	
${OBJECTDIR}/src/FreeRTOS/portable/port.o: src/FreeRTOS/portable/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/FreeRTOS/portable 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/portable/port.o.d 
	@${FIXDEPS} "${OBJECTDIR}/src/FreeRTOS/portable/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/FreeRTOS" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/FreeRTOS/portable" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/low-level" -MMD -MF "${OBJECTDIR}/src/FreeRTOS/portable/port.o.d" -o ${OBJECTDIR}/src/FreeRTOS/portable/port.o src/FreeRTOS/portable/port.c   
	
${OBJECTDIR}/src/main.o: src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${FIXDEPS} "${OBJECTDIR}/src/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/FreeRTOS" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/FreeRTOS/portable" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/low-level" -MMD -MF "${OBJECTDIR}/src/main.o.d" -o ${OBJECTDIR}/src/main.o src/main.c   
	
${OBJECTDIR}/src/low-level/board.o: src/low-level/board.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/low-level 
	@${RM} ${OBJECTDIR}/src/low-level/board.o.d 
	@${FIXDEPS} "${OBJECTDIR}/src/low-level/board.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/FreeRTOS" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/FreeRTOS/portable" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/low-level" -MMD -MF "${OBJECTDIR}/src/low-level/board.o.d" -o ${OBJECTDIR}/src/low-level/board.o src/low-level/board.c   
	
else
${OBJECTDIR}/src/FreeRTOS/croutine.o: src/FreeRTOS/croutine.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/FreeRTOS 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/croutine.o.d 
	@${FIXDEPS} "${OBJECTDIR}/src/FreeRTOS/croutine.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/FreeRTOS" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/FreeRTOS/portable" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/low-level" -MMD -MF "${OBJECTDIR}/src/FreeRTOS/croutine.o.d" -o ${OBJECTDIR}/src/FreeRTOS/croutine.o src/FreeRTOS/croutine.c   
	
${OBJECTDIR}/src/FreeRTOS/list.o: src/FreeRTOS/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/FreeRTOS 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/list.o.d 
	@${FIXDEPS} "${OBJECTDIR}/src/FreeRTOS/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/FreeRTOS" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/FreeRTOS/portable" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/low-level" -MMD -MF "${OBJECTDIR}/src/FreeRTOS/list.o.d" -o ${OBJECTDIR}/src/FreeRTOS/list.o src/FreeRTOS/list.c   
	
${OBJECTDIR}/src/FreeRTOS/queue.o: src/FreeRTOS/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/FreeRTOS 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/queue.o.d 
	@${FIXDEPS} "${OBJECTDIR}/src/FreeRTOS/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/FreeRTOS" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/FreeRTOS/portable" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/low-level" -MMD -MF "${OBJECTDIR}/src/FreeRTOS/queue.o.d" -o ${OBJECTDIR}/src/FreeRTOS/queue.o src/FreeRTOS/queue.c   
	
${OBJECTDIR}/src/FreeRTOS/tasks.o: src/FreeRTOS/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/FreeRTOS 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/tasks.o.d 
	@${FIXDEPS} "${OBJECTDIR}/src/FreeRTOS/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/FreeRTOS" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/FreeRTOS/portable" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/low-level" -MMD -MF "${OBJECTDIR}/src/FreeRTOS/tasks.o.d" -o ${OBJECTDIR}/src/FreeRTOS/tasks.o src/FreeRTOS/tasks.c   
	
${OBJECTDIR}/src/FreeRTOS/timers.o: src/FreeRTOS/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/FreeRTOS 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/timers.o.d 
	@${FIXDEPS} "${OBJECTDIR}/src/FreeRTOS/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/FreeRTOS" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/FreeRTOS/portable" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/low-level" -MMD -MF "${OBJECTDIR}/src/FreeRTOS/timers.o.d" -o ${OBJECTDIR}/src/FreeRTOS/timers.o src/FreeRTOS/timers.c   
	
${OBJECTDIR}/src/FreeRTOS/portable/heap_4.o: src/FreeRTOS/portable/heap_4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/FreeRTOS/portable 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/portable/heap_4.o.d 
	@${FIXDEPS} "${OBJECTDIR}/src/FreeRTOS/portable/heap_4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/FreeRTOS" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/FreeRTOS/portable" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/low-level" -MMD -MF "${OBJECTDIR}/src/FreeRTOS/portable/heap_4.o.d" -o ${OBJECTDIR}/src/FreeRTOS/portable/heap_4.o src/FreeRTOS/portable/heap_4.c   
	
${OBJECTDIR}/src/FreeRTOS/portable/port.o: src/FreeRTOS/portable/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/FreeRTOS/portable 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/portable/port.o.d 
	@${FIXDEPS} "${OBJECTDIR}/src/FreeRTOS/portable/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/FreeRTOS" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/FreeRTOS/portable" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/low-level" -MMD -MF "${OBJECTDIR}/src/FreeRTOS/portable/port.o.d" -o ${OBJECTDIR}/src/FreeRTOS/portable/port.o src/FreeRTOS/portable/port.c   
	
${OBJECTDIR}/src/main.o: src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${FIXDEPS} "${OBJECTDIR}/src/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/FreeRTOS" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/FreeRTOS/portable" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/low-level" -MMD -MF "${OBJECTDIR}/src/main.o.d" -o ${OBJECTDIR}/src/main.o src/main.c   
	
${OBJECTDIR}/src/low-level/board.o: src/low-level/board.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/low-level 
	@${RM} ${OBJECTDIR}/src/low-level/board.o.d 
	@${FIXDEPS} "${OBJECTDIR}/src/low-level/board.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/FreeRTOS" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/FreeRTOS/portable" -I"C:/Users/Dan/Projects/Electronics/Quad Rotor/QuadRotorRevB.X/include/low-level" -MMD -MF "${OBJECTDIR}/src/low-level/board.o.d" -o ${OBJECTDIR}/src/low-level/board.o src/low-level/board.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/QuadRotorRevB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/QuadRotorRevB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}         -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__ICD2RAM=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1
else
dist/${CND_CONF}/${IMAGE_TYPE}/QuadRotorRevB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/QuadRotorRevB.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}         -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION)
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/QuadRotorRevB.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif