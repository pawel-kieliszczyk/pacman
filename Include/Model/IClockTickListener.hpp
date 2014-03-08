#ifndef PACMAN_MODEL_ICLOCKTICKLISTENER_HPP
#define PACMAN_MODEL_ICLOCKTICKLISTENER_HPP


namespace Pacman
{
namespace Model
{


class IClockTickListener
{
public:
    virtual void onClockTick() = 0;
    virtual ~IClockTickListener() = default;
};


} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_ICLOCKTICKLISTENER_HPP
