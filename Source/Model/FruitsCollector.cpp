#include <Model/FruitsCollector.hpp>


namespace Pacman
{
namespace Model
{


void FruitsCollector::collectFruit(std::shared_ptr<IFruit> fruit)
{
    collectedFruits.push_back(fruit);
}


void FruitsCollector::drawFruits() const
{
    for(std::vector<std::shared_ptr<IFruit>>::size_type i = 0; i < collectedFruits.size(); ++i)
        collectedFruits[i]->draw(static_cast<unsigned>(i));
}


void FruitsCollector::reset()
{
    collectedFruits.clear();
}


} // namespace Model
} // namespace Pacman
