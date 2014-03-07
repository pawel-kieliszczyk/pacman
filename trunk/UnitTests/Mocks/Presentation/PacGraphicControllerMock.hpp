#ifndef PACMAN_PRESENTATION_TESTING_PACGRAPHICCONTROLLERMOCK_HPP
#define PACMAN_PRESENTATION_TESTING_PACGRAPHICCONTROLLERMOCK_HPP


#include <gmock/gmock.h>

#include <Presentation/IPacGraphicController.hpp>


namespace Pacman
{
namespace Presentation
{
namespace Testing
{


class PacGraphicControllerMock : public IPacGraphicController
{
public:
    MOCK_METHOD6(draw, void(int, int, int, int, unsigned, unsigned));
};


} // namespace Testing
} // namespace Presentation
} // namespace Pacman


#endif // PACMAN_PRESENTATION_TESTING_PACGRAPHICCONTROLLERMOCK_HPP
