#ifndef PACMAN_MODEL_IGAMECONTROLLER_HPP
#define PACMAN_MODEL_IGAMECONTROLLER_HPP


#include <Model/GameControllerEvents.hpp>


namespace Pacman
{
namespace Model
{


class IGameController
{
public:
    virtual void process(const KeyPressed& event) = 0;
    virtual void process(const MoveRequested& event) = 0;
    virtual void process(const DrawRequested& event) = 0;

    virtual ~IGameController() = default;
};


} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_IGAMECONTROLLER_HPP
