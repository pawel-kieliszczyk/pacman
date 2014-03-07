#ifndef PACMAN_MODEL_IBOARD_HPP
#define PACMAN_MODEL_IBOARD_HPP


#include <Model/IPac.hpp>


namespace Pacman
{
namespace Model
{


class IBoard
{
public:
    virtual unsigned long getNumOfRows() const = 0;
    virtual unsigned long getNumOfColumns() const = 0;

    virtual bool isVisitable(unsigned row, unsigned column) const = 0;
    virtual void visit(unsigned row, unsigned column, IPac& pac) = 0;

    virtual bool areInTheSameHole(unsigned row1, unsigned column1, unsigned row2, unsigned column2) const = 0;

    virtual void draw() const = 0;

    virtual void reset() = 0;

    virtual ~IBoard() = default;
};


} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_IBOARD_HPP
