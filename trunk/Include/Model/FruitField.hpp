#ifndef PACMAN_MODEL_FRUITFIELD_HPP
#define PACMAN_MODEL_FRUITFIELD_HPP


#include <memory>
#include <vector>

#include <boost/optional.hpp>

#include <Model/FieldBase.hpp>
#include <Model/IFruit.hpp>
#include <Model/IFruitVisibilityManager.hpp>


namespace Pacman
{
namespace Model
{


class FruitField : public FieldBase, public IFruitVisibilityManager
{
public:
    FruitField(
            unsigned row,
            unsigned col,
            unsigned maxNumberOfFruitsToEat_ = 5u);

    bool isVisitable() const override;
    void visit(IPac& pac) override;
    void draw(Presentation::IBoardGraphicController& graphicController) const override;
    void reset() override;

    void showFruit(std::shared_ptr<IFruit> f) override;
    void hideFruit() override;

private:
    const unsigned maxNumberOfFruitsToEat;
    unsigned numberOfEatenFruits;

    boost::optional<std::shared_ptr<IFruit>> currentShownFruit;
};


} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_FRUITFIELD_HPP
