#ifndef PACMAN_MODEL_DETAIL_GAMECONTROLLERFSMGUARDS_HPP
#define PACMAN_MODEL_DETAIL_GAMECONTROLLERFSMGUARDS_HPP


#include <algorithm>
#include <iterator>
#include <vector>

#include <Model/GameControllerEvents.hpp>


namespace Pacman
{
namespace Model
{
namespace Detail
{


template<Key K>
struct IsKey
{
    template<class Event, class Fsm, class SourceState, class TargetState>
    bool operator()(const Event& e, Fsm&, SourceState&, TargetState&)
    {
        return (e.getKey() == K);
    }
};


template<Key... Ks>
struct IsAnyOfKeys
{
    template<class Event, class Fsm, class SourceState, class TargetState>
    bool operator()(const Event& e, Fsm&, SourceState&, TargetState&)
    {
        std::vector<Key> ks{Ks...};
        return (std::find(std::begin(ks), std::end(ks), e.getKey()) != ks.end());
    }
};


struct AreAllCoinsCollected
{
    template<class Event, class Fsm, class SourceState, class TargetState>
    bool operator()(const Event&, Fsm& fsm, SourceState&, TargetState&)
    {
        return fsm.areAllCoinsCollected();
    }
};


struct IsBigCoinModeActive
{
    template<class Event, class Fsm, class SourceState, class TargetState>
    bool operator()(const Event&, Fsm& fsm, SourceState&, TargetState&)
    {
        return fsm.isBigCoinModeActive();
    }
};


struct AreAnyCollisions
{
    template<class Event, class Fsm, class SourceState, class TargetState>
    bool operator()(const Event&, Fsm& fsm, SourceState&, TargetState&)
    {
        return fsm.areAnyCollisions();
    }
};


struct IsPacDead
{
    template<class Event, class Fsm, class SourceState, class TargetState>
    bool operator()(const Event&, Fsm& fsm, SourceState&, TargetState&)
    {
        return fsm.isPacDead();
    }
};


} // namespace Detail
} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_DETAIL_GAMECONTROLLERFSMGUARDS_HPP
