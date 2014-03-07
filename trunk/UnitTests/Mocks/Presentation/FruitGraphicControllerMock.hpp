#ifndef PACMAN_PRESENTATION_TESTING_FRUITGRAPHICCONTROLLERMOCK_HPP
#define PACMAN_PRESENTATION_TESTING_FRUITGRAPHICCONTROLLERMOCK_HPP


#include <gmock/gmock.h>

#include <Presentation/IFruitGraphicController.hpp>


namespace Pacman
{
namespace Presentation
{
namespace Testing
{


class FruitGraphicControllerMock : public IFruitGraphicController
{
public:
    MOCK_METHOD1(drawApple, void(const unsigned));
    MOCK_METHOD1(drawCherry, void(const unsigned));
    MOCK_METHOD1(drawOrange, void(const unsigned));
};


} // namespace Testing
} // namespace Presentation
} // namespace Pacman


#endif // PACMAN_PRESENTATION_TESTING_FRUITGRAPHICCONTROLLERMOCK_HPP
