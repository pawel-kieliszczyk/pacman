#include <Model/Detail/GameControllerFsm.hpp>
#include <Model/Direction.hpp>
#include <Model/GameControllerEvents.hpp>


namespace Pacman
{
namespace Model
{
namespace Detail
{


GameControllerFsm::GameControllerFsm(
        std::shared_ptr<IBoard> board_,
        std::shared_ptr<IPac> pac_,
        std::vector<std::shared_ptr<IGhost>> ghosts_,
        std::shared_ptr<IClock> clock_,
        std::shared_ptr<IGameModeManager> gameModeManager_,
        std::shared_ptr<ICoinsCollector> coinsCollector_,
        std::shared_ptr<IFruitsCollector> fruitsCollector_,
        std::shared_ptr<ICollisionDetector> collisionDetector_,
        std::shared_ptr<IPacsLifesController> pacsLifesController_,
        std::shared_ptr<IScoreController> scoreController_,
        std::shared_ptr<Presentation::IWindowGraphicController> windowGraphicController_)
    : board(board_),
      pac(pac_),
      ghosts(ghosts_),
      clock(clock_),
      gameModeManager(gameModeManager_),
      coinsCollector(coinsCollector_),
      fruitsCollector(fruitsCollector_),
      collisionDetector(collisionDetector_),
      pacsLifesController(pacsLifesController_),
      scoreController(scoreController_),
      windowGraphicController(windowGraphicController_)
{
}


void GameControllerFsm::clearWindow()
{
    windowGraphicController->clearWindow();
}


void GameControllerFsm::drawBoard()
{
    board->draw();
}


void GameControllerFsm::drawPac()
{
    pac->draw();
}


void GameControllerFsm::drawGhosts()
{
    for(auto& g : ghosts)
        g->draw();
}


void GameControllerFsm::drawPacsLifes()
{
    pacsLifesController->drawPacsLifes();
}


void GameControllerFsm::drawScore()
{
    scoreController->drawScore();
}


void GameControllerFsm::drawFruits()
{
    fruitsCollector->drawFruits();
}


void GameControllerFsm::drawStoppedGameCurtain()
{
    windowGraphicController->drawStoppedGameCurtain();
}


void GameControllerFsm::drawPausedGameCurtain()
{
    windowGraphicController->drawPausedGameCurtain();
}


void GameControllerFsm::drawWonGameCurtain()
{
    windowGraphicController->drawWonGameCurtain();
}


void GameControllerFsm::drawLostGameCurtain()
{
    windowGraphicController->drawLostGameCurtain();
}


void GameControllerFsm::tickClock()
{
    clock->tick();
}


void GameControllerFsm::setPacsDirection(const KeyPressed& event)
{
    switch(event.getKey())
    {
        case Key::UpArrow :
            pac->setDirection(Direction::Up);
            break;
        case Key::DownArrow :
            pac->setDirection(Direction::Down);
            break;
        case Key::LeftArrow :
            pac->setDirection(Direction::Left);
            break;
        case Key::RightArrow :
            pac->setDirection(Direction::Right);
            break;
        default :
            break;
    }
}


void GameControllerFsm::movePac()
{
    pac->move();
}


void GameControllerFsm::moveGhosts()
{
    for(auto& g : ghosts)
        g->move();
}


void GameControllerFsm::consumePacsLife()
{
    pacsLifesController->consumeNextLife();
}


void GameControllerFsm::resetBoard()
{
    board->reset();
}


void GameControllerFsm::resetPac()
{
    pac->reset();
}


void GameControllerFsm::resetGhosts()
{
    for(auto& g : ghosts)
        g->reset();
}


void GameControllerFsm::resetCollidingGhosts()
{
    for(auto const& ghost : ghosts)
    {
        if(collisionDetector->areColliding(*pac, *ghost))
        {
            ghost->reset();
            scoreController->addGhostScore();
        }
    }
}


void GameControllerFsm::resetCoinsCollector()
{
    coinsCollector->reset();
}


void GameControllerFsm::resetFruitsCollector()
{
    fruitsCollector->reset();
}


void GameControllerFsm::resetPacsLifesController()
{
    pacsLifesController->reset();
}


void GameControllerFsm::resetScoreController()
{
    scoreController->reset();
}


void GameControllerFsm::resetGameModeManager()
{
    gameModeManager->reset();
}


bool GameControllerFsm::areAllCoinsCollected() const
{
    return coinsCollector->allCoinsCollected();
}


bool GameControllerFsm::isBigCoinModeActive() const
{
    const GameMode mode = gameModeManager->getGameMode();
    return (mode == GameMode::BigCoin) || (mode == GameMode::BigCoinLastSeconds);
}


bool GameControllerFsm::areAnyCollisions() const
{
    for(auto const& ghost : ghosts)
    {
        if(collisionDetector->areColliding(*pac, *ghost))
            return true;
    }

    return false;
}


bool GameControllerFsm::isPacDead() const
{
    return pacsLifesController->isDead();
}


} // namespace Detail
} // namespace Model
} // namespace Pacman
