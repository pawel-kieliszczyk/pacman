#ifndef PACMAN_MODEL_TESTING_GAMEMODEMANAGERMOCK_HPP
#define PACMAN_MODEL_TESTING_GAMEMODEMANAGERMOCK_HPP


#include <gmock/gmock.h>

#include <Model/IGameModeManager.hpp>


namespace Pacman
{
namespace Model
{
namespace Testing
{


class GameModeManagerMock : public IGameModeManager
{
public:
    MOCK_METHOD0(activateBigCoinMode, void());
    MOCK_CONST_METHOD0(getGameMode, GameMode());
    MOCK_METHOD0(reset, void());
};


} // namespace Testing
} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_TESTING_GAMEMODEMANAGERMOCK_HPP
