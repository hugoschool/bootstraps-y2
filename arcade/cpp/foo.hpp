#pragma once

#include "IDisplayModule.hpp"

class Foo : public IDisplayModule {
    public:
        Foo();
        ~Foo();

        void init() override;
        const std::string &getName() const override;
        void stop() override;
    private:
        const std::string _name;
};
