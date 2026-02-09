// this copies the example_3 but in bootstrap mode we're testing out here
#include "Circuit.hpp"
#include "ClockComponent.hpp"
#include "IComponent.hpp"
#include "OutputComponent.hpp"
#include <memory>

int main(void)
{
    nts::Circuit circuit;

    auto clock = std::make_unique<nts::ClockComponent>();
    auto output = std::make_unique<nts::OutputComponent>();

    output->setLink(1, *clock, 1);
    circuit.add("cl", std::move(clock));
    circuit.add("out", std::move(output));
    circuit.display();

    nts::ClockComponent *find_clock = static_cast<nts::ClockComponent *>(circuit.find("cl"));
    find_clock->store(nts::False);
    circuit.display();

    circuit.simulate();
    circuit.display();

    circuit.simulate();
    circuit.display();

    circuit.simulate();
    circuit.simulate();
    circuit.simulate();
    circuit.display();
    return 0;
}
