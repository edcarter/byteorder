#include "byteorder.h"

/* returns 1 if we are network order, otherwise 0 */
static char network_order()
{
	/* 
	 * i = 0xb0000000000000001
	 * 
	 * For Big-Endian (network order) the most significant byte
	 * is stored at the lower address so we can check if the byte
	 * of i at the lowest address is 0, if it is that means 
	 * this machine is Big-Endian.
	 *
	 * Big Endian
	 * i = 0xb[00000000]00000001
	 * &i ----^
	 *
	 * Little Endian
	 * i = 0xb00000000[00000001]
	 * &i ------------^
	 */       
	short __i = 1;
	return ((char*)&__i)[0] == 0;
}

uint32_t htonl(uint32_t hostlong)
{
	/* already in network order, nothing to do */
	if (network_order()) return hostlong;

	/*
	 * Reverse the order of bytes. Our Litte-Endian int is formatted as follows:
	 * &hostlong -> [LSB] BYTE0
	 *                    BYTE1
	 *                    BYTE2
	 *              [MSB] BYTE3
	 *
	 * We need to swap the order of bytes to be Big-Endian:
	 * &hostlong -> [MSB] BYTE3
	 *                    BYTE2
	 *                    BYTE1
	 *              [LSB] BYTE0
	 */
	return ((hostlong & 0xFF000000) >> 24) | 
	       ((hostlong & 0xFF0000) >> 8) |
	       ((hostlong & 0xFF00) << 8) | 
	       ((hostlong & 0xFF << 24);
}

uint16_t htons(uint16_t hostshort)
{
	/* already in network order, nothing to do */
	if (network_order()) return hostshort;

	/*
	 * Reverse the order of bytes. Our Litte-Endian short is formatted as follows:
	 * &hostlong -> [LSB] BYTE0
	 *              [MSB] BYTE1
	 *
	 * We need to swap the order of bytes to be Big-Endian:
	 * &hostlong -> [MSB] BYTE1
	 *              [LSB] BYTE0
	 */
	return ((hostshort & 0xFF00) >> 8) | ((hostshort & 0xFF) << 8); 
}

uint32_t ntohl(uint32_t netlong)
{
	/* to convert back to host byte order, we can reuse htonl to swap the bytes back */
	return htonl(netlong);
}

uint16_t ntohs(uint16_t netshort)
{
	/* to convert back to host byte order, we can reuse htons to swap the bytes back */
	return htons(netshort);
}
