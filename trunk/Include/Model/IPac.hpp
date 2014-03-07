#ifndef PACMAN_MODEL_IPAC_HPP
#define PACMAN_MODEL_IPAC_HPP


#include <memory>

#include <Model/Direction.hpp>
#include <Model/IFruit.hpp>


namespace Pacman
{
namespace Model
{


class IPac
{
public:
    virtual void setDirection(Direction newDirection) = 0;
    virtual void move() = 0;

    virtual int getCurrentRow() const = 0;
    virtual int getCurrentColumn() const = 0;

    virtual double getCurrentX() const = 0;
    virtual double getCurrentY() const = 0;

    virtual void eatCoin() = 0;
    virtual void eatBigCoin() = 0;
    virtual void eatFruit(std::shared_ptr<IFruit> fruit) = 0;

    virtual void draw() const = 0;

    virtual void reset() = 0;

    virtual ~IPac() = default;
};


} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_IPAC_HPP
