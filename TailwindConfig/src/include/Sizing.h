#pragma once
#include "Base.h"

namespace Tailwind {

    class Sizing {
    public:
        Sizing(std::vector<std::string> sizing_variants = {});
        Propriety width;
        Propriety min_width;
        Propriety max_width;

        Propriety height;
        Propriety min_height;
        Propriety max_height;
        
        std::string WidthData();
        std::string HeightData();
        std::string MinWidthData();
        std::string MaxWidthData();
        std::string MinHeightData();
        std::string MaxHeightData();
        
        
    };
    
};
