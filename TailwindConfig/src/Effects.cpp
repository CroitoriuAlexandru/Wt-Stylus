#include "include/Effects.h"

using namespace Tailwind;

Effects::Effects()
{
    // box-shadow
    StyleClass shadow_sm = StyleClass("shadow-sm", "box-shadow: 0 1px 2px 0 rgba(0, 0, 0, 0.05);");
    StyleClass shadow_md = StyleClass("shadow-md", "box-shadow: 0 4px 6px -1px rgba(0, 0, 0, 0.1), 0 2px 4px -1px rgba(0, 0, 0, 0.06);");
    StyleClass shadow_lg = StyleClass("shadow-lg", "box-shadow: 0 10px 15px -3px rgba(0, 0, 0, 0.1), 0 4px 6px -2px rgba(0, 0, 0, 0.05);");
    StyleClass shadow_xl = StyleClass("shadow-xl", "box-shadow: 0 20px 25px -5px rgba(0, 0, 0, 0.1), 0 10px 10px -5px rgba(0, 0, 0, 0.04);");
    StyleClass shadow_2xl = StyleClass("shadow-2xl", "box-shadow: 0 25px 50px -12px rgba(0, 0, 0, 0.25);");
    StyleClass shadow_none = StyleClass("shadow-none", "box-shadow: none;");
    StyleClass shadow = StyleClass("shadow", "box-shadow: 0 1px 3px 0 rgba(0, 0, 0, 0.1), 0 1px 2px 0 rgba(0, 0, 0, 0.06);");
    box_shadow = Propriety({shadow_sm, shadow_md, shadow_lg, shadow_xl, shadow_2xl, shadow_none, shadow}, "https://tailwindcss.com/docs/box-shadow");

    // box shadow inset
    StyleClass shadow_inner = StyleClass("shadow-inner", "box-shadow: inset 0 2px 4px 0 rgba(0, 0, 0, 0.06);");
    box_shadow_inset = Propriety({shadow_inner}, "https://tailwindcss.com/docs/box-shadow#inset");

    // opacity
    std::vector<std::string> opacity_variants = {"0", "5", "10", "15", "20", "25", "30", "35", "40", "50", "60", "70", "75", "80", "90", "95", "100"};
    opacity = Propriety({}, "https://tailwindcss.com/docs/opacity");
    for(auto size : opacity_variants)
    {
        opacity.styleClasses_.push_back(StyleClass("opacity-" + size, "opacity: " + size + "%;"));
    }

    // mix blend mode
    // background blend mode
    std::vector<std::string> mix_blend_mode_variants = {"normal", "multiply", "screen", "overlay", "darken", "lighten", "color-dodge", "color-burn", "hard-light", "soft-light", "difference", "exclusion", "hue", "saturation", "color", "luminosity"};
    mix_blend_mode = Propriety({}, "https://tailwindcss.com/docs/mix-blend-mode");
    background_blend_mode = Propriety({}, "https://tailwindcss.com/docs/background-blend-mode");
    for(auto size : mix_blend_mode_variants)
    {
        mix_blend_mode.styleClasses_.push_back(StyleClass("mix-blend-" + size, "mix-blend-mode: " + size + ";"));
        background_blend_mode.styleClasses_.push_back(StyleClass("bg-blend-" + size, "background-blend-mode: " + size + ";"));
    }

}

std::string Effects::BoxShadowData()
{
    std::string data = "Box Shadow ------------------------------------\n";
    data += "Box Shadow ---------\n";
    for(auto styleClass : box_shadow.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\nBox Shadow Inset ---------\n";
    for(auto styleClass : box_shadow_inset.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Effects::OpacityData()
{
    std::string data = "Opacity ------------------------------------\n";
    for(auto styleClass : opacity.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Effects::MixBlendModeData()
{
    std::string data = "Blend Mode ------------------------------------\n";
    data += "Mix Blend Mode ---------\n";
    for(auto styleClass : mix_blend_mode.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\nBackground Blend Mode ---------\n";
    for(auto styleClass : background_blend_mode.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

