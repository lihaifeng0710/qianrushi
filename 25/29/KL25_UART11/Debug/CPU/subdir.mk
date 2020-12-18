################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CPU/sysinit.c \
../CPU/vectors.c 

OBJS += \
./CPU/sysinit.o \
./CPU/vectors.o 

C_DEPS += \
./CPU/sysinit.d \
./CPU/vectors.d 


# Each subdirectory must supply rules for building sources it contributes
CPU/%.o: ../CPU/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -I"E:/workspace_kds/KL25_UART/Sources" -I"E:/workspace_kds/KL25_UART/Drivers/uart" -I"E:/workspace_kds/KL25_UART/SwComponents" -I"E:/workspace_kds/KL25_UART/SwComponents/light" -I"E:/workspace_kds/KL25_UART/Drivers" -I"E:/workspace_kds/KL25_UART/Common" -I"E:/workspace_kds/KL25_UART/CPU" -I"E:/workspace_kds/KL25_UART/Doc" -I"E:/workspace_kds/KL25_UART/Drivers/gpio" -I"E:/workspace_kds/KL25_UART/Project_Settings/Startup_Code" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


