################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/Src/Timer.c \
../HAL/Src/UART.c 

OBJS += \
./HAL/Src/Timer.o \
./HAL/Src/UART.o 

C_DEPS += \
./HAL/Src/Timer.d \
./HAL/Src/UART.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/Src/%.o HAL/Src/%.su HAL/Src/%.cyclo: ../HAL/Src/%.c HAL/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../HAL -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-HAL-2f-Src

clean-HAL-2f-Src:
	-$(RM) ./HAL/Src/Timer.cyclo ./HAL/Src/Timer.d ./HAL/Src/Timer.o ./HAL/Src/Timer.su ./HAL/Src/UART.cyclo ./HAL/Src/UART.d ./HAL/Src/UART.o ./HAL/Src/UART.su

.PHONY: clean-HAL-2f-Src

