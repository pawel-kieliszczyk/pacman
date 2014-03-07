#include <Model/GameModeManager.hpp>


namespace Pacman
{
namespace Model
{


GameModeManager::GameModeManager(unsigned bigCoinModeDuration_, unsigned bigCoinLastSecondsModeDuration_)
    : bigCoinModeDuration(bigCoinModeDuration_),
      bigCoinLastSecondsModeDuration(bigCoinLastSecondsModeDuration_),
      bigCoinModesClockTicksToExpire(0u)
{
}


void GameModeManager::activateBigCoinMode()
{
    bigCoinModesClockTicksToExpire = bigCoinModeDuration + bigCoinLastSecondsModeDuration;
}


void GameModeManager::onClockTick()
{
    if(bigCoinModesClockTicksToExpire > 0u)
        --bigCoinModesClockTicksToExpire;
}


GameMode GameModeManager::getGameMode() const
{
    if(bigCoinModesClockTicksToExpire == 0u)
        return GameMode::Normal;

    if(bigCoinModesClockTicksToExpire <= bigCoinLastSecondsModeDuration)
        return GameMode::BigCoinLastSeconds;

    return GameMode::BigCoin;
}

void GameModeManager::reset()
{
    bigCoinModesClockTicksToExpire = 0u;
}


} // namespace Model
} // namespace Pacman
