#ifndef PACMAN_PRESENTATION_SCOREGRAPHICCONTROLLER_HPP
#define PACMAN_PRESENTATION_SCOREGRAPHICCONTROLLER_HPP


#include <Presentation/IScoreGraphicController.hpp>


namespace Pacman
{
namespace Presentation
{


class ScoreGraphicController : public IScoreGraphicController
{
public:
    void draw(unsigned score) override;
};


} // namespace Presentation
} // namespace Pacman


#endif // PACMAN_PRESENTATION_SCOREGRAPHICCONTROLLER_HPP
