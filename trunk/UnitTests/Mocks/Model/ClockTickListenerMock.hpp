#ifndef PACMAN_MODEL_TESTING_CLOCKTICKLISTENERMOCK_HPP
#define PACMAN_MODEL_TESTING_CLOCKTICKLISTENERMOCK_HPP


#include <gmock/gmock.h>

#include <Model/IClockTickListener.hpp>


namespace Pacman
{
namespace Model
{
namespace Testing
{


class ClockTickListenerMock : public IClockTickListener
{
public:
    MOCK_METHOD0(onClockTick, void());
};


} // namespace Testing
} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_TESTING_CLOCKTICKLISTENERMOCK_HPP
