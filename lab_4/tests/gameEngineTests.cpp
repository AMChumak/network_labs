//
// Created by anton on 12/7/24.
//

#include <memory>
#include <gtest/gtest.h>

#include "../src/engine/Field.h"
#include "../src/engine/FoodDistributor.h"
#include "../src/engine/Snake.h"


using namespace gameEngine;

namespace
{

    class gameEngineTest: public testing::Test
    {
    public:
        int hX,hY;
        Direction hDirection;
        int uId;
        std::shared_ptr<Snake> snake;
        std::shared_ptr<std::vector<Snake>> snakes;
        std::shared_ptr<FoodDistributor> foodDistributor;
    protected:
        void SetUp() override
        {
            uId = 1;
            hX = 4;
            hY = 5;
            hDirection = RIGHT;
            auto fieldp = std::make_shared<Field>(10,12);
            auto snakep = std::make_shared<Snake>(uId, Coord(hX,hY),hDirection, fieldp);
            snake = snakep;
            auto snakesp = std::make_shared<std::vector<Snake>>();
            snakesp->emplace_back(uId+1, Coord(hX,hY+1),hDirection, fieldp);
            snakes = snakesp;
            auto distrp = std::make_shared<FoodDistributor>(fieldp, snakes, 3);
            foodDistributor = distrp;
        };
        void TearDown() override {};
    };
}


TEST(field_tests, field_getters_test)
{
    Field field{10,12};
    ASSERT_EQ(10,field.getWidth());
    ASSERT_EQ(12, field.getHeight());
}

TEST(field_tests, field_canonize_test)
{
    Field field{10,12};
    Coord x{1,1};
    Coord t = field.canonizeCoord( Coord{11, -11} );
    ASSERT_EQ(x,t);
}

TEST(snake_tests, snake_getters_test)
{
    auto fieldp = std::make_shared<Field>(10,12);
    Snake snake{1, Coord(0,0),UP, fieldp};

    ASSERT_EQ(snake.getOwnerId(), 1);
    ASSERT_EQ(snake.getHeadCoord(), Coord(0,0));
    ASSERT_EQ(snake.getHeadDirection(), UP);
    ASSERT_TRUE(snake.getBody()->size() == 2);
    ASSERT_EQ(snake.getBody()->at(0), Coord(0,0));
    ASSERT_EQ(snake.getBody()->at(1), Coord(0,1));
}

TEST_F(gameEngineTest, snake_intersect_test)
{
    for (int i = 0, endI = snake->getField()->getHeight(); i < endI; ++i )
    {
        for (int j = 0, endJ = snake->getField()->getWidth(); j < endJ; ++j )
        {
            if (Coord(j, i) == Coord(hX,hY) || Coord(j, i) == Coord(hX - 1,hY))
            {
                ASSERT_TRUE(snake->intersect(Coord(j,i)));
            } else
            {
                ASSERT_FALSE(snake->intersect(Coord(j,i)));
            }
        }
    }
}

TEST_F(gameEngineTest, snake_step_forward_test)
{
    snake->step();
    for (int i = 0, endI = snake->getField()->getHeight(); i < endI; ++i )
    {
        for (int j = 0, endJ = snake->getField()->getWidth(); j < endJ; ++j )
        {
            if (Coord(j, i) == Coord(hX,hY) || Coord(j, i) == Coord(hX + 1,hY))
            {
                ASSERT_TRUE(snake->intersect(Coord(j,i)));
            } else
            {
                ASSERT_FALSE(snake->intersect(Coord(j,i)));
            }
        }
    }
}

TEST_F(gameEngineTest, snake_turn_down_and_step_test)
{
    snake->turn(gameEngine::Direction::DOWN);
    snake->step();
    for (int i = 0, endI = snake->getField()->getHeight(); i < endI; ++i )
    {
        for (int j = 0, endJ = snake->getField()->getWidth(); j < endJ; ++j )
        {
            if (Coord(j, i) == Coord(hX,hY + 1) || Coord(j, i) == Coord(hX,hY))
            {
                ASSERT_TRUE(snake->intersect(Coord(j,i)));
            } else
            {
                ASSERT_FALSE(snake->intersect(Coord(j,i)));
            }
        }
    }
}

TEST_F(gameEngineTest, snake_grow_back_test)
{
    snake->grow();
    for (int i = 0, endI = snake->getField()->getHeight(); i < endI; ++i )
    {
        for (int j = 0, endJ = snake->getField()->getWidth(); j < endJ; ++j )
        {
            if (Coord(j, i) == Coord(hX,hY) || Coord(j, i) == Coord(hX - 1,hY) || Coord(j, i) == Coord(hX - 2,hY) )
            {
                ASSERT_TRUE(snake->intersect(Coord(j,i)));
            } else
            {
                ASSERT_FALSE(snake->intersect(Coord(j,i)));
            }
        }
    }
}

TEST_F(gameEngineTest, snake_turn_grow_test)
{
    snake->turn(gameEngine::Direction::DOWN);
    snake->step();
    snake->turn(gameEngine::Direction::RIGHT);
    snake->step();
    snake->grow();
    for (int i = 0, endI = snake->getField()->getHeight(); i < endI; ++i )
    {
        for (int j = 0, endJ = snake->getField()->getWidth(); j < endJ; ++j )
        {
            if (Coord(j, i) == Coord(hX + 1,hY + 1) || Coord(j, i) == Coord(hX,hY + 1) || Coord(j, i) == Coord(hX,hY) )
            {
                ASSERT_TRUE(snake->intersect(Coord(j,i)));
            } else
            {
                ASSERT_FALSE(snake->intersect(Coord(j,i)));
            }
        }
    }
}

TEST_F(gameEngineTest, food_fill_test)
{
    foodDistributor->fillFood();
    int cnt = 0;
    for(auto food : foodDistributor->getFoods())
    {
        cnt++;
        ASSERT_FALSE(snake->intersect(food));
    }
    ASSERT_EQ(cnt, snakes->size() + 3);
}


