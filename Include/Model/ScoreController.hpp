#ifndef PACMAN_MODEL_SCORECONTROLLER_HPP
#define PACMAN_MODEL_SCORECONTROLLER_HPP


#include <memory>

#include <Model/IScoreController.hpp>
#include <Presentation/IScoreGraphicController.hpp>


namespace Pacman
{
namespace Model
{


class ScoreController : public IScoreController
{
public:
    ScoreController(
            unsigned coinScore_,
            unsigned bigCoinScore_,
            unsigned ghostScore_,
            std::shared_ptr<Presentation::IScoreGraphicController> graphicController_);

    void addCoinScore() override;
    void addBigCoinScore() override;
    void addGhostScore() override;

    void drawScore() const override;

    void reset() override;

private:
    const unsigned coinScore;
    const unsigned bigCoinScore;
    const unsigned ghostScore;

    unsigned score;

    std::shared_ptr<Presentation::IScoreGraphicController> graphicController;
};


} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_SCORECONTROLLER_HPP
