#pragma once
#include "Base.h"

using namespace Tailwind;

namespace Tailwind {

    class Accessibility {
    public:
        Accessibility();
        Propriety screen_readers;

        std::string screenReadersData();
    };

};