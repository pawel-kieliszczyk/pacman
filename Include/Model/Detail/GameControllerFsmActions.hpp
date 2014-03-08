#ifndef PACMAN_MODEL_DETAIL_GAMECONTROLLERFSMACTIONS_HPP
#define PACMAN_MODEL_DETAIL_GAMECONTROLLERFSMACTIONS_HPP


namespace Pacman
{
namespace Model
{
namespace Detail
{


struct ClearWindow
{
    template<class Event, class Fsm, class SourceState, class TargetState>
    void operator()(const Event&, Fsm& fsm, SourceState&, TargetState&)
    {
        fsm.clearWindow();
    }
};


struct DrawBoard
{
    template<class Event, class Fsm, class SourceState, class TargetState>
    void operator()(const Event&, Fsm& fsm, SourceState&, TargetState&)
    {
        fsm.drawBoard();
    }
};


struct DrawPac
{
    template<class Event, class Fsm, class SourceState, class TargetState>
    void operator()(const Event&, Fsm& fsm, SourceState&, TargetState&)
    {
        fsm.drawPac();
    }
};


struct DrawGhosts
{
    template<class Event, class Fsm, class SourceState, class TargetState>
    void operator()(const Event&, Fsm& fsm, SourceState&, TargetState&)
    {
        fsm.drawGhosts();
    }
};


struct DrawPacsLifes
{
    template<class Event, class Fsm, class SourceState, class TargetState>
    void operator()(const Event&, Fsm& fsm, SourceState&, TargetState&)
    {
        fsm.drawPacsLifes();
    }
};


struct DrawScore
{
    template<class Event, class Fsm, class SourceState, class TargetState>
    void operator()(const Event&, Fsm& fsm, SourceState&, TargetState&)
    {
        fsm.drawScore();
    }
};


struct DrawFruits
{
    template<class Event, class Fsm, class SourceState, class TargetState>
    void operator()(const Event&, Fsm& fsm, SourceState&, TargetState&)
    {
        fsm.drawFruits();
    }
};


struct DrawStoppedGameCurtain
{
    template<class Event, class Fsm, class SourceState, class TargetState>
    void operator()(const Event&, Fsm& fsm, SourceState&, TargetState&)
    {
        fsm.drawStoppedGameCurtain();
    }
};


struct DrawPausedGameCurtain
{
    template<class Event, class Fsm, class SourceState, class TargetState>
    void operator()(const Event&, Fsm& fsm, SourceState&, TargetState&)
    {
        fsm.drawPausedGameCurtain();
    }
};


struct DrawWonGameCurtain
{
    template<class Event, class Fsm, class SourceState, class TargetState>
    void operator()(const Event&, Fsm& fsm, SourceState&, TargetState&)
    {
        fsm.drawWonGameCurtain();
    }
};


struct DrawLostGameCurtain
{
    template<class Event, class Fsm, class SourceState, class TargetState>
    void operator()(const Event&, Fsm& fsm, SourceState&, TargetState&)
    {
        fsm.drawLostGameCurtain();
    }
};


struct TickClock
{
    template<class Event, class Fsm, class SourceState, class TargetState>
    void operator()(const Event&, Fsm& fsm, SourceState&, TargetState&)
    {
        fsm.tickClock();
    }
};


struct SetPacsDirection
{
    template<class Event, class Fsm, class SourceState, class TargetState>
    void operator()(const Event& e, Fsm& fsm, SourceState&, TargetState&)
    {
        fsm.setPacsDirection(e);
    }
};


struct MovePac
{
    template<class Event, class Fsm, class SourceState, class TargetState>
    void operator()(const Event&, Fsm& fsm, SourceState&, TargetState&)
    {
        fsm.movePac();
    }
};


struct MoveGhosts
{
    template<class Event, class Fsm, class SourceState, class TargetState>
    void operator()(const Event&, Fsm& fsm, SourceState&, TargetState&)
    {
        fsm.moveGhosts();
    }
};


struct ConsumePacsLife
{
    template<class Event, class Fsm, class SourceState, class TargetState>
    void operator()(const Event&, Fsm& fsm, SourceState&, TargetState&)
    {
        fsm.consumePacsLife();
    }
};


struct ResetBoard
{
    template<class Event, class Fsm, class SourceState, class TargetState>
    void operator()(const Event&, Fsm& fsm, SourceState&, TargetState&)
    {
        fsm.resetBoard();
    }
};


struct ResetPac
{
    template<class Event, class Fsm, class SourceState, class TargetState>
    void operator()(const Event&, Fsm& fsm, SourceState&, TargetState&)
    {
        fsm.resetPac();
    }
};


struct ResetGhosts
{
    template<class Event, class Fsm, class SourceState, class TargetState>
    void operator()(const Event&, Fsm& fsm, SourceState&, TargetState&)
    {
        fsm.resetGhosts();
    }
};


struct ResetCollidingGhosts
{
    template<class Event, class Fsm, class SourceState, class TargetState>
    void operator()(const Event&, Fsm& fsm, SourceState&, TargetState&)
    {
        fsm.resetCollidingGhosts();
    }
};


struct ResetCoinsCollector
{
    template<class Event, class Fsm, class SourceState, class TargetState>
    void operator()(const Event&, Fsm& fsm, SourceState&, TargetState&)
    {
        fsm.resetCoinsCollector();
    }
};


struct ResetFruitsCollector
{
    template<class Event, class Fsm, class SourceState, class TargetState>
    void operator()(const Event&, Fsm& fsm, SourceState&, TargetState&)
    {
        fsm.resetFruitsCollector();
    }
};


struct ResetPacsLifesController
{
    template<class Event, class Fsm, class SourceState, class TargetState>
    void operator()(const Event&, Fsm& fsm, SourceState&, TargetState&)
    {
        fsm.resetPacsLifesController();
    }
};


struct ResetScoreController
{
    template<class Event, class Fsm, class SourceState, class TargetState>
    void operator()(const Event&, Fsm& fsm, SourceState&, TargetState&)
    {
        fsm.resetScoreController();
    }
};


struct ResetGameModeManager
{
    template<class Event, class Fsm, class SourceState, class TargetState>
    void operator()(const Event&, Fsm& fsm, SourceState&, TargetState&)
    {
        fsm.resetGameModeManager();
    }
};


} // namespace Detail
} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_DETAIL_GAMECONTROLLERFSMACTIONS_HPP
