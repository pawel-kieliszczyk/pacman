#ifndef PACMAN_MODEL_FIELDBASE_HPP
#define PACMAN_MODEL_FIELDBASE_HPP


#include <Model/IField.hpp>


namespace Pacman
{
namespace Model
{


class FieldBase : public IField
{
public:
    FieldBase(unsigned row_, unsigned col_);

    virtual ~FieldBase() {}

protected:
    unsigned getRow() const;
    unsigned getCol() const;

private:
    const unsigned row;
    const unsigned col;
};


} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_FIELDBASE_HPP
