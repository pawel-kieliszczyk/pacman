#include <Model/Apple.hpp>


namespace Pacman
{
namespace Model
{


Apple::Apple(std::shared_ptr<Presentation::IFruitGraphicController> graphicController_)
    : graphicController(graphicController_)
{
}


void Apple::draw(const unsigned fruitNumber) const
{
    graphicController->drawApple(fruitNumber);
}


void Apple::draw(
        const unsigned row,
        const unsigned column,
        Presentation::IBoardGraphicController& graphicController) const
{
    graphicController.drawApple(row, column);
}


} // namespace Model
} // namespace Pacman
