#include <algorithm>
#include <iterator>
#include <vector>

#include <cinder/gl/gl.h>
#include <cinder/Vector.h>

#include <Presentation/FruitGraphicController.hpp>


namespace Pacman
{
namespace Presentation
{


FruitGraphicController::FruitGraphicController(
        unsigned fruitSize_,
        unsigned boardHeight_,
        unsigned horizontalOffset_,
        unsigned horizontalMargin_)
    : fruitSize(fruitSize_),
      boardHeight(boardHeight_),
      horizontalOffset(horizontalOffset_),
      horizontalMargin(horizontalMargin_)
{
}


void FruitGraphicController::drawApple(const unsigned fruitNumber)
{
    // TODO: draw an apple instead of a star. Even if it looks nice... ;)

    float x = static_cast<float>(horizontalOffset) + static_cast<float>(horizontalMargin) / 2.0f;
    float y = static_cast<float>(boardHeight) - 1.5f * fruitSize;

    y -= static_cast<float>(fruitNumber) * (1.5f * fruitSize);

    ci::Vec2f center(x, y);

    std::vector<ci::Vec2f> skeleton = std::move(createStarSkeleton(fruitSize));

    std::vector<ci::Vec2f> points = std::move(createStarBorderPoints(skeleton, center));

    ci::gl::color(0.0f, 0.5f, 0.0f);
    drawStarBody(points, center);
    ci::gl::color(0.0f, 1.0f, 0.0f);
    drawStarBorder(points);
}


void FruitGraphicController::drawCherry(const unsigned fruitNumber)
{
    // TODO: draw a cherry instead of a star. Even if it looks nice... ;)

    float x = static_cast<float>(horizontalOffset) + static_cast<float>(horizontalMargin) / 2.0f;
    float y = static_cast<float>(boardHeight) - 1.5f * fruitSize;

    y -= static_cast<float>(fruitNumber) * (1.5f * fruitSize);

    ci::Vec2f center(x, y);

    std::vector<ci::Vec2f> skeleton = std::move(createStarSkeleton(fruitSize));
    std::vector<ci::Vec2f> points = std::move(createStarBorderPoints(skeleton, center));

    ci::gl::color(0.5f, 0.0f, 0.0f);
    drawStarBody(points, center);
    ci::gl::color(1.0f, 0.0f, 0.0f);
    drawStarBorder(points);
}


void FruitGraphicController::drawOrange(const unsigned fruitNumber)
{
    // TODO: draw an orange instead of a star. Even if it looks nice... ;)

    float x = static_cast<float>(horizontalOffset) + static_cast<float>(horizontalMargin) / 2.0f;
    float y = static_cast<float>(boardHeight) - 1.5f * fruitSize;

    y -= static_cast<float>(fruitNumber) * (1.5f * fruitSize);

    ci::Vec2f center(x, y);

    std::vector<ci::Vec2f> skeleton = std::move(createStarSkeleton(fruitSize));
    std::vector<ci::Vec2f> points = std::move(createStarBorderPoints(skeleton, center));

    ci::gl::color(0.5f, 0.0f, 0.5f);
    drawStarBody(points, center);
    ci::gl::color(1.0f, 0.0f, 1.0f);
    drawStarBorder(points);
}


std::vector<ci::Vec2f> FruitGraphicController::createStarSkeleton(unsigned starSize) const
{

    const float R = starSize / 2.0f;
    const float r = starSize / 4.0f;

    const float PI = 3.14159265f;

    std::vector<ci::Vec2f> skeleton;
    skeleton.emplace_back(R * std::cos(0.0f), R * std::sin(0.0f));
    skeleton.emplace_back(r * std::cos(0.0f + 0.2f * PI), r * std::sin(0.0f + 0.2f * PI));
    skeleton.emplace_back(R * std::cos(0.2f * 2.0f * PI), R * std::sin(0.2f * 2.0f * PI));
    skeleton.emplace_back(r * std::cos(0.2f * 2.0f * PI + 0.2f * PI), r * std::sin(0.2f * 2.0f * PI + 0.2f * PI));
    skeleton.emplace_back(R * std::cos(0.4f * 2.0f * PI), R * std::sin(0.4f * 2.0f * PI));
    skeleton.emplace_back(r * std::cos(0.4f * 2.0f * PI + 0.2f * PI), r * std::sin(0.4f * 2.0f * PI + 0.2f * PI));
    skeleton.emplace_back(R * std::cos(0.6f * 2.0f * PI), R * std::sin(0.6f * 2.0f * PI));
    skeleton.emplace_back(r * std::cos(0.6f * 2.0f * PI + 0.2f * PI), r * std::sin(0.6f * 2.0f * PI + 0.2f * PI));
    skeleton.emplace_back(R * std::cos(0.8f * 2.0f * PI), R * std::sin(0.8f * 2.0f * PI));
    skeleton.emplace_back(r * std::cos(0.8f * 2.0f * PI + 0.2f * PI), r * std::sin(0.8f * 2.0f * PI + 0.2f * PI));

    return skeleton;
}


std::vector<ci::Vec2f> FruitGraphicController::createStarBorderPoints(
        const std::vector<ci::Vec2f>& skeleton,
        const ci::Vec2f& position) const
{
    std::vector<ci::Vec2f> points;

    std::transform(
                std::begin(skeleton),
                std::end(skeleton),
                std::back_inserter(points),
                [&position](const ci::Vec2f& v){ return v + position; });

    return points;
}


void FruitGraphicController::drawStarBody(const std::vector<ci::Vec2f>& points, const ci::Vec2f& center)
{
    for(auto i = 0u; i < points.size() - 1; ++i)
    {
        const ci::Vec2f& p1 = points[i];
        const ci::Vec2f& p2 = points[i+1];

        ci::gl::drawSolidTriangle(p1, p2, center);
    }
    const ci::Vec2f& p1 = points.back();
    const ci::Vec2f& p2 = points.front();

    ci::gl::drawSolidTriangle(p1, p2, center);
}


void FruitGraphicController::drawStarBorder(const std::vector<ci::Vec2f>& points)
{
    ci::PolyLine2f pl(points);
    pl.setClosed();

    ci::gl::draw(pl);
}


} // namespace Presentation
} // namespace Pacman
