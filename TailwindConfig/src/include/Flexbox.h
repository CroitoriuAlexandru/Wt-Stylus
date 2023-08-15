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

        Propriety place_content;
        Propriety place_items;
        Propriety place_self;

        Propriety justify_content;
        Propriety justify_items;
        Propriety justify_self;

        Propriety align_content;
        Propriety align_items;
        Propriety align_self;

        std::string BasisData();
        std::string DirectionData();
        std::string WrapData();
        std::string FlexData();
        std::string GrowData();
        std::string ShrinkData();
        std::string OrderData();
        std::string PlaceData();
        std::string JustifyData();
        std::string AlignData();
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