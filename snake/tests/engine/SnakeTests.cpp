#include "../../src/engine/Snake.h"
#include <memory>
#include <gtest/gtest.h>

using namespace engine;

class SnakeTests : public ::testing::Test
{
protected:
    int first_user_id = 1;
    int second_user_id = 2;
    Coord start_position{3, 3};
    Direction start_direction = Direction::RIGHT;
    std::shared_ptr<Field> field;
    std::shared_ptr<Snake> snake;

protected:
    SnakeTests()
    {
        field = std::make_shared<Field>(10, 6);
        snake = std::make_shared<Snake>(first_user_id, start_position, start_direction, field);
    }
};

TEST_F(SnakeTests, snake_intersect_test)
{
    for (int i = 0, end_i = snake->get_field()->get_height(); i < end_i; ++i)
    {
        for (int j = 0, end_j = snake->get_field()->get_width(); j < end_j; ++j)
        {
            if (Coord(j, i) == start_position || Coord(j, i) == start_position + Coord(-1, 0))
            {
                ASSERT_TRUE(snake->intersect(Coord(j,i)));
            }
            else
            {
                ASSERT_FALSE(snake->intersect(Coord(j,i)));
            }
        }
    }
}


TEST_F(SnakeTests, snake_step_forward_test)
{
    snake->step();
    for (int i = 0, end_i = snake->get_field()->get_height(); i < end_i; ++i)
    {
        for (int j = 0, end_j = snake->get_field()->get_width(); j < end_j; ++j)
        {
            if (Coord(j, i) == start_position || Coord(j, i) == start_position + Coord(1, 0))
            {
                ASSERT_TRUE(snake->intersect(Coord(j,i)));
            }
            else
            {
                ASSERT_FALSE(snake->intersect(Coord(j,i)));
            }
        }
    }
}


TEST_F(SnakeTests, snake_incorrect_turn_test)
{
    snake->turn(LEFT);
    snake->step();
    for (int i = 0, end_i = snake->get_field()->get_height(); i < end_i; ++i)
    {
        for (int j = 0, end_j = snake->get_field()->get_width(); j < end_j; ++j)
        {
            if (Coord(j, i) == start_position || Coord(j, i) == start_position + Coord(1, 0))
            {
                ASSERT_TRUE(snake->intersect(Coord(j,i)));
            }
            else
            {
                ASSERT_FALSE(snake->intersect(Coord(j,i)));
            }
        }
    }
}


TEST_F(SnakeTests, snake_turn_down_and_step_test)
{
    snake->turn(DOWN);
    snake->step();
    for (int i = 0, end_i = snake->get_field()->get_height(); i < end_i; ++i)
    {
        for (int j = 0, end_j = snake->get_field()->get_width(); j < end_j; ++j)
        {
            if (Coord(j, i) == start_position || Coord(j, i) == start_position + Coord(0, 1))
            {
                ASSERT_TRUE(snake->intersect(Coord(j,i)));
            }
            else
            {
                ASSERT_FALSE(snake->intersect(Coord(j,i)));
            }
        }
    }
}


TEST_F(SnakeTests, snake_grow_back_test)
{
    snake->grow();
    for (int i = 0, end_i = snake->get_field()->get_height(); i < end_i; ++i)
    {
        for (int j = 0, end_j = snake->get_field()->get_width(); j < end_j; ++j)
        {
            if (Coord(j, i) == start_position || Coord(j, i) == start_position + Coord(-1, 0) ||
                Coord(j, i) == start_position + Coord(-2, 0))
            {
                ASSERT_TRUE(snake->intersect(Coord(j,i)));
            }
            else
            {
                ASSERT_FALSE(snake->intersect(Coord(j,i)));
            }
        }
    }
}


TEST_F(SnakeTests, snake_turn_grow_test)
{
    snake->turn(DOWN);
    snake->step();
    snake->turn(RIGHT);
    snake->step();
    snake->grow();
    for (int i = 0, end_i = snake->get_field()->get_height(); i < end_i; ++i)
    {
        for (int j = 0, end_j = snake->get_field()->get_width(); j < end_j; ++j)
        {
            if (Coord(j, i) == start_position + Coord(1, 1) ||
                Coord(j, i) == start_position + Coord(0, 1) || Coord(j, i) == start_position)
            {
                ASSERT_TRUE(snake->intersect(Coord(j,i)));
            }
            else
            {
                ASSERT_FALSE(snake->intersect(Coord(j,i)));
            }
        }
    }
}


TEST_F(SnakeTests, snake_get_body_test)
{
    snake->grow();
    snake->grow();
    snake->turn(DOWN);
    snake->step();
    snake->turn(RIGHT);
    snake->step();
    snake->grow();

    std::vector<Coord>body = snake->get_body();

    for (int i = 0, end_i = snake->get_field()->get_height(); i < end_i; ++i)
    {
        for (int j = 0, end_j = snake->get_field()->get_width(); j < end_j; ++j)
        {
            bool found = false;
            for (auto cell : body)
            {
                if (cell == Coord(j, i))
                {
                    found = true;
                    ASSERT_TRUE(snake->intersect(cell));
                    break;
                }
            }
            if (!found)
                ASSERT_FALSE(snake->intersect(Coord(j, i)));
        }
    }
}