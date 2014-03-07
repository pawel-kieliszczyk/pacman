#include <cmath>

#include <Model/CollisionDetector.hpp>


namespace Pacman
{
namespace Model
{


CollisionDetector::CollisionDetector(double distanceToCollide_)
    : distanceToCollide(distanceToCollide_)
{
}


bool CollisionDetector::areColliding(const IPac& pac, const IGhost& ghost) const
{
    const auto x1 = pac.getCurrentX();
    const auto y1 = pac.getCurrentY();

    const auto x2 = ghost.getCurrentX();
    const auto y2 = ghost.getCurrentY();

    const auto xd = x2 - x1;
    const auto yd = y2 - y1;
    return (std::sqrt(xd * xd + yd * yd) < distanceToCollide);
}


} // namespace Model
} // namespace Pacman
