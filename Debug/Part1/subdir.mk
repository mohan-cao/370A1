################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Part1/OSA1.1.c \
../Part1/OSA1.c \
../Part1/threads0.c \
../Part1/threads1.c 

OBJS += \
./Part1/OSA1.1.o \
./Part1/OSA1.o \
./Part1/threads0.o \
./Part1/threads1.o 

C_DEPS += \
./Part1/OSA1.1.d \
./Part1/OSA1.d \
./Part1/threads0.d \
./Part1/threads1.d 


# Each subdirectory must supply rules for building sources it contributes
Part1/%.o: ../Part1/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I/usr/bin/gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


