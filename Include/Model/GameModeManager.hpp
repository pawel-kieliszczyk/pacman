#ifndef PACMAN_MODEL_GAMEMODEMANAGER_HPP
#define PACMAN_MODEL_GAMEMODEMANAGER_HPP


#include <Model/IClockTickListener.hpp>
#include <Model/IGameModeManager.hpp>


namespace Pacman
{
namespace Model
{


class GameModeManager : public IGameModeManager, public IClockTickListener
{
public:
    GameModeManager(unsigned bigCoinModeDuration_, unsigned bigCoinLastSecondsModeDuration_);

    void activateBigCoinMode() override;
    void onClockTick() override;
    GameMode getGameMode() const override;

    void reset() override;

private:
    const unsigned bigCoinModeDuration;
    const unsigned bigCoinLastSecondsModeDuration;

    unsigned bigCoinModesClockTicksToExpire;
};


} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_GAMEMODEMANAGER_HPP
