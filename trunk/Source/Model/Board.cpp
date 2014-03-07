#include <algorithm>
#include <cassert>
#include <utility>

#include <Model/Board.hpp>


namespace Pacman
{
namespace Model
{


Board::Board(
        std::vector<std::vector<std::shared_ptr<IField>>>&& fields_,
        std::shared_ptr<Presentation::IBoardGraphicController> graphicController_)
    : fields(std::move(fields_)),
      graphicController(graphicController_),
      rows(0),
      columns(0)
{
    rows = fields.size();
    if(!fields.empty())
        columns = fields[0].size();
}


unsigned long Board::getNumOfRows() const
{
    return rows;
}


unsigned long Board::getNumOfColumns() const
{
    return columns;
}


bool Board::isVisitable(unsigned row, unsigned column) const
{
    return fields[row][column]->isVisitable();
}


void Board::visit(unsigned row, unsigned column, IPac& pac)
{
    fields[row][column]->visit(pac);
}


bool Board::areInTheSameHole(unsigned row1, unsigned column1, unsigned row2, unsigned column2) const
{
    assert(fields[row1][column1]->isVisitable());
    assert(fields[row2][column2]->isVisitable());

    // checks if fields have the same rows:
    if(row1 == row2)
    {
        auto minColumn = std::min(column1, column2);
        auto maxColumn = std::max(column1, column2);

        for(auto c = minColumn + 1; c < maxColumn; ++c)
        {
            if(!fields[row1][c]->isVisitable())
            {
                // there is non-visitable field between the two fields
                return false;
            }
        }

        return true;
    }

    // checks if fields have the same columns:
    if(column1 == column2)
    {
        auto minRow = std::min(row1, row2);
        auto maxRow = std::max(row1, row2);

        for(auto r = minRow + 1; r < maxRow; ++r)
        {
            if(!fields[r][column1]->isVisitable())
            {
                // there is non-visitable field between the two fields
                return false;
            }
        }

        return true;
    }

    // the two fields have different rows and columns...
    assert((row1 != row2) && (column1 != column2));

    // ...so cannot be in the same hole
    return false;
}


void Board::draw() const
{
    for(const auto& row : fields)
        for(const auto& f : row)
            f->draw(*graphicController);
}


void Board::reset()
{
    for(auto& row : fields)
        for(auto& f : row)
            f->reset();
}


} // namespace Model
} // namespace Pacman
