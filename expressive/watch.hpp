#pragma once

#include <functional>
#include <map>

namespace unpure
{

template<class Value>
struct watch
{
    using action_type = std::function<void(Value, Value)>;

    explicit watch(action_type action, Value initial = Value{}) : action(action), value(initial)
    {
    }

    auto operator = (Value value) -> void
    {
        std::swap(this->value, value);

        if (not this->value == value)
        {
            action(value, this->value);
        }
    }

    auto operator * () const -> Value
    {
        return value;
    }

private:
    action_type action;
    Value value;
};

} // namespace unpure
