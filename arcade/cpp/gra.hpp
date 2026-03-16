#pragma once

#include "IDisplayModule.hpp"

class Gra : public IDisplayModule {
    public:
        Gra();
        ~Gra();

        void init() override;
        const std::string &getName() const override;
        void stop() override;
    private:
        const std::string _name;
};
