################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ICU.c \
../LCD.c \
../LED.c \
../Main_App.c \
../US_Sensor.c \
../buzzer.c \
../gpio.c 

OBJS += \
./ICU.o \
./LCD.o \
./LED.o \
./Main_App.o \
./US_Sensor.o \
./buzzer.o \
./gpio.o 

C_DEPS += \
./ICU.d \
./LCD.d \
./LED.d \
./Main_App.d \
./US_Sensor.d \
./buzzer.d \
./gpio.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


