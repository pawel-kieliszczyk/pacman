#include <Model/ScoreController.hpp>


namespace Pacman
{
namespace Model
{


ScoreController::ScoreController(
        unsigned coinScore_,
        unsigned bigCoinScore_,
        unsigned ghostScore_,
        std::shared_ptr<Presentation::IScoreGraphicController> graphicController_)
    : coinScore(coinScore_),
      bigCoinScore(bigCoinScore_),
      ghostScore(ghostScore_),
      score(0u),
      graphicController(graphicController_)
{
}


void ScoreController::addCoinScore()
{
    score += coinScore;
}


void ScoreController::addBigCoinScore()
{
    score += bigCoinScore;
}


void ScoreController::addGhostScore()
{
    score += ghostScore;
}


void ScoreController::drawScore() const
{
    graphicController->draw(score);
}


void ScoreController::reset()
{
    score = 0u;
}


} // namespace Model
} // namespace Pacman
