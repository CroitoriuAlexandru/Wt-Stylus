#pragma once
#include <string>
#include <vector>
#include <regex>


namespace Tailwind {


    struct StyleClass {
        StyleClass(std::string className, std::string propriety) : className_{className}, propriety_{propriety} {};
        std::string className_;
        std::string propriety_;
    };

    struct Propriety {

        Propriety(std::vector<StyleClass> styleClasses = {}, std::string docsLink = "") : styleClasses_{styleClasses}, docsLink_{docsLink} {};
        std::vector<StyleClass> styleClasses_;
        std::string docsLink_;
    };

};