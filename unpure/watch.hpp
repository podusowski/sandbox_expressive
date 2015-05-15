#pragma once

#include <functional>
#include <map>

namespace unpure
{

template<class Value>
struct watch
{
    using action_type = std::function<void()>;

    watch() : value{}
    {
    }

    explicit watch(Value value) : value(value)
    {
    }

    auto operator = (Value value) -> void
    {
        this->value = value;

        auto it = actions.find(value);
        if (it != actions.end())
        {
            it->second();
        }
    }

    auto operator * () const -> Value
    {
        return value;
    }

    auto when_changed_to(Value value, action_type action) -> void
    {
        actions[value] = action;
    }

private:
    Value value;
    std::map<Value, action_type> actions;
};

} // namespace unpure
