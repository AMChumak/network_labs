//
// Created by anton on 12/12/24.
//

#include "FieldState.h"

#include <memory>
#include <utility>


namespace modelSpace
{
    FoodState::FoodState(Point initCell): cell{initCell}
    {
    }

    void FoodState::visit(std::shared_ptr<Drawer> drawer, const FieldState& field)
    {
        drawer->draw(*this, field);
    }

    SnakeState::SnakeState(std::vector<Point> initKeyPoints, DirectionState initState): keyPoints{
        std::move(initKeyPoints)
    }, headState{initState}
    {
    }

    void SnakeState::visit(std::shared_ptr<Drawer> drawer, const FieldState& field)
    {
        drawer->draw(*this, field);
    }

    std::vector<Point> SnakeState::getKeyPoints()
    {
        return keyPoints;
    }

    DirectionState SnakeState::getHeadDirection()
    {
        return headState;
    }

    FieldState::FieldState(int initHeight, int initWidth): height{initHeight}, width{initHeight}
    {
    }

    Point FieldState::canonizePoint(Point p) const
    {
        int cx = p.x >= 0 ? p.x % width : p.x % width + width;
        int cy = p.y >= 0 ? p.y % height : p.y % height + height;
        return {cx, cy};
    }

    std::vector<Point> convertCoords(const std::vector<Coord>& coords)
    {
        std::vector<Point> result;
        for (auto c : coords)
        {
            result.emplace_back(c.x, c.y);
        }
        return result;
    }

    std::vector<Point> convertCoords(const google::protobuf::RepeatedPtrField<GameState_Coord>& coords)
    {
        std::vector<Point> modelSnakePoints;
        for (const auto& point : coords)
        {
            modelSnakePoints.emplace_back(point.x(), point.y());
        }
        return modelSnakePoints;
    }

    DirectionState convertDirection(const gameEngine::Direction& dir)
    {
        switch (dir)
        {
        case gameEngine::UP:
            {
                return UP_STATE;
            }
        case gameEngine::DOWN:
            {
                return DOWN_STATE;
            }
        case gameEngine::LEFT:
            {
                return LEFT_STATE;
            }
        case gameEngine::RIGHT:
            {
                return RIGHT_STATE;
            }
        }
        return UP_STATE;
    }


    DirectionState convertDirection(const ::Direction& dir)
    {
        switch (dir)
        {
        case ::UP:
            {
                return UP_STATE;
            }
        case ::DOWN:
            {
                return DOWN_STATE;
            }
        case ::LEFT:
            {
                return LEFT_STATE;
            }
        case ::RIGHT:
            {
                return RIGHT_STATE;
            }
        }
        return UP_STATE;
    }

    void FieldState::generateState(const std::shared_ptr<std::vector<Snake>>& snakes,
                                   const std::shared_ptr<FoodDistributor>& foodDistr)
    {
        std::lock_guard<std::mutex> lock(stateMtx);
        objects.clear();
        for (auto snake : *snakes)
        {
            SnakeState snakeSt{convertCoords(*snake.getBody()), convertDirection(snake.getHeadDirection())};
            objects.push_back(snakeSt);
        }

        std::vector<Point> foodPointsState = convertCoords(foodDistr->getFoods());

        for (auto food : foodPointsState)
        {
            objects.push_back(FoodState{food});
        }
        isUpdated = true;
    }

    void FieldState::generateState(const GameState& state)
    {
        std::lock_guard<std::mutex> lock(stateMtx);
        objects.clear();

        for (const GameState_Snake &snake : state.snakes())
        {
            SnakeState snakeSt{convertCoords(snake.points()), convertDirection(snake.head_direction())};
        }
    }

    void FieldState::drawObjects(const std::shared_ptr<Drawer>& drawer)
    {
        std::lock_guard<std::mutex> lock(stateMtx);
        for (ObjectState& object : objects)
        {
            object.visit(drawer, *this);
        }
        isUpdated = false;
    }
} // modelSpace
