/*
 * scaler_config.h
 *
 *  Created on: Apr 26, 2017
 *      Author: wtangney
 */

#ifndef SCALER_CONFIG_H_
#define SCALER_CONFIG_H_
#define SCALE_CONST 1048576	// 2^20
#define HSF_OFFSET 0x0100
#define VSF_OFFSET 0x0104
#define H_APERATURE_OFFSET 0x010C
#define V_APERATURE_OFFSET 0x0110
#define INPUT_SIZE_OFFSET 0x0108
#define OUTPUT_SIZE_OFFSET 0x0114


#define ILLEGAL_PIXEL_SIZE -1

#include <stdlib.h>

int enable_sw_scaler(int * baseAddr) {
	//(*baseAddr) |= 0x0001; //set sw enable bit

	return 0;
}

/**
 * set output size to 1920x1080 table 2-9
 */
int set_output_size(int * baseAddr) {
	//0x114

	*(baseAddr + OUTPUT_SIZE_OFFSET) &= 0x7070; //clear 0-12 and 16-28 perserve others

	*(baseAddr + OUTPUT_SIZE_OFFSET) |= 1920; // set lower 12 bits to starting pixel

	*(baseAddr + OUTPUT_SIZE_OFFSET) |= (1080 << 16); //set bits 16-28 to stopping pixel

	return 0;
}

/**
 * set input size to 1920x1080
 */
int set_input_size(int * baseAddr) {
	//0x0108

	*(baseAddr + INPUT_SIZE_OFFSET) &= 0x7070; //clear 0-12 and 16-28 perserve others

	*(baseAddr + INPUT_SIZE_OFFSET) |= 1920; // set lower 12 bits to starting pixel

	*(baseAddr + INPUT_SIZE_OFFSET) |= (1080 << 16); //set bits 16-28 to stopping pixel

	return 0;
}

/**
 * table 2-9
 */
int set_aperature(int * baseAddr, int v_start, int v_stop, int h_start,
		int h_stop) {
	if (v_start < 0 || v_stop > 4096 || v_start > v_stop || h_start < 0
			|| h_stop > 4096 || h_start > h_stop)
		return ILLEGAL_PIXEL_SIZE;

	*(baseAddr + H_APERATURE_OFFSET) &= 0x7070; //clear 0-12 and 16-28 perserve others

	*(baseAddr + H_APERATURE_OFFSET) |= h_start; // set lower 12 bits to starting pixel

	*(baseAddr + H_APERATURE_OFFSET) |= (h_stop << 16); //set bits 16-28 to stopping pixel

	*(baseAddr + V_APERATURE_OFFSET) &= 0x7070; //clear 0-12 and 16-28 perserve others

	*(baseAddr + V_APERATURE_OFFSET) |= v_start; //set lower 12 bits to starting pixel

	*(baseAddr + V_APERATURE_OFFSET) |= (v_stop << 16); //set 16-28 to stopping pixel

}

/**
 * up-scaling is achieved using a shrink-factor value less than one. Down-scaling is
 * achieved with a shrink-factor greater than one.
 * The allowed range of values on these parameters is 1/12 to 12 (0x015555 to 0xC00000)
 */
int set_scale_factor(u32* baseAddr, float hsf, float vsf) {
	hsf = hsf * SCALE_CONST;

	vsf = vsf * SCALE_CONST;

	int* targetAddr = baseAddr + HSF_OFFSET;

	*targetAddr = hsf;

	targetAddr = baseAddr + VSF_OFFSET;

	*targetAddr = vsf;

	return 0;
}

#endif /* SCALER_CONFIG_H_ */
