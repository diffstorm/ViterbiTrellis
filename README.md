# ViterbiTrellis C++ Library [![Awesome](https://awesome.re/badge.svg)](https://github.com/diffstorm/ViterbiTrellis)

[![Build Status](https://github.com/diffstorm/ViterbiTrellis/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/diffstorm/ViterbiTrellis/actions)
[![License](https://img.shields.io/github/license/diffstorm/ViterbiTrellis)](https://github.com/diffstorm/ViterbiTrellis/blob/main/LICENSE)
[![Language](https://img.shields.io/github/languages/top/diffstorm/ViterbiTrellis)](https://github.com/diffstorm/ViterbiTrellis)
[![Code Coverage](https://codecov.io/gh/diffstorm/ViterbiTrellis/branch/main/graph/badge.svg)](https://codecov.io/gh/diffstorm/ViterbiTrellis)
![GitHub Stars](https://img.shields.io/github/stars/diffstorm/ViterbiTrellis?style=social)
![Platforms](https://img.shields.io/badge/Platform-Linux%20%7C%20Windows%20%7C%20macOS-lightgrey)

The **ViterbiTrellis** library is a single-header C++ implementation of the Viterbi algorithm, which is used for error correction and decoding of convolutional codes. This library provides a simple API to encode and decode byte arrays using convolutional codes, making it suitable for applications in digital communications and data transmission where reliability is critical.

## Features

- **Platform-independent**: The library is written in standard C++ and can be compiled on any platform.
- **Simple API**: Easy-to-use functions for encoding and decoding byte arrays.
- **Customizable**: Supports custom constraint lengths and generator polynomials.

## Viterbi Trellis Theory

The Viterbi algorithm is a dynamic programming algorithm used to find the most likely sequence of hidden states—called the Viterbi path—that results in a sequence of observed events, especially in the context of Markov information sources and hidden Markov models. In digital communications, it is used to decode convolutional codes, which are a type of error-correcting code. 

### Convolutional Codes

Convolutional codes are a type of error-correcting code where each input bit influences multiple output bits, spreading the information across the code sequence. This is achieved using shift registers and a set of generator polynomials. The Viterbi algorithm efficiently decodes the received data by finding the most likely transmitted sequence, given the noisy received sequence.

### Trellis Diagram

A Trellis diagram represents the possible states and transitions of a convolutional code. Each state corresponds to a possible state of the shift registers, and each transition represents the generation of a bit based on the input bit and the current state. The Viterbi algorithm traverses this Trellis to find the most likely path, representing the most likely transmitted sequence.

## Limitations

- **Memory Usage**: The algorithm's memory usage grows exponentially with the constraint length (`K`), which defines the number of bits that the encoder memory holds. For large constraint lengths, the memory usage can become significant.
- **Processing Time**: The decoding process can be computationally intensive for large sequences, especially with a large constraint length and number of states.
- **Error Propagation**: If the encoded data is highly corrupted, error propagation may occur during decoding, leading to incorrect output.

## Data Size and Growth

The size of the encoded data is determined by the constraint length and the generator polynomials used:

- **Encoded Data Size**: The size of the encoded data is `n * m`, where `n` is the length of the input data and `m` is the number of generator polynomials.
- **Expansion Ratio**: If `m` generator polynomials are used, the encoded data will be `m` times larger than the original data. For example, if 2 generator polynomials are used, the encoded data will be twice the size of the original data.

### Factors Influencing Data Size

1. **Constraint Length (`K`)**: The larger the constraint length, the more memory the encoder holds, and the more complex the Trellis diagram becomes.
2. **Generator Polynomials**: The number and complexity of the generator polynomials directly affect the size of the encoded data.
3. **Input Data Length**: The longer the input data, the larger the resulting encoded data.

### Example

For an input sequence of length 100 bytes, using 2 generator polynomials (`m=2`), the encoded sequence will be 200 bytes. The ratio of expansion is directly proportional to the number of generator polynomials.

## Best Practices

- **Choosing Constraint Length (`K`)**: Use a constraint length that balances between performance and error-correcting capability. Larger constraint lengths provide better error correction but at the cost of increased computational complexity and memory usage.
- **Generator Polynomials**: Choose generator polynomials that are well-suited for your application's noise characteristics. Standard polynomials like `(0b111, 0b101)` are commonly used.
- **Performance Optimization**: For applications with limited resources, consider optimizing the Viterbi decoder for your specific use case, such as reducing the state space or parallelizing the decoding process.
- **Testing with Noisy Data**: Always test the encoder and decoder with noisy data to ensure that the error-correcting capability meets your application's requirements.

## Error Correction Capability

The error correction capability of the ViterbiTrellis library is directly tied to the constraint length and the chosen generator polynomials of the convolutional code. Here's an overview of what influences the error correction capability and the typical expectations:

### Factors Affecting Error Correction

1. **Constraint Length (K):**
   - The constraint length, K, determines how many previous bits affect the current encoded output. A higher constraint length generally improves the ability to correct errors because it provides more redundancy and a richer Trellis structure for the Viterbi algorithm to work with. However, it also increases computational complexity and memory usage.

2. **Generator Polynomials:**
   - The choice of generator polynomials determines how the input bits are combined to produce the output bits. Well-chosen polynomials can distribute the information more evenly across the encoded sequence, improving error correction. The number of polynomials (or output bits per input bit) also affects the redundancy and, consequently, the error correction capability.

3. **Code Rate:**
   - The code rate, defined as `R = 1/m` where `m` is the number of output bits per input bit, affects the trade-off between redundancy and efficiency. Lower code rates (more redundancy) generally result in better error correction capabilities but reduce the effective data rate.

### Error Correction Capabilities

- **Single-Bit Errors:**
  - The Viterbi algorithm is highly effective at correcting single-bit errors within a codeword, particularly when the constraint length is adequately large. It can easily identify and correct a single erroneous bit by tracing the most likely path through the Trellis.

- **Burst Errors:**
  - For burst errors (where multiple consecutive bits are corrupted), the algorithm's effectiveness depends on the length of the burst relative to the constraint length. If the burst is shorter than or comparable to the constraint length, the Viterbi decoder often can correct the error. Longer burst errors are more challenging and might result in residual errors after decoding.

- **Error Rate and Channel Conditions:**
  - The overall error correction capability also depends on the bit error rate (BER) of the communication channel. In channels with a low BER, the Viterbi algorithm performs well and can correct most errors. However, as the BER increases, the probability of multiple errors occurring close together also increases, which can overwhelm the decoder and lead to uncorrectable errors.

### Practical Considerations

In practical terms, with a typical constraint length (e.g., `K = 7`) and well-chosen generator polynomials, the Viterbi algorithm can correct a few isolated errors over a relatively long encoded sequence. However, it may struggle with more dense error patterns unless the code rate is sufficiently low (i.e., high redundancy).

**In summary**, the ViterbiTrellis library is effective at correcting single-bit errors and small bursts of errors in typical communication channels, particularly when using a moderate to high constraint length and well-designed generator polynomials. For very noisy channels or channels with frequent burst errors, increasing the constraint length and reducing the code rate can enhance error correction performance but at the cost of increased complexity and reduced data throughput.

## Installation and Usage

### Installation

Simply include the `ViterbiTrellis.hpp` header file in your project. No additional dependencies are required.

### Usage Example

```cpp
#include <iostream>
#include "ViterbiTrellis.hpp"

int main() {
    std::vector<int> generatorPolynomials = { 0b111, 0b101 }; // Generator polynomials
    ViterbiTrellis viterbi(3, generatorPolynomials);

    std::vector<uint8_t> data = { 1, 0, 1, 1, 0, 1, 0 };
    std::vector<uint8_t> encodedData = viterbi.encode(data);

    std::cout << "Encoded Data: ";
    for (uint8_t bit : encodedData) {
        std::cout << static_cast<int>(bit);
    }
    std::cout << std::endl;

    std::vector<uint8_t> decodedData = viterbi.decode(encodedData);

    std::cout << "Decoded Data: ";
    for (uint8_t bit : decodedData) {
        std::cout << static_cast<int>(bit);
    }
    std::cout << std::endl;

    return 0;
}
```

## Building and Running

### Building

1. Install [CMake](https://cmake.org/).
2. Install [Google Test](https://github.com/google/googletest).
3. Clone the repository.
4. Navigate to the project directory.

```sh
git clone https://github.com/diffstorm/ViterbiTrellis.git
mkdir -p build
cd build
cmake ..
make
```

### Running the Example

After building the project, you can run the example with:

```sh
./ViterbiTrellis
```

### Running Tests

To run the unit tests, use:

```sh
./ViterbiTrellisTest
```

## Helper Scripts
The project includes **helper scripts** (in both Python and C++) to assist with generating convolutional code polynomials and calculating key parameters for the ViterbiTrellis library. These scripts serve the same purpose and share identical functionality, but are provided in two languages for flexibility.

### Key Functions & Parameters 
Both helpers provide the following core functionality:  

1. **Polynomial Generation**  
   - **`generate_polynomial(degree)`**:  
     Generates a polynomial of the specified `degree` with randomized coefficients (the highest-degree term is always 1).  
     - Example: `degree=3` ? `[1, 0, 1, 1]` (represents \(1 + x^2 + x^3\)).  

   - **`generate_polynomials(degree, count)`**:  
     Generates `count` polynomials of the given `degree`.  

2. **Parameter Calculation**  
   - **`calculate_parameters(...)`**:  
     Computes the **code rate** (\(R = 1/m\), where \(m\) is the number of generator polynomials).  

#### Common Parameters:  
- **`constraint_length` (\(K\))**:  
  Memory depth of the encoder (e.g., \(K=3\) means the encoder uses 2 previous bits).  
- **`generator_polynomials`**:  
  List of polynomials defining how input bits are combined (e.g., `[0b111, 0b101]` for polynomials \(1 + x + x^2\) and \(1 + x^2\)).  
- **`data_length`**:  
  Length of input data (in bytes).  
- **`error_bits`**:  
  Maximum number of correctable errors.  

### Usage 
- **Python**:  
  ```bash
  python3 helper.py
  ```
- **C++**:  
  ```bash
  ./helper
  ```

### Why Two Versions?
- **Python**: Quick prototyping and easy modification.  
- **C++**: Seamless integration with the ViterbiTrellis library for consistency.  

## :snowman: Author
Eray Öztürk ([@diffstorm](https://github.com/diffstorm))

## LICENSE
This project is licensed under the [GPL-3 License](LICENSE) - see the LICENSE file for details.
