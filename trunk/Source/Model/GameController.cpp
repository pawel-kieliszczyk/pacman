#include <utility>

#include <Model/GameController.hpp>


namespace Pacman
{
namespace Model
{


GameController::~GameController()
{
    gameControllerFsm->stop();
}


void GameController::process(const KeyPressed& event)
{
    gameControllerFsm->process_event(event);
}


void GameController::process(const MoveRequested& event)
{
    gameControllerFsm->process_event(event);
}


void GameController::process(const DrawRequested& event)
{
    gameControllerFsm->process_event(event);
}


} // namespace Model
} // namespace Pacman
