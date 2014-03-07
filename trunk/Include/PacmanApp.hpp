#ifndef PACMAN_PACMANAPP_HPP
#define PACMAN_PACMANAPP_HPP


#include <memory>

#include <cinder/app/AppBasic.h>

#include <Model/IBoard.hpp>
#include <Model/IGameController.hpp>
#include <Presentation/IWindowGraphicController.hpp>


namespace Pacman
{


class PacmanApp : public ci::app::AppBasic
{
public:
    PacmanApp(
            const unsigned fieldSize_,
            const unsigned horizontalMargin_,
            std::shared_ptr<Model::IBoard> board_,
            std::shared_ptr<Model::IGameController> gameController_,
            std::shared_ptr<Presentation::IWindowGraphicController> windowGraphicController_);

    void prepareSettings(Settings* settings) override;

    void setup() override;
    void update() override;
    void draw() override;

    void keyDown(ci::app::KeyEvent event) override;

private:
    const unsigned fieldSize;
    const unsigned horizontalMargin;

    std::shared_ptr<Model::IBoard> board;
    std::shared_ptr<Model::IGameController> gameController;
    std::shared_ptr<Presentation::IWindowGraphicController> windowGraphicController;
};


} // namespace Pacman


#endif // PACMAN_PACMANAPP_HPP
