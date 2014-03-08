#include <boost/none.hpp>

#include <Presentation/DirectionCalculator.hpp>


namespace Pacman
{
namespace Presentation
{


boost::optional<Model::Direction> DirectionCalculator::calculate(
            int fromRow,
            int fromColumn,
            int toRow,
            int toColumn)
{
    if(toRow > fromRow)
        return Model::Direction::Down;
    if(toRow < fromRow)
        return Model::Direction::Up;
    if(toColumn > fromColumn)
        return Model::Direction::Right;
    if(toColumn < fromColumn)
        return Model::Direction::Left;

    return boost::none;
}


} // namespace Presentation
} // namespace Pacman
