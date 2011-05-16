# List of all the ChibiOS/RT HAL files, there is no need to remove the files
# from this list, you can disable parts of the kernel by editing halconf.h.
HALSRC = ${CHIBIOS}/os/hal/src/hal.c \
         ${CHIBIOS}/os/hal/src/adc.c \
         ${CHIBIOS}/os/hal/src/can.c \
         ${CHIBIOS}/os/hal/src/mac.c \
         ${CHIBIOS}/os/hal/src/pal.c \
         ${CHIBIOS}/os/hal/src/pwm.c \
         ${CHIBIOS}/os/hal/src/serial.c \
         ${CHIBIOS}/os/hal/src/spi.c \
         ${CHIBIOS}/os/hal/src/uart.c \
         ${CHIBIOS}/os/hal/src/mmc_spi.c

# Required include directories
HALINC = ${CHIBIOS}/os/hal/include
