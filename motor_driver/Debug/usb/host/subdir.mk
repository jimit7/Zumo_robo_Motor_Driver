################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../usb/host/usb_host_devices.c \
../usb/host/usb_host_ehci.c \
../usb/host/usb_host_framework.c \
../usb/host/usb_host_hci.c \
../usb/host/usb_host_ip3516hs.c \
../usb/host/usb_host_khci.c \
../usb/host/usb_host_ohci.c 

OBJS += \
./usb/host/usb_host_devices.o \
./usb/host/usb_host_ehci.o \
./usb/host/usb_host_framework.o \
./usb/host/usb_host_hci.o \
./usb/host/usb_host_ip3516hs.o \
./usb/host/usb_host_khci.o \
./usb/host/usb_host_ohci.o 

C_DEPS += \
./usb/host/usb_host_devices.d \
./usb/host/usb_host_ehci.d \
./usb/host/usb_host_framework.d \
./usb/host/usb_host_hci.d \
./usb/host/usb_host_ip3516hs.d \
./usb/host/usb_host_khci.d \
./usb/host/usb_host_ohci.d 


# Each subdirectory must supply rules for building sources it contributes
usb/host/%.o: ../usb/host/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_LPC54114J256BD64 -DCPU_LPC54114J256BD64_cm4 -D__LPC5411X__ -DCORE_M4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -D__MULTICORE_MASTER -I../board -I../source -I../ -I../drivers -I../CMSIS -I../device -I../component/serial_manager -I../component/uart -I../utilities -I../usb/include -I../usb/phy -I../osa -I../usb/device/class -I../usb/device/source -I../usb/device/include -I../usb/device/source/ehci -I../usb/device/source/khci -I../usb/device/source/lpcip3511 -I../source/generated -I../usb/host/class -I../usb/host -I../startup -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


