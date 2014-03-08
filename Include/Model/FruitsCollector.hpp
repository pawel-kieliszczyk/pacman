#ifndef PACMAN_MODEL_FRUITSCOLLECTOR_HPP
#define PACMAN_MODEL_FRUITSCOLLECTOR_HPP


#include <memory>
#include <vector>

#include <Model/IFruit.hpp>
#include <Model/IFruitsCollector.hpp>


namespace Pacman
{
namespace Model
{


class FruitsCollector : public IFruitsCollector
{
public:
    void collectFruit(std::shared_ptr<IFruit> fruit) override;
    void drawFruits() const override;
    void reset() override;

private:
    std::vector<std::shared_ptr<IFruit>> collectedFruits;
};


} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_FRUITSCOLLECTOR_HPP
