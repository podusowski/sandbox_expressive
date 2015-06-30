#pragma once

namespace expressive
{
namespace functional
{

template<class Struct, class Member>
struct member_callable
{
    member_callable(Member Struct::* member) : member(member)
    {
    }

    auto operator() (const Struct & s) -> Member
    {
        return s.*member;
    }

private:
    Member Struct::* member;
};

template<class Struct, class Member>
auto member(Member Struct::* member) -> member_callable<Struct, Member>
{
    return member_callable<Struct, Member>{member};
}

} // namespace functional
} // namespace expressive
