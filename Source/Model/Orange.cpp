#include <Model/Orange.hpp>


namespace Pacman
{
namespace Model
{


Orange::Orange(std::shared_ptr<Presentation::IFruitGraphicController> graphicController_)
    : graphicController(graphicController_)
{
}


void Orange::draw(const unsigned fruitNumber) const
{
    graphicController->drawOrange(fruitNumber);
}

void Orange::draw(
        const unsigned row,
        const unsigned column,
        Presentation::IBoardGraphicController& graphicController) const
{
    graphicController.drawOrange(row, column);
}


} // namespace Model
} // namespace Pacman
