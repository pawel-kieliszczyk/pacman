#include <Model/CoinField.hpp>


namespace Pacman
{
namespace Model
{


CoinField::CoinField(unsigned row, unsigned col)
    : FieldBase(row, col),
      visited(false)
{
}


bool CoinField::isVisitable() const
{
    return true;
}


void CoinField::visit(IPac& pac)
{
    if(visited)
        return;

    pac.eatCoin();
    visited = true;
}


void CoinField::draw(Presentation::IBoardGraphicController& graphicController) const
{
    if(!visited)
        graphicController.drawCoin(getRow(), getCol());
}


void CoinField::reset()
{
    visited = false;
}


} // namespace Model
} // namespace Pacman
