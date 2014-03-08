#ifndef PACMAN_MODEL_IGAMEMODEMANAGER_HPP
#define PACMAN_MODEL_IGAMEMODEMANAGER_HPP


#include <Model/GameMode.hpp>


namespace Pacman
{
namespace Model
{


class IGameModeManager
{
public:
    virtual void activateBigCoinMode() = 0;
    virtual GameMode getGameMode() const = 0;

    virtual void reset() = 0;

    virtual ~IGameModeManager() = default;
};


} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_IGAMEMODEMANAGER_HPP
