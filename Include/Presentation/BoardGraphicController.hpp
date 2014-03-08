#ifndef PACMAN_PRESENTATION_BOARDGRAPHICCONTROLLER_HPP
#define PACMAN_PRESENTATION_BOARDGRAPHICCONTROLLER_HPP


#include <vector>

#include <cinder/Vector.h>

#include <Presentation/IBoardGraphicController.hpp>


namespace Pacman
{
namespace Presentation
{


class BoardGraphicController : public IBoardGraphicController
{
public:
    BoardGraphicController(unsigned fieldSize_, unsigned horizontalOffset_);

    void drawCoin(unsigned row, unsigned column) override;
    void drawBigCoin(unsigned row, unsigned column) override;

    void drawApple(unsigned row, unsigned column) override;
    void drawCherry(unsigned row, unsigned column) override;
    void drawOrange(unsigned row, unsigned column) override;

    void drawWall(unsigned row, unsigned column) override;

private:
    std::vector<ci::Vec2f> createStarSkeleton(unsigned starSize) const;

    std::vector<ci::Vec2f> createStarBorderPoints(
            const std::vector<ci::Vec2f>& skeleton,
            const ci::Vec2f& position) const;

    void drawStarBody(const std::vector<ci::Vec2f>& points, const ci::Vec2f& center);

    void drawStarBorder(const std::vector<ci::Vec2f>& points);

    const unsigned fieldSize;
    const unsigned horizontalOffset;
};


} // namespace Presentation
} // namespace Pacman


#endif // PACMAN_PRESENTATION_BOARDGRAPHICCONTROLLER_HPP
