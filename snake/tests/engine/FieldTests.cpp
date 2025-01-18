#include <memory>
#include <gtest/gtest.h>

#include "../../src/engine/Field.h"

using namespace engine;

TEST(field_tests, field_getters_test)
{
    Field field{10,12};
    ASSERT_EQ(10,field.get_width());
    ASSERT_EQ(12, field.get_height());
}

TEST(field_tests, field_canonize_test)
{
    Field field{10,12};
    Coord coord{1,1};
    Coord canonized = field.canonize_coord( Coord{11, -11} );
    ASSERT_EQ(coord,canonized);
}

TEST(geometry_tests, bypass_right_offset_test)
{
    auto field = std::make_shared<Field>(10, 10);
    Coord coord{5,6};
    Coord check_next{6,6};
    get_next_pos(coord, field);
    ASSERT_EQ(check_next, coord);
}

TEST(geometry_tests, bypass_line_feed_test)
{
    auto field = std::make_shared<Field>(10, 10);
    Coord coord{9,6};
    Coord check_next{0,7};
    get_next_pos(coord, field);
    ASSERT_EQ(check_next, coord);
}

TEST(geometry_tests, bypass_round_test)
{
    auto field = std::make_shared<Field>(10, 10);
    Coord coord{9,9};
    Coord check_next{0,0};
    get_next_pos(coord, field);
    ASSERT_EQ(check_next, coord);
}