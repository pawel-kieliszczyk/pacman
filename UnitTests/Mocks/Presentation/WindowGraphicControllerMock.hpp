#ifndef PACMAN_PRESENTATION_TESTING_WINDOWGRAPHICCONTROLLERMOCK_HPP
#define PACMAN_PRESENTATION_TESTING_WINDOWGRAPHICCONTROLLERMOCK_HPP


#include <gmock/gmock.h>

#include <Presentation/IWindowGraphicController.hpp>


namespace Pacman
{
namespace Presentation
{
namespace Testing
{


class WindowGraphicControllerMock : public IWindowGraphicController
{
public:
    MOCK_METHOD4(prepareSettings, void(ci::app::AppBasic::Settings&, unsigned long, unsigned long, unsigned long));
    MOCK_METHOD0(clearWindow, void());
    MOCK_METHOD0(drawStoppedGameCurtain, void());
    MOCK_METHOD0(drawPausedGameCurtain, void());
    MOCK_METHOD0(drawWonGameCurtain, void());
    MOCK_METHOD0(drawLostGameCurtain, void());
};


} // namespace Testing
} // namespace Presentation
} // namespace Pacman


#endif // PACMAN_PRESENTATION_TESTING_WINDOWGRAPHICCONTROLLERMOCK_HPP
