#include "Convolution.hpp"
#include <stdint.h>

extern "C"{



//HLS VECTOR METHOD

void convolution(wide_data_t matrix[HEIGHT][WIDTH / VECTOR_WIDTH],
                 data_t kernel[KERNEL_SIZE][KERNEL_SIZE],
                 wide_data_t output[HEIGHT][WIDTH / VECTOR_WIDTH]) {

    #pragma HLS INTERFACE m_axi port=matrix bundle=gmem0
    #pragma HLS INTERFACE m_axi port=kernel bundle=gmem1
    #pragma HLS INTERFACE m_axi port=output bundle=gmem2
    #pragma HLS INTERFACE s_axilite port=return

    // Temporary storage for the kernel
    data_t temp_kernel[KERNEL_SIZE][KERNEL_SIZE];

    // Copy kernel into temp_kernel
    for (int i = 0; i < KERNEL_SIZE; i++) {
        for (int j = 0; j < KERNEL_SIZE; j++) {
            temp_kernel[i][j] = kernel[i][j];
        }
    }

    // Convolution logic with packed data
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH / VECTOR_WIDTH; x++) {
//            #pragma HLS UNROLL factor=16

			#pragma HLS PIPELINE

            wide_data_t sum_vec = 0;  // Vectorized accumulator

            // Apply the kernel
            for (int ky = 0; ky < KERNEL_SIZE; ky++) {
                for (int kx = 0; kx < KERNEL_SIZE; kx++) {
                    int in_y = y + ky - 1;
                    int in_x = (x * VECTOR_WIDTH) + kx - 1;

                    if (in_y >= 0 && in_y < HEIGHT && in_x >= 0 && in_x < WIDTH) {
                        wide_data_t mat_vec = matrix[in_y][in_x / VECTOR_WIDTH];
                        for (int v = 0; v < VECTOR_WIDTH; v++) {
                            sum_vec[v] += mat_vec[v] * temp_kernel[ky][kx];
                        }
                    }
                }
            }

            // Write the accumulated result to the output
            output[y][x] = sum_vec;
        }
    }
}


//Initial code

//void convolution(int32_t matrix[1300][1300], int32_t kernel[3][3], int32_t output[1300][1300]) {
//
//    // Define separate memory interfaces for each array
//    #pragma HLS INTERFACE m_axi port=matrix bundle=gmem0
//    #pragma HLS INTERFACE m_axi port=kernel bundle=gmem1
//    #pragma HLS INTERFACE m_axi port=output bundle=gmem2
//
//	//m_axi supports burst transfers
//
//   // Temporary arrays to hold matrix and kernel
//    int32_t temp_matrix[1300][1300];
//    int32_t temp_kernel[3][3];
//
//	#pragma HLS ARRAY_PARTITION variable=temp_matrix type=cyclic factor=16 dim=2
//
//
//    // Copy matrix into temp_matrix
//    for (int i = 0; i < 1300; i++) {
////		#pragma HLS UNROLL factor = 16
//        for (int j = 0; j < 1300; j++) {
//			#pragma HLS UNROLL factor = 16
////			#pragma HLS PIPELINE
//            temp_matrix[i][j] = matrix[i][j];
//        }
//    }
//
//    // Copy kernel into temp_kernel
//    for (int i = 0; i < 3; i++) {
//        for (int j = 0; j < 3; j++) {
////			#pragma HLS PIPELINE II=1
//            temp_kernel[i][j] = kernel[i][j];
//        }
//    }
//
//    // Convolution logic
//
//    for (int y = 0; y < 1300; y++) {
//        for (int x = 0; x < 1300; x++) {
//			#pragma HLS UNROLL factor = 16
//
////			#pragma HLS PIPELINE
//
//            int64_t sum = 0;  // Accumulate sum for this pixel
//
//            // Apply the kernel
//            for (int ky = 0; ky < 3; ky++) {
//                for (int kx = 0; kx < 3; kx++) {
//
////					#pragma HLS UNROLL factor = 3 (Unrolled by default)
//
//                	sum  += temp_matrix[y + ky][x + kx] * temp_kernel[ky][kx];
//                }
//            }
//
//            // Write the accumulated result to the output
//             output[y][x]= sum;
//        }
//    }
//
//
//
//}

}  //extern C







