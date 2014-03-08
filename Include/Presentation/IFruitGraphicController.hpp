#ifndef PACMAN_PRESENTATION_IFRUITGRAPHICCONTROLLER_HPP
#define PACMAN_PRESENTATION_IFRUITGRAPHICCONTROLLER_HPP


namespace Pacman
{
namespace Presentation
{


class IFruitGraphicController
{
public:
    virtual void drawApple(const unsigned fruitNumber) = 0;
    virtual void drawCherry(const unsigned fruitNumber) = 0;
    virtual void drawOrange(const unsigned fruitNumber) = 0;

    virtual ~IFruitGraphicController() = default;
};


} // namespace Presentation
} // namespace Pacman


#endif // PACMAN_PRESENTATION_IFRUITGRAPHICCONTROLLER_HPP
