################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../03_MCU/MCU_drivers/flash.c \
../03_MCU/MCU_drivers/gpio.c \
../03_MCU/MCU_drivers/i2c.c \
../03_MCU/MCU_drivers/systick.c \
../03_MCU/MCU_drivers/uart.c \
../03_MCU/MCU_drivers/wdog.c 

OBJS += \
./03_MCU/MCU_drivers/flash.o \
./03_MCU/MCU_drivers/gpio.o \
./03_MCU/MCU_drivers/i2c.o \
./03_MCU/MCU_drivers/systick.o \
./03_MCU/MCU_drivers/uart.o \
./03_MCU/MCU_drivers/wdog.o 

C_DEPS += \
./03_MCU/MCU_drivers/flash.d \
./03_MCU/MCU_drivers/gpio.d \
./03_MCU/MCU_drivers/i2c.d \
./03_MCU/MCU_drivers/systick.d \
./03_MCU/MCU_drivers/uart.d \
./03_MCU/MCU_drivers/wdog.d 


# Each subdirectory must supply rules for building sources it contributes
03_MCU/MCU_drivers/%.o: ../03_MCU/MCU_drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O1 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:\Users\wangheng\Desktop\CH06-UART-20200902\UART_KL36_20200907\02_CPU" -I"C:\Users\wangheng\Desktop\CH06-UART-20200902\UART_KL36_20200907\03_MCU" -I"C:\Users\wangheng\Desktop\CH06-UART-20200902\UART_KL36_20200907\03_MCU\linker_file" -I"C:\Users\wangheng\Desktop\CH06-UART-20200902\UART_KL36_20200907\03_MCU\MCU_drivers" -I"C:\Users\wangheng\Desktop\CH06-UART-20200902\UART_KL36_20200907\03_MCU\startup" -I"C:\Users\wangheng\Desktop\CH06-UART-20200902\UART_KL36_20200907\04_GEC" -I"C:\Users\wangheng\Desktop\CH06-UART-20200902\UART_KL36_20200907\05_UserBoard" -I"C:\Users\wangheng\Desktop\CH06-UART-20200902\UART_KL36_20200907\06_SoftComponent" -I"C:\Users\wangheng\Desktop\CH06-UART-20200902\UART_KL36_20200907\07_NosPrg" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


