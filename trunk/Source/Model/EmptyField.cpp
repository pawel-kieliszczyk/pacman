#include <Model/EmptyField.hpp>


namespace Pacman
{
namespace Model
{


EmptyField::EmptyField(unsigned row, unsigned col)
    : FieldBase(row, col)
{
}


bool EmptyField::isVisitable() const
{
    return true;
}


void EmptyField::visit(IPac& /*pac*/)
{
    // visiting an empty field doesn't trigger any actions
}


void EmptyField::draw(Presentation::IBoardGraphicController& /*graphicController*/) const
{
    // an empty field doesn't draw anything
}


void EmptyField::reset()
{
    // nothing to be done
}


} // namespace Model
} // namespace Pacman
