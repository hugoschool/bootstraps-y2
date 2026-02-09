#include "FalseComponent.hpp"
#include "AComponent.hpp"
#include "IComponent.hpp"

nts::FalseComponent::FalseComponent() : AComponent()
{
}

nts::FalseComponent::~FalseComponent()
{
}

nts::Tristate nts::FalseComponent::compute(std::size_t pin)
{
    return nts::False;
}
