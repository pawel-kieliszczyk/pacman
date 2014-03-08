#include <string>

#include <cinder/app/AppBasic.h>
#include <cinder/gl/gl.h>

#include <Presentation/ScoreGraphicController.hpp>


namespace Pacman
{
namespace Presentation
{


void ScoreGraphicController::draw(unsigned score)
{
    // TODO: use some nice looking effects
//    const int width = ci::app::getWindowWidth();
//    const int height = ci::app::getWindowHeight();
    ci::gl::drawString(
            "Score: " + std::to_string(score),
            ci::Vec2f(10.0f, 10.0f),
            ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f));
}


} // namespace Presentation
} // namespace Pacman
