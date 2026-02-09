#include "FalseComponent.hpp"
#include "AComponent.hpp"
#include "IComponent.hpp"
#include "Tristate.hpp"

nts::FalseComponent::FalseComponent() : AComponent()
{
}

nts::FalseComponent::~FalseComponent()
{
}

nts::Tristate nts::FalseComponent::compute(std::size_t pin)
{
    if (pin != 1)
        return nts::Undefined;
    return nts::False;
}
