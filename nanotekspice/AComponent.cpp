#include "AComponent.hpp"
#include "IComponent.hpp"
#include <cstddef>
#include <stdexcept>
#include <utility>

nts::AComponent::AComponent() : IComponent()
{
}

nts::AComponent::~AComponent()
{
}

void nts::AComponent::simulate(std::size_t tick)
{
    static_cast<void>(tick);
}

void nts::AComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    std::pair<nts::IComponent &, std::size_t> pair = std::make_pair(std::ref(other), otherPin);

    // TODO: replace if already inserted
    _pins.insert({pin, pair});
}

nts::IComponent *nts::AComponent::getLink(std::size_t pin)
{
    try {
        nts::IComponent &component = _pins.at(pin).first;
        return &component;
    } catch (const std::out_of_range &) {
        return nullptr;
    }
}
