################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Part3/threads3.c 

OBJS += \
./Part3/threads3.o 

C_DEPS += \
./Part3/threads3.d 


# Each subdirectory must supply rules for building sources it contributes
Part3/%.o: ../Part3/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I/usr/bin/gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


