#ifndef PACMAN_MODEL_TESTING_RANDOMNUMBERGENERATORMOCK_HPP
#define PACMAN_MODEL_TESTING_RANDOMNUMBERGENERATORMOCK_HPP


#include <gmock/gmock.h>

#include <Model/IRandomNumberGenerator.hpp>


namespace Pacman
{
namespace Model
{
namespace Testing
{


template<class NumberType>
class RandomNumberGeneratorMock : public IRandomNumberGenerator<NumberType>
{
public:
    MOCK_METHOD2_T(next, NumberType(NumberType, NumberType));
};


typedef RandomNumberGeneratorMock<unsigned long> RandomUnsignedLongGeneratorMock;


} // namespace Testing
} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_TESTING_RANDOMNUMBERGENERATORMOCK_HPP
