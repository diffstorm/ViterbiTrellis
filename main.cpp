#include <iostream>
#include <random>
#include <vector>

#include "ViterbiTrellis.hpp"

void printVector(const char *title, const std::vector<uint8_t>& data) {
    std::cout << title << " : ";
	for (uint8_t bit : data) {
        std::cout << static_cast<int>(bit);
    }
    std::cout << std::endl;
}

std::vector<uint8_t> generate_random_vector(size_t size)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint8_t> dist(0, 1);
    std::vector<uint8_t> data(size);

    for(size_t i = 0; i < size; ++i)
    {
        data[i] = dist(gen);
    }

    return data;
}

int main()
{
    std::vector<int> generatorPolynomials = { 0b111, 0b101 }; // Generator polynomials
    ViterbiTrellis viterbi(3, generatorPolynomials);
#if 1
    std::vector<uint8_t> data = { 1, 0, 1 }; // Data
#else
    size_t size = 10;
    std::vector<uint8_t> data = generate_random_vector(size);
#endif
	printVector("Data", data);

    std::vector<uint8_t> encodedData = viterbi.encode(data);
    printVector("Encoded Data", encodedData);

    std::vector<uint8_t> decodedData = viterbi.decode(encodedData);
	printVector("Decoded Data", decodedData);

    if(std::equal(data.begin(), data.end(), decodedData.begin()))
    {
        std::cout << "Data and decoded-data are matching" << std::endl;
    }

    return 0;
}
