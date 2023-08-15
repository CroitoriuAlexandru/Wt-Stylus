#include "include/Config.h"

using namespace Tailwind;


Config::Config()
{
    spacing_VARIANTS = {"96", "80", "72", "64", "60", "56", "52", "48", "44", "40", "36", "32", "28", "24", "20", "16", "14", "12", "11", "10", "9", "8", "7", "6", "5", "4", "3.5", "3", "2.5", "2", "1.5", "1", "0.5", "0", "px"};

    opacity_VARIANTS = {"100", "95", "90", "85", "80", "75", "70", "65", "60", "55", "50", "45", "40", "35", "30", "25", "20", "15", "10", "5", "0"};


    columns_VARIANTS = {"7xl", "6xl", "5xl", "4xl", "3xl", "2xl", "xl", "lg", "md", "sm", "xs", "2xs", "3xs", "12", "11", "10", "9", "8", "7", "6", "5", "4", "3", "2", "1", "auto"};

    contrast_VARIANTS = {"200", "150", "125", "100", "75", "50", "0"};

    flex_basis_VARIANTS = {"auto", "1/2", "1/3", "2/3", "1/4", "2/4", "3/4", "1/5", "2/5", "3/5", "4/5", "1/6", "2/6", "3/6", "4/6", "5/6", "1/12", "2/12", "3/12", "4/12", "5/12", "6/12", "7/12", "8/12", "9/12", "10/12", "11/12", "full"};
    // for(auto size : spacing_VARIANTS) {
    //     flex_basis_VARIANTS.push_back(size);
    // }

    gradient_stops_VARIANTS = {"100%", "95%", "90%", "85%", "80%", "75%", "70%", "65%", "60%", "55%", "50%", "45%", "40%", "35%", "30%", "25%", "20%", "15%", "10%", "5%", "0%"};

    height_VARIANTS = {"auto", "fit", "max", "min", "screen", "full", "5/6", "4/6", "3/6", "2/6", "1/6", "4/5", "3/5", "2/5", "1/5", "3/4", "2/4", "1/4", "2/3", "1/3", "1/2"};
    // for(auto size : spacing_VARIANTS) {
    //     height_VARIANTS.push_back(size);
    // }

    // max_height_VARIANTS = {"none", "full", "screen", "min", "max", "fit"};
    // for(auto size : spacing_VARIANTS) {
    //     max_height_VARIANTS.push_back(size);
    // }

    max_width_VARIANTS = {"none", "full", "screen", "min", "max", "fit"};

    // margin_VARIANTS = {"auto"};
    // for(auto size : spacing_VARIANTS) {
    //     margin_VARIANTS.push_back(size);
    // }

    base_colors_VARIANTS = {"inherit", "current", "transparent", "black", "white"};
    colors_VARIANTS = {"slate", "gray", "zinc", "neutral", "stone", "red", "orange", "amber", "yellow", "lime", "green", "emerald", "teal", "cyan", "sky", "blue", "indigo", "violet", "purple", "fuchsia", "pink", "rose"};
    color_intensity_VARIANTS = {"950", "900", "800", "700", "600", "500", "400", "300", "200", "100", "50"};
    color_opacity_VARIANTS = {"100", "95", "90", "80", "75", "70", "60", "50", "40", "30", "25", "20", "10", "5", "0"}; 



    layout = Layout(spacing_VARIANTS);
    flexbox = Flexbox(spacing_VARIANTS);
    grid = Grid(spacing_VARIANTS);
    spacing = Spacing(spacing_VARIANTS);
    sizing = Sizing(spacing_VARIANTS);
    typography = Typography(spacing_VARIANTS);
    backgrounds = Backgrounds();
    borders = Borders();
    effects = Effects();
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
