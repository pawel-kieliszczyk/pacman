#ifndef PACMAN_PRESENTATION_TESTING_GHOSTGRAPHICCONTROLLERMOCK_HPP
#define PACMAN_PRESENTATION_TESTING_GHOSTGRAPHICCONTROLLERMOCK_HPP


#include <gmock/gmock.h>

#include <Presentation/IGhostGraphicController.hpp>


namespace Pacman
{
namespace Presentation
{
namespace Testing
{


class GhostGraphicControllerMock : public IGhostGraphicController
{
public:
    MOCK_METHOD7(drawNormalGhost, void(int, int, int, int, unsigned, unsigned, Model::Color));
    MOCK_METHOD7(drawScaredGhost, void(int, int, int, int, unsigned, unsigned, Model::Color));
    MOCK_METHOD7(drawLastSecondsScaredGhost, void(int, int, int, int, unsigned, unsigned, Model::Color));
};


} // namespace Testing
} // namespace Presentation
} // namespace Pacman


#endif // PACMAN_PRESENTATION_TESTING_GHOSTGRAPHICCONTROLLERMOCK_HPP
