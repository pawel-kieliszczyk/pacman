#include <Model/FruitField.hpp>


namespace Pacman
{
namespace Model
{


FruitField::FruitField(unsigned row, unsigned col, unsigned maxNumberOfFruitsToEat_)
    : FieldBase(row, col),
      maxNumberOfFruitsToEat(maxNumberOfFruitsToEat_),
      numberOfEatenFruits(0u)
{
}


bool FruitField::isVisitable() const
{
    return true;
}


void FruitField::visit(IPac& pac)
{
    if(currentShownFruit)
    {
        std::shared_ptr<IFruit> fruitToEat = *currentShownFruit;
        currentShownFruit = boost::none;

        pac.eatFruit(fruitToEat);
        ++numberOfEatenFruits;
    }
}


void FruitField::draw(Presentation::IBoardGraphicController& graphicController) const
{
    if(currentShownFruit)
        (*currentShownFruit)->draw(getRow(), getCol(), graphicController);
}


void FruitField::reset()
{
    currentShownFruit = boost::none;
    numberOfEatenFruits = 0u;
}


void FruitField::showFruit(std::shared_ptr<IFruit> f)
{
    if(numberOfEatenFruits < maxNumberOfFruitsToEat)
        currentShownFruit = f;
}


void FruitField::hideFruit()
{
    currentShownFruit = boost::none;
}


} // namespace Model
} // namespace Pacman
