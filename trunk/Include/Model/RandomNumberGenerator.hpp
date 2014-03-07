#ifndef PACMAN_MODEL_RANDOMNUMBERGENERATOR_HPP
#define PACMAN_MODEL_RANDOMNUMBERGENERATOR_HPP


#include <random>

#include <Model/IRandomNumberGenerator.hpp>


namespace Pacman
{
namespace Model
{


template<class NumberType>
class RandomNumberGenerator : public IRandomNumberGenerator<NumberType>
{
public:
    RandomNumberGenerator()
        : gen(rd())
    {
    }

    NumberType next(NumberType min, NumberType max) override
    {
        std::uniform_int_distribution<NumberType> dis(min, max);
        return dis(gen);
    }

private:
    std::random_device rd;
    std::mt19937 gen;
};


typedef RandomNumberGenerator<unsigned long> RandomUnsignedLongGenerator;


} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_RANDOMNUMBERGENERATOR_HPP
