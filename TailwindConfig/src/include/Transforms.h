#pragma once
#include "Base.h"

namespace Tailwind {

    class Transforms {
    public:
        Transforms(std::vector<std::string> sizing_variants = {});
        Propriety scale = Propriety({}, "");
        Propriety scale_x = Propriety({}, "");
        Propriety scale_y = Propriety({}, "");
        Propriety rotate = Propriety({}, "");
        Propriety translate_x = Propriety({}, "");
        Propriety translate_y = Propriety({}, "");
        Propriety skew_x = Propriety({}, "");
        Propriety skew_y = Propriety({}, "");
        Propriety transform_origin = Propriety({}, "");

        std::string scaleData();
        std::string rotateData();
        std::string translateData();
        std::string skewData();
        std::string transformOriginData();

        std::regex scale_regex = std::regex("[!]?[-]?(scale|scale-x|scale-y)-(150|125|110|105|100|95|90|75|50|0)");
        std::regex rotate_regex = std::regex("[!]?[-]?rotate-(180|90|45|12|6|3|2|1|0)");
        std::regex translate_regex = std::regex("[!]?[-]?(translate-x|translate-y)-(full|3\\/4|2\\/4|1\\/4|2\\/3|1\\/3|1\\/2|98|80|72|64|60|56|52|48|44|40|36|32|28|24|20|16|14|12|11|10|9|8|7|6|5|4|3.5|3|2.5|2|1.5|1|0.5|0|px)");
        std::regex skew_regex = std::regex("[!]?[-]?(skew-y|skew-x)-(12|6|3|2|1|0)");
        std::regex origin_regex = std::regex("[!]?[-]?origin-(top-left|top-right|bottom-right|bottom-left|top|left|bottom|right|center)");
    };

};
