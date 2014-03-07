#ifndef PACMAN_MODEL_TESTING_RANDOMDIRECTIONSELECTORMOCK_HPP
#define PACMAN_MODEL_TESTING_RANDOMDIRECTIONSELECTORMOCK_HPP


#include <gmock/gmock.h>

#include <Model/IRandomDirectionSelector.hpp>


namespace Pacman
{
namespace Model
{
namespace Testing
{


class RandomDirectionSelectorMock : public IRandomDirectionSelector
{
public:
    MOCK_METHOD1(selectDirection, Direction(const std::vector<Direction>&));
};


} // namespace Testing
} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_TESTING_RANDOMDIRECTIONSELECTORMOCK_HPP
