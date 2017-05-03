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
* @file xscaler_intr.c
*
* This code contains interrupt related functions of Xilinx MVI Video Scaler
* device driver. The Scaler device converts a specified rectangular area of an
* input digital video image from one original sampling grid to a desired target
* sampling grid. Please see xscaler.h for more details of the driver.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver	Who  Date     Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00a xd   02/10/09 First release
* 2.00a xd   12/14/09 Updated doxygen document tags
* </pre>
*
******************************************************************************/

#include "xscaler.h"

/*****************************************************************************/
/**
*
* This function is the interrupt handler for the Scaler driver.
*
* This handler reads the pending interrupt from the IER/ISR, determines the
* source of the interrupts, calls according callbacks, and finally clears the
* interrupts.
*
* The application is responsible for connecting this function to the interrupt
* system. Application beyond this driver is also responsible for providing
* callbacks to	handle interrupts and installing the callbacks using
* XScaler_SetCallBack() during initialization phase. An example delivered with
* this driver demonstrates how this could be done.
*
* @param   InstancePtr is a pointer to the XScaler instance that just
*	   interrupted.
* @return  None.
* @note	   None.
*
******************************************************************************/
void XScaler_IntrHandler(void *InstancePtr)
{
	XScaler *XScalerPtr;
	u32 PendingIntr;
	u32 ErrorMask;
	u32 EventMask;

	XScalerPtr = (XScaler *)InstancePtr;

	/* Validate parameters */
	Xil_AssertVoid(XScalerPtr != NULL);
	Xil_AssertVoid(XScalerPtr->IsReady == XIL_COMPONENT_IS_READY);

	/* Get pending interrupts */
	PendingIntr = XScaler_IntrGetPending(XScalerPtr);

	/* Clear pending interrupt(s) */
	XScaler_IntrClear(XScalerPtr, PendingIntr);

	/* Error interrupt is occurring or spurious interrupt */
	if ((0 == (PendingIntr & XSCL_IXR_ALLINTR_MASK)) ||
		(PendingIntr & XSCL_IXR_ERROR_MASK)) {
		ErrorMask = PendingIntr & XSCL_IXR_ERROR_MASK;
		XScalerPtr->ErrorCallBack(XScalerPtr->ErrorRef, ErrorMask);

		/* The Error Interrupt Callback should reset the Scaler device
		 * and so there is no need to handle other pending interrupts
		 */
		 return;
	}

	/* A normal event just happened */
	if ((PendingIntr & XSCL_IXR_EVENT_MASK)) {
		EventMask = PendingIntr & XSCL_IXR_EVENT_MASK;
		XScalerPtr->EventCallBack(XScalerPtr->EventRef, EventMask);
	}

	return;
}

/*****************************************************************************/
/**
*
* This routine installs an asynchronous callback function for the given
* HandlerType:
*
* <pre>
* HandlerType		   Callback Function Type
* -----------------------  ---------------------------
* XSCL_HANDLER_EVENT	   XScaler_CallBack
* XSCL_HANDLER_ERROR	   XScaler_CallBack
*
* HandlerType		   Invoked by this driver when:
* -----------------------  --------------------------------------------------
* XSCL_HANDLER_EVENT	   A normal event just happened. Normal events include
*			   frame done, Coefficient FIFO Ready and Shadow
*			   Register updated.
*
* XSCL_HANDLER_ERROR	   An error just happened.
*
* </pre>
*
* @param	InstancePtr is a pointer to the XScaler instance to be worked
*		on.
* @param	HandlerType specifies which callback is to be attached.
* @param	CallBackFunc is the address of the callback function.
* @param	CallBackRef is a user data item that will be passed to the
*		callback function when it is invoked.
*
* @return
*		- XST_SUCCESS when handler is installed.
*		- XST_INVALID_PARAM when HandlerType is invalid.
*
* @note
* Invoking this function for a handler that already has been installed replaces
* it with the new handler.
*
******************************************************************************/
int XScaler_SetCallBack(XScaler *InstancePtr, u32 HandlerType,
				void *CallBackFunc, void *CallBackRef)
{
	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);
	Xil_AssertNonvoid(CallBackFunc != NULL);
	Xil_AssertNonvoid(CallBackRef != NULL);

	switch (HandlerType) {
	case XSCL_HANDLER_EVENT:
		InstancePtr->EventCallBack = (XScaler_CallBack)CallBackFunc;
		InstancePtr->EventRef = CallBackRef;
		break;

	case XSCL_HANDLER_ERROR:
		InstancePtr->ErrorCallBack = (XScaler_CallBack)CallBackFunc;
		InstancePtr->ErrorRef = CallBackRef;
		break;

	default:
		return XST_INVALID_PARAM;
	}
	return XST_SUCCESS;
}
