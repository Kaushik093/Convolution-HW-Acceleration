#include <hls_stream.h>
#include <hls_vector.h>
#include <ap_int.h>

const int HEIGHT = 1300;
const int WIDTH = 1300;
const int KERNEL_SIZE = 3;
const int VECTOR_WIDTH = 16;  // 16 elements of int32_t for 512-bit

using data_t = int32_t;
using wide_data_t = hls::vector<data_t, VECTOR_WIDTH>;  // 512-bit wide type


extern "C"
{

//    void convolution(int32_t matrix[1300][1300], int32_t kernel[3][3], int32_t output[1300][1300]);

    void convolution(wide_data_t matrix[HEIGHT][WIDTH / VECTOR_WIDTH],
                     data_t kernel[KERNEL_SIZE][KERNEL_SIZE],
                     wide_data_t output[HEIGHT][WIDTH / VECTOR_WIDTH]);


}






