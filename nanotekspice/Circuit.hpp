#pragma once

#include "AComponent.hpp"
#include "IComponent.hpp"
#include <unordered_map>
#include <memory>
#include <string>

namespace nts {
    class Circuit : public AComponent {
        public:
            Circuit();
            ~Circuit();

            nts::Tristate compute(std::size_t pin) override;
            void simulate(std::size_t tick = 1) override final;
            void display();
            void add(std::string, std::unique_ptr<IComponent>);
            IComponent *find(const std::string &);
        private:
            std::unordered_map<std::string, std::unique_ptr<IComponent>> _components;
            std::size_t _tick;
    };
}
