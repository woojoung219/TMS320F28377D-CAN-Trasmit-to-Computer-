################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1220/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --fp_mode=relaxed --include_path="C:/Users/LG/workspace_CCS12/5_CAN_Transmit_Receive" --include_path="C:/Users/LG/workspace_CCS12/5_CAN_Transmit_Receive/device" --include_path="C:/Users/LG/workspace_CCS12/5_CAN_Transmit_Receive/device/device_support/common/Include" --include_path="C:/Users/LG/workspace_CCS12/5_CAN_Transmit_Receive/device/device_support/headers/Include" --include_path="C:/Users/LG/workspace_CCS12/5_CAN_Transmit_Receive/device/driverlib" --include_path="C:/ti/ccs1220/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --advice:performance=all --define=DEBUG --define=_DUAL_HEADERS --define=CPU1 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --gen_data_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.obj: ../%.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1220/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --fp_mode=relaxed --include_path="C:/Users/LG/workspace_CCS12/5_CAN_Transmit_Receive" --include_path="C:/Users/LG/workspace_CCS12/5_CAN_Transmit_Receive/device" --include_path="C:/Users/LG/workspace_CCS12/5_CAN_Transmit_Receive/device/device_support/common/Include" --include_path="C:/Users/LG/workspace_CCS12/5_CAN_Transmit_Receive/device/device_support/headers/Include" --include_path="C:/Users/LG/workspace_CCS12/5_CAN_Transmit_Receive/device/driverlib" --include_path="C:/ti/ccs1220/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --advice:performance=all --define=DEBUG --define=_DUAL_HEADERS --define=CPU1 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --gen_data_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


