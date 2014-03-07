#ifndef PACMAN_PRESENTATION_IPACGRAPHICCONTROLLER_HPP
#define PACMAN_PRESENTATION_IPACGRAPHICCONTROLLER_HPP


namespace Pacman
{
namespace Presentation
{


class IPacGraphicController
{
public:
    virtual void draw(
            int fromRow,
            int fromColumn,
            int toRow,
            int toColumn,
            unsigned step,
            unsigned resolution) = 0;

    virtual ~IPacGraphicController() = default;
};


} // namespace Presentation
} // namespace Pacman


#endif // PACMAN_PRESENTATION_IPACGRAPHICCONTROLLER_HPP
