#ifndef PACMAN_MODEL_ICOLLISIONDETECTOR_HPP
#define PACMAN_MODEL_ICOLLISIONDETECTOR_HPP


#include <Model/IGhost.hpp>
#include <Model/IPac.hpp>


namespace Pacman
{
namespace Model
{


class ICollisionDetector
{
public:
    virtual bool areColliding(const IPac& pac, const IGhost& ghost) const = 0;

    virtual ~ICollisionDetector() = default;
};


} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_ICOLLISIONDETECTOR_HPP
