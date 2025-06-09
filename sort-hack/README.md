# Adversarial Input Generator for libcxx std::sort

## Problem Statement

The goal of this project is to generate adversarial inputs that force the `std::sort` implementation from libcxx v.10 to run in O(n²) time complexity instead of the expected O(n log n). This is achieved by exploiting the quicksort implementation's pivot selection strategy.

## Approach

The project uses the antiqsort technique, which was described in the paper ["A Killer Adversary for Quicksort" by M. D. McIlroy](https://www.cs.dartmouth.edu/~doug/mdmspe.pdf). The technique exploits the fact that quicksort's performance heavily depends on the pivot selection strategy. By carefully constructing input sequences, we can force the algorithm to consistently choose bad pivots, leading to worst-case O(n²) performance.

The implementation is based on the original antiqsort algorithm, adapted to work with libcxx's specific implementation of `std::sort`.

## Project Structure

- `run.cpp` - The main program that measures sorting time. Reading input from `stdin`.
- `gen.cpp` - The utility program that generates adversarial sequences.
   Reading desired length from `stdin`. Writing output to `stdout`.
- `libcxx_v10_sort.cpp` - reference `std::sort` implementation from `libcxx`.
- `antiqsort.c` - reference implementation of `antiqsort` from the [paper](https://www.cs.dartmouth.edu/~doug/mdmspe.pdf).
- `Makefile` - Build configuration for the project

## Building and Running

1. Build the project:

```bash
make
```

2. Generate an adversarial input sequence of 1000 elements:

```bash
echo 1000 | ./gen > data.txt
```

3. Run the sorting test:

```bash
./run < data.txt
```

or

```bash
echo 15000 | ./gen | ./run
```

## Expected Results

When running the program with the generated adversarial input, you should observe:

1. The sorting time should grow quadratically with input size
2. The number of comparisons should be close to $0.12 \cdot n^2$
3. The actual running time should be significantly higher than for random input

## Dependencies

- C++14 compatible compiler
- libcxx v.10
- Make

## References

1. McIlroy, M. D. (1998). "A Killer Adversary for Quicksort". Software: Practice and Experience, 29(4), 341-344.
2. libcxx documentation: <https://libcxx.llvm.org/>
