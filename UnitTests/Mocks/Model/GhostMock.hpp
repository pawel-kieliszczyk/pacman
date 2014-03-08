#ifndef PACMAN_MODEL_TESTING_GHOSTMOCK_HPP
#define PACMAN_MODEL_TESTING_GHOSTMOCK_HPP


#include <gmock/gmock.h>

#include <Model/IGhost.hpp>


namespace Pacman
{
namespace Model
{
namespace Testing
{


class GhostMock : public IGhost
{
public:
    MOCK_METHOD0(move, void());
    MOCK_CONST_METHOD0(getCurrentX, double());
    MOCK_CONST_METHOD0(getCurrentY, double());
    MOCK_CONST_METHOD0(draw, void());
    MOCK_METHOD0(reset, void());
};


} // namespace Testing
} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_TESTING_GHOSTMOCK_HPP
