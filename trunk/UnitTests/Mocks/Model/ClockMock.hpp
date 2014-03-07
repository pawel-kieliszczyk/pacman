#ifndef PACMAN_MODEL_TESTING_CLOCKMOCK_HPP
#define PACMAN_MODEL_TESTING_CLOCKMOCK_HPP


#include <gmock/gmock.h>

#include <Model/IClock.hpp>


namespace Pacman
{
namespace Model
{
namespace Testing
{


class ClockMock : public IClock
{
public:
    MOCK_METHOD0(tick, void());
};


} // namespace Testing
} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_TESTING_CLOCKMOCK_HPP
