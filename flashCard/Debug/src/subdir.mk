################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/db.cpp \
../src/main.cpp \
../src/menu.cpp \
../src/set.cpp 

OBJS += \
./src/db.o \
./src/main.o \
./src/menu.o \
./src/set.o 

CPP_DEPS += \
./src/db.d \
./src/main.d \
./src/menu.d \
./src/set.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++14 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


