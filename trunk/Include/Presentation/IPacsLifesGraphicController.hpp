#ifndef PACMAN_PRESENTATION_IPACSLIFESGRAPHICCONTROLLER_HPP
#define PACMAN_PRESENTATION_IPACSLIFESGRAPHICCONTROLLER_HPP


namespace Pacman
{
namespace Presentation
{


class IPacsLifesGraphicController
{
public:
    virtual void draw(unsigned lifes) = 0;

    virtual ~IPacsLifesGraphicController() = default;
};


} // namespace Presentation
} // namespace Pacman


#endif // PACMAN_PRESENTATION_IPACSLIFESGRAPHICCONTROLLER_HPP
