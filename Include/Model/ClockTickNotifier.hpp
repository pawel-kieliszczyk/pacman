#ifndef PACMAN_MODEL_CLOCKTICKNOTIFIER_HPP
#define PACMAN_MODEL_CLOCKTICKNOTIFIER_HPP


#include <memory>
#include <vector>

#include <Model/IClock.hpp>
#include <Model/IClockTickListener.hpp>


namespace Pacman
{
namespace Model
{


class ClockTickNotifier : public IClock
{
public:
    explicit ClockTickNotifier(std::vector<std::shared_ptr<IClockTickListener>>&& listeners_);

    void tick() override;

private:
    std::vector<std::shared_ptr<IClockTickListener>> listeners;
};


} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_CLOCKTICKNOTIFIER_HPP
