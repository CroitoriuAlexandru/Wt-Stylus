#include "include/Config.h"

using namespace Tailwind;


Config::Config()
{
    // 98|80|72|64|60|56|52|48|44|40|36|32|28|24|20|16|14|12|11|10|9|8|7|6|5|4|3.5|3|2.5|2|1.5|1|0.5|0|px
    spacing_VARIANTS = {"96", "80", "72", "64", "60", "56", "52", "48", "44", "40", "36", "32", "28", "24", "20", "16", "14", "12", "11", "10", "9", "8", "7", "6", "5", "4", "3.5", "3", "2.5", "2", "1.5", "1", "0.5", "0", "px"};

    opacity_VARIANTS = {"100", "95", "90", "85", "80", "75", "70", "65", "60", "55", "50", "45", "40", "35", "30", "25", "20", "15", "10", "5", "0"};


    gradient_stops_VARIANTS = {"100%", "95%", "90%", "85%", "80%", "75%", "70%", "65%", "60%", "55%", "50%", "45%", "40%", "35%", "30%", "25%", "20%", "15%", "10%", "5%", "0%"};

    base_colors_VARIANTS = {"inherit", "current", "transparent", "black", "white"};
    colors_VARIANTS = {"slate", "gray", "zinc", "neutral", "stone", "red", "orange", "amber", "yellow", "lime", "green", "emerald", "teal", "cyan", "sky", "blue", "indigo", "violet", "purple", "fuchsia", "pink", "rose"};
    color_intensity_VARIANTS = {"950", "900", "800", "700", "600", "500", "400", "300", "200", "100", "50"};
    color_opacity_VARIANTS = {"100", "95", "90", "80", "75", "70", "60", "50", "40", "30", "25", "20", "10", "5", "0"}; 


    for(auto color_intensity : color_intensity_VARIANTS)
    {
        color_intensity_propriety.styleClasses_.push_back(StyleClass(color_intensity, ""));
    }
    for(auto color_opacity : color_opacity_VARIANTS)
    {
        color_opacity_propriety.styleClasses_.push_back(StyleClass(color_opacity, ""));
    }


    layout = Layout(spacing_VARIANTS);
    flexbox = Flexbox(spacing_VARIANTS);
    grid = Grid(spacing_VARIANTS);
    spacing = Spacing(spacing_VARIANTS);
    sizing = Sizing(spacing_VARIANTS);
    typography = Typography(spacing_VARIANTS);
    backgrounds = Backgrounds(  base_colors_VARIANTS, 
                                colors_VARIANTS, 
                                color_intensity_propriety, 
                                color_opacity_propriety,
                                gradient_stops_VARIANTS);
    borders = Borders();
    effects = Effects(  opacity_VARIANTS,
                        base_colors_VARIANTS, 
                        colors_VARIANTS, 
                        color_intensity_propriety, 
                        color_opacity_propriety);
    filters = Filters();
    tables = Tables(spacing_VARIANTS);
    TransitionsAndAnimation transitions_and_animation = TransitionsAndAnimation();
    transforms = Transforms(spacing_VARIANTS);
    interactivity = Interactivity(  spacing.margin.styleClasses_,
                                    spacing.margin_x.styleClasses_,
                                    spacing.margin_y.styleClasses_,
                                    spacing.margin_top.styleClasses_,
                                    spacing.margin_right.styleClasses_,
                                    spacing.margin_bottom.styleClasses_,
                                    spacing.margin_left.styleClasses_,
                                    spacing.margin_start.styleClasses_,
                                    spacing.margin_end.styleClasses_,
                                    spacing.padding.styleClasses_,
                                    spacing.padding_x.styleClasses_,
                                    spacing.padding_y.styleClasses_,
                                    spacing.padding_top.styleClasses_,
                                    spacing.padding_right.styleClasses_,
                                    spacing.padding_bottom.styleClasses_,
                                    spacing.padding_left.styleClasses_,
                                    spacing.padding_start.styleClasses_,
                                    spacing.padding_end.styleClasses_);
    svg = Svg();
    accessibility = Accessibility();

};