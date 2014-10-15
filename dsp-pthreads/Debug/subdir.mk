################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../gnuplot.cc \
../list.cc \
../main.cc \
../stages.cc 

OBJS += \
./gnuplot.o \
./list.o \
./main.o \
./stages.o 

CC_DEPS += \
./gnuplot.d \
./list.d \
./main.d \
./stages.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/home/luis/gnuplot-iostream -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


