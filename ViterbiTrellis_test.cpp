#include <gtest/gtest.h>
#include "ViterbiTrellis.hpp"

// Test case to verify the encoding functionality
TEST(ViterbiTrellisTest, EncodingTest)
{
    std::vector<int> generatorPolynomials = {0b111, 0b101};
    ViterbiTrellis viterbi(3, generatorPolynomials);
    std::vector<uint8_t> data = {1, 0, 1, 1, 0, 1, 0};
    std::vector<uint8_t> expectedEncodedData = {1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1};
    std::vector<uint8_t> encodedData = viterbi.encode(data);
    ASSERT_EQ(encodedData, expectedEncodedData);
}

// Test case to verify the decoding functionality
TEST(ViterbiTrellisTest, DecodingTest)
{
    std::vector<int> generatorPolynomials = {0b111, 0b101};
    ViterbiTrellis viterbi(3, generatorPolynomials);
    std::vector<uint8_t> encodedData = {1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1};
    std::vector<uint8_t> expectedDecodedData = {1, 0, 1, 1, 0, 1, 0};
    std::vector<uint8_t> decodedData = viterbi.decode(encodedData);
    ASSERT_EQ(decodedData, expectedDecodedData);
}

// Test case to verify round-trip encoding and decoding
TEST(ViterbiTrellisTest, RoundTripTest)
{
    std::vector<int> generatorPolynomials = {0b111, 0b101};
    ViterbiTrellis viterbi(3, generatorPolynomials);
    std::vector<uint8_t> originalData = {1, 0, 1, 1, 0, 1, 0};
    std::vector<uint8_t> encodedData = viterbi.encode(originalData);
    std::vector<uint8_t> decodedData = viterbi.decode(encodedData);
    ASSERT_EQ(decodedData, originalData);
}

// Test case to check handling of invalid input during decoding
TEST(ViterbiTrellisTest, InvalidDecodingTest)
{
    std::vector<int> generatorPolynomials = {0b111, 0b101};
    ViterbiTrellis viterbi(3, generatorPolynomials);
    // Invalid encoded data length
    std::vector<uint8_t> invalidEncodedData = {1, 1, 1};
    EXPECT_THROW(viterbi.decode(invalidEncodedData), std::invalid_argument);
}

// Test case to verify behavior with different generator polynomials
TEST(ViterbiTrellisTest, DifferentPolynomialsTest)
{
    std::vector<int> generatorPolynomials = {0b110, 0b101};
    ViterbiTrellis viterbi(3, generatorPolynomials);
    std::vector<uint8_t> data = {1, 0, 1, 1, 0, 1, 0};
    std::vector<uint8_t> expectedEncodedData = {1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1};
    std::vector<uint8_t> encodedData = viterbi.encode(data);
    ASSERT_EQ(encodedData, expectedEncodedData);
}

// Test case to verify the correction of a single-bit error
TEST(ViterbiTrellisTest, SingleBitErrorCorrectionTest)
{
    std::vector<int> generatorPolynomials = {0b111, 0b101};
    ViterbiTrellis viterbi(3, generatorPolynomials);
    std::vector<uint8_t> originalData = {1, 0, 1, 1, 0, 1, 0};
    std::vector<uint8_t> encodedData = viterbi.encode(originalData);
    // Introduce a single-bit error in the encoded data
    encodedData[2] ^= 1; // Flip the 3rd bit
    std::vector<uint8_t> decodedData = viterbi.decode(encodedData);
    ASSERT_EQ(decodedData, originalData); // Should be able to correct the single-bit error
}

// Test case to verify the correction of a burst of errors within the capability of the Viterbi algorithm
TEST(ViterbiTrellisTest, BurstErrorCorrectionTest)
{
    std::vector<int> generatorPolynomials = {0b111, 0b101};
    ViterbiTrellis viterbi(3, generatorPolynomials);
    std::vector<uint8_t> originalData = {1, 0, 1, 1, 0, 1, 0};
    std::vector<uint8_t> encodedData = viterbi.encode(originalData);
    // Introduce a burst error of 2 bits
    encodedData[4] ^= 1; // Flip the 5th bit
    encodedData[5] ^= 1; // Flip the 6th bit
    std::vector<uint8_t> decodedData = viterbi.decode(encodedData);
    ASSERT_EQ(decodedData, originalData); // Should be able to correct the small burst error
}

// Test case to verify that the Viterbi algorithm fails to correct a large burst of errors
TEST(ViterbiTrellisTest, LargeBurstErrorFailureTest)
{
    std::vector<int> generatorPolynomials = {0b111, 0b101};
    ViterbiTrellis viterbi(3, generatorPolynomials);
    std::vector<uint8_t> originalData = {1, 0, 1, 1, 0, 1, 0};
    std::vector<uint8_t> encodedData = viterbi.encode(originalData);
    // Introduce a burst error of 4 bits (larger than what the algorithm can handle effectively)
    encodedData[2] ^= 1; // Flip the 3rd bit
    encodedData[3] ^= 1; // Flip the 4th bit
    encodedData[4] ^= 1; // Flip the 5th bit
    encodedData[5] ^= 1; // Flip the 6th bit
    std::vector<uint8_t> decodedData = viterbi.decode(encodedData);
    ASSERT_NE(decodedData, originalData); // The algorithm should fail to correct this error
}

// Test case to verify correction when no errors are introduced
TEST(ViterbiTrellisTest, NoErrorTest)
{
    std::vector<int> generatorPolynomials = {0b111, 0b101};
    ViterbiTrellis viterbi(3, generatorPolynomials);
    std::vector<uint8_t> originalData = {1, 0, 1, 1, 0, 1, 0};
    std::vector<uint8_t> encodedData = viterbi.encode(originalData);
    std::vector<uint8_t> decodedData = viterbi.decode(encodedData);
    ASSERT_EQ(decodedData, originalData); // Should correctly decode without any errors
}

// Test case to verify handling of an error in the last bit
TEST(ViterbiTrellisTest, LastBitErrorCorrectionTest)
{
    std::vector<int> generatorPolynomials = {0b111, 0b101};
    ViterbiTrellis viterbi(3, generatorPolynomials);
    std::vector<uint8_t> originalData = {1, 0, 1, 1, 0, 1, 0};
    std::vector<uint8_t> encodedData = viterbi.encode(originalData);
    // Introduce an error in the last bit of the encoded data
    encodedData[encodedData.size() - 1] ^= 1;
    std::vector<uint8_t> decodedData = viterbi.decode(encodedData);
    ASSERT_EQ(decodedData, originalData); // Should correct the error in the last bit
}

// Test case to verify correction of 10 bytes of errors in a 1024-byte data block
TEST(ViterbiTrellisTest, LargeErrorCorrectionTest)
{
    // Parameters for strong error correction
    std::vector<int> generatorPolynomials = {0b111100111, 0b101101011, 0b110110001}; // NASA standard polynomials
    ViterbiTrellis viterbi(9, generatorPolynomials); // High constraint length (K=9)
    // Create a large data block of 1024 bytes
    std::vector<uint8_t> originalData(1024);

    for(int i = 0; i < 1024; ++i)
    {
        originalData[i] = i % 256; // Fill with some data pattern
    }

    // Encode the data
    std::vector<uint8_t> encodedData = viterbi.encode(originalData);

    // Introduce 10 bytes of errors randomly
    for(int i = 0; i < 10; ++i)
    {
        int errorPosition = rand() % (encodedData.size() * 8); // Random bit position
        encodedData[errorPosition / 8] ^= (1 << (errorPosition % 8)); // Flip the bit
    }

    // Decode the corrupted data
    std::vector<uint8_t> decodedData = viterbi.decode(encodedData);
    // Check if the original data is successfully recovered
    ASSERT_EQ(decodedData, originalData); // Should be able to correct the 10 byte errors
}

// Test case to verify correction of 100 bytes of errors in a 1024-byte data block
TEST(ViterbiTrellisTest, VeryLargeErrorCorrectionTest)
{
    // Parameters for extremely strong error correction
    std::vector<int> generatorPolynomials =
    {
        0b111100111101011,
        0b101101011110111,
        0b110110001101101,
        0b100101111011101
    }; // Strong polynomials for K=15
    ViterbiTrellis viterbi(15, generatorPolynomials); // Very high constraint length (K=15)
    // Create a large data block of 1024 bytes
    std::vector<uint8_t> originalData(1024);

    for(int i = 0; i < 1024; ++i)
    {
        originalData[i] = i % 256; // Fill with some data pattern
    }

    // Encode the data
    std::vector<uint8_t> encodedData = viterbi.encode(originalData);

    // Introduce 100 bytes of errors randomly
    for(int i = 0; i < 100; ++i)
    {
        int errorPosition = rand() % (encodedData.size() * 8); // Random bit position
        encodedData[errorPosition / 8] ^= (1 << (errorPosition % 8)); // Flip the bit
    }

    // Decode the corrupted data
    std::vector<uint8_t> decodedData = viterbi.decode(encodedData);
    // Check if the original data is successfully recovered
    ASSERT_EQ(decodedData, originalData); // Should be able to correct the 100 byte errors
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}