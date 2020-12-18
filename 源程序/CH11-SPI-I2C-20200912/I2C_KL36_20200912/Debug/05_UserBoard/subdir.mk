################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../05_UserBoard/printf.c 

OBJS += \
./05_UserBoard/printf.o 

C_DEPS += \
./05_UserBoard/printf.d 


# Each subdirectory must supply rules for building sources it contributes
05_UserBoard/%.o: ../05_UserBoard/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O1 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:\Users\wangheng\Desktop\CH06-UART-20200902\UART_KL36_20200907\02_CPU" -I"C:\Users\wangheng\Desktop\CH06-UART-20200902\UART_KL36_20200907\03_MCU" -I"C:\Users\wangheng\Desktop\CH06-UART-20200902\UART_KL36_20200907\03_MCU\linker_file" -I"C:\Users\wangheng\Desktop\CH06-UART-20200902\UART_KL36_20200907\03_MCU\MCU_drivers" -I"C:\Users\wangheng\Desktop\CH06-UART-20200902\UART_KL36_20200907\03_MCU\startup" -I"C:\Users\wangheng\Desktop\CH06-UART-20200902\UART_KL36_20200907\04_GEC" -I"C:\Users\wangheng\Desktop\CH06-UART-20200902\UART_KL36_20200907\05_UserBoard" -I"C:\Users\wangheng\Desktop\CH06-UART-20200902\UART_KL36_20200907\06_SoftComponent" -I"C:\Users\wangheng\Desktop\CH06-UART-20200902\UART_KL36_20200907\07_NosPrg" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


