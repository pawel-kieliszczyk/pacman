#include <memory>

#include <Model/Apple.hpp>
#include <Model/Cherry.hpp>
#include <Model/FruitsVisibilityDurationController.hpp>
#include <Model/Orange.hpp>


namespace Pacman
{
namespace Model
{


FruitsVisibilityDurationController::FruitsVisibilityDurationController(
            const unsigned long minShownFruitDuration_,
            const unsigned long maxShownFruitDuration_,
            const unsigned long minHiddenFruitDuration_,
            const unsigned long maxHiddenFruitDuration_,
            std::shared_ptr<IRandomUnsignedLongGenerator> randomDurationGenerator_,
            std::shared_ptr<IFruitVisibilityManager> visibilityManager_,
            std::shared_ptr<Presentation::IFruitGraphicController> fruitGraphicController_)
    : minShownFruitDuration(minShownFruitDuration_),
      maxShownFruitDuration(maxShownFruitDuration_),
      minHiddenFruitDuration(minHiddenFruitDuration_),
      maxHiddenFruitDuration(maxHiddenFruitDuration_),
      randomDurationGenerator(randomDurationGenerator_),
      visibilityManager(visibilityManager_),
      fruitGraphicController(fruitGraphicController_),
      state(FruitState::Invisible),
      timeToStateTransition(maxHiddenFruitDuration)
{
}


void FruitsVisibilityDurationController::onClockTick()
{
    switch(state)
    {
        case FruitState::Visible :
            if(--timeToStateTransition == 0)
            {
                visibilityManager->hideFruit();

                state = FruitState::Invisible;
                timeToStateTransition = randomDurationGenerator->next(minHiddenFruitDuration, maxHiddenFruitDuration);
            }
            break;
        case FruitState::Invisible :
            if(--timeToStateTransition == 0)
            {
                auto randomFruit = getRandomFruit();
                visibilityManager->showFruit(randomFruit);

                state = FruitState::Visible;
                timeToStateTransition = randomDurationGenerator->next(minShownFruitDuration, maxShownFruitDuration);
            }
            break;
    }
}


std::shared_ptr<IFruit> FruitsVisibilityDurationController::getRandomFruit()
{
    const auto  rand = randomDurationGenerator->next(0, 2);

    switch(rand)
    {
        case 0 :
            return std::make_shared<Apple>(fruitGraphicController);
        case 1 :
            return std::make_shared<Cherry>(fruitGraphicController);
        default :
            return std::make_shared<Orange>(fruitGraphicController);
    }
}


} // namespace Model
} // namespace Pacman
