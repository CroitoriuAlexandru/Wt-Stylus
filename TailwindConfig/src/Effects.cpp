#include "include/Effects.h"

using namespace Tailwind;

Effects::Effects(
                std::vector<std::string> opacity_variants,
                std::vector<std::string> base_colors_variants,
                std::vector<std::string> colors_variants,
                Propriety color_intensity_propriety,
                Propriety color_saturation_propriety
                )
{
    // box-shadow
    box_shadow = Propriety({
        StyleClass("none", ""),
        StyleClass("shadow-sm", "box-shadow: 0 1px 2px 0 rgba(0, 0, 0, 0.05);"),
        StyleClass("shadow", "box-shadow: 0 1px 3px 0 rgba(0, 0, 0, 0.1), 0 1px 2px 0 rgba(0, 0, 0, 0.06);"),
        StyleClass("shadow-md", "box-shadow: 0 4px 6px -1px rgba(0, 0, 0, 0.1), 0 2px 4px -1px rgba(0, 0, 0, 0.06);"),
        StyleClass("shadow-lg", "box-shadow: 0 10px 15px -3px rgba(0, 0, 0, 0.1), 0 4px 6px -2px rgba(0, 0, 0, 0.05);"),
        StyleClass("shadow-xl", "box-shadow: 0 20px 25px -5px rgba(0, 0, 0, 0.1), 0 10px 10px -5px rgba(0, 0, 0, 0.04);"),
        StyleClass("shadow-2xl", "box-shadow: 0 25px 50px -12px rgba(0, 0, 0, 0.25);"),
        StyleClass("shadow-none", "box-shadow: none;")
    }, "https://tailwindcss.com/docs/box-shadow");

    // box shadow inset
    box_shadow_inset = Propriety({
        StyleClass("none", ""),
        StyleClass("shadow-inner", "box-shadow: inset 0 2px 4px 0 rgba(0, 0, 0, 0.06);")
    }, "https://tailwindcss.com/docs/box-shadow#inset");

    // box shadow color
    auto propriety = Propriety({StyleClass("none", "")}, "https://tailwindcss.com/docs/box-shadow-color");
    box_shadow_color = ProprietyColor(propriety, color_intensity_propriety, color_saturation_propriety); 
    
    for(auto color : base_colors_variants){
        box_shadow_color.styleClasses_.push_back(StyleClass("shadow-" + color, ""));
    }
    box_shadow_color.styleClasses_.push_back(StyleClass("none", ""));
    for(auto color : colors_variants){
        box_shadow_color.styleClasses_.push_back(StyleClass("shadow-" + color, ""));
    }

    // opacity
    opacity = Propriety({StyleClass("none", "")}, "https://tailwindcss.com/docs/opacity");
    for(auto size : opacity_variants)
    {
        opacity.styleClasses_.push_back(StyleClass("opacity-" + size, "opacity: " + size + "%;"));
    }

    // mix blend mode
    // background blend mode
    // normal|multiply|screen|overlay|darken|lighten|color-dodge|color-burn|hard-light|soft-light|difference|exclusion|hue|saturation|color|luminosity
    std::vector<std::string> mix_blend_mode_variants = {"normal", "multiply", "screen", "overlay", "darken", "lighten", "color-dodge", "color-burn", "hard-light", "soft-light", "difference", "exclusion", "hue", "saturation", "color", "luminosity"};
    mix_blend_mode = Propriety({StyleClass("none", "")}, "https://tailwindcss.com/docs/mix-blend-mode");
    background_blend_mode = Propriety({StyleClass("none", "")}, "https://tailwindcss.com/docs/background-blend-mode");
    for(auto size : mix_blend_mode_variants)
    {
        mix_blend_mode.styleClasses_.push_back(StyleClass("mix-blend-" + size, "mix-blend-mode: " + size + ";"));
        background_blend_mode.styleClasses_.push_back(StyleClass("bg-blend-" + size, "background-blend-mode: " + size + ";"));
    }

}

std::string Effects::boxShadowData()
{
    std::string data = " ";
    for(auto styleClass : box_shadow.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    for(auto styleClass : box_shadow_inset.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    return data;
}

std::string Effects::boxShadowColorData()
{
    std::string data = " ";
    for(auto styleClass : box_shadow_color.styleClasses_)
    {
        data += styleClass.className_ + "-500/20 ";
    }
    data += "\n ";
    return data;
}

std::string Effects::opacityData()
{
    std::string data = " ";
    for(auto styleClass : opacity.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    return data;
}

std::string Effects::mixBlendModeData()
{
    std::string data = " ";
    for(auto styleClass : mix_blend_mode.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    for(auto styleClass : background_blend_mode.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    return data;
}

