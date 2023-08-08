################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/DHT20.c \
../Core/Src/DHT20_FSM.c \
../Core/Src/LCD.c \
../Core/Src/Moisture.c \
../Core/Src/RGB.c \
../Core/Src/button.c \
../Core/Src/config.c \
../Core/Src/fan.c \
../Core/Src/fsmLedRgb.c \
../Core/Src/global.c \
../Core/Src/main.c \
../Core/Src/newRGB.c \
../Core/Src/scheduler.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c \
../Core/Src/timer.c 

C_DEPS += \
./Core/Src/DHT20.d \
./Core/Src/DHT20_FSM.d \
./Core/Src/LCD.d \
./Core/Src/Moisture.d \
./Core/Src/RGB.d \
./Core/Src/button.d \
./Core/Src/config.d \
./Core/Src/fan.d \
./Core/Src/fsmLedRgb.d \
./Core/Src/global.d \
./Core/Src/main.d \
./Core/Src/newRGB.d \
./Core/Src/scheduler.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d \
./Core/Src/timer.d 

OBJS += \
./Core/Src/DHT20.o \
./Core/Src/DHT20_FSM.o \
./Core/Src/LCD.o \
./Core/Src/Moisture.o \
./Core/Src/RGB.o \
./Core/Src/button.o \
./Core/Src/config.o \
./Core/Src/fan.o \
./Core/Src/fsmLedRgb.o \
./Core/Src/global.o \
./Core/Src/main.o \
./Core/Src/newRGB.o \
./Core/Src/scheduler.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o \
./Core/Src/timer.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/DHT20.d ./Core/Src/DHT20.o ./Core/Src/DHT20.su ./Core/Src/DHT20_FSM.d ./Core/Src/DHT20_FSM.o ./Core/Src/DHT20_FSM.su ./Core/Src/LCD.d ./Core/Src/LCD.o ./Core/Src/LCD.su ./Core/Src/Moisture.d ./Core/Src/Moisture.o ./Core/Src/Moisture.su ./Core/Src/RGB.d ./Core/Src/RGB.o ./Core/Src/RGB.su ./Core/Src/button.d ./Core/Src/button.o ./Core/Src/button.su ./Core/Src/config.d ./Core/Src/config.o ./Core/Src/config.su ./Core/Src/fan.d ./Core/Src/fan.o ./Core/Src/fan.su ./Core/Src/fsmLedRgb.d ./Core/Src/fsmLedRgb.o ./Core/Src/fsmLedRgb.su ./Core/Src/global.d ./Core/Src/global.o ./Core/Src/global.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/newRGB.d ./Core/Src/newRGB.o ./Core/Src/newRGB.su ./Core/Src/scheduler.d ./Core/Src/scheduler.o ./Core/Src/scheduler.su ./Core/Src/stm32f1xx_hal_msp.d ./Core/Src/stm32f1xx_hal_msp.o ./Core/Src/stm32f1xx_hal_msp.su ./Core/Src/stm32f1xx_it.d ./Core/Src/stm32f1xx_it.o ./Core/Src/stm32f1xx_it.su ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f1xx.d ./Core/Src/system_stm32f1xx.o ./Core/Src/system_stm32f1xx.su ./Core/Src/timer.d ./Core/Src/timer.o ./Core/Src/timer.su

.PHONY: clean-Core-2f-Src

