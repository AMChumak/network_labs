//
// Created by anton on 12/12/24.
//

#ifndef FIELDSTATE_H
#define FIELDSTATE_H
#include <memory>
#include <vector>

#include "../engine/Snake.h"
#include "../engine/FoodDistributor.h"
#include "snakes.pb.h"

using namespace gameEngine;

namespace modelSpace
{
    struct Point
    {
        int x;
        int y;
    };

    std::vector<Point> convertCoords(const std::vector<Coord> &coords);
    std::vector<Point> convertCoords(const google::protobuf::RepeatedPtrField<GameState_Coord>& coords);

    enum DirectionState
    {
        UP_STATE = 0,
        DOWN_STATE,
        LEFT_STATE,
        RIGHT_STATE
    };

    DirectionState convertDirection(const gameEngine::Direction &dir);
    DirectionState convertDirection(const ::Direction& dir);

    class Drawer;
    class FieldState;

    class ObjectState
    {
    public:
        virtual ~ObjectState() = default;
        virtual void visit(std::shared_ptr<Drawer> drawer, const FieldState &field) =0;
    };

    class FoodState : public ObjectState
    {
    public:
        FoodState(Point initCell);
        void visit(std::shared_ptr<Drawer> drawer, const FieldState &field) override;

    public:
        Point cell;
    };

    class SnakeState : public ObjectState
    {
    public:
        SnakeState(std::vector<Point> initKeyPoints, DirectionState initState);
        void visit(std::shared_ptr<Drawer> drawer, const FieldState &field) override;

        std::vector<Point> getKeyPoints();
        DirectionState getHeadDirection();
    private:
        std::vector<Point> keyPoints;
        DirectionState headState;
    };

    class Drawer
    {
    public:
        virtual ~Drawer() = default;
        virtual void draw(const FoodState &food, const FieldState &field)=0;
        virtual void draw(const SnakeState &snake, const FieldState &field)=0;
    };

    class FieldState
    {
    public:
        FieldState(int initHeight, int initWidth);
        Point canonizePoint(Point p) const;
        void generateState(const std::shared_ptr<std::vector<Snake>>& snakes, const std::shared_ptr<FoodDistributor>& foodDistr);
        void generateState(const GameState &state);

        void drawObjects(const std::shared_ptr<Drawer>& drawer);

    private:
        int height;
        int width;
        std::mutex stateMtx;
        bool isUpdated = false;
        std::vector<ObjectState> objects;
    };
} // modelSpace

#endif //FIELDSTATE_H
