#include <Model/Cherry.hpp>


namespace Pacman
{
namespace Model
{


Cherry::Cherry(std::shared_ptr<Presentation::IFruitGraphicController> graphicController_)
    : graphicController(graphicController_)
{
}


void Cherry::draw(const unsigned fruitNumber) const
{
    graphicController->drawCherry(fruitNumber);
}


void Cherry::draw(
        const unsigned row,
        const unsigned column,
        Presentation::IBoardGraphicController& graphicController) const
{
    graphicController.drawCherry(row, column);
}


} // namespace Model
} // namespace Pacman
