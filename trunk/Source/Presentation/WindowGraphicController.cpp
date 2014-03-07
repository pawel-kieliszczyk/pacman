#include <cinder/app/AppBasic.h>
#include <cinder/gl/gl.h>

#include <Presentation/WindowGraphicController.hpp>


namespace Pacman
{
namespace Presentation
{


void WindowGraphicController::prepareSettings(
        ci::app::AppBasic::Settings& settings,
        unsigned long boardWidth,
        unsigned long boardHeight,
        unsigned long horizontalMargin)
{
    settings.setWindowSize(static_cast<int>(boardWidth + 2 * horizontalMargin), static_cast<int>(boardHeight));
    settings.setFrameRate(30.0f);
}


void WindowGraphicController::clearWindow()
{
    ci::gl::clear();
}


void WindowGraphicController::drawStoppedGameCurtain()
{
    // TODO: use some nice looking effects
    const int width = ci::app::getWindowWidth();
    const int height = ci::app::getWindowHeight();
    ci::gl::drawStringCentered(
            "Push return key to play",
            ci::Vec2f(ci::app::toPixels(width) / 2.0f, ci::app::toPixels(height) / 2.0f),
            ci::ColorA(1.0f, 0.0f, 0.0f, 0.5f));
}


void WindowGraphicController::drawPausedGameCurtain()
{
    // TODO: use some nice looking effects
    const int width = ci::app::getWindowWidth();
    const int height = ci::app::getWindowHeight();
    ci::gl::drawStringCentered(
            "Game paused",
            ci::Vec2f(ci::app::toPixels(width) / 2.0f, ci::app::toPixels(height) / 2.0f),
            ci::ColorA(1.0f, 0.0f, 0.0f, 0.5f));
}


void WindowGraphicController::drawWonGameCurtain()
{
    // TODO: use some nice looking effects
    const int width = ci::app::getWindowWidth();
    const int height = ci::app::getWindowHeight();
    ci::gl::drawStringCentered(
            "Game won",
            ci::Vec2f(ci::app::toPixels(width) / 2.0f, ci::app::toPixels(height) / 2.0f),
            ci::ColorA(1.0f, 0.0f, 0.0f, 0.5f));
}


void WindowGraphicController::drawLostGameCurtain()
{
    // TODO: use some nice looking effects
    const int width = ci::app::getWindowWidth();
    const int height = ci::app::getWindowHeight();
    ci::gl::drawStringCentered(
            "Game lost",
            ci::Vec2f(ci::app::toPixels(width) / 2.0f, ci::app::toPixels(height) / 2.0f),
            ci::ColorA(1.0f, 0.0f, 0.0f, 0.5f));
}


} // namespace Presentation
} // namespace Pacman
