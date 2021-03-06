#ifndef PACMAN_MODEL_CHERRY_HPP
#define PACMAN_MODEL_CHERRY_HPP


#include <memory>

#include <Model/IFruit.hpp>
#include <Presentation/IFruitGraphicController.hpp>


namespace Pacman
{
namespace Model
{


class Cherry : public IFruit
{
public:
    Cherry(std::shared_ptr<Presentation::IFruitGraphicController> graphicController_);

    void draw(const unsigned fruitNumber) const override;

    void draw(
            const unsigned row,
            const unsigned column,
            Presentation::IBoardGraphicController& graphicController) const override;

private:
    std::shared_ptr<Presentation::IFruitGraphicController> graphicController;
};


} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_CHERRY_HPP
