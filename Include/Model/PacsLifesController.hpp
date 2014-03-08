#ifndef PACMAN_MODEL_PACSLIFESCONTROLLER_HPP
#define PACMAN_MODEL_PACSLIFESCONTROLLER_HPP


#include <memory>

#include <Model/IPacsLifesController.hpp>
#include <Presentation/IPacsLifesGraphicController.hpp>


namespace Pacman
{
namespace Model
{


class PacsLifesController : public IPacsLifesController
{
public:
    PacsLifesController(
            unsigned numberOfLifes_,
            std::shared_ptr<Presentation::IPacsLifesGraphicController> graphicController_);

    void consumeNextLife() override;
    bool isDead() const override;

    void drawPacsLifes() const override;

    void reset() override;

private:
    const unsigned initialNumberOfLifes;
    unsigned numberOfLifes;

    std::shared_ptr<Presentation::IPacsLifesGraphicController> graphicController;
};


} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_PACSLIFESCONTROLLER_HPP
