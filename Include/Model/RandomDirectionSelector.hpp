#ifndef PACMAN_MODEL_RANDOMDIRECTIONSELECTOR_HPP
#define PACMAN_MODEL_RANDOMDIRECTIONSELECTOR_HPP


#include <memory>

#include <Model/IRandomDirectionSelector.hpp>
#include <Model/IRandomNumberGenerator.hpp>


namespace Pacman
{
namespace Model
{


class RandomDirectionSelector : public IRandomDirectionSelector
{
public:
    RandomDirectionSelector(std::shared_ptr<IRandomUnsignedLongGenerator> randomUnsignedLongGenerator_);

    Direction selectDirection(const std::vector<Direction>& directions) override;

private:
    std::shared_ptr<IRandomUnsignedLongGenerator> randomUnsignedLongGenerator;
};


} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_RANDOMDIRECTIONSELECTOR_HPP
