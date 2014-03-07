#include <stdexcept>

#include <Model/WallField.hpp>


namespace Pacman
{
namespace Model
{


WallField::WallField(unsigned row, unsigned col)
    : FieldBase(row, col)
{
}


bool WallField::isVisitable() const
{
    return false;
}


void WallField::visit(IPac& /*pac*/)
{
    throw std::logic_error("Wall fields cannot be visited");
}


void WallField::draw(Presentation::IBoardGraphicController& graphicController) const
{
    graphicController.drawWall(getRow(), getCol());
}


void WallField::reset()
{
    // nothing to be done
}


} // namespace Model
} // namespace Pacman
