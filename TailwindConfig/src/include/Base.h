#pragma once
#include <string> 
#include <vector>
#include <regex>
#include <boost/regex.hpp>


namespace Tailwind {


    struct StyleClass {
        StyleClass(
            std::string className = "",
            std::string propriety = "")
            : className_{className},
            propriety_{propriety} {};

        std::string className_;
        std::string propriety_;
    };

    struct Propriety {
        public:
        Propriety(
            std::vector<StyleClass> styleClasses = {},
            std::string docsLink = "")
            : styleClasses_{styleClasses},
            docsLink_{docsLink} {};

        std::vector<StyleClass> styleClasses_;
        std::string docsLink_;
    };

    struct ProprietyColor : public Propriety {

        ProprietyColor(Propriety propriety = Propriety(),
                    Propriety intensity_variants = Propriety(),
                    Propriety opacity_variants = Propriety()
                    )
                    : Propriety(propriety),
                        intensity_(intensity_variants),
                        opacity_(opacity_variants) {}

            Propriety intensity_;
            Propriety opacity_;
    };

};