#ifndef PACMAN_PRESENTATION_IDIRECTIONCALCULATOR_HPP
#define PACMAN_PRESENTATION_IDIRECTIONCALCULATOR_HPP


#include <boost/optional.hpp>

#include <Model/Direction.hpp>


namespace Pacman
{
namespace Presentation
{


class IDirectionCalculator
{
public:
    virtual boost::optional<Model::Direction> calculate(
            int fromRow,
            int fromColumn,
            int toRow,
            int toColumn) = 0;

    virtual ~IDirectionCalculator() = default;
};


} // namespace Presentation
} // namespace Pacman


#endif // PACMAN_PRESENTATION_IDIRECTIONCALCULATOR_HPP
