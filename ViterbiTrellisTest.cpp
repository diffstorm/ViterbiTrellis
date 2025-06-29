#include <gtest/gtest.h>
#include "ViterbiTrellis.hpp"

// Test case to verify the encoding functionality
TEST(ViterbiTrellisTest, EncodingTest)
{
    std::vector<int> generatorPolynomials = {0b111, 0b101};
    ViterbiTrellis viterbi(3, generatorPolynomials);
    std::vector<uint8_t> data = {1, 0, 1, 1, 0, 1, 0};
    std::vector<uint8_t> expectedEncodedData = {1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0};
    std::vector<uint8_t> encodedData = viterbi.encode(data);
    ASSERT_EQ(encodedData, expectedEncodedData);
}

// Test case to verify the decoding functionality
TEST(ViterbiTrellisTest, DecodingTest)
{
    std::vector<int> generatorPolynomials = {0b111, 0b101};
    ViterbiTrellis viterbi(3, generatorPolynomials);
    std::vector<uint8_t> encodedData = {1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0};
    std::vector<uint8_t> expectedDecodedData = {1, 0, 1, 1, 0, 1, 0};
    std::vector<uint8_t> decodedData = viterbi.decode(encodedData);
    ASSERT_EQ(decodedData, expectedDecodedData);
}

// Test case for different generator polynomials
TEST(ViterbiTrellisTest, DifferentPolynomialsTest)
{
    std::vector<int> generatorPolynomials = {0b110, 0b101};
    ViterbiTrellis viterbi(3, generatorPolynomials);
    std::vector<uint8_t> data = {1, 0, 1, 1, 0, 1, 0};
    std::vector<uint8_t> expectedEncodedData = {0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0};
    std::vector<uint8_t> encodedData = viterbi.encode(data);
    ASSERT_EQ(encodedData, expectedEncodedData);
}

// Test case for single-bit error correction
TEST(ViterbiTrellisTest, SingleBitErrorCorrectionTest)
{
    std::vector<int> generatorPolynomials = {0b111, 0b101};
    ViterbiTrellis viterbi(3, generatorPolynomials);
    std::vector<uint8_t> originalData = {1, 0, 1, 1, 0, 1, 0};
    std::vector<uint8_t> encodedData = viterbi.encode(originalData);
    // Flip the 3rd bit (index 2)
    encodedData[2] ^= 1;
    std::vector<uint8_t> decodedData = viterbi.decode(encodedData);
    ASSERT_EQ(decodedData, originalData);
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

// Test case for encoding and decoding an empty data vector
TEST(ViterbiTrellisTest, EmptyDataTest)
{
    std::vector<int> generatorPolynomials = {0b111, 0b101};
    ViterbiTrellis viterbi(3, generatorPolynomials);
    std::vector<uint8_t> originalData = {};
    std::vector<uint8_t> encodedData = viterbi.encode(originalData);
    ASSERT_TRUE(encodedData.empty());
    std::vector<uint8_t> decodedData = viterbi.decode(encodedData);
    ASSERT_TRUE(decodedData.empty());
}

// Test case for encoding and decoding data with all zeros
TEST(ViterbiTrellisTest, AllZerosDataTest)
{
    std::vector<int> generatorPolynomials = {0b111, 0b101};
    ViterbiTrellis viterbi(3, generatorPolynomials);
    std::vector<uint8_t> originalData = {0, 0, 0, 0, 0};
    std::vector<uint8_t> encodedData = viterbi.encode(originalData);
    std::vector<uint8_t> expectedEncodedData = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    ASSERT_EQ(encodedData, expectedEncodedData);
    std::vector<uint8_t> decodedData = viterbi.decode(encodedData);
    ASSERT_EQ(decodedData, originalData);
}

// Test case for encoding and decoding data with all ones
TEST(ViterbiTrellisTest, AllOnesDataTest)
{
    std::vector<int> generatorPolynomials = {0b111, 0b101};
    ViterbiTrellis viterbi(3, generatorPolynomials);
    std::vector<uint8_t> originalData = {1, 1, 1, 1, 1};
    std::vector<uint8_t> encodedData = viterbi.encode(originalData);
    std::vector<uint8_t> expectedEncodedData = {1, 1, 0, 1, 1, 0, 1, 0, 1, 0};
    ASSERT_EQ(encodedData, expectedEncodedData);
    std::vector<uint8_t> decodedData = viterbi.decode(encodedData);
    ASSERT_EQ(decodedData, originalData);
}

// Test case for different constraint lengths (K=1)
TEST(ViterbiTrellisTest, ConstraintLengthOneTest)
{
    std::vector<int> generatorPolynomials = {0b1};
    ViterbiTrellis viterbi(1, generatorPolynomials);
    std::vector<uint8_t> originalData = {1, 0, 1, 1, 0};
    std::vector<uint8_t> encodedData = viterbi.encode(originalData);
    std::vector<uint8_t> expectedEncodedData = {1, 0, 1, 1, 0};
    ASSERT_EQ(encodedData, expectedEncodedData);
    std::vector<uint8_t> decodedData = viterbi.decode(encodedData);
    ASSERT_EQ(decodedData, originalData);
}

// Test case for different constraint lengths (K=2)
TEST(ViterbiTrellisTest, ConstraintLengthTwoTest)
{
    std::vector<int> generatorPolynomials = {0b11, 0b10};
    ViterbiTrellis viterbi(2, generatorPolynomials);
    std::vector<uint8_t> originalData = {1, 0, 1, 1, 0};
    std::vector<uint8_t> encodedData = viterbi.encode(originalData);
    std::vector<uint8_t> expectedEncodedData = {1, 0, 1, 1, 1, 0, 0, 1, 1, 1};
    ASSERT_EQ(encodedData, expectedEncodedData);
    std::vector<uint8_t> decodedData = viterbi.decode(encodedData);
    ASSERT_EQ(decodedData, originalData);
}

// Test case for different constraint lengths (K=4)
TEST(ViterbiTrellisTest, ConstraintLengthFourTest)
{
    std::vector<int> generatorPolynomials = {0b1111, 0b1010};
    ViterbiTrellis viterbi(4, generatorPolynomials);
    std::vector<uint8_t> originalData = {1, 0, 1, 1, 0};
    std::vector<uint8_t> encodedData = viterbi.encode(originalData);
    std::vector<uint8_t> expectedEncodedData = {1, 0, 1, 1, 0, 0, 1, 0, 0, 1};
    ASSERT_EQ(encodedData, expectedEncodedData);
    std::vector<uint8_t> decodedData = viterbi.decode(encodedData);
    ASSERT_EQ(decodedData, originalData);
}

// Test case for invalid constraint length (<= 0) in constructor
TEST(ViterbiTrellisTest, ConstructorInvalidConstraintLengthTest)
{
    std::vector<int> generatorPolynomials = {0b111, 0b101};
    EXPECT_THROW(ViterbiTrellis viterbi(0, generatorPolynomials), std::invalid_argument);
    EXPECT_THROW(ViterbiTrellis viterbi(-1, generatorPolynomials), std::invalid_argument);
}

// Test case for empty generator polynomials in constructor
TEST(ViterbiTrellisTest, ConstructorEmptyGeneratorPolynomialsTest)
{
    std::vector<int> generatorPolynomials = {};
    EXPECT_THROW(ViterbiTrellis viterbi(3, generatorPolynomials), std::invalid_argument);
}

// Test case for a longer data sequence
TEST(ViterbiTrellisTest, LongDataSequenceTest)
{
    std::vector<int> generatorPolynomials = {0b111, 0b101};
    ViterbiTrellis viterbi(3, generatorPolynomials);
    std::vector<uint8_t> originalData = {1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1};
    std::vector<uint8_t> encodedData = viterbi.encode(originalData);
    std::vector<uint8_t> decodedData = viterbi.decode(encodedData);
    ASSERT_EQ(decodedData, originalData);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
