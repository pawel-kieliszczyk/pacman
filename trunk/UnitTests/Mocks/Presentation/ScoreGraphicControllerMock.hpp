#ifndef PACMAN_PRESENTATION_TESTING_SCOREGRAPHICCONTROLLERMOCK_HPP
#define PACMAN_PRESENTATION_TESTING_SCOREGRAPHICCONTROLLERMOCK_HPP


#include <gmock/gmock.h>

#include <Presentation/IScoreGraphicController.hpp>


namespace Pacman
{
namespace Presentation
{
namespace Testing
{


class ScoreGraphicControllerMock : public IScoreGraphicController
{
public:
    MOCK_METHOD1(draw, void(unsigned));
};


} // namespace Testing
} // namespace Presentation
} // namespace Pacman


#endif // PACMAN_PRESENTATION_TESTING_SCOREGRAPHICCONTROLLERMOCK_HPP
