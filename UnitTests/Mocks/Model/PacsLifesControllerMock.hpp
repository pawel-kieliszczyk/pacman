#ifndef PACMAN_MODEL_TESTING_PACSLIFESCONTROLLERMOCK_HPP
#define PACMAN_MODEL_TESTING_PACSLIFESCONTROLLERMOCK_HPP


#include <gmock/gmock.h>

#include <Model/IPacsLifesController.hpp>


namespace Pacman
{
namespace Model
{
namespace Testing
{


class PacsLifesControllerMock : public IPacsLifesController
{
public:
    MOCK_METHOD0(consumeNextLife, void());
    MOCK_CONST_METHOD0(isDead, bool());
    MOCK_CONST_METHOD0(drawPacsLifes, void());
    MOCK_METHOD0(reset, void());
};


} // namespace Testing
} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_TESTING_PACSLIFESCONTROLLERMOCK_HPP
