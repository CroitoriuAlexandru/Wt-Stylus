#include "include/Config.h"

using namespace Tailwind;


Config::Config()
{
    // |11\/12|10\/12|9\/12|8\/12|7\/12|6\/12|5\/12|4\/12|3\/12|2\/12|1\/12|5\/6|4\/6|3\/6|2\/6|1\/6|4\/5|3\/5|2\/5|1\/5|3\/4|2\/4|1\/4|2\/3|1\/3|1\/2

    // 96|80|72|64|60|56|52|48|44|40|36|32|28|24|20|16|14|12|11|10|9|8|7|6|5|4|3.5|3|2.5|2|1.5|1|0.5|0|px
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
    interactivity = Interactivity(spacing_VARIANTS);
    svg = Svg();
    accessibility = Accessibility();

};

int Config::getIndesOfStringInVector(std::string str, std::vector<StyleClass> vec){
	for(int index = 0; index < vec.size(); ++index){
		if(vec[index].className_.compare(str) == 0) return index;
	}
	return 0;
}
