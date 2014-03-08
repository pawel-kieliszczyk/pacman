#ifndef PACMAN_PRESENTATION_IBOARDGRAPHICCONTROLLER_HPP
#define PACMAN_PRESENTATION_IBOARDGRAPHICCONTROLLER_HPP


namespace Pacman
{
namespace Presentation
{


class IBoardGraphicController
{
public:
    virtual void drawCoin(unsigned row, unsigned column) = 0;
    virtual void drawBigCoin(unsigned row, unsigned column) = 0;

    virtual void drawApple(unsigned row, unsigned column) = 0;
    virtual void drawCherry(unsigned row, unsigned column) = 0;
    virtual void drawOrange(unsigned row, unsigned column) = 0;

    virtual void drawWall(unsigned row, unsigned column) = 0;

    virtual ~IBoardGraphicController() = default;
};


} // namespace Presentation
} // namespace Pacman


#endif // PACMAN_PRESENTATION_IBOARDGRAPHICCONTROLLER_HPP
