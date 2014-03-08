#include <Model/PacsLifesController.hpp>


namespace Pacman
{
namespace Model
{


PacsLifesController::PacsLifesController(
        unsigned numberOfLifes_,
        std::shared_ptr<Presentation::IPacsLifesGraphicController> graphicController_)
    : initialNumberOfLifes(numberOfLifes_),
      numberOfLifes(numberOfLifes_),
      graphicController(graphicController_)
{
}


void PacsLifesController::consumeNextLife()
{
    --numberOfLifes;
}


bool PacsLifesController::isDead() const
{
    return (numberOfLifes == 0);
}


void PacsLifesController::drawPacsLifes() const
{
    graphicController->draw(numberOfLifes);
}


void PacsLifesController::reset()
{
    numberOfLifes = initialNumberOfLifes;
}


} // namespace Model
} // namespace Pacman
