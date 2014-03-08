#include <memory>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <PacmanApp.hpp>

#include <Mocks/Model/BoardMock.hpp>
#include <Mocks/Model/GameControllerMock.hpp>
#include <Mocks/Presentation/WindowGraphicControllerMock.hpp>


namespace GT = testing;


namespace Pacman
{


namespace Testing
{


struct PacmanAppTester : public GT::Test
{
    struct PushedKeyEvent : public ci::app::KeyEvent
    {
        PushedKeyEvent(int key) : ci::app::KeyEvent() { mCode = key; }
    };

    const unsigned fieldSize = 20;
    const unsigned horizontalMargin = 100;

    // mocks:
    std::shared_ptr<Model::Testing::BoardMock> boardMock =
            std::make_shared<GT::StrictMock<Model::Testing::BoardMock>>();
    std::shared_ptr<Model::Testing::GameControllerMock> gameControllerMock =
            std::make_shared<GT::StrictMock<Model::Testing::GameControllerMock>>();
    std::shared_ptr<Presentation::Testing::WindowGraphicControllerMock> windowGraphicControllerMock =
            std::make_shared<GT::StrictMock<Presentation::Testing::WindowGraphicControllerMock>>();

    // tested class:
    PacmanApp pacmanApp{
            fieldSize,
            horizontalMargin,
            boardMock,
            gameControllerMock,
            windowGraphicControllerMock};
};


MATCHER_P(HasMemoryAddress, address, "") { return &arg == address; }


TEST_F(PacmanAppTester, preparesSettingsForPacmanApp)
{
    // given
    const unsigned long numOfRows = 11;
    const unsigned long numOfCols = 22;
    ci::app::AppBasic::Settings settings;

    // expect
    EXPECT_CALL(*boardMock, getNumOfRows()).WillOnce(GT::Return(numOfRows));
    EXPECT_CALL(*boardMock, getNumOfColumns()).WillOnce(GT::Return(numOfCols));

    const unsigned boardWidth = numOfCols * fieldSize;
    const unsigned boardHeight = numOfRows * fieldSize;
    EXPECT_CALL(*windowGraphicControllerMock, prepareSettings(HasMemoryAddress(&settings), boardWidth, boardHeight, horizontalMargin));

    // when and then
    pacmanApp.prepareSettings(&settings);
}


TEST_F(PacmanAppTester, setupsPacmanApp)
{
    // expect
    EXPECT_CALL(*windowGraphicControllerMock, clearWindow());

    // when and then
    pacmanApp.setup();
}


TEST_F(PacmanAppTester, updatesPacmanApp)
{
    // expect
    Model::MoveRequested mr;
    EXPECT_CALL(*gameControllerMock, process(mr));

    // when and then
    pacmanApp.update();
}


TEST_F(PacmanAppTester, drawsPacmanApp)
{
    // expect
    Model::DrawRequested dr;
    EXPECT_CALL(*gameControllerMock, process(dr));

    // when and then
    pacmanApp.draw();
}


TEST_F(PacmanAppTester, pushesKeyUp)
{
    // given
    PushedKeyEvent up(ci::app::KeyEvent::KEY_UP);

    // expect
    Model::KeyPressed kp(Model::Key::UpArrow);
    EXPECT_CALL(*gameControllerMock, process(kp));

    // when and then
    pacmanApp.keyDown(up);
}


TEST_F(PacmanAppTester, pushesKeyDown)
{
    // given
    PushedKeyEvent down(ci::app::KeyEvent::KEY_DOWN);

    // expect
    Model::KeyPressed kp(Model::Key::DownArrow);
    EXPECT_CALL(*gameControllerMock, process(kp));

    // when and then
    pacmanApp.keyDown(down);
}


TEST_F(PacmanAppTester, pushesKeyLeft)
{
    // given
    PushedKeyEvent left(ci::app::KeyEvent::KEY_LEFT);

    // expect
    Model::KeyPressed kp(Model::Key::LeftArrow);
    EXPECT_CALL(*gameControllerMock, process(kp));

    // when and then
    pacmanApp.keyDown(left);
}


TEST_F(PacmanAppTester, pushesKeyRight)
{
    // given
    PushedKeyEvent right(ci::app::KeyEvent::KEY_RIGHT);

    // expect
    Model::KeyPressed kp(Model::Key::RightArrow);
    EXPECT_CALL(*gameControllerMock, process(kp));

    // when and then
    pacmanApp.keyDown(right);
}


TEST_F(PacmanAppTester, pushesKeyP)
{
    // given
    PushedKeyEvent p(ci::app::KeyEvent::KEY_p);

    // expect
    Model::KeyPressed kp(Model::Key::P);
    EXPECT_CALL(*gameControllerMock, process(kp));

    // when and then
    pacmanApp.keyDown(p);
}


TEST_F(PacmanAppTester, pushesKeyEnter)
{
    // given
    PushedKeyEvent ret(ci::app::KeyEvent::KEY_RETURN);

    // expect
    Model::KeyPressed kp(Model::Key::Return);
    EXPECT_CALL(*gameControllerMock, process(kp));

    // when and then
    pacmanApp.keyDown(ret);
}


TEST_F(PacmanAppTester, pushesKeyEscape)
{
    // given
    PushedKeyEvent escape(ci::app::KeyEvent::KEY_ESCAPE);

    // expect
    Model::KeyPressed kp(Model::Key::Escape);
    EXPECT_CALL(*gameControllerMock, process(kp));

    // when and then
    pacmanApp.keyDown(escape);
}


} // namespace Testing
} // namespace Pacman
