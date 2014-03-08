#include <algorithm>
#include <cmath>
#include <iterator>
#include <utility>
#include <vector>

#include <cinder/gl/gl.h>
#include <cinder/Vector.h>

#include <Presentation/PacsLifesGraphicController.hpp>

namespace Pacman
{
namespace Presentation
{


namespace Detail
{


std::vector<ci::Vec2f> PacsLifeSkeletonFactory::create(const float lifeSize)
{
    const float PI = 3.14159265f;

    std::vector<ci::Vec2f> skeleton;

    const auto openMouth = 0.5f;

    auto openMouthAlpha = openMouth * PI / 4.0f;

    float startAlpha = openMouthAlpha;

    float endAlpha = startAlpha + 2.0f * PI - 2.0f * openMouthAlpha;
    if(endAlpha < startAlpha)
        endAlpha += 2.0f * PI;

    const float STEP = 0.2;

    for(float alpha = startAlpha; alpha <= endAlpha; alpha += STEP)
    {
        const float r = lifeSize / 2.0f;

        const float x = r * std::cos(alpha);
        const float y = r * std::sin(alpha);
        skeleton.emplace_back(x, y);
    }

    ci::Vec2f center(0.0f, 0.0f);
    const float centerOffset = lifeSize / 4;
    center -= ci::Vec2f(centerOffset, 0.0f);

    skeleton.push_back(std::move(center));

    return skeleton;
}


} // namespace Detail


PacsLifesGraphicController::PacsLifesGraphicController(unsigned lifeSize_, unsigned boardHeight_, unsigned horizontalMargin_)
    : lifeSize(lifeSize_),
      boardHeight(boardHeight_),
      horizontalMargin(horizontalMargin_),
      skeleton(Detail::PacsLifeSkeletonFactory::create(lifeSize_))
{
}


void PacsLifesGraphicController::draw(unsigned lifes)
{
    float x = static_cast<float>(horizontalMargin) / 2.0f;
    float y = static_cast<float>(boardHeight) - 1.5f * lifeSize;

    ci::gl::color(1.0f, 1.0f, 0.0f);

    while(lifes-- > 0)
    {
        ci::Vec2f center(x, y);
        const std::vector<ci::Vec2f> points = std::move(createLifesBorderPoints(center));

        drawLifesBody(points);
        drawLifesBorder(points);

        y -= 1.5f * lifeSize;
    }
}


std::vector<ci::Vec2f> PacsLifesGraphicController::createLifesBorderPoints(const ci::Vec2f& position) const
{
    std::vector<ci::Vec2f> points;

    std::transform(
            std::begin(skeleton),
            std::end(skeleton),
            std::back_inserter(points),
            [&position](const ci::Vec2f& v){ return v + position; });

    return points;
}


void PacsLifesGraphicController::drawLifesBody(const std::vector<ci::Vec2f>& points)
{
    ci::gl::color(1.0f, 1.0f, 0.0f);

    const ci::Vec2f& center = points.back();

    for(auto i = 0u; i < points.size() - 1; ++i)
    {
        const ci::Vec2f& p1 = points[i];
        const ci::Vec2f& p2 = points[i+1];

        ci::gl::drawSolidTriangle(p1, p2, center);
    }
}


void PacsLifesGraphicController::drawLifesBorder(const std::vector<ci::Vec2f>& points)
{
    ci::PolyLine2f pl(points);
    pl.setClosed();

    ci::gl::color(1.0f, 1.0f, 1.0f);
    ci::gl::draw(pl);
}


} // namespace Presentation
} // namespace Pacman
