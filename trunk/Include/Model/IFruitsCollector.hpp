#ifndef PACMAN_MODEL_IFRUITSCOLLECTOR_HPP
#define PACMAN_MODEL_IFRUITSCOLLECTOR_HPP


#include <memory>

#include <Model/IFruit.hpp>


namespace Pacman
{
namespace Model
{


class IFruitsCollector
{
public:
    virtual void collectFruit(std::shared_ptr<IFruit> fruit) = 0;
    virtual void drawFruits() const = 0;
    virtual void reset() = 0;

    virtual ~IFruitsCollector() = default;
};


} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_IFRUITSCOLLECTOR_HPP
