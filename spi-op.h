#ifndef _SPI_OP_H_
#define _SPI_OP_H_

#include <cstddef>

bool SPIDeviceInit(int *clk_khz = NULL);
void SPIDeviceRelease(void);
bool SPIWrite(const unsigned char *data, unsigned int size);
bool SPIWriteTwo(const unsigned char *in1, unsigned int in1_size, const unsigned char *in2, unsigned int in2_size);
bool SPIWriteThenRead(const unsigned char *in, unsigned int in_size, unsigned char *out, unsigned int out_size);

#endif /* _SPI_OP_H_ */
