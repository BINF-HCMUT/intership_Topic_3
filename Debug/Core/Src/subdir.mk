################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/DHT.c \
../Core/Src/DHT20_FSM.c \
../Core/Src/PWM.c \
../Core/Src/adc.c \
../Core/Src/button.c \
../Core/Src/dma.c \
../Core/Src/fan.c \
../Core/Src/fsmLedRgb.c \
../Core/Src/global.c \
../Core/Src/gpio.c \
../Core/Src/i2c-lcd.c \
../Core/Src/i2c.c \
../Core/Src/main.c \
../Core/Src/newRGB.c \
../Core/Src/scheduler.c \
../Core/Src/software_timer.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c \
../Core/Src/tim.c 

OBJS += \
./Core/Src/DHT.o \
./Core/Src/DHT20_FSM.o \
./Core/Src/PWM.o \
./Core/Src/adc.o \
./Core/Src/button.o \
./Core/Src/dma.o \
./Core/Src/fan.o \
./Core/Src/fsmLedRgb.o \
./Core/Src/global.o \
./Core/Src/gpio.o \
./Core/Src/i2c-lcd.o \
./Core/Src/i2c.o \
./Core/Src/main.o \
./Core/Src/newRGB.o \
./Core/Src/scheduler.o \
./Core/Src/software_timer.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o \
./Core/Src/tim.o 

C_DEPS += \
./Core/Src/DHT.d \
./Core/Src/DHT20_FSM.d \
./Core/Src/PWM.d \
./Core/Src/adc.d \
./Core/Src/button.d \
./Core/Src/dma.d \
./Core/Src/fan.d \
./Core/Src/fsmLedRgb.d \
./Core/Src/global.d \
./Core/Src/gpio.d \
./Core/Src/i2c-lcd.d \
./Core/Src/i2c.d \
./Core/Src/main.d \
./Core/Src/newRGB.d \
./Core/Src/scheduler.d \
./Core/Src/software_timer.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d \
./Core/Src/tim.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

