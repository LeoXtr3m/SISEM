################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
src/algoritmo.obj: C:/Users/LeoXtr3m/workspace_v8/CCS/subirEscaleras/src/algoritmo.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/Programas extras/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.4.LTS/bin/cl430" -vmsp --use_hw_mpy=none --include_path="C:/Programas extras/ti/ccsv8/ccs_base/msp430/include" --include_path="C:/Users/LeoXtr3m/workspace_v8/CCS/subirEscaleras/include" --include_path="C:/Users/LeoXtr3m/workspace_v8/CCS/subirEscaleras/test/Round-robin" --include_path="C:/Programas extras/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.4.LTS/include" --advice:power=all --define=__MSP430G2553__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="src/$(basename $(<F)).d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/i2c.obj: C:/Users/LeoXtr3m/workspace_v8/CCS/subirEscaleras/src/i2c.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/Programas extras/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.4.LTS/bin/cl430" -vmsp --use_hw_mpy=none --include_path="C:/Programas extras/ti/ccsv8/ccs_base/msp430/include" --include_path="C:/Users/LeoXtr3m/workspace_v8/CCS/subirEscaleras/include" --include_path="C:/Users/LeoXtr3m/workspace_v8/CCS/subirEscaleras/test/Round-robin" --include_path="C:/Programas extras/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.4.LTS/include" --advice:power=all --define=__MSP430G2553__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="src/$(basename $(<F)).d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/imu.obj: C:/Users/LeoXtr3m/workspace_v8/CCS/subirEscaleras/src/imu.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/Programas extras/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.4.LTS/bin/cl430" -vmsp --use_hw_mpy=none --include_path="C:/Programas extras/ti/ccsv8/ccs_base/msp430/include" --include_path="C:/Users/LeoXtr3m/workspace_v8/CCS/subirEscaleras/include" --include_path="C:/Users/LeoXtr3m/workspace_v8/CCS/subirEscaleras/test/Round-robin" --include_path="C:/Programas extras/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.4.LTS/include" --advice:power=all --define=__MSP430G2553__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="src/$(basename $(<F)).d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/timer_hw.obj: C:/Users/LeoXtr3m/workspace_v8/CCS/subirEscaleras/src/timer_hw.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/Programas extras/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.4.LTS/bin/cl430" -vmsp --use_hw_mpy=none --include_path="C:/Programas extras/ti/ccsv8/ccs_base/msp430/include" --include_path="C:/Users/LeoXtr3m/workspace_v8/CCS/subirEscaleras/include" --include_path="C:/Users/LeoXtr3m/workspace_v8/CCS/subirEscaleras/test/Round-robin" --include_path="C:/Programas extras/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.4.LTS/include" --advice:power=all --define=__MSP430G2553__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="src/$(basename $(<F)).d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/uart.obj: C:/Users/LeoXtr3m/workspace_v8/CCS/subirEscaleras/src/uart.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/Programas extras/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.4.LTS/bin/cl430" -vmsp --use_hw_mpy=none --include_path="C:/Programas extras/ti/ccsv8/ccs_base/msp430/include" --include_path="C:/Users/LeoXtr3m/workspace_v8/CCS/subirEscaleras/include" --include_path="C:/Users/LeoXtr3m/workspace_v8/CCS/subirEscaleras/test/Round-robin" --include_path="C:/Programas extras/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.4.LTS/include" --advice:power=all --define=__MSP430G2553__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="src/$(basename $(<F)).d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/utils.obj: C:/Users/LeoXtr3m/workspace_v8/CCS/subirEscaleras/src/utils.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/Programas extras/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.4.LTS/bin/cl430" -vmsp --use_hw_mpy=none --include_path="C:/Programas extras/ti/ccsv8/ccs_base/msp430/include" --include_path="C:/Users/LeoXtr3m/workspace_v8/CCS/subirEscaleras/include" --include_path="C:/Users/LeoXtr3m/workspace_v8/CCS/subirEscaleras/test/Round-robin" --include_path="C:/Programas extras/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.4.LTS/include" --advice:power=all --define=__MSP430G2553__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="src/$(basename $(<F)).d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


