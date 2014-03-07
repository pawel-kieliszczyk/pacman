#include <algorithm>
#include <cassert>
#include <cmath>
#include <iterator>
#include <utility>
#include <vector>

#include <boost/optional.hpp>

#include <cinder/gl/gl.h>
#include <cinder/PolyLine.h>
#include <cinder/Vector.h>

#include <Presentation/PacGraphicController.hpp>


namespace Pacman
{
namespace Presentation
{


PacGraphicController::PacGraphicController(
        unsigned fieldSize_,
        unsigned horizontalOffset_,
        float pacSizeScale,
        std::shared_ptr<IDirectionCalculator> directionCalculator_)
    : fieldSize(fieldSize_),
      horizontalOffset(horizontalOffset_),
      directionCalculator(directionCalculator_),
      pacSize(pacSizeScale * static_cast<float>(fieldSize)),
      PI(3.14159265f),
      direction(Model::Direction::Right)
{
}


void PacGraphicController::draw(
        int fromRow,
        int fromColumn,
        int toRow,
        int toColumn,
        unsigned step,
        unsigned resolution)
{
    calculateDirection(fromRow, fromColumn, toRow, toColumn);

    std::vector<ci::Vec2f> skeleton = std::move(createPacsSkeleton(step, resolution));

    ci::Vec2f position = std::move(calculatePacsPosition(fromRow, fromColumn, toRow, toColumn, step, resolution));

    std::vector<ci::Vec2f> points = std::move(createPacsBorderPoints(skeleton, position));

    drawPacsBody(points);
    drawPacsBorder(points);
}


void PacGraphicController::calculateDirection(
            int fromRow,
            int fromColumn,
            int toRow,
            int toColumn)
{
    boost::optional<Model::Direction> dir = directionCalculator->calculate(fromRow, fromColumn, toRow, toColumn);
    if(dir)
        direction = *dir;
}


void PacGraphicController::alignAlphaToDirection(float& alpha) const
{
    if(direction == Model::Direction::Down)
        alpha += PI / 2.0f;
    else if(direction == Model::Direction::Left)
        alpha += PI;
    else if(direction == Model::Direction::Up)
        alpha += PI * 3.0f / 2.0f;
}


void PacGraphicController::alignPacsCenterToDirection(ci::Vec2f& center) const
{
    const float offset = pacSize / 4;

    switch(direction)
    {
        case Model::Direction::Up :
            center += ci::Vec2f(0.0f, offset);
            break;
        case Model::Direction::Down :
            center += ci::Vec2f(0.0f, -offset);
            break;
        case Model::Direction::Left :
            center += ci::Vec2f(offset, 0.0f);
            break;
        case Model::Direction::Right :
            center += ci::Vec2f(-offset, 0.0f);
            break;
    }
}


std::vector<ci::Vec2f> PacGraphicController::createPacsSkeleton(unsigned step, unsigned resolution) const
{
    std::vector<ci::Vec2f> skeleton;

    const auto halfOfResolution = resolution / 2;
    const auto normalizedStep = (step < halfOfResolution) ? step : (resolution - step);
    const auto openMouth = static_cast<float>(normalizedStep) / static_cast<float>(halfOfResolution);

    assert(openMouth >= 0.0f && openMouth <= 1.0f);

    auto openMouthAlpha = openMouth * PI / 4.0f;

    float startAlpha = openMouthAlpha;
    alignAlphaToDirection(startAlpha);

    float endAlpha = startAlpha + 2.0f * PI - 2.0f * openMouthAlpha;
    if(endAlpha < startAlpha)
        endAlpha += 2.0f * PI;

    const float STEP = 0.2;

    for(float alpha = startAlpha; alpha <= endAlpha; alpha += STEP)
    {
        const float r = pacSize / 2.0f;

        const float x = r * std::cos(alpha);
        const float y = r * std::sin(alpha);
        skeleton.emplace_back(x, y);
    }

    ci::Vec2f center(0.0f, 0.0f);
    alignPacsCenterToDirection(center);

    skeleton.push_back(std::move(center));

    return skeleton;
}


ci::Vec2f PacGraphicController::calculatePacsPosition(
            int fromRow,
            int fromColumn,
            int toRow,
            int toColumn,
            unsigned step,
            unsigned resolution) const
{
    float x = (fromColumn * static_cast<int>(fieldSize)) + (static_cast<float>(fieldSize) / 2);
    float y = (fromRow * static_cast<int>(fieldSize)) + (static_cast<float>(fieldSize) / 2);

    if(toColumn > fromColumn)
        x += static_cast<float>(fieldSize * step) / static_cast<float>(resolution);
    if(toColumn < fromColumn)
        x -= static_cast<float>(fieldSize * step) / static_cast<float>(resolution);

    if(toRow > fromRow)
        y += static_cast<float>(fieldSize * step) / static_cast<float>(resolution);
    if(toRow < fromRow)
        y -= static_cast<float>(fieldSize * step) / static_cast<float>(resolution);

    ci::Vec2f position(horizontalOffset + x, y);

    return position;
}


std::vector<ci::Vec2f> PacGraphicController::createPacsBorderPoints(
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


void PacGraphicController::drawPacsBody(const std::vector<ci::Vec2f>& points)
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


void PacGraphicController::drawPacsBorder(const std::vector<ci::Vec2f>& points)
{
    ci::PolyLine2f pl(points);
    pl.setClosed();

    ci::gl::color(1.0f, 1.0f, 1.0f);
    ci::gl::draw(pl);
}


} // namespace Presentation
} // namespace Pacman
