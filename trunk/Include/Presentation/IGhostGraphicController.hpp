#ifndef PACMAN_PRESENTATION_IGHOSTGRAPHICCONTROLLER_HPP
#define PACMAN_PRESENTATION_IGHOSTGRAPHICCONTROLLER_HPP


#include <Model/Color.hpp>


namespace Pacman
{
namespace Presentation
{


class IGhostGraphicController
{
public:
    virtual void drawNormalGhost(
            int fromRow,
            int fromColumn,
            int toRow,
            int toColumn,
            unsigned step,
            unsigned resolution,
            Model::Color color) = 0;

    virtual void drawScaredGhost(
            int fromRow,
            int fromColumn,
            int toRow,
            int toColumn,
            unsigned step,
            unsigned resolution,
            Model::Color color) = 0;

    virtual void drawLastSecondsScaredGhost(
            int fromRow,
            int fromColumn,
            int toRow,
            int toColumn,
            unsigned step,
            unsigned resolution,
            Model::Color color) = 0;

    virtual ~IGhostGraphicController() = default;
};


} // namespace Presentation
} // namespace Pacman


#endif // PACMAN_PRESENTATION_IGHOSTGRAPHICCONTROLLER_HPP
