#include "ClockComponent.hpp"
#include "AComponent.hpp"
#include "IComponent.hpp"
#include <optional>

nts::ClockComponent::ClockComponent() : AComponent(), _new_state(), _state(nts::Undefined)
{
}

nts::ClockComponent::~ClockComponent()
{
}

void nts::ClockComponent::store(nts::Tristate state)
{
    _new_state = std::make_optional(state);
}

void nts::ClockComponent::simulate(std::size_t tick)
{
    if (_new_state.has_value()) {
        _state = _new_state.value();
        return;
    }
    _state = static_cast<nts::Tristate>(!static_cast<bool>(_state));
}

nts::Tristate nts::ClockComponent::compute(std::size_t pin)
{
    return _state;
}
