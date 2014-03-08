#include <utility>

#include <Model/ClockTickNotifier.hpp>


namespace Pacman
{
namespace Model
{


ClockTickNotifier::ClockTickNotifier(std::vector<std::shared_ptr<IClockTickListener>>&& listeners_)
    : listeners(std::move(listeners_))
{
}


void ClockTickNotifier::tick()
{
    for(auto& l : listeners)
        l->onClockTick();
}


} // namespace Model
} // namespace Pacman
