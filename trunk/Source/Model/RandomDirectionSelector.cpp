#include <cassert>
#include <random>

#include <Model/RandomDirectionSelector.hpp>


namespace Pacman
{
namespace Model
{


RandomDirectionSelector::RandomDirectionSelector(std::shared_ptr<IRandomUnsignedLongGenerator> randomUnsignedLongGenerator_)
    : randomUnsignedLongGenerator(randomUnsignedLongGenerator_)
{
}


Direction RandomDirectionSelector::selectDirection(const std::vector<Direction>& directions)
{
    assert(!directions.empty());

    const unsigned long min = 0;
    const unsigned long max = directions.size() - 1;
    const auto random = randomUnsignedLongGenerator->next(min, max);

    return directions[random];

//    assert(!directions.empty());
//
//    std::random_device rd;
//    std::mt19937 gen(rd());
//    std::uniform_int_distribution<> dis(0, static_cast<int>(directions.size()) - 1);
//
//    return directions[dis(gen)];
}


} // namespace Model
} // namespace Pacman
