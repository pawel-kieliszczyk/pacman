#ifndef PACMAN_MODEL_TESTING_COLLISIONDETECTORMOCK_HPP
#define PACMAN_MODEL_TESTING_COLLISIONDETECTORMOCK_HPP


#include <gmock/gmock.h>

#include <Model/ICollisionDetector.hpp>


namespace Pacman
{
namespace Model
{
namespace Testing
{


class CollisionDetectorMock : public ICollisionDetector
{
public:
    MOCK_CONST_METHOD2(areColliding, bool(const IPac&, const IGhost&));
};


} // namespace Testing
} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_TESTING_COLLISIONDETECTORMOCK_HPP
