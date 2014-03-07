#ifndef PACMAN_MODEL_TESTING_GAMECONTROLLERMOCK_HPP
#define PACMAN_MODEL_TESTING_GAMECONTROLLERMOCK_HPP


#include <gmock/gmock.h>

#include <Model/IGameController.hpp>


namespace Pacman
{
namespace Model
{
namespace Testing
{


class GameControllerMock : public IGameController
{
public:
    MOCK_METHOD1(process, void(const KeyPressed&));
    MOCK_METHOD1(process, void(const MoveRequested&));
    MOCK_METHOD1(process, void(const DrawRequested&));
};


} // namespace Testing
} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_TESTING_GAMECONTROLLERMOCK_HPP
