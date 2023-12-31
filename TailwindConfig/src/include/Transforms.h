#pragma once
#include "Base.h"

namespace Tailwind {

    class Transforms {
    public:
        Transforms(std::vector<std::string> sizing_variants = {});
        Propriety scale;
        Propriety scale_x;
        Propriety scale_y;
        Propriety rotate;
        Propriety translate_x;
        Propriety translate_y;
        Propriety skew_x;
        Propriety skew_y;
        Propriety transform_origin;

        std::vector<std::string> search_data();

        std::string scaleData();
        std::string rotateData();
        std::string translateData();
        std::string skewData();
        std::string transformOriginData();

        boost::regex scale_regex = boost::regex("(?<=\n| )(!)?[-]?(scale|scale-x|scale-y)-(150|125|110|105|100|95|90|75|50|0)(?!\\w|-)");
        boost::regex rotate_regex = boost::regex("(?<=\n| )(!)?[-]?rotate-(180|90|45|12|6|3|2|1|0)(?!\\w|-)");
        boost::regex translate_regex = boost::regex("(?<=\n| )(!)?[-]?(translate-x|translate-y)-(full|3\\/4|2\\/4|1\\/4|2\\/3|1\\/3|1\\/2|96|80|72|64|60|56|52|48|44|40|36|32|28|24|20|16|14|12|11|10|9|8|7|6|5|4|3.5|3|2.5|2|1.5|1|0.5|0|px)(?!\\w|-)");
        boost::regex skew_regex = boost::regex("(?<=\n| )(!)?[-]?(skew-y|skew-x)-(12|6|3|2|1|0)(?!\\w|-)");
        boost::regex origin_regex = boost::regex("(?<=\n| )(!)?[-]?origin-(top-left|top-right|bottom-right|bottom-left|top|left|bottom|right|center)(?!\\w|-)");
    };

};


// place self               (?<=\n| )(!)?place-self-(auto|start|end|center|stretch)(?!\\w|-)
// place items              (?<=\n| )(!)?place-items-(start|end|center|baseline|stretch)(?!\\w|-)
// place Content            (?<=\n| )(!)?place-content-(center|start|end|between|around|evenly|baseline|stretch)(?!\\w|-)
// align self               (?<=\n| )(!)?self-(auto|start|end|center|stretch|baseline)(?!\\w|-)
// alidn items              (?<=\n| )(!)?items-(start|end|center|stretch|baseline)(?!\\w|-)
// align content            (?<=\n| )(!)?content-(normal|between|around|evenly|start|end|center|stretch|baseline)(?!\\w|-)
// justify self             (?<=\n| )(!)?justify-self-(auto|start|end|center|stretch)(?!\\w|-)
// justify items            (?<=\n| )(!)?justify-items-(start|end|center|stretch)(?!\\w|-)
// justify content          (?<=\n| )(!)?justify-(normal|start|end|center|between|around|evenly|stretch)(?!\\w|-)
// gap                      (?<=\n| )(!)?gap(-x|-y)?-(96|80|72|64|60|56|52|48|44|40|36|32|28|24|20|16|14|12|11|10|9|8|7|6|5|4|3.5|3|2.5|2|1.5|1|0.5|0|px)(?!\\w|-)
// grid auto rows           (?<=\n| )(!)?auto-rows-(auto|min|max|fr)(?!\\w|-)
// grid auto columns        (?<=\n| )(!)?auto-cols-(auto|min|max|fr)(?!\\w|-)
// grid auto flow           (?<=\n| )(!)?grid-flow-(row|col|dense|row-dense|col-dense)(?!\\w|-)
// grid row span            (?<=\n| )(!)?row-(auto|span-(12|11|10|9|8|7|6|5|4|3|2|1|full))(?!\\w|-)
// grid row start           (?<=\n| )(!)?row-start-(13|12|11|10|9|8|7|6|5|4|3|2|1|full|auto)(?!\\w|-)
// grid row end             (?<=\n| )(!)?row-end-(13|12|11|10|9|8|7|6|5|4|3|2|1|full|auto)(?!\\w|-)
// grid template rows
// grid column start / end
// grid template columns
// order
// flex shrink
// flex grow
// flex
// flex wrap
// flex direction
// flex basis