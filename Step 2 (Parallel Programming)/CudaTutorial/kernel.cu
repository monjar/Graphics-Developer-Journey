
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <iostream>
#include <math.h>
#include <chrono>

void addBasic(int n, float* x, float* y)
{

    for (int i = 0; i < n; i += 1)
        y[i] = x[i] + y[i];

}
// Kernel function to add the elements of two arrays
__global__
void add(int n, float* x, float* y)
{
    int index = threadIdx.x;
    int stride = blockDim.x;
    for (int i = index; i < n; i += stride)
        y[i] = x[i] + y[i];
    
}

__global__
void addBlocks(int n, float* x, float* y)
{
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    int stride = blockDim.x * gridDim.x;
    for (int i = index; i < n; i += stride)
        y[i] = x[i] + y[i];
}



int main(void)
{
    int N = 100000000;
    float* x, * y;

    // Allocate Unified Memory – accessible from CPU or GPU
    cudaMallocManaged(&x, N * sizeof(float));
    cudaMallocManaged(&y, N * sizeof(float));

    std::cout << "Initializing... " << std::endl;
    // initialize x and y arrays on the host
    for (int i = 0; i < N; i++) {
        x[i] = 1.0f;
        y[i] = 2.0f;
    }
    std::cout << "Adding: " << std::endl;
    auto start1 = std::chrono::steady_clock::now();

    int blockSize = 256;
    int numBlocks = (N + blockSize - 1) / blockSize;
    addBlocks << <numBlocks, blockSize >> > (N, x, y);

    //addBasic(N, x, y);
    //add << <1, 256 >> > (N, x, y);
    cudaDeviceSynchronize();

    auto end1 = std::chrono::steady_clock::now();

    std::cout << "Time 1: " << std::chrono::duration<double, std::milli>((end1 - start1)).count() << std::endl;
  

    cudaFree(x);
    cudaFree(y);

    return 0;
}