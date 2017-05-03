/* $Id: */
/******************************************************************************
* (c) Copyright 2009 Xilinx, Inc. All rights reserved.
*
* This file contains confidential and proprietary information
* of Xilinx, Inc. and is protected under U.S. and
* international copyright and other intellectual property
* laws.
*
* DISCLAIMER
* This disclaimer is not a license and does not grant any
* rights to the materials distributed herewith. Except as
* otherwise provided in a valid license issued to you by
* Xilinx, and to the maximum extent permitted by applicable
* law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND
* WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
* AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
* BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
* INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
* (2) Xilinx shall not be liable (whether in contract or tort,
* including negligence, or under any other theory of
* liability) for any loss or damage of any kind or nature
* related to, arising under or in connection with these
* materials, including for any direct, or any indirect,
* special, incidental, or consequential loss or damage
* (including loss of data, profits, goodwill, or any type of
* loss or damage suffered as a result of any action brought
* by a third party) even if such damage or loss was
* reasonably foreseeable or Xilinx had been advised of the
* possibility of the same.
*
* CRITICAL APPLICATIONS
* Xilinx products are not designed or intended to be fail-
* safe, or for use in any application requiring fail-safe
* performance, such as life-support or safety devices or
* systems, Class III medical devices, nuclear facilities,
* applications related to the deployment of airbags, or any
* other applications that could lead to death, personal
* injury, or severe property or environmental damage
* (individually and collectively, "Critical
* Applications"). Customer assumes the sole risk and
* liability of any use of Xilinx products in Critical
* Applications, subject only to applicable laws and
* regulations governing limitations on product liability.
*
* THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
* PART OF THIS FILE AT ALL TIMES.
*
* All rights reserved.
*
******************************************************************************/
/**
*
* @file xscaler_hw.h
*
* This header file contains identifiers and register-level driver functions (or
* macros) that can be used to access the Xilinx MVI Video Scaler device.
*
* For more information about the operation of this device, see the hardware
* specification and documentation in the higher level driver xscaler.h source
* code file.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00a xd   05/14/09 First release
* 2.00a xd   12/14/09 Updated doxygen document tags
* 4.03a mpv  05/28/13 Updated the Driver input, output and aperture size mask
* </pre>
*
******************************************************************************/

#ifndef XSCALER_HW_H      /* prevent circular inclusions */
#define XSCALER_HW_H      /* by using protection macros */

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/

#include "xil_io.h"

/************************** Constant Definitions *****************************/

/** @name Device Register Offsets
 *  @{
 */
#define XSCL_CTL              0x000    /**< Control */
#define XSCL_STATUS           0x004    /**< Status */
#define XSCL_ERROR            0x008    /**< Error status */
#define IRQ_ENABLE            0x00C    /**< For detecting operation status */
#define XSCL_VER              0x010    /**< Version Register */

#define XSCL_HSF              0x100    /**< Horizontal Shrink Factor */
#define XSCL_VSF              0x104    /**< Vertical Shrink Factor */
#define XSCL_SRCSIZE          0x108    /**< Source-video resolution */
#define XSCL_APTHORI          0x10C /**< First and last subject pixels in input line */
#define XSCL_APTVERT          0x110    /**< First and last subject lines in input image */
#define XSCL_OUTSIZE          0x114    /**< Output image size:width and height */
#define XSCL_NUMPHASE         0x118    /**< The numbers of phases in current filter */
#define XSCL_COEFFSETS        0x11C    /**< Active horizontal and vertical coefficient sets to use */
#define XSCL_FRCTLUMALEFT     0x120    /**< Fractional value used to initialize horizontal accumulator
                                          at rectangle left edge for luma */
#define XSCL_FRCTCHROMALEFT   0x124    /**< Fractional value used to initialize horizontal accumulator
                                          at rectangle left edge for chroma */
#define XSCL_FRCTLUMATOP      0x128    /**< Fractional value used to initialize horizontal accumulator
                                          at rectangle top edge for luma */
#define XSCL_FRCTCHROMATOP    0x12C    /**< Fractional value used to initialize horizontal accumulator
                                          at rectangle top edge for chroma */
#define XSCL_COEFFSETADDR     0x130    /**< Address of Coefficient set to write */
#define XSCL_COEFFVALUE       0x134    /**< Coefficient values to write */
#define XSCL_COEFF_SET_BANK   0x138    /**< Coefficient set/bank read address */
#define XSCL_COEFF_MEM        0x13C    /**< Coefficient mem read address */

/*@}*/

/** @name Control Register bit definition
 *  @{
 */
#define XSCL_CTL_REGUPDATE    0x00000002 /**< Register Update Enable for
                  register HSF thru
                  FRCTCHROMATOP */
#define XSCL_CTL_ENABLE       0x00000001 /**< Enable the scaler on the next
                  video frame */
/*@}*/

/** @name Status Register bit definition
 *  @{
 */
#define XSCL_STS_COEF_W_RDY_MASK 0x00000001 /**< If 1, Coefficient values can
                   be written into the core */
/*@}*/

/** @name Error Status Register bit definition (to be defined)
 *  @{
 */
#define XSCL_STSERR_CODE3_MASK   0xFF000000  /**< code 3 */
#define XSCL_STSERR_CODE2_MASK   0x00FF0000  /**< code 2 */
#define XSCL_STSERR_CODE1_MASK   0x0000FF00  /**< code 1 */
#define XSCL_STSERR_CODE0_MASK   0x000000FF  /**< code 0 */
/*@}*/

/** @name Done Status Register bit definition
 *  @{
 */
#define XSCL_STSDONE_DONE   0x00000001 /**< indicator of end of scaler
                  operation */
/*@}*/

/** @name Horizontal Shrink Factor Register bit definition
 *  @{
 */
#define XSCL_HSF_INT_MASK   0x00F00000 /**< Horizontal Shrink Factor
                  integer */
#define XSCL_HSF_FRAC_MASK   0x000FFFFF /**< Horizontal Shrink Factor
                  fractional */
/*@}*/

/** @name Vertical Shrink Factor Register bit definition
 *  @{
 */
#define XSCL_VSF_INT_MASK   0x00F00000 /**< Vertical Shrink Factor integer
                    */
#define XSCL_VSF_FRAC_MASK   0x000FFFFF /**< Vertical Shrink Factor
                  fractional */
/*@}*/

/** @name Aperture Horizontal Register bit definition
 *   @{
 */
#define XSCL_APTHORI_LASTPXL_MASK   0x1FFF0000 /**< Location of last pixel
                     in line */
#define XSCL_APTHORI_LASTPXL_SHIFT   16      /**< Shift for location of
                     last pixel */
#define XSCL_APTHORI_FIRSTPXL_MASK   0x00001FFF /**< Location of first pixel
                     in line */
/*@}*/

/** @name Aperture Vertical Register bit definition
 *  @{
 */
#define XSCL_APTVERT_LASTLINE_MASK   0x1FFF0000 /**< Location of last line
                     in active video */
#define XSCL_APTVERT_LASTLINE_SHIFT   16      /**< Shift for location of
                     last line */
#define XSCL_APTVERT_FIRSTLINE_MASK   0x00001FFF /**< Location of first line
                     in active video */
/*@}*/

/** @name Output Size Register bit definition
 *  @{
 */
#define XSCL_OUTSIZE_NUMLINE_MASK   0x1FFF0000 /**< The number of lines in
                     output rectangle */
#define XSCL_OUTSIZE_NUMLINE_SHIFT   16      /**< Shift for the number of
                     lines */
#define XSCL_OUTSIZE_NUMPXL_MASK   0x00001FFF /**< The number of pixels in
                     output rectangle */
/*@}*/

/** @name Source Size Register bit definition
 *  @{
 */
#define XSCL_SRCSIZE_NUMLINE_MASK   0x1FFF0000 /**< The number of lines in
                     source image */
#define XSCL_SRCSIZE_NUMLINE_SHIFT   16      /**< Shift for the number of
                     lines */
#define XSCL_SRCSIZE_NUMPXL_MASK   0x00001FFF /**< The number of pixels in
                     source image */
/*@}*/


/** @name Number of Phases Register bit definition
 *  @{
 */
#define XSCL_NUMPHASE_VERT_MASK      0x00007F00 /**< The number of vertical
                     phases */
#define XSCL_NUMPHASE_VERT_SHIFT   8      /**< Shift for the number of
                     vertical phases */
#define XSCL_NUMPHASE_HORI_MASK      0x0000007F /**< The number of
                     horizontal phases */
/*@}*/

/** @name Active Coefficient Set Register bit definition
 *  @{
 */
#define XSCL_COEFFSETS_VERT_MASK   0x000000F0 /**< Active vertical
                     coefficient set */
#define XSCL_COEFFSETS_VERT_SHIFT   4      /**< Active vertical
                     coefficient set
                     shift */
#define XSCL_COEFFSETS_HORI_MASK   0x0000000F /**< Active horizontal
                     coefficient set */
/*@}*/

/** @name Luma left edge horizontal accumulator fractional value register
 *  @{
 */
#define XSCL_FRCTLUMALEFT_VALUE_MASK   0x001FFFFF /**< Fractional value to
                     initialize horizontal
                     accumulator for luma */
/*@}*/

/** @name Chroma left edge horizontal accumulator fractional value register
 *  @{
 */
#define XSCL_FRCTCHROMALEFT_VALUE_MASK   0x001FFFFF /**< Fractional value to
                     initialize horizontal
                     accumulator for
                     chroma */
/*@}*/

/** @name Luma top edge vertical accumulator fractional value register
 *  @{
 */
#define XSCL_FRCTLUMATOP_VALUE_MASK   0x001FFFFF /**< Fractional value to
                     initialize vertical
                     accumulator for luma */
/*@}*/

/** @name Chroma top edge vertical accumulator fractional value register
 *  @{
 */
#define XSCL_FRCTCHROMATOP_VALUE_MASK   0x001FFFFF /**< Fractional value to
                     initialize vertical
                     accumulator for
                     chroma */
/*@}*/

/** @name Coefficient band address register bit definition
 *  @{
 */
#define XSCL_COEFFSETADDR_ADDR_MASK   0x0000000F /**< Address of the
                     Coefficient bank to
                     write next */
/*@}*/

/** @name Coefficient Value Register bit definition
 *  @{
 */
#define XSCL_COEFFVALUE_NPLUS1_MASK   0xFFFF0000 /**< Second value in the
                     pair */
#define XSCL_COEFFVALUE_N_MASK      0x0000FFFF /**< First value in the
                     pair */
/*@}*/

/** @name Reset Register bit definition
 *  @{
 */
#define XSCL_RESET_RESET_MASK      0x80000000 /**< Software reset bit */
/*@}*/

/** @name Global Interrupt Enable Register bit definition
 *  @{
 */
#define XSCL_GIER_GIE_MASK      0x80000000 /**< Global interrupt
                     enable */
/*@}*/

/** @name Interrupt Status/Enable Register bit definition
 *  @{
 */
#define XSCL_IXR_REG_UPDATE_DONE_MASK   0x00000020 /**< Shadow Register
                     Update Interrupt */
#define XSCL_IXR_COEF_WR_ERROR_MASK   0x00000010 /**< Coefficient FIFO
                     Write Error
                     Interrupt */
#define XSCL_IXR_OUTPUT_ERROR_MASK   0x00000008 /**< Output Error
                     Interrupt */
#define XSCL_IXR_INPUT_ERROR_MASK   0x00000004 /**< Input Error
                     Interrupt */
#define XSCL_IXR_COEF_FIFO_READY_MASK   0x00000002 /**< Coefficient FIFO
                     Ready Interrupt */
#define XSCL_IXR_OUTPUT_FRAME_DONE_MASK 0x00000001 /**< Video Frame Done
                     Interrupt */

#define XSCL_IXR_EVENT_MASK   (XSCL_IXR_OUTPUT_FRAME_DONE_MASK | \
               XSCL_IXR_COEF_FIFO_READY_MASK | \
               XSCL_IXR_REG_UPDATE_DONE_MASK)
                     /**< Mask for all
                     normal event
                     interrupts */
#define XSCL_IXR_ERROR_MASK   (XSCL_IXR_INPUT_ERROR_MASK | \
               XSCL_IXR_OUTPUT_ERROR_MASK | \
               XSCL_IXR_COEF_WR_ERROR_MASK)
                     /**< Mask for all
                     error interrupts */
#define XSCL_IXR_ALLINTR_MASK   (XSCL_IXR_EVENT_MASK | \
               XSCL_IXR_ERROR_MASK) /**< Mask for all
                          interrupts */
/*@}*/

/** @name Chroma Format Type Definition
 *  @{
 */
#define XSCL_CHROMA_FORMAT_420      1   /**< YUV4:2:0 */
#define XSCL_CHROMA_FORMAT_422      2   /**< YUV4:2:2 */
#define XSCL_CHROMA_FORMAT_444      3   /**< YUV4:4:4 */
/*@}*/

/**************************** Type Definitions *******************************/


/***************** Macros (Inline Functions) Definitions *********************/

/** @name Scaler Register Access Macro Definition
 *  @{
 */
#define XScaler_In32  Xil_In32
#define XScaler_Out32 Xil_Out32

/*****************************************************************************/
/**
*
* Read the given register.
*
* @param   BaseAddress is the base address of the device
* @param   RegOffset is the register offset to be read
*
* @return   The 32-bit value of the register
*
* @note
* C-style signature:
*    u32 XScaler_ReadReg(u32 BaseAddress, u32 RegOffset)
*
******************************************************************************/
#define XScaler_ReadReg(BaseAddress, RegOffset)            \
         XScaler_In32((BaseAddress) + (RegOffset))

/*****************************************************************************/
/**
*
* Write the given register.
*
* @param   BaseAddress is the base address of the device
* @param   RegOffset is the register offset to be written
* @param   Data is the 32-bit value to write to the register
*
* @return   None.
*
* @note
* C-style signature:
*    void XScaler_WriteReg(u32 BaseAddress, u32 RegOffset, u32 Data)
*
******************************************************************************/
#define XScaler_WriteReg(BaseAddress, RegOffset, Data)         \
         XScaler_Out32((BaseAddress) + (RegOffset), (Data))

/*@}*/

/************************** Function Prototypes ******************************/

#ifdef __cplusplus
}
#endif

#endif /* end of protection macro */
