#ifndef MATRIX_BUFFER_H
#define MATRIX_BUFFER_H

#include <arduino.h>

namespace MatrixBuffer
{
    const uint8_t BOUND_X = 64;
    const uint8_t BOUND_Y = 32;
}

using matrixBuffer = int[MatrixBuffer::BOUND_Y][MatrixBuffer::BOUND_X];
using ptrMatrixBuffer = int (*)[MatrixBuffer::BOUND_X];

#endif