#################################################################
# Makefile generated by Xilinx Platform Studio 
# Project:C:\tmp\MP-2\system\system.xmp
#
# WARNING : This file will be re-generated every time a command
# to run a make target is invoked. So, any changes made to this  
# file manually, will be lost when make is invoked next. 
#################################################################

SHELL = CMD

XILINX_EDK_DIR = C:/Xilinx/14.7/ISE_DS/EDK

SYSTEM = system

MHSFILE = system.mhs

PCWPRJFILE = data/ps7_system_prj.xml

FPGA_ARCH = zynq

DEVICE = xc7z020clg484-1

INTSTYLE = default

XPS_HDL_LANG = vhdl
GLOBAL_SEARCHPATHOPT = 
PROJECT_SEARCHPATHOPT =  -lp C:/tmp/MP-2/repository/

SEARCHPATHOPT = $(PROJECT_SEARCHPATHOPT) $(GLOBAL_SEARCHPATHOPT)

SUBMODULE_OPT = 

PLATGEN_OPTIONS = -p $(DEVICE) -lang $(XPS_HDL_LANG) -intstyle $(INTSTYLE) $(SEARCHPATHOPT) $(SUBMODULE_OPT) -msg __xps/ise/xmsgprops.lst

OBSERVE_PAR_OPTIONS = -error no

MICROBLAZE_BOOTLOOP = $(XILINX_EDK_DIR)/sw/lib/microblaze/mb_bootloop.elf
MICROBLAZE_BOOTLOOP_LE = $(XILINX_EDK_DIR)/sw/lib/microblaze/mb_bootloop_le.elf
PPC405_BOOTLOOP = $(XILINX_EDK_DIR)/sw/lib/ppc405/ppc_bootloop.elf
PPC440_BOOTLOOP = $(XILINX_EDK_DIR)/sw/lib/ppc440/ppc440_bootloop.elf
BOOTLOOP_DIR = bootloops

BRAMINIT_ELF_IMP_FILES =
BRAMINIT_ELF_IMP_FILE_ARGS =

BRAMINIT_ELF_SIM_FILES =
BRAMINIT_ELF_SIM_FILE_ARGS =

SIM_CMD = isim_system

BEHAVIORAL_SIM_SCRIPT = simulation/behavioral/$(SYSTEM)_setup.tcl

STRUCTURAL_SIM_SCRIPT = simulation/structural/$(SYSTEM)_setup.tcl

TIMING_SIM_SCRIPT = simulation/timing/$(SYSTEM)_setup.tcl

DEFAULT_SIM_SCRIPT = $(BEHAVIORAL_SIM_SCRIPT)

SIMGEN_OPTIONS = -p $(DEVICE) -lang $(XPS_HDL_LANG) -intstyle $(INTSTYLE) $(SEARCHPATHOPT) $(BRAMINIT_ELF_SIM_FILE_ARGS) -msg __xps/ise/xmsgprops.lst -s isim -X C:/tmp/MP-2/system/


CORE_STATE_DEVELOPMENT_FILES = 

WRAPPER_NGC_FILES = implementation/system_v_vid_in_axi4s_0_wrapper.ngc \
implementation/system_v_tc_1_wrapper.ngc \
implementation/system_v_tc_0_wrapper.ngc \
implementation/system_v_scaler_0_wrapper.ngc \
implementation/system_v_axi4s_vid_out_0_wrapper.ngc \
implementation/system_processing_system7_0_wrapper.ngc \
implementation/system_fmc_imageon_iic_0_wrapper.ngc \
implementation/system_fmc_imageon_hdmi_out_0_wrapper.ngc \
implementation/system_clock_generator_1_wrapper.ngc \
implementation/system_axi_vdma_0_wrapper.ngc \
implementation/system_axi_tpg_0_wrapper.ngc \
implementation/system_axi_interconnect_1_wrapper.ngc \
implementation/system_axi4lite_0_wrapper.ngc \
implementation/system_sws_8bits_wrapper.ngc \
implementation/system_iic_fmc_wrapper.ngc \
implementation/system_btns_5bits_wrapper.ngc

POSTSYN_NETLIST = implementation/$(SYSTEM).ngc

SYSTEM_BIT = implementation/$(SYSTEM).bit

DOWNLOAD_BIT = implementation/download.bit

SYSTEM_ACE = implementation/$(SYSTEM).ace

UCF_FILE = data\system.ucf

BMM_FILE = implementation/$(SYSTEM).bmm

BITGEN_UT_FILE = etc/bitgen.ut

XFLOW_OPT_FILE = etc/fast_runtime.opt
XFLOW_DEPENDENCY = __xps/xpsxflow.opt $(XFLOW_OPT_FILE)

XPLORER_DEPENDENCY = __xps/xplorer.opt
XPLORER_OPTIONS = -p $(DEVICE) -uc $(SYSTEM).ucf -bm $(SYSTEM).bmm -max_runs 7

FPGA_IMP_DEPENDENCY = $(BMM_FILE) $(POSTSYN_NETLIST) $(UCF_FILE) $(XFLOW_DEPENDENCY)

SDK_EXPORT_DIR = SDK\SDK_Export\hw
SYSTEM_HW_HANDOFF = $(SDK_EXPORT_DIR)/$(SYSTEM).xml
SYSTEM_HW_HANDOFF_BIT = $(SDK_EXPORT_DIR)/$(SYSTEM).bit
SYSTEM_HW_HANDOFF_DEP = $(SYSTEM_HW_HANDOFF) $(SYSTEM_HW_HANDOFF_BIT)
