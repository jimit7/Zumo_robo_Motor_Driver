################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../usb/host/class/usb_host_audio.c \
../usb/host/class/usb_host_cdc.c \
../usb/host/class/usb_host_hid.c \
../usb/host/class/usb_host_hub.c \
../usb/host/class/usb_host_hub_app.c \
../usb/host/class/usb_host_msd.c \
../usb/host/class/usb_host_msd_ufi.c \
../usb/host/class/usb_host_phdc.c \
../usb/host/class/usb_host_printer.c 

OBJS += \
./usb/host/class/usb_host_audio.o \
./usb/host/class/usb_host_cdc.o \
./usb/host/class/usb_host_hid.o \
./usb/host/class/usb_host_hub.o \
./usb/host/class/usb_host_hub_app.o \
./usb/host/class/usb_host_msd.o \
./usb/host/class/usb_host_msd_ufi.o \
./usb/host/class/usb_host_phdc.o \
./usb/host/class/usb_host_printer.o 

C_DEPS += \
./usb/host/class/usb_host_audio.d \
./usb/host/class/usb_host_cdc.d \
./usb/host/class/usb_host_hid.d \
./usb/host/class/usb_host_hub.d \
./usb/host/class/usb_host_hub_app.d \
./usb/host/class/usb_host_msd.d \
./usb/host/class/usb_host_msd_ufi.d \
./usb/host/class/usb_host_phdc.d \
./usb/host/class/usb_host_printer.d 


# Each subdirectory must supply rules for building sources it contributes
usb/host/class/%.o: ../usb/host/class/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_LPC54114J256BD64 -DCPU_LPC54114J256BD64_cm4 -D__LPC5411X__ -DCORE_M4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -D__MULTICORE_MASTER -I../board -I../source -I../ -I../drivers -I../CMSIS -I../device -I../component/serial_manager -I../component/uart -I../utilities -I../usb/include -I../usb/phy -I../osa -I../usb/device/class -I../usb/device/source -I../usb/device/include -I../usb/device/source/ehci -I../usb/device/source/khci -I../usb/device/source/lpcip3511 -I../source/generated -I../usb/host/class -I../usb/host -I../startup -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


