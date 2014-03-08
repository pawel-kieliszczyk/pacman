#ifndef PACMAN_MODEL_TESTING_FRUITMOCK_HPP
#define PACMAN_MODEL_TESTING_FRUITMOCK_HPP


#include <gmock/gmock.h>

#include <Model/IFruit.hpp>


namespace Pacman
{
namespace Model
{
namespace Testing
{


class FruitMock : public IFruit
{
public:
    MOCK_CONST_METHOD1(draw, void(const unsigned));
    MOCK_CONST_METHOD3(draw, void(const unsigned, const unsigned, Presentation::IBoardGraphicController&));
};


} // namespace Testing
} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_TESTING_FRUITMOCK_HPP
