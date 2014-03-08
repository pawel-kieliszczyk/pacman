#include <Model/FieldBase.hpp>


namespace Pacman
{
namespace Model
{


FieldBase::FieldBase(unsigned row_, unsigned col_)
    : row(row_),
      col(col_)
{
}


unsigned FieldBase::getRow() const
{
    return row;
}


unsigned FieldBase::getCol() const
{
    return col;
}


} // namespace Model
} // namespace Pacman
