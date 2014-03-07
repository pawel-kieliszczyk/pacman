#ifndef PACMAN_PRESENTATION_FRUITGRAPHICCONTROLLER_HPP
#define PACMAN_PRESENTATION_FRUITGRAPHICCONTROLLER_HPP


#include <vector>

#include <cinder/Vector.h>

#include <Presentation/IFruitGraphicController.hpp>


namespace Pacman
{
namespace Presentation
{


class FruitGraphicController : public IFruitGraphicController
{
public:
    FruitGraphicController(unsigned fruitSize_, unsigned boardHeight_, unsigned horizontalOffset_, unsigned horizontalMargin_);

    void drawApple(const unsigned fruitNumber) override;
    void drawCherry(const unsigned fruitNumber) override;
    void drawOrange(const unsigned fruitNumber) override;

private:
    std::vector<ci::Vec2f> createStarSkeleton(unsigned starSize) const;

    std::vector<ci::Vec2f> createStarBorderPoints(
            const std::vector<ci::Vec2f>& skeleton,
            const ci::Vec2f& position) const;

    void drawStarBody(const std::vector<ci::Vec2f>& points, const ci::Vec2f& center);

    void drawStarBorder(const std::vector<ci::Vec2f>& points);

    const unsigned fruitSize;
    const unsigned boardHeight;
    const unsigned horizontalOffset;
    const unsigned horizontalMargin;
};


} // namespace Presentation
} // namespace Pacman


#endif // PACMAN_PRESENTATION_FRUITGRAPHICCONTROLLER_HPP
