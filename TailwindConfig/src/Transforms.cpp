#include "include/Transforms.h"

using namespace Tailwind;

Transforms::Transforms(std::vector<std::string> sizing_variants)
{
    // scale
    std::vector<std::string> scale_variants = {"0", "50", "75", "90", "95", "100", "105", "110", "125", "150"};
    // iterate in reverse for negative values
    for(auto variant = scale_variants.rbegin(); variant != scale_variants.rend(); variant++)
    {
        if((*variant).compare("0") == 0) continue;
        // Add the scale class to the style classes.
        scale.styleClasses_.push_back(StyleClass("-scale-" + *variant, "transform: scale(" + *variant + ");"));
        scale_x.styleClasses_.push_back(StyleClass("-scale-x-" + *variant, "transform: scaleX(" + *variant + ");"));
        scale_y.styleClasses_.push_back(StyleClass("-scale-y-" + *variant, "transform: scaleY(" + *variant + ");"));
    }
    
    for(auto variant : scale_variants)
    {
        scale.styleClasses_.push_back(StyleClass("scale-" + variant, ""));
        scale_x.styleClasses_.push_back(StyleClass("scale-x-" + variant, ""));
        scale_y.styleClasses_.push_back(StyleClass("scale-y-" + variant, ""));
    }

    // rotate
    rotate = Propriety({
        StyleClass("-rotate-180", "transform: rotate(-180deg);"),
        StyleClass("-rotate-90", "transform: rotate(-90deg);"),
        StyleClass("-rotate-45", "transform: rotate(-45deg);"),
        StyleClass("-rotate-12", "transform: rotate(-12deg);"),
        StyleClass("-rotate-6", "transform: rotate(-6deg);"),
        StyleClass("-rotate-3", "transform: rotate(-3deg);"),
        StyleClass("-rotate-2", "transform: rotate(-2deg);"),
        StyleClass("-rotate-1", "transform: rotate(-1deg);"),
        StyleClass("rotate-0", "transform: rotate(0deg);"),
        StyleClass("rotate-1", "transform: rotate(1deg);"),
        StyleClass("rotate-2", "transform: rotate(2deg);"),
        StyleClass("rotate-3", "transform: rotate(3deg);"),
        StyleClass("rotate-6", "transform: rotate(6deg);"),
        StyleClass("rotate-12", "transform: rotate(12deg);"),
        StyleClass("rotate-45", "transform: rotate(45deg);"),
        StyleClass("rotate-90", "transform: rotate(90deg);"),
        StyleClass("rotate-180", "transform: rotate(180deg);")
    }, "https://tailwindcss.com/docs/rotate");

    // translate
    std::vector<std::string> extra_translate_skew_variants = {};
    for(auto variant : sizing_variants) extra_translate_skew_variants.push_back(variant);
    extra_translate_skew_variants.push_back("3/4");
    extra_translate_skew_variants.push_back("2/4");
    extra_translate_skew_variants.push_back("1/4");
    extra_translate_skew_variants.push_back("2/3");
    extra_translate_skew_variants.push_back("1/3");
    extra_translate_skew_variants.push_back("1/2");

    translate_x = Propriety({}, "https://tailwindcss.com/docs/translate");
    translate_y = Propriety({}, "https://tailwindcss.com/docs/translate");
    StyleClass translate_full_x = StyleClass("translate-x-full", "");
    StyleClass translate_full_y = StyleClass("translate-y-full", "");

    // iterate in reverse for negative values
    for(auto variant = extra_translate_skew_variants.rbegin(); variant != extra_translate_skew_variants.rend(); variant++)
    {
        if((*variant).compare("0") == 0) continue;
        translate_x.styleClasses_.push_back(StyleClass("-translate-x-" + *variant, ""));
        translate_y.styleClasses_.push_back(StyleClass("-translate-y-" + *variant, ""));
    }
    translate_x.styleClasses_.push_back(translate_full_x);
    translate_y.styleClasses_.push_back(translate_full_y);

    for(auto variant : extra_translate_skew_variants)
    {
        translate_x.styleClasses_.push_back(StyleClass("translate-x-" + variant, ""));
        translate_y.styleClasses_.push_back(StyleClass("translate-y-" + variant, ""));
    }

    // skew

    skew_x = Propriety({
        StyleClass("-skew-x-12", "transform: skewX(-12deg);"),
        StyleClass("-skew-x-6", "transform: skewX(-6deg);"),
        StyleClass("-skew-x-3", "transform: skewX(-3deg);"),
        StyleClass("-skew-x-2", "transform: skewX(-2deg);"),
        StyleClass("-skew-x-1", "transform: skewX(-1deg);"),
        StyleClass("skew-x-0", "transform: skewX(0deg);"),
        StyleClass("skew-x-1", "transform: skewX(1deg);"),
        StyleClass("skew-x-2", "transform: skewX(2deg);"),
        StyleClass("skew-x-3", "transform: skewX(3deg);"),
        StyleClass("skew-x-6", "transform: skewX(6deg);"),
        StyleClass("skew-x-12", "transform: skewX(12deg);"),
    }, "https://tailwindcss.com/docs/skew");
    skew_y = Propriety({
        StyleClass("-skew-y-12", "transform: skewY(-12deg);"),
        StyleClass("-skew-y-6", "transform: skewY(-6deg);"),
        StyleClass("-skew-y-3", "transform: skewY(-3deg);"),
        StyleClass("-skew-y-2", "transform: skewY(-2deg);"),
        StyleClass("-skew-y-1", "transform: skewY(-1deg);"),
        StyleClass("skew-y-0", "transform: skewY(0deg);"),
        StyleClass("skew-y-1", "transform: skewY(1deg);"),
        StyleClass("skew-y-2", "transform: skewY(2deg);"),
        StyleClass("skew-y-3", "transform: skewY(3deg);"),
        StyleClass("skew-y-6", "transform: skewY(6deg);"),
        StyleClass("skew-y-12", "transform: skewY(12deg);"),
    }, "https://tailwindcss.com/docs/skew");

    // transform origin
    transform_origin = Propriety({
        StyleClass("origin-top-left", "transform-origin: top left;"),
        StyleClass("origin-top-right", "transform-origin: top right;"),
        StyleClass("origin-bottom-right", "transform-origin: bottom right;"),
        StyleClass("origin-bottom-left", "transform-origin: bottom left;"),
        StyleClass("origin-top", "transform-origin: top;"),
        StyleClass("origin-left", "transform-origin: left;"),
        StyleClass("origin-bottom", "transform-origin: bottom;"),
        StyleClass("origin-right", "transform-origin: right;"),
        StyleClass("origin-center", "transform-origin: center;"),
    }, "https://tailwindcss.com/docs/transform-origin");

}

std::string Transforms::ScaleData()
{
    std::string data = " Scale ------------------------------------\n";
    for(auto styleClass : scale.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n";
    for(auto styleClass : scale_x.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n";
    for(auto styleClass : scale_y.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Transforms::RotateData()
{
    std::string data = "\n";
    for(auto styleClass : rotate.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Transforms::TranslateData()
{
    std::string data = "\n";
    for(auto styleClass : translate_x.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n";
    for(auto styleClass : translate_y.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Transforms::SkewData()
{
    std::string data = "\n";
    for(auto styleClass : skew_x.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n";
    for(auto styleClass : skew_y.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Transforms::TransformOriginData()
{
    std::string data = "\n";
    for(auto styleClass : transform_origin.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}
