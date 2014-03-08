#include <Model/BigCoinField.hpp>


namespace Pacman
{
namespace Model
{


BigCoinField::BigCoinField(unsigned row, unsigned col)
    : FieldBase(row, col),
      visited(false)
{
}


bool BigCoinField::isVisitable() const
{
    return true;
}


void BigCoinField::visit(IPac& pac)
{
    if(visited)
        return;

    pac.eatBigCoin();
    visited = true;
}


void BigCoinField::draw(Presentation::IBoardGraphicController& graphicController) const
{
    if(!visited)
        graphicController.drawBigCoin(getRow(), getCol());
}


void BigCoinField::reset()
{
    visited = false;
}


} // namespace Model
} // namespace Pacman
