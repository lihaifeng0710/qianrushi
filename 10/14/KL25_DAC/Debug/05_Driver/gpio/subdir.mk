################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../05_Driver/gpio/gpio.c 

OBJS += \
./05_Driver/gpio/gpio.o 

C_DEPS += \
./05_Driver/gpio/gpio.d 


# Each subdirectory must supply rules for building sources it contributes
05_Driver/gpio/%.o: ../05_Driver/gpio/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -I"C:/Users/Administrator/Desktop/qianrushi/jifanganzhuang/SD-FSL-KL25-CD(V3.3)KDS-20141009/KL25-Program/ch10-ADC-DAC-CMP(KDS)/KL25_DAC/08_Source" -I"C:/Users/Administrator/Desktop/qianrushi/jifanganzhuang/SD-FSL-KL25-CD(V3.3)KDS-20141009/KL25-Program/ch10-ADC-DAC-CMP(KDS)/KL25_DAC/05_Driver/uart" -I"C:/Users/Administrator/Desktop/qianrushi/jifanganzhuang/SD-FSL-KL25-CD(V3.3)KDS-20141009/KL25-Program/ch10-ADC-DAC-CMP(KDS)/KL25_DAC/06_App_Component" -I"C:/Users/Administrator/Desktop/qianrushi/jifanganzhuang/SD-FSL-KL25-CD(V3.3)KDS-20141009/KL25-Program/ch10-ADC-DAC-CMP(KDS)/KL25_DAC/06_App_Component/light" -I"C:/Users/Administrator/Desktop/qianrushi/jifanganzhuang/SD-FSL-KL25-CD(V3.3)KDS-20141009/KL25-Program/ch10-ADC-DAC-CMP(KDS)/KL25_DAC/05_Driver" -I"C:/Users/Administrator/Desktop/qianrushi/jifanganzhuang/SD-FSL-KL25-CD(V3.3)KDS-20141009/KL25-Program/ch10-ADC-DAC-CMP(KDS)/KL25_DAC/07_Soft_Component/common" -I"C:/Users/Administrator/Desktop/qianrushi/jifanganzhuang/SD-FSL-KL25-CD(V3.3)KDS-20141009/KL25-Program/ch10-ADC-DAC-CMP(KDS)/KL25_DAC/07_Soft_Component" -I"C:/Users/Administrator/Desktop/qianrushi/jifanganzhuang/SD-FSL-KL25-CD(V3.3)KDS-20141009/KL25-Program/ch10-ADC-DAC-CMP(KDS)/KL25_DAC/02_CPU" -I"C:/Users/Administrator/Desktop/qianrushi/jifanganzhuang/SD-FSL-KL25-CD(V3.3)KDS-20141009/KL25-Program/ch10-ADC-DAC-CMP(KDS)/KL25_DAC/03_MCU" -I"C:/Users/Administrator/Desktop/qianrushi/jifanganzhuang/SD-FSL-KL25-CD(V3.3)KDS-20141009/KL25-Program/ch10-ADC-DAC-CMP(KDS)/KL25_DAC/04_Linker_File" -I"C:/Users/Administrator/Desktop/qianrushi/jifanganzhuang/SD-FSL-KL25-CD(V3.3)KDS-20141009/KL25-Program/ch10-ADC-DAC-CMP(KDS)/KL25_DAC/01_Doc" -I"C:/Users/Administrator/Desktop/qianrushi/jifanganzhuang/SD-FSL-KL25-CD(V3.3)KDS-20141009/KL25-Program/ch10-ADC-DAC-CMP(KDS)/KL25_DAC/05_Driver/gpio" -I"C:/Users/Administrator/Desktop/qianrushi/jifanganzhuang/SD-FSL-KL25-CD(V3.3)KDS-20141009/KL25-Program/ch10-ADC-DAC-CMP(KDS)/KL25_DAC/05_Driver/dac" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


