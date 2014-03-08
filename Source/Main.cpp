#include <memory>
#include <utility>
#include <vector>

#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#define BOOST_MPL_LIMIT_VECTOR_SIZE 30

#define BOOST_MSM_CONSTRUCTOR_ARG_SIZE 11

#include <boost/msm/back/state_machine.hpp> // to avoid compilation conflicts with cinder

#include <cinder/app/AppBasic.h>

#include <Model/Board.hpp>
#include <Model/ClockTickNotifier.hpp>
#include <Model/CoinsCollector.hpp>
#include <Model/CollisionDetector.hpp>
#include <Model/Direction.hpp>
#include <Model/FieldsCreator.hpp>
#include <Model/FruitsCollector.hpp>
#include <Model/fruitsVisibilityDurationController.hpp>
#include <Model/GameController.hpp>
#include <Model/GameModeManager.hpp>
#include <Model/Ghost.hpp>
#include <Model/Pac.hpp>
#include <Model/PacsLifesController.hpp>
#include <Model/RandomDirectionSelector.hpp>
#include <Model/RandomNumberGenerator.hpp>
#include <Model/ScoreController.hpp>

#include <Presentation/BoardGraphicController.hpp>
#include <Presentation/DirectionCalculator.hpp>
#include <Presentation/FruitGraphicController.hpp>
#include <Presentation/GhostGraphicController.hpp>
#include <Presentation/PacGraphicController.hpp>
#include <Presentation/PacsLifesGraphicController.hpp>
#include <Presentation/ScoreGraphicController.hpp>
#include <Presentation/WindowGraphicController.hpp>

#include <Configuration.hpp>
#include <PacmanApp.hpp>


namespace Pacman
{
namespace Detail
{


Configuration configuration;

auto boardGraphicController = std::make_shared<Presentation::BoardGraphicController>(
        configuration.FIELD_SIZE,
        configuration.HORIZONTAL_MARGIN);

Model::FieldsData fieldsData(std::move(Model::FieldsCreator::create()));

auto board = std::make_shared<Model::Board>(std::move(fieldsData.getFields()), boardGraphicController);

auto windowGraphicController = std::make_shared<Presentation::WindowGraphicController>();

auto directionCalculator = std::make_shared<Presentation::DirectionCalculator>();

auto pacGraphicController = std::make_shared<Presentation::PacGraphicController>(
        configuration.FIELD_SIZE,
        configuration.HORIZONTAL_MARGIN,
        configuration.PAC_SIZE_SCALE,
        directionCalculator);

auto ghostGraphicController = std::make_shared<Presentation::GhostGraphicController>(
        configuration.FIELD_SIZE,
        configuration.HORIZONTAL_MARGIN,
        configuration.GHOST_SIZE_SCALE,
        directionCalculator);

auto pacsLifesGraphicController = std::make_shared<Presentation::PacsLifesGraphicController>(
        configuration.PACS_LIFE_SIZE,
        board->getNumOfRows() * configuration.FIELD_SIZE,
        configuration.HORIZONTAL_MARGIN);

auto scoreGraphicController = std::make_shared<Presentation::ScoreGraphicController>();

auto gameModeManager = std::make_shared<Model::GameModeManager>(
        configuration.BIG_COIN_MODE_DURATION,
        configuration.BIG_COIN_LAST_SECONDS_MODE_DURATION);

auto randomUnsignedLongGenerator = std::make_shared<Model::RandomUnsignedLongGenerator>();

auto fruitGraphicController = std::make_shared<Presentation::FruitGraphicController>(
        configuration.FRUIT_SIZE,
        board->getNumOfRows() * configuration.FIELD_SIZE,
        configuration.HORIZONTAL_MARGIN + board->getNumOfColumns() * configuration.FIELD_SIZE,
        configuration.HORIZONTAL_MARGIN);

auto fruitsVisibilityDurationController = std::make_shared<Model::FruitsVisibilityDurationController>(
        configuration.MIN_SHOWN_FRUIT_DURATION,
        configuration.MAX_SHOWN_FRUIT_DURATION,
        configuration.MIN_HIDDEN_FRUIT_DURATION,
        configuration.MAX_HIDDEN_FRUIT_DURATION,
        randomUnsignedLongGenerator,
        fieldsData.getFruitField(),
        fruitGraphicController);

auto clockTickNotifier = std::make_shared<Model::ClockTickNotifier>(
        std::vector<std::shared_ptr<Model::IClockTickListener>>{gameModeManager, fruitsVisibilityDurationController});

auto coinsCollector = std::make_shared<Model::CoinsCollector>(fieldsData.getNumOfCoinsToCollect());

auto fruitsCollector = std::make_shared<Model::FruitsCollector>();

auto scoreController = std::make_shared<Model::ScoreController>(
        configuration.COIN_SCORE,
        configuration.BIG_COIN_SCORE,
        configuration.GHOST_SCORE,
        scoreGraphicController);

auto pac = std::make_shared<Model::Pac>(
        fieldsData.getPacsStartingRow(),
        fieldsData.getPacsStartingColumn(),
        configuration.MOVE_RESOLUTION,
        Model::Direction::Right,
        board,
        gameModeManager,
        coinsCollector,
        fruitsCollector,
        scoreController,
        pacGraphicController);

auto randomDirectionSelector = std::make_shared<Model::RandomDirectionSelector>(randomUnsignedLongGenerator);

std::vector<std::shared_ptr<Model::IGhost>> ghosts{
        std::make_shared<Model::Ghost>(
                fieldsData.getGhostsStartingRow(),
                fieldsData.getGhostsStartingColumn(),
                configuration.MOVE_RESOLUTION,
                Model::Color::Red,
                board,
                pac,
                gameModeManager,
                randomDirectionSelector,
                ghostGraphicController),
        std::make_shared<Model::Ghost>(
                fieldsData.getGhostsStartingRow(),
                fieldsData.getGhostsStartingColumn(),
                configuration.MOVE_RESOLUTION,
                Model::Color::Green,
                board,
                pac,
                gameModeManager,
                randomDirectionSelector,
                ghostGraphicController),
        std::make_shared<Model::Ghost>(
                fieldsData.getGhostsStartingRow(),
                fieldsData.getGhostsStartingColumn(),
                configuration.MOVE_RESOLUTION,
                Model::Color::Pink,
                board,
                pac,
                gameModeManager,
                randomDirectionSelector,
                ghostGraphicController),
        std::make_shared<Model::Ghost>(
                fieldsData.getGhostsStartingRow(),
                fieldsData.getGhostsStartingColumn(),
                configuration.MOVE_RESOLUTION,
                Model::Color::Orange,
                board,
                pac,
                gameModeManager,
                randomDirectionSelector,
                ghostGraphicController)};

auto collisionDetector = std::make_shared<Model::CollisionDetector>(configuration.DISTANCE_TO_COLLISION);

auto pacsLifesController = std::make_shared<Model::PacsLifesController>(
        configuration.NUMBER_OF_PACS_LIFES,
        pacsLifesGraphicController);

auto gameController = std::make_shared<Model::GameController>(
        board,
        pac,
        ghosts,
        clockTickNotifier,
        gameModeManager,
        coinsCollector,
        fruitsCollector,
        collisionDetector,
        pacsLifesController,
        scoreController,
        windowGraphicController);


} // namespace Detail
} // namespace Pacman


CINDER_APP_BASIC( \
        Pacman::PacmanApp( \
                Pacman::Detail::configuration.FIELD_SIZE, \
                Pacman::Detail::configuration.HORIZONTAL_MARGIN, \
                Pacman::Detail::board, \
                Pacman::Detail::gameController, \
                Pacman::Detail::windowGraphicController), \
        ci::app::RendererGl)
