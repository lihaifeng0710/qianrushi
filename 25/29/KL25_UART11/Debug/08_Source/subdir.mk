################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../08_Source/isr.c \
../08_Source/main.c 

OBJS += \
./08_Source/isr.o \
./08_Source/main.o 

C_DEPS += \
./08_Source/isr.d \
./08_Source/main.d 


# Each subdirectory must supply rules for building sources it contributes
08_Source/%.o: ../08_Source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -I"C:/Users/Administrator/Desktop/kaoshi/29/KL25_UART11/08_Source" -I"C:/Users/Administrator/Desktop/kaoshi/29/KL25_UART11/07_Soft_Component" -I"C:/Users/Administrator/Desktop/kaoshi/29/KL25_UART11/07_Soft_Component/common" -I"C:/Users/Administrator/Desktop/kaoshi/29/KL25_UART11/04_Linker_File" -I"C:/Users/Administrator/Desktop/kaoshi/29/KL25_UART11/05_Driver/uart" -I"C:/Users/Administrator/Desktop/kaoshi/29/KL25_UART11/06_App_Component" -I"C:/Users/Administrator/Desktop/kaoshi/29/KL25_UART11/06_App_Component/light" -I"C:/Users/Administrator/Desktop/kaoshi/29/KL25_UART11/05_Driver" -I"C:/Users/Administrator/Desktop/kaoshi/29/KL25_UART11/03_MCU" -I"C:/Users/Administrator/Desktop/kaoshi/29/KL25_UART11/02_CPU" -I"C:/Users/Administrator/Desktop/kaoshi/29/KL25_UART11/01_Doc" -I"C:/Users/Administrator/Desktop/kaoshi/29/KL25_UART11/05_Driver/gpio" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


