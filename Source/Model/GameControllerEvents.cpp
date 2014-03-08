#include <Model/GameControllerEvents.hpp>


namespace Pacman
{
namespace Model
{


KeyPressed::KeyPressed(Key key_)
    : key(key_)
{
}


Key KeyPressed::getKey() const
{
    return key;
}


bool operator==(const KeyPressed& lhs, const KeyPressed& rhs)
{
    return (lhs.getKey() == rhs.getKey());
}


bool operator==(const MoveRequested&, const MoveRequested&)
{
    return true;
}


bool operator==(const DrawRequested&, const DrawRequested&)
{
    return true;
}


} // namespace Model
} // namespace Pacman
