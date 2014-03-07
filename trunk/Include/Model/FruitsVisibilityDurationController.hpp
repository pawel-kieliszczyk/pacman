#ifndef PACMAN_MODEL_FRUITSVISIBILITYDURATIONCONTROLLER_HPP
#define PACMAN_MODEL_FRUITSVISIBILITYDURATIONCONTROLLER_HPP


#include <memory>

#include <Model/IClockTickListener.hpp>
#include <Model/IFruit.hpp>
#include <Model/IFruitVisibilityManager.hpp>
#include <Model/IRandomNumberGenerator.hpp>

#include <Presentation/IFruitGraphicController.hpp>


namespace Pacman
{
namespace Model
{


class FruitsVisibilityDurationController : public IClockTickListener
{
public:
    FruitsVisibilityDurationController(
            const unsigned long minShownFruitDuration_,
            const unsigned long maxShownFruitDuration_,
            const unsigned long minHiddenFruitDuration_,
            const unsigned long maxHiddenFruitDuration_,
            std::shared_ptr<IRandomUnsignedLongGenerator> randomDurationGenerator_,
            std::shared_ptr<IFruitVisibilityManager> visibilityManager_,
            std::shared_ptr<Presentation::IFruitGraphicController> fruitGraphicController_);

    void onClockTick() override;

private:
    std::shared_ptr<IFruit> getRandomFruit();

    enum class FruitState { Visible, Invisible };

    const unsigned long minShownFruitDuration;
    const unsigned long maxShownFruitDuration;
    const unsigned long minHiddenFruitDuration;
    const unsigned long maxHiddenFruitDuration;

    std::shared_ptr<IRandomUnsignedLongGenerator> randomDurationGenerator;
    std::shared_ptr<IFruitVisibilityManager> visibilityManager;
    std::shared_ptr<Presentation::IFruitGraphicController> fruitGraphicController;

    FruitState state;
    unsigned long timeToStateTransition;
};


} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_FRUITSVISIBILITYDURATIONCONTROLLER_HPP
