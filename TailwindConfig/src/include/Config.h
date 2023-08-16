#pragma once
#include "Base.h"
#include "Layout.h"
#include "Flexbox.h"
#include "Grid.h"
#include "Spacing.h"
#include "Sizing.h"
#include "Typography.h"
#include "Backgrounds.h"
#include "Borders.h"
#include "Effects.h"
#include "Filters.h"
#include "Tables.h"
#include "TransitionsAndAnimation.h"
#include "Transforms.h"
#include "Interactivity.h"
#include "Svg.h"
#include "Accessibility.h"

#include <string>
#include <vector>


namespace Tailwind {

    class Config
    {
    public:
        Config();
        Layout layout;
        Flexbox flexbox;
        Grid grid;
        Spacing spacing;
        Sizing sizing;
        Typography typography;
        Backgrounds backgrounds;
        Borders borders;
        Effects effects;
        Filters filters;
        Tables tables;
        TransitionsAndAnimation transitions_and_animation;
        Transforms transforms;
        Interactivity interactivity;
        Svg svg;
        Accessibility accessibility;
    
    

        std::vector<std::string> spacing_VARIANTS;
        std::vector<std::string> opacity_VARIANTS;
        std::vector<std::string> gradient_stops_VARIANTS;

        std::vector<std::string> colors_VARIANTS;
        std::vector<std::string> base_colors_VARIANTS;
        std::vector<std::string> color_intensity_VARIANTS;
        std::vector<std::string> color_opacity_VARIANTS;

        Propriety color_intensity_propriety;
        Propriety color_opacity_propriety;

    private: 
    };
};