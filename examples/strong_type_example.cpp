#include "strong_type.hpp"

#include <type_traits>
#include <iostream>

struct player_id_tag {};
struct ship_id_tag {};

int main()
{
    using player_id_type = unpure::strong_type<player_id_tag, int>;
    using ship_id_type = unpure::strong_type<ship_id_tag, int>;

    auto player_id = player_id_type{1};
    auto ship_id = ship_id_type{1};

    // calling void foo(player_id_type id); function with ship_id will not compile

    std::cout << player_id << std::endl;

    static_assert(not std::is_convertible<decltype(player_id), decltype(ship_id)>::value, "two strong_type<>'s should not be convertible");

    auto another_player_id = unpure::strong_int<player_id_tag>{2};

    static_assert(std::is_same<decltype(another_player_id), decltype(player_id)>::value, "string_int should be string_type<int>");
}
