#ifndef PACMAN_MODEL_IRANDOMNUMBERGENERATOR_HPP
#define PACMAN_MODEL_IRANDOMNUMBERGENERATOR_HPP


namespace Pacman
{
namespace Model
{


template<class NumberType>
class IRandomNumberGenerator
{
public:
    virtual NumberType next(NumberType min, NumberType max) = 0;

    virtual ~IRandomNumberGenerator() = default;
};


typedef IRandomNumberGenerator<unsigned long> IRandomUnsignedLongGenerator;


} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_IRANDOMNUMBERGENERATOR_HPP
