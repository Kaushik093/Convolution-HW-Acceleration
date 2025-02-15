#include "Convolution.hpp"
#include <stdint.h>
#include <cstdlib>
#include <iostream>


int32_t kernel[3][3] = {
    {15, 2 , 3},
    {3, 5 , 4},
	{4,4 , 5 }
};

int32_t matrix[1300][1300];

int32_t output_matrix[1300][1300];

int32_t test_output[1300][1300];

int main() {


	//Init the matrix

	for (int i = 0; i < 1300; i++) {
		for (int j = 0; j < 1300; j++) {
			matrix[i][j] = j + 1;  // Initialize each row with values 1 to 13
		}
	}

    // Call the convolution function with 2x2 kernel
    convolution(matrix, kernel, output_matrix);

    // Testing code (manually computing convolution with 3x3 kernel)
    for (int y = 0; y < 1300; y++) {  // Stop at 12 to prevent out-of-bounds access
        for (int x = 0; x < 1300; x++) {  // Stop at 12 to prevent out-of-bounds access
            for (int ky = 0; ky < 3; ky++) {
                for (int kx = 0; kx < 3; kx++) {
                    test_output[y][x] += matrix[y + ky][x + kx] * kernel[ky][kx];
                }
            }
        }
    }

    // Compare test_output with output_matrix for validation
    bool match = true;
    for (int y = 0; y < 1298; y++) {
        for (int x = 0; x < 1298; x++) {
            if (test_output[y][x] != output_matrix[y][x]) {
                match = false;
                std::cout << "Mismatch at (" << y << ", " << x << "): "
                          << "expected " << test_output[y][x] << ", got " << output_matrix[y][x] << std::endl;
            }
        }
    }

    if (match) {
        std::cout << "Test passed!" << std::endl;
        std::cout << "First 10 values for comparison:" << std::endl;
		for (int i = 0; i < 10; i++) {
			std::cout << "test_output[" << i << "] = " << test_output[0][i]
					  << ", output_matrix[" << i << "] = " << output_matrix[0][i] << std::endl;
		}

        return EXIT_SUCCESS;
    } else {
        std::cout << "Test failed!" << std::endl;
        return EXIT_FAILURE;
    }
}
