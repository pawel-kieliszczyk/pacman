#ifndef PACMAN_PRESENTATION_WINDOWGRAPHICCONTROLLER_HPP
#define PACMAN_PRESENTATION_WINDOWGRAPHICCONTROLLER_HPP


#include <Presentation/IWindowGraphicController.hpp>


namespace Pacman
{
namespace Presentation
{


class WindowGraphicController : public IWindowGraphicController
{
public:
    void prepareSettings(
            ci::app::AppBasic::Settings& settings,
            unsigned long boardWidth,
            unsigned long boardHeight,
            unsigned long horizontalMargin) override;

    void clearWindow() override;

    void drawStoppedGameCurtain() override;
    void drawPausedGameCurtain() override;
    void drawWonGameCurtain() override;
    void drawLostGameCurtain() override;
};


} // namespace Presentation
} // namespace Pacman


#endif // PACMAN_PRESENTATION_WINDOWGRAPHICCONTROLLER_HPP
