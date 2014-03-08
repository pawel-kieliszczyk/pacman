#ifndef PACMAN_MODEL_TESTING_BOARDGRAPHICCONTROLLERMOCK_HPP
#define PACMAN_MODEL_TESTING_BOARDGRAPHICCONTROLLERMOCK_HPP


#include <gmock/gmock.h>

#include <Presentation/IBoardGraphicController.hpp>


namespace Pacman
{
namespace Presentation
{
namespace Testing
{


class BoardGraphicControllerMock : public IBoardGraphicController
{
public:
    MOCK_METHOD2(drawCoin, void(unsigned, unsigned));
    MOCK_METHOD2(drawBigCoin, void(unsigned, unsigned));
    MOCK_METHOD2(drawApple, void(unsigned, unsigned));
    MOCK_METHOD2(drawCherry, void(unsigned, unsigned));
    MOCK_METHOD2(drawOrange, void(unsigned, unsigned));
    MOCK_METHOD2(drawWall, void(unsigned, unsigned));
};


} // namespace Testing
} // namespace Presentation
} // namespace Pacman


#endif // PACMAN_MODEL_TESTING_BOARDGRAPHICCONTROLLERMOCK_HPP
