#ifndef PACMAN_PRESENTATION_IWINDOWGRAPHICCONTROLLER_HPP
#define PACMAN_PRESENTATION_IWINDOWGRAPHICCONTROLLER_HPP


#include <cinder/app/AppBasic.h>


namespace Pacman
{
namespace Presentation
{


class IWindowGraphicController
{
public:
    virtual void prepareSettings(
            ci::app::AppBasic::Settings& settings,
            unsigned long boardWidth,
            unsigned long boardHeight,
            unsigned long horizontalMargin) = 0;

    virtual void clearWindow() = 0;

    virtual void drawStoppedGameCurtain() = 0;
    virtual void drawPausedGameCurtain() = 0;
    virtual void drawWonGameCurtain() = 0;
    virtual void drawLostGameCurtain() = 0;

    virtual ~IWindowGraphicController() = default;
};


} // namespace Presentation
} // namespace Pacman


#endif // PACMAN_PRESENTATION_IWINDOWGRAPHICCONTROLLER_HPP
