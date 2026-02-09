#include "TrueComponent.hpp"
#include "AComponent.hpp"

nts::TrueComponent::TrueComponent() : AComponent()
{
}

nts::TrueComponent::~TrueComponent()
{
}

nts::Tristate nts::TrueComponent::compute(std::size_t pin)
{
    if (pin != 1)
        return nts::Undefined;
    return nts::True;
}
