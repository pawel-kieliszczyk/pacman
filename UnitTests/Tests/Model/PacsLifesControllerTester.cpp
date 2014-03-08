#include <memory>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <Model/PacsLifesController.hpp>

#include <Mocks/Presentation/PacsLifesGraphicControllerMock.hpp>


namespace GT = testing;


namespace Pacman
{
namespace Model
{
namespace Testing
{


struct PacsLifesControllerTester : public GT::Test
{

    const unsigned numberOfLifes = 3u;

    // mocks:
    std::shared_ptr<Presentation::Testing::PacsLifesGraphicControllerMock> pacsLifesGraphicController =
            std::make_shared<GT::StrictMock<Presentation::Testing::PacsLifesGraphicControllerMock>>();

    // tested class:
    PacsLifesController pacsLifesController{numberOfLifes, pacsLifesGraphicController};
};


TEST_F(PacsLifesControllerTester, checksWhetherPacIsDead)
{
    // when and then
    for(unsigned i = numberOfLifes; i > 0; --i)
    {
        EXPECT_FALSE(pacsLifesController.isDead());
        pacsLifesController.consumeNextLife();
    }

    EXPECT_TRUE(pacsLifesController.isDead());
}


TEST_F(PacsLifesControllerTester, resetsController)
{
    // given
    for(unsigned i = numberOfLifes; i > 0; --i)
    {
        pacsLifesController.consumeNextLife();
    }
    ASSERT_TRUE(pacsLifesController.isDead());

    // when
    pacsLifesController.reset();

    // then
    for(unsigned i = numberOfLifes; i > 0; --i)
    {
        EXPECT_FALSE(pacsLifesController.isDead());
        pacsLifesController.consumeNextLife();
    }

    EXPECT_TRUE(pacsLifesController.isDead());
}


TEST_F(PacsLifesControllerTester, drawsPacsLifes)
{
    // expect
    EXPECT_CALL(*pacsLifesGraphicController, draw(numberOfLifes));

    // when and then
    pacsLifesController.drawPacsLifes();

    // given
    pacsLifesController.consumeNextLife();

    // expect
    EXPECT_CALL(*pacsLifesGraphicController, draw(numberOfLifes - 1));

    // when and then
    pacsLifesController.drawPacsLifes();

    // given
    pacsLifesController.consumeNextLife();
    pacsLifesController.consumeNextLife();

    // expect
    EXPECT_CALL(*pacsLifesGraphicController, draw(0u));

    // when and then
    pacsLifesController.drawPacsLifes();
}


} // namespace Testing
} // namespace Model
} // namespace Pacman
