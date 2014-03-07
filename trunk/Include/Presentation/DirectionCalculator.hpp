#ifndef PACMAN_PRESENTATION_DIRECTIONCALCULATOR_HPP
#define PACMAN_PRESENTATION_DIRECTIONCALCULATOR_HPP


#include <Presentation/IDirectionCalculator.hpp>


namespace Pacman
{
namespace Presentation
{


class DirectionCalculator : public IDirectionCalculator
{
public:
    boost::optional<Model::Direction> calculate(
            int fromRow,
            int fromColumn,
            int toRow,
            int toColumn) override;
};


} // namespace Presentation
} // namespace Pacman


#endif // PACMAN_PRESENTATION_DIRECTIONCALCULATOR_HPP
