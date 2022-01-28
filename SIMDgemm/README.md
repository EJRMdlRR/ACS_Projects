# Single Instruction Multiple Data (SIMD) General Matrix Multiplication (gemm) Tests

## Introduction

This project will explore the advantages of using SIMD intrinsincs to optimize matrix multiplication, a common operation in most fields of computing.

## Design Choices

* No templating is done because templating is slow. (Testing needs to be done to dertermine if diff is negligible.)
* By saving matrices as 1D matrices of size length x width entire matrix is contiguous. Makes memory access slightly faster as there are no lookups.
* Since matrices are of known size, allocate memory ahead of time. Removes penalty of changing vector size mid-matrix creation.
* The transpose is generated at the same time as the matrix. This wastes twice as much memory, but prevents O(length*width) operations each time a transpose for a multiplication is needed. Thus the more frequently a matrix is used as the second operand the lower the cost of that memory. (future implementations might leverage caching instead.)
* All 2D matrix dimensions are set as uint32_t, meaning it can reach a maximum size of ~4.3E9x4.2E9 elements. (Even though it is unlikely to exceed the uint16_t capacity of ~65E3x65E3)
* AVX was chosen over SSE as it has larger vector implementations (256 bits vs 128 bits). The best implementation would likely be a combination of the two so that if you can't fill the 256 bits you don't have to fall abck on classical techniques, as is done here currently.

## Testing

A more thorough testing gauntlet still needs implementation.

## Summary

The Intel SIMD Intrinsics were easy to use, but tricky to debug. By packing the data and sending it off to registers it's difficult at times to see where the error lies.