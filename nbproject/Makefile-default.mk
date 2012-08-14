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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/QuadRotorRevA2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/QuadRotorRevA2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/croutine.o ${OBJECTDIR}/heap_2.o ${OBJECTDIR}/list.o ${OBJECTDIR}/port.o ${OBJECTDIR}/port_asm.o ${OBJECTDIR}/queue.o ${OBJECTDIR}/tasks.o ${OBJECTDIR}/timers.o ${OBJECTDIR}/gyro.o ${OBJECTDIR}/i2c.o ${OBJECTDIR}/imu.o ${OBJECTDIR}/mag.o ${OBJECTDIR}/main.o ${OBJECTDIR}/radio.o ${OBJECTDIR}/accel.o
POSSIBLE_DEPFILES=${OBJECTDIR}/croutine.o.d ${OBJECTDIR}/heap_2.o.d ${OBJECTDIR}/list.o.d ${OBJECTDIR}/port.o.d ${OBJECTDIR}/port_asm.o.d ${OBJECTDIR}/queue.o.d ${OBJECTDIR}/tasks.o.d ${OBJECTDIR}/timers.o.d ${OBJECTDIR}/gyro.o.d ${OBJECTDIR}/i2c.o.d ${OBJECTDIR}/imu.o.d ${OBJECTDIR}/mag.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/radio.o.d ${OBJECTDIR}/accel.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/croutine.o ${OBJECTDIR}/heap_2.o ${OBJECTDIR}/list.o ${OBJECTDIR}/port.o ${OBJECTDIR}/port_asm.o ${OBJECTDIR}/queue.o ${OBJECTDIR}/tasks.o ${OBJECTDIR}/timers.o ${OBJECTDIR}/gyro.o ${OBJECTDIR}/i2c.o ${OBJECTDIR}/imu.o ${OBJECTDIR}/mag.o ${OBJECTDIR}/main.o ${OBJECTDIR}/radio.o ${OBJECTDIR}/accel.o


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
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/QuadRotorRevA2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/port_asm.o: port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/port_asm.o.d 
	@${RM} ${OBJECTDIR}/port_asm.o.ok ${OBJECTDIR}/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/port_asm.o.d" "${OBJECTDIR}/port_asm.o.asm.d" -t $(SILENT) -c  ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/port_asm.o.d"  -o ${OBJECTDIR}/port_asm.o port_asm.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/port_asm.o.asm.d",--defsym=__MPLAB_DEBUG=1,--defsym=__ICD2RAM=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1
	
else
${OBJECTDIR}/port_asm.o: port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/port_asm.o.d 
	@${RM} ${OBJECTDIR}/port_asm.o.ok ${OBJECTDIR}/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/port_asm.o.d" "${OBJECTDIR}/port_asm.o.asm.d" -t $(SILENT) -c  ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/port_asm.o.d"  -o ${OBJECTDIR}/port_asm.o port_asm.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/port_asm.o.asm.d",--gdwarf-2
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/croutine.o: croutine.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/croutine.o.d 
	@${FIXDEPS} "${OBJECTDIR}/croutine.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/" -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/inc/" -MMD -MF "${OBJECTDIR}/croutine.o.d" -o ${OBJECTDIR}/croutine.o croutine.c  
	
${OBJECTDIR}/heap_2.o: heap_2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/heap_2.o.d 
	@${FIXDEPS} "${OBJECTDIR}/heap_2.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/" -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/inc/" -MMD -MF "${OBJECTDIR}/heap_2.o.d" -o ${OBJECTDIR}/heap_2.o heap_2.c  
	
${OBJECTDIR}/list.o: list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/list.o.d 
	@${FIXDEPS} "${OBJECTDIR}/list.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/" -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/inc/" -MMD -MF "${OBJECTDIR}/list.o.d" -o ${OBJECTDIR}/list.o list.c  
	
${OBJECTDIR}/port.o: port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/port.o.d 
	@${FIXDEPS} "${OBJECTDIR}/port.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/" -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/inc/" -MMD -MF "${OBJECTDIR}/port.o.d" -o ${OBJECTDIR}/port.o port.c  
	
${OBJECTDIR}/queue.o: queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/queue.o.d 
	@${FIXDEPS} "${OBJECTDIR}/queue.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/" -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/inc/" -MMD -MF "${OBJECTDIR}/queue.o.d" -o ${OBJECTDIR}/queue.o queue.c  
	
${OBJECTDIR}/tasks.o: tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/tasks.o.d 
	@${FIXDEPS} "${OBJECTDIR}/tasks.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/" -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/inc/" -MMD -MF "${OBJECTDIR}/tasks.o.d" -o ${OBJECTDIR}/tasks.o tasks.c  
	
${OBJECTDIR}/timers.o: timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/timers.o.d 
	@${FIXDEPS} "${OBJECTDIR}/timers.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/" -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/inc/" -MMD -MF "${OBJECTDIR}/timers.o.d" -o ${OBJECTDIR}/timers.o timers.c  
	
${OBJECTDIR}/gyro.o: gyro.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/gyro.o.d 
	@${FIXDEPS} "${OBJECTDIR}/gyro.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/" -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/inc/" -MMD -MF "${OBJECTDIR}/gyro.o.d" -o ${OBJECTDIR}/gyro.o gyro.c  
	
${OBJECTDIR}/i2c.o: i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/i2c.o.d 
	@${FIXDEPS} "${OBJECTDIR}/i2c.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/" -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/inc/" -MMD -MF "${OBJECTDIR}/i2c.o.d" -o ${OBJECTDIR}/i2c.o i2c.c  
	
${OBJECTDIR}/imu.o: imu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/imu.o.d 
	@${FIXDEPS} "${OBJECTDIR}/imu.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/" -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/inc/" -MMD -MF "${OBJECTDIR}/imu.o.d" -o ${OBJECTDIR}/imu.o imu.c  
	
${OBJECTDIR}/mag.o: mag.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/mag.o.d 
	@${FIXDEPS} "${OBJECTDIR}/mag.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/" -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/inc/" -MMD -MF "${OBJECTDIR}/mag.o.d" -o ${OBJECTDIR}/mag.o mag.c  
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/" -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/inc/" -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c  
	
${OBJECTDIR}/radio.o: radio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/radio.o.d 
	@${FIXDEPS} "${OBJECTDIR}/radio.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/" -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/inc/" -MMD -MF "${OBJECTDIR}/radio.o.d" -o ${OBJECTDIR}/radio.o radio.c  
	
${OBJECTDIR}/accel.o: accel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/accel.o.d 
	@${FIXDEPS} "${OBJECTDIR}/accel.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/" -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/inc/" -MMD -MF "${OBJECTDIR}/accel.o.d" -o ${OBJECTDIR}/accel.o accel.c  
	
else
${OBJECTDIR}/croutine.o: croutine.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/croutine.o.d 
	@${FIXDEPS} "${OBJECTDIR}/croutine.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/" -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/inc/" -MMD -MF "${OBJECTDIR}/croutine.o.d" -o ${OBJECTDIR}/croutine.o croutine.c  
	
${OBJECTDIR}/heap_2.o: heap_2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/heap_2.o.d 
	@${FIXDEPS} "${OBJECTDIR}/heap_2.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/" -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/inc/" -MMD -MF "${OBJECTDIR}/heap_2.o.d" -o ${OBJECTDIR}/heap_2.o heap_2.c  
	
${OBJECTDIR}/list.o: list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/list.o.d 
	@${FIXDEPS} "${OBJECTDIR}/list.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/" -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/inc/" -MMD -MF "${OBJECTDIR}/list.o.d" -o ${OBJECTDIR}/list.o list.c  
	
${OBJECTDIR}/port.o: port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/port.o.d 
	@${FIXDEPS} "${OBJECTDIR}/port.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/" -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/inc/" -MMD -MF "${OBJECTDIR}/port.o.d" -o ${OBJECTDIR}/port.o port.c  
	
${OBJECTDIR}/queue.o: queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/queue.o.d 
	@${FIXDEPS} "${OBJECTDIR}/queue.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/" -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/inc/" -MMD -MF "${OBJECTDIR}/queue.o.d" -o ${OBJECTDIR}/queue.o queue.c  
	
${OBJECTDIR}/tasks.o: tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/tasks.o.d 
	@${FIXDEPS} "${OBJECTDIR}/tasks.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/" -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/inc/" -MMD -MF "${OBJECTDIR}/tasks.o.d" -o ${OBJECTDIR}/tasks.o tasks.c  
	
${OBJECTDIR}/timers.o: timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/timers.o.d 
	@${FIXDEPS} "${OBJECTDIR}/timers.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/" -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/inc/" -MMD -MF "${OBJECTDIR}/timers.o.d" -o ${OBJECTDIR}/timers.o timers.c  
	
${OBJECTDIR}/gyro.o: gyro.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/gyro.o.d 
	@${FIXDEPS} "${OBJECTDIR}/gyro.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/" -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/inc/" -MMD -MF "${OBJECTDIR}/gyro.o.d" -o ${OBJECTDIR}/gyro.o gyro.c  
	
${OBJECTDIR}/i2c.o: i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/i2c.o.d 
	@${FIXDEPS} "${OBJECTDIR}/i2c.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/" -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/inc/" -MMD -MF "${OBJECTDIR}/i2c.o.d" -o ${OBJECTDIR}/i2c.o i2c.c  
	
${OBJECTDIR}/imu.o: imu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/imu.o.d 
	@${FIXDEPS} "${OBJECTDIR}/imu.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/" -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/inc/" -MMD -MF "${OBJECTDIR}/imu.o.d" -o ${OBJECTDIR}/imu.o imu.c  
	
${OBJECTDIR}/mag.o: mag.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/mag.o.d 
	@${FIXDEPS} "${OBJECTDIR}/mag.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/" -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/inc/" -MMD -MF "${OBJECTDIR}/mag.o.d" -o ${OBJECTDIR}/mag.o mag.c  
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/" -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/inc/" -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c  
	
${OBJECTDIR}/radio.o: radio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/radio.o.d 
	@${FIXDEPS} "${OBJECTDIR}/radio.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/" -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/inc/" -MMD -MF "${OBJECTDIR}/radio.o.d" -o ${OBJECTDIR}/radio.o radio.c  
	
${OBJECTDIR}/accel.o: accel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/accel.o.d 
	@${FIXDEPS} "${OBJECTDIR}/accel.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/" -I"D:/My Documents/Electronics/MPLABXProjects/QuadRotorRevA2.X/inc/" -MMD -MF "${OBJECTDIR}/accel.o.d" -o ${OBJECTDIR}/accel.o accel.c  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/QuadRotorRevA2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/QuadRotorRevA2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}       -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__ICD2RAM=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1
else
dist/${CND_CONF}/${IMAGE_TYPE}/QuadRotorRevA2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/QuadRotorRevA2.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}       -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION)
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/QuadRotorRevA2.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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
