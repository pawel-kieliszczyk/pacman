#ifndef PACMAN_PRESENTATION_ISCOREGRAPHICCONTROLLER_HPP
#define PACMAN_PRESENTATION_ISCOREGRAPHICCONTROLLER_HPP


namespace Pacman
{
namespace Presentation
{


class IScoreGraphicController
{
public:
    virtual void draw(unsigned score) = 0;

    virtual ~IScoreGraphicController() = default;
};


} // namespace Presentation
} // namespace Pacman


#endif // PACMAN_PRESENTATION_ISCOREGRAPHICCONTROLLER_HPP
