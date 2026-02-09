#include "InputComponent.hpp"
#include "AComponent.hpp"
#include "IComponent.hpp"

nts::InputComponent::InputComponent() : AComponent(), _state(nts::Undefined)
{
}

nts::InputComponent::~InputComponent()
{
}

void nts::InputComponent::store(nts::Tristate state)
{
    _state = state;
}

nts::Tristate nts::InputComponent::compute(std::size_t pin)
{
    return _state;
}
