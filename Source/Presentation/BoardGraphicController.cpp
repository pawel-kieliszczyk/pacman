#include <algorithm>
#include <iterator>
#include <vector>

#include <cinder/gl/gl.h>
#include <cinder/Rect.h>
#include <cinder/Vector.h>

#include <Presentation/BoardGraphicController.hpp>


namespace Pacman
{
namespace Presentation
{


BoardGraphicController::BoardGraphicController(unsigned fieldSize_, unsigned horizontalOffset_)
    : fieldSize(fieldSize_),
      horizontalOffset(horizontalOffset_)
{
}


void BoardGraphicController::drawCoin(unsigned row, unsigned column)
{
    ci::gl::color(1.0f, 1.0f, 1.0f);

    const float x = (column * fieldSize) + (fieldSize / 2.0f);
    const float y = (row * fieldSize) + (fieldSize / 2.0f);
    ci::Vec2f center(horizontalOffset + x, y);

    ci::gl::drawSolidCircle(center, fieldSize / 8.0f);
}


void BoardGraphicController::drawBigCoin(unsigned row, unsigned column)
{
    ci::gl::color(1.0f, 1.0f, 1.0f);

    const float x = (column * fieldSize) + (fieldSize / 2.0f);
    const float y = (row * fieldSize) + (fieldSize / 2.0f);
    ci::Vec2f center(horizontalOffset + x, y);

    ci::gl::drawSolidCircle(center, fieldSize / 3.0f);
}


void BoardGraphicController::drawApple(unsigned row, unsigned column)
{
    // TODO: draw an apple instead of a star. Even if it looks nice... ;)

    const float x = (column * fieldSize) + (fieldSize / 2.0f);
    const float y = (row * fieldSize) + (fieldSize / 2.0f);
    ci::Vec2f center(horizontalOffset + x, y);

    std::vector<ci::Vec2f> skeleton = std::move(createStarSkeleton(fieldSize));

    std::vector<ci::Vec2f> points = std::move(createStarBorderPoints(skeleton, center));

    ci::gl::color(0.0f, 0.5f, 0.0f);
    drawStarBody(points, center);
    ci::gl::color(0.0f, 1.0f, 0.0f);
    drawStarBorder(points);
}


void BoardGraphicController::drawCherry(unsigned row, unsigned column)
{
    // TODO: draw a cherry instead of a star. Even if it looks nice... ;)

    const float x = (column * fieldSize) + (fieldSize / 2.0f);
    const float y = (row * fieldSize) + (fieldSize / 2.0f);
    ci::Vec2f center(horizontalOffset + x, y);

    std::vector<ci::Vec2f> skeleton = std::move(createStarSkeleton(fieldSize));
    std::vector<ci::Vec2f> points = std::move(createStarBorderPoints(skeleton, center));

    ci::gl::color(0.5f, 0.0f, 0.0f);
    drawStarBody(points, center);
    ci::gl::color(1.0f, 0.0f, 0.0f);
    drawStarBorder(points);
}


void BoardGraphicController::drawOrange(unsigned row, unsigned column)
{
    // TODO: draw an orange instead of a star. Even if it looks nice... ;)

    const float x = (column * fieldSize) + (fieldSize / 2.0f);
    const float y = (row * fieldSize) + (fieldSize / 2.0f);
    ci::Vec2f center(horizontalOffset + x, y);

    std::vector<ci::Vec2f> skeleton = std::move(createStarSkeleton(fieldSize));
    std::vector<ci::Vec2f> points = std::move(createStarBorderPoints(skeleton, center));

    ci::gl::color(0.5f, 0.0f, 0.5f);
    drawStarBody(points, center);
    ci::gl::color(1.0f, 0.0f, 1.0f);
    drawStarBorder(points);
}


void BoardGraphicController::drawWall(unsigned row, unsigned column)
{
    ci::gl::color(0.0f, 0.0f, 1.0f);

    const float x1 = column * fieldSize + 0.2f * fieldSize;
    const float y1 = row * fieldSize + 0.2f * fieldSize;
    const float x2 = (column + 1) * fieldSize - 0.2f * fieldSize;
    const float y2 = (row + 1) * fieldSize - 0.2f * fieldSize;
    ci::Rectf rect(horizontalOffset + x1, y1, horizontalOffset + x2, y2);

    ci::gl::drawSolidRect(rect);
}


std::vector<ci::Vec2f> BoardGraphicController::createStarSkeleton(unsigned starSize) const
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


std::vector<ci::Vec2f> BoardGraphicController::createStarBorderPoints(
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


void BoardGraphicController::drawStarBody(const std::vector<ci::Vec2f>& points, const ci::Vec2f& center)
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


void BoardGraphicController::drawStarBorder(const std::vector<ci::Vec2f>& points)
{
    ci::PolyLine2f pl(points);
    pl.setClosed();

    ci::gl::draw(pl);
}


} // namespace Presentation
} // namespace Pacman
