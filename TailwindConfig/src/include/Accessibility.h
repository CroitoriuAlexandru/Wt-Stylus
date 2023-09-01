#pragma once
#include "Base.h"

using namespace Tailwind;

namespace Tailwind {

    class Accessibility {
    public:
        Accessibility();
        Propriety screen_readers;
        
        std::vector<std::string> search_data();

        std::string screenReadersData();
        boost::regex screen_readers_regex = boost::regex("(?<!\\S)(!)?(sr-only|not-sr-only)(?!\\w|-)");
    };

};