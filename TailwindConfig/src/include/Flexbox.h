#pragma once
#include "Base.h"

namespace Tailwind {

    class Flexbox {
    public:
        Flexbox(std::vector<std::string> spacing_variants = {});
        Propriety order;
        Propriety basis;
        Propriety direction;
        Propriety wrap;
        Propriety flex;
        Propriety grow;
        Propriety shrink;

        Propriety justify_content;
        Propriety justify_items;
        Propriety justify_self;

        Propriety align_content;
        Propriety align_items;
        Propriety align_self;

        std::vector<std::string> search_data();

        
        boost::regex order_regex = boost::regex("(?<=\n| )(!)?order-(12|11|10|9|8|7|6|5|4|3|2|1|none|last|first)(?!\\w|-)");
        boost::regex basis_regex = boost::regex("(?<=\n| )(!)?basis-(full|auto|11\\/12|10\\/12|9\\/12|8\\/12|7\\/12|6\\/12|5\\/12|4\\/12|3\\/12|2\\/12|1\\/12|5\\/6|4\\/6|3\\/6|2\\/6|1\\/6|4\\/5|3\\/5|2\\/5|1\\/5|3\\/4|2\\/4|1\\/4|2\\/3|1\\/3|1\\/2|96|80|72|64|60|56|52|48|44|40|36|32|28|24|20|16|14|12|11|10|9|8|7|6|5|4|3.5|3|2.5|2|1.5|1|0.5|0|px)(?!\\w|-)");
        boost::regex direction_regex = boost::regex("(?<=\n| )(!)?flex-(row-reverse|row|col-reverse|col)(?!\\w|-)");
        boost::regex wrap_regex = boost::regex("(?<=\n| )(!)?flex-(wrap-reverse|wrap|nowrap)(?!\\w|-)");
        boost::regex flex_regex = boost::regex("(?<=\n| )(!)?flex-(1|auto|initial|none)(?!\\w|-)");
        boost::regex grow_regex = boost::regex("(?<=\n| )(!)?grow(-0)?(?!\\w|-)");
        boost::regex shrink_regex = boost::regex("(?<=\n| )(!)?shrink(-0)?(?!\\w|-)");

        boost::regex justify_content_regex = boost::regex("(?<=\n| )(!)?justify-(normal|start|end|center|between|around|evenly|stretch)(?!\\w|-)");
        boost::regex justify_items_regex = boost::regex("(?<=\n| )(!)?justify-items-(start|end|center|stretch)(?!\\w|-)");
        boost::regex justify_self_regex = boost::regex("(?<=\n| )(!)?justify-self-(auto|start|end|center|stretch)(?!\\w|-)");

        boost::regex align_content_regex = boost::regex("(?<=\n| )(!)?content-(normal|between|around|evenly|start|end|center|stretch|baseline)(?!\\w|-)");
        boost::regex align_items_regex = boost::regex("(?<=\n| )(!)?items-(start|end|center|stretch|baseline)(?!\\w|-)");
        boost::regex align_self_regex = boost::regex("(?<=\n| )(!)?self-(auto|start|end|center|stretch|baseline)(?!\\w|-)");



        std::string basisData();
        std::string directionData();
        std::string wrapData();
        std::string flexData();
        std::string growData();
        std::string shrinkData();
        std::string orderData();
        std::string justifyData();
        std::string alignData();
    };

};


// justify-content / align-content / place-content

// justify-normal	    content-normal      
// justify-start	    content-start       place-content-start
// justify-end	        content-end         place-content-end
// justify-center	    content-center      place-content-center
// justify-between	    content-between     place-content-between
// justify-around	    content-around      place-content-around
// justify-evenly	    content-evenly      place-content-evenly
// justify-stretch	    content-stretch     place-content-stretch
//                     content-baseline    place-content-baseline


// justify-items / align-items / place-items

// justify-items-start     items-start         place-items-start
// justify-items-end       items-end           place-items-end
// justify-items-center    items-center        place-items-center
// justify-items-stretch   items-stretch       place-items-stretch
//                         items-baseline      place-items-baseline


// justify-self / align-self / place-self

// justify-self-auto	    self-auto           place-self-auto
// justify-self-start	    self-start          place-self-start
// justify-self-end	        self-end            place-self-end
// justify-self-center	    self-center         place-self-center
// justify-self-stretch    self-stretch         place-self-stretch
//                         self-baseline