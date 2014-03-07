#ifndef PACMAN_MODEL_IFRUIT_HPP
#define PACMAN_MODEL_IFRUIT_HPP


#include <Presentation/IBoardGraphicController.hpp>


namespace Pacman
{
namespace Model
{


class IFruit
{
public:
    virtual void draw(const unsigned fruitNumber) const = 0;

    virtual void draw(
            const unsigned row,
            const unsigned column,
            Presentation::IBoardGraphicController& graphicController) const = 0;

    virtual ~IFruit() = default;
};


} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_IFRUIT_HPP
