#ifndef PACMAN_MODEL_COLLISIONDETECTOR_HPP
#define PACMAN_MODEL_COLLISIONDETECTOR_HPP


#include <Model/ICollisionDetector.hpp>


namespace Pacman
{
namespace Model
{


class CollisionDetector : public ICollisionDetector
{
public:
    CollisionDetector(double distanceToCollide_);

    bool areColliding(const IPac& pac, const IGhost& ghost) const override;

private:
    const double distanceToCollide;
};


} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_COLLISIONDETECTOR_HPP
