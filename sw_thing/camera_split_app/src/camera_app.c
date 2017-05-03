/*****************************************************************************
 * Joseph Zambreno
 * Phillip Jones
 *
 * Department of Electrical and Computer Engineering
 * Iowa State University
 *****************************************************************************/

/*****************************************************************************
 * camera_app.c - main camera application code. The camera configures the various
 * video in and video out peripherals, and (optionally) performs some
 * image processing on data coming in from the vdma.
 *
 *
 * NOTES:
 * 02/04/14 by JAZ::Design created.
 *****************************************************************************/

#include "camera_app.h"
#include "scaler_config.h"
#include "xscaler.h"
#define SCALER_BASE_ADDR

camera_config_t camera_config;




// Main function. Initializes the devices and configures VDMA
int main() {



	XScaler_Config x = {3,0x52300000,2,2,3,0,422,3,3};

	XScaler y;

	XScalerAperture z;
	XScalerStartFraction h;

	XScaler_IsEnabled(&y);
	XScaler_Enable(&y);



	/* Initialization */
	XScaler_CfgInitialize(&y, &x, 0x5230000);


	/* Aperture & Scale */
	XScaler_SetAperture(&y, &z);
	XScaler_GetAperture(&y, &z);

	/* Phase */
	XScaler_SetPhaseNum(&y, u16 VertPhaseNum, u16 HoriPhaseNum);
	XScaler_GetPhaseNum(&y, u16 *VertPhaseNumPtr,u16 *HoriPhaseNumPtr);

	/* Start Fractional value setting */
	XScaler_SetStartFraction(&y, XScalerStartFraction *StartFractionPtr);
	XScaler_GetStartFraction(&y, XScalerStartFraction *StartFractionPtr);

	/* Coefficient functions */
	s16 *XScaler_CoefValueLookup(u32 InSize, u32 OutSize, u32 Tap, u32 Phase);
	XScaler_LoadCoeffBank(&y, XScalerCoeffBank *CoeffBankPtr);


	XScaler_SetActiveCoeffSet(&y, u8 VertSetIndex, u8 HoriSetIndex);


	XScaler_GetActiveCoeffSet(&y, u8 *VertSetIndexPtr, u8 *HoriSetIndexPtr);


	XScaler_GetCoeffBankSharingInfo(XScaler *InstancePtr, u8 *ChromaFormat, u8 *ChromaLumaShareCoeff, u8 *HoriVertShareCoeff);





//	xil_printf("Entering scaler\r\n");
//	scaler_init();
//	xil_printf("Exiting scaler\r\n");

	camera_config_init(&camera_config);
	xil_printf("Entering fmc\r\n");
	fmc_imageon_enable(&camera_config);

//	camera_loop(&camera_config);

	return 0;
}

//void scaler_init() {
//#define OUTPUT_SIZE_OFFSET 0x0114
//	u32* baseadr = 0x52300000;
//	//enable_sw_scaler(baseadr);
//
//
//	(*baseadr) |= 0x0001;
//	xil_printf("Exiting enable_sw_scaler\r\n");
//
//	//set_output_size(baseadr);
//
//	*(baseadr + OUTPUT_SIZE_OFFSET) &= 0x7070; //clear 0-12 and 16-28 perserve others
//
//	*(baseadr + OUTPUT_SIZE_OFFSET) |= 1920; // set lower 12 bits to starting pixel
//
//	*(baseadr + OUTPUT_SIZE_OFFSET) |= (1080 << 16); //set bits 16-28 to stopping pixel
//	xil_printf("Exiting output_size\r\n");
//
//
//
//	set_input_size(baseadr);
//	xil_printf("Exiting input_size\r\n");
//
//	set_aperature(baseadr, 0, 400, 0, 400);
//	xil_printf("Exiting set_aperature\r\n");
//
//	set_scale_factor(baseadr, 1.1, 1.1);
//}

// Initialize the camera configuration data structure
void camera_config_init(camera_config_t *config) {

	config->uBaseAddr_IIC_FmcIpmi = XPAR_IIC_FMC_BASEADDR;
	config->uBaseAddr_IIC_FmcImageon = XPAR_FMC_IMAGEON_IIC_0_BASEADDR;
//    config->uBaseAddr_VITA_Receiver = XPAR_FMC_IMAGEON_VITA_RECEIVER_0_BASEADDR;
//    config->uBaseAddr_CFA = XPAR_CFA_0_BASEADDR;
//    config->uBaseAddr_CRES = XPAR_CRESAMPLE_0_BASEADDR;
//    config->uBaseAddr_RGBYCC = XPAR_RGB2YCRCB_0_BASEADDR;
	config->uBaseAddr_TPG_PatternGenerator = XPAR_AXI_TPG_0_BASEADDR;

	config->uDeviceId_VTC_ipipe = XPAR_V_TC_0_DEVICE_ID;
	config->uDeviceId_VTC_tpg = XPAR_V_TC_1_DEVICE_ID;

	config->uDeviceId_VDMA_HdmiFrameBuffer = XPAR_AXI_VDMA_0_DEVICE_ID;
	config->uBaseAddr_MEM_HdmiFrameBuffer = XPAR_DDR_MEM_BASEADDR + 0x10000000;
	config->uNumFrames_HdmiFrameBuffer = XPAR_AXIVDMA_0_NUM_FSTORES;

	return;
}

// Main (SW) processing loop. Recommended to have an explicit exit condition
void camera_loop(camera_config_t *config) {

	Xuint32 parkptr;
	Xuint32 vdma_S2MM_DMACR, vdma_MM2S_DMACR;
	int i, j;

	xil_printf("Entering main SW processing loop\r\n");

	// Grab the DMA parkptr, and update it to ensure that when parked, the S2MM side is on frame 0, and the MM2S side on frame 1
	parkptr =
			XAxiVdma_ReadReg(config->vdma_hdmi.BaseAddr, XAXIVDMA_PARKPTR_OFFSET);
	parkptr &= ~XAXIVDMA_PARKPTR_READREF_MASK;
	parkptr &= ~XAXIVDMA_PARKPTR_WRTREF_MASK;
	parkptr |= 0x1;
	XAxiVdma_WriteReg(config->vdma_hdmi.BaseAddr, XAXIVDMA_PARKPTR_OFFSET,
			parkptr);

	// Grab the DMA Control Registers, and clear circular park mode.
	vdma_MM2S_DMACR =
			XAxiVdma_ReadReg(config->vdma_hdmi.BaseAddr, XAXIVDMA_TX_OFFSET+XAXIVDMA_CR_OFFSET);
	XAxiVdma_WriteReg(config->vdma_hdmi.BaseAddr,
			XAXIVDMA_TX_OFFSET+XAXIVDMA_CR_OFFSET,
			vdma_MM2S_DMACR & ~XAXIVDMA_CR_TAIL_EN_MASK);
	vdma_S2MM_DMACR =
			XAxiVdma_ReadReg(config->vdma_hdmi.BaseAddr, XAXIVDMA_RX_OFFSET+XAXIVDMA_CR_OFFSET);
	XAxiVdma_WriteReg(config->vdma_hdmi.BaseAddr,
			XAXIVDMA_RX_OFFSET+XAXIVDMA_CR_OFFSET,
			vdma_S2MM_DMACR & ~XAXIVDMA_CR_TAIL_EN_MASK);

	// Pointers to the S2MM memory frame and M2SS memory frame
	volatile Xuint16 *pS2MM_Mem =
			(Xuint16 *) XAxiVdma_ReadReg(config->vdma_hdmi.BaseAddr, XAXIVDMA_S2MM_ADDR_OFFSET+XAXIVDMA_START_ADDR_OFFSET);
	volatile Xuint16 *pMM2S_Mem =
			(Xuint16 *) XAxiVdma_ReadReg(config->vdma_hdmi.BaseAddr, XAXIVDMA_MM2S_ADDR_OFFSET+XAXIVDMA_START_ADDR_OFFSET+4);

	// Run for 1000 frames before going back to HW mode
	for (j = 0; j < 1000; j++) {
		for (i = 0; i < 1920 * 1080; i++) {
			pMM2S_Mem[i] = pS2MM_Mem[1920 * 1080 - i - 1];
		}
	}

	// Grab the DMA Control Registers, and re-enable circular park mode.
	vdma_MM2S_DMACR =
			XAxiVdma_ReadReg(config->vdma_hdmi.BaseAddr, XAXIVDMA_TX_OFFSET+XAXIVDMA_CR_OFFSET);
	XAxiVdma_WriteReg(config->vdma_hdmi.BaseAddr,
			XAXIVDMA_TX_OFFSET+XAXIVDMA_CR_OFFSET,
			vdma_MM2S_DMACR | XAXIVDMA_CR_TAIL_EN_MASK);
	vdma_S2MM_DMACR =
			XAxiVdma_ReadReg(config->vdma_hdmi.BaseAddr, XAXIVDMA_RX_OFFSET+XAXIVDMA_CR_OFFSET);
	XAxiVdma_WriteReg(config->vdma_hdmi.BaseAddr,
			XAXIVDMA_RX_OFFSET+XAXIVDMA_CR_OFFSET,
			vdma_S2MM_DMACR | XAXIVDMA_CR_TAIL_EN_MASK);

	xil_printf("Main SW processing loop complete!\r\n");

	return;
}
