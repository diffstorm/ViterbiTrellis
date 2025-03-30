/**
    @file ViterbiTrellis.hpp
    @brief ViterbiTrellis C++ Library

    The ViterbiTrellis library is a single-header C++ implementation of the Viterbi algorithm, which is used for error correction and decoding of convolutional codes. This library provides a simple API to encode and decode byte arrays using convolutional codes, making it suitable for applications in digital communications and data transmission where reliability is critical.

    @date 2025-03-30
    @version 1.1
    @author by Eray Ozturk | erayozturk1@gmail.com
    @url github.com/diffstorm
    @license GPL-3 License
*/
#ifndef VITERBI_TRELLIS_HPP
#define VITERBI_TRELLIS_HPP

#include <vector>
#include <stdexcept>
#include <limits>
#include <algorithm>
#include <iostream>

class ViterbiTrellis
{
public:
    ViterbiTrellis(int constraintLength, const std::vector<int> &generatorPolynomials)
        : m_constraintLength(constraintLength), m_generatorPolynomials(generatorPolynomials)
    {
        if(constraintLength <= 0 || generatorPolynomials.empty())
        {
            throw std::invalid_argument("Invalid constraint length or generator polynomials.");
        }
    }

    std::vector<uint8_t> encode(const std::vector<uint8_t> &data) const
    {
        std::vector<uint8_t> encodedData;
        int state = 0;
        int mask = (1 << (m_constraintLength - 1)) - 1;

        for(uint8_t bit : data)
        {
            int combined = (state << 1) | bit;

            for(int generator : m_generatorPolynomials)
            {
                uint8_t encodedBit = 0;

                for(int i = 0; i < m_constraintLength; ++i)
                {
                    if(generator & (1 << i))
                    {
                        encodedBit ^= (combined >> i) & 1;
                    }
                }

                encodedData.push_back(encodedBit);
            }

            state = combined & mask;
        }

        return encodedData;
    }

    std::vector<uint8_t> decode(const std::vector<uint8_t> &encodedData) const
    {
        if(encodedData.size() % m_generatorPolynomials.size() != 0)
        {
            throw std::invalid_argument("Invalid encoded data size.");
        }

        int numStates = 1 << (m_constraintLength - 1);
        int trellisSize = encodedData.size() / m_generatorPolynomials.size();
        std::vector<std::vector<int>> trellis(trellisSize + 1, std::vector<int>(numStates, std::numeric_limits<int>::max()));
        std::vector<std::vector<int>> path(trellisSize + 1, std::vector<int>(numStates, -1));
        trellis[0][0] = 0;

        for(size_t i = 0; i < encodedData.size(); i += m_generatorPolynomials.size())
        {
            for(int state = 0; state < numStates; ++state)
            {
                if(trellis[i / m_generatorPolynomials.size()][state] == std::numeric_limits<int>::max())
                {
                    continue; // Skip unreachable states
                }

                for(int inputBit = 0; inputBit < 2; ++inputBit)
                {
                    int combined = (state << 1) | inputBit;
                    int nextState = combined & (numStates - 1);
                    int cost = trellis[i / m_generatorPolynomials.size()][state];
                    int segmentCost = 0;

                    for(size_t j = 0; j < m_generatorPolynomials.size(); ++j)
                    {
                        uint8_t expectedBit = 0;

                        for(int k = 0; k < m_constraintLength; ++k)
                        {
                            if(m_generatorPolynomials[j] & (1 << k))
                            {
                                expectedBit ^= (combined >> k) & 1;
                            }
                        }

                        if(encodedData[i + j] != expectedBit)
                        {
                            segmentCost++;
                        }
                    }

                    cost += segmentCost;

                    if(i / m_generatorPolynomials.size() + 1 < trellisSize + 1 && cost < trellis[i / m_generatorPolynomials.size() + 1][nextState])
                    {
                        trellis[i / m_generatorPolynomials.size() + 1][nextState] = cost;
                        path[i / m_generatorPolynomials.size() + 1][nextState] = state;
                    }
                }
            }
        }

        // Find the state with the minimal cost in the last step
        int state = 0;
        int minCost = trellis[trellisSize][0];

        for(int s = 1; s < numStates; ++s)
        {
            if(trellis[trellisSize][s] < minCost)
            {
                minCost = trellis[trellisSize][s];
                state = s;
            }
        }

        // Traceback to recover the decoded bits
        std::vector<uint8_t> decodedData;

        for(size_t i = trellisSize; i-- > 0;)
        {
            decodedData.push_back(state & 1); // LSB of current state is the decoded bit
            state = path[i + 1][state];
        }

        std::reverse(decodedData.begin(), decodedData.end());
        return decodedData;
    }

private:
    int m_constraintLength;
    std::vector<int> m_generatorPolynomials;
};

#endif // VITERBI_TRELLIS_HPP
