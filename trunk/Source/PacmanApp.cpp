#include <cassert>
#include <memory>
#include <utility>
#include <vector>

#include <cinder/app/AppBasic.h>

#include <Model/GameControllerEvents.hpp>
#include <PacmanApp.hpp>


namespace Pacman
{


PacmanApp::PacmanApp(
        const unsigned fieldSize_,
        const unsigned horizontalMargin_,
        std::shared_ptr<Model::IBoard> board_,
        std::shared_ptr<Model::IGameController> gameController_,
        std::shared_ptr<Presentation::IWindowGraphicController> windowGraphicController_)
    : fieldSize(fieldSize_),
      horizontalMargin(horizontalMargin_),
      board(board_),
      gameController(gameController_),
      windowGraphicController(windowGraphicController_)
{
}


void PacmanApp::prepareSettings(Settings* settings)
{
    const auto boardWidth = board->getNumOfColumns() * fieldSize;
    const auto boardHeight = board->getNumOfRows() * fieldSize;

    assert(settings != nullptr);

    windowGraphicController->prepareSettings(*settings, boardWidth, boardHeight, horizontalMargin);
}


void PacmanApp::setup()
{
    windowGraphicController->clearWindow();
}


void PacmanApp::update()
{
    gameController->process(Model::MoveRequested());
}


void PacmanApp::draw()
{
    gameController->process(Model::DrawRequested());
}


void PacmanApp::keyDown(ci::app::KeyEvent event)
{
    switch(event.getCode())
    {
        case ci::app::KeyEvent::KEY_UP :
            gameController->process(Model::KeyPressed(Model::Key::UpArrow));
            break;
        case ci::app::KeyEvent::KEY_DOWN :
            gameController->process(Model::KeyPressed(Model::Key::DownArrow));
            break;
        case ci::app::KeyEvent::KEY_LEFT :
            gameController->process(Model::KeyPressed(Model::Key::LeftArrow));
            break;
        case ci::app::KeyEvent::KEY_RIGHT :
            gameController->process(Model::KeyPressed(Model::Key::RightArrow));
            break;
        case ci::app::KeyEvent::KEY_p :
            gameController->process(Model::KeyPressed(Model::Key::P));
            break;
        case ci::app::KeyEvent::KEY_RETURN :
            gameController->process(Model::KeyPressed(Model::Key::Return));
            break;
        case ci::app::KeyEvent::KEY_ESCAPE :
            gameController->process(Model::KeyPressed(Model::Key::Escape));
            break;
    }
}


} // namespace Pacman
