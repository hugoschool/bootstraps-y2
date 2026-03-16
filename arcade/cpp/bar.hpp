#pragma once

#include "IDisplayModule.hpp"

class Bar : public IDisplayModule {
    public:
        Bar();
        ~Bar();

        void init() override;
        const std::string &getName() const override;
        void stop() override;
    private:
        const std::string _name;
};
