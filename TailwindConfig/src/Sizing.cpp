#include "include/Sizing.h"

using namespace Tailwind;

Sizing::Sizing(std::vector<std::string> sizing_variants)
{
    // width and height max-height
    std::vector<std::string> extra_size_variants = {"5/6", "4/6", "3/6", "2/6", "1/6", "4/6", "3/5", "2/5", "1/5", "3/4", "2/4", "1/4", "2/3", "1/3", "1/2", "screen", "min", "max", "fit", "full"};
    std::vector<std::string> extra_size_variants_12 = {"11/12", "10/12", "9/12", "8/12", "7/12", "6/12", "5/12", "4/12", "3/12", "2/12", "1/12"};
    width = Propriety({}, "https://tailwindcss.com/docs/width");
    height = Propriety({}, "https://tailwindcss.com/docs/height");
    max_height = Propriety({}, "https://tailwindcss.com/docs/max-height");

    StyleClass width_auto = StyleClass("w-auto", "");
    StyleClass height_auto = StyleClass("h-auto", "");


    for(auto size : extra_size_variants_12)
    {
        width.styleClasses_.push_back(StyleClass("w-" + size, ""));
    }

    for(auto size : extra_size_variants)
    {
        width.styleClasses_.push_back(StyleClass("w-" + size, ""));
        height.styleClasses_.push_back(StyleClass("h-" + size, ""));
    }
    for(auto size : sizing_variants)
    {
        width.styleClasses_.push_back(StyleClass("w-" + size, ""));
        height.styleClasses_.push_back(StyleClass("h-" + size, ""));
        max_height.styleClasses_.push_back(StyleClass("max-h-" + size, ""));
    }
    width.styleClasses_.push_back(width_auto);
    height.styleClasses_.push_back(height_auto);
    // max height
    max_height.styleClasses_.push_back(StyleClass("max-h-none", ""));
    max_height.styleClasses_.push_back(StyleClass("max-h-full", ""));
    max_height.styleClasses_.push_back(StyleClass("max-h-screen", ""));
    max_height.styleClasses_.push_back(StyleClass("max-h-min", ""));
    max_height.styleClasses_.push_back(StyleClass("max-h-max", ""));
    max_height.styleClasses_.push_back(StyleClass("max-h-fit", ""));

    // min-width 
    min_width = Propriety({
        StyleClass("min-w-0", ""),
        StyleClass("min-w-full", ""),
        StyleClass("min-w-min", ""),
        StyleClass("min-w-max", ""),
        StyleClass("min-w-fit", "")
    }, "https://tailwindcss.com/docs/min-width");

    // min-height
    // StyleClass min_h_0 = StyleClass("min-h-0", "");
    // StyleClass min_h_full = StyleClass("min-h-full", "");
    // StyleClass min_h_screen = StyleClass("min-h-screen", "");
    // StyleClass min_h_min = StyleClass("min-h-min", "");
    // StyleClass min_h_max = StyleClass("min-h-max", "");
    // StyleClass min_h_fit = StyleClass("min-h-fit", "");
    min_height = Propriety({
        StyleClass("min-h-0", ""),
        StyleClass("min-h-full", ""),
        StyleClass("min-h-screen", ""),
        StyleClass("min-h-min", ""),
        StyleClass("min-h-max", ""),
        StyleClass("min-h-fit", "")
    }, "https://tailwindcss.com/docs/min-height");

    // max-widht
    max_width = Propriety({
        StyleClass("max-w-0", "max-width: 0rem; /* 0px */"),
        StyleClass("max-w-none", ""),
        StyleClass("max-w-xs", "max-width: 20rem; /* 320px */"),
        StyleClass("max-w-sm", "max-width: 24rem; /* 384px */"),
        StyleClass("max-w-md", "max-width: 28rem; /* 448px */"),
        StyleClass("max-w-lg", "max-width: 32rem; /* 512px */"),
        StyleClass("max-w-xl", "max-width: 36rem; /* 576px */"),
        StyleClass("max-w-2xl", "max-width: 42rem; /* 672px */"),
        StyleClass("max-w-3xl", "max-width: 48rem; /* 768px */"),
        StyleClass("max-w-4xl", "max-width: 56rem; /* 896px */"),
        StyleClass("max-w-5xl", "max-width: 64rem; /* 1024px */"),
        StyleClass("max-w-6xl", "max-width: 72rem; /* 1152px */"),
        StyleClass("max-w-7xl", "max-width: 80rem; /* 1280px */"),
        StyleClass("max-w-full", "max-width: 100%;"),
        StyleClass("max-w-min", "max-width: min-content;"),
        StyleClass("max-w-max", "max-width: max-content;"),
        StyleClass("max-w-fit", "max-width: fit-content;"),
        StyleClass("max-w-prose", "max-width: 65ch;"),
        StyleClass("max-w-screen-sm", "max-width: 640px;"),
        StyleClass("max-w-screen-md", "max-width: 768px;"),
        StyleClass("max-w-screen-lg", "max-width: 1024px;"),
        StyleClass("max-w-screen-xl", "max-width: 1280px;"),
        StyleClass("max-w-screen-2xl", "max-width: 1536px;")
    }, "https://tailwindcss.com/docs/max-width");
}

std::string Sizing::WidthData()
{
    std::string data = "Width ------------------------------------\n";
    for(auto styleClass : width.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Sizing::HeightData()
{
    std::string data = "Height ------------------------------------\n";
    for(auto styleClass : height.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Sizing::MaxHeightData()
{
    std::string data = "Max Height ------------------------------------\n";
    for(auto styleClass : max_height.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Sizing::MinWidthData()
{
    std::string data = "Min Width ------------------------------------\n";
    for(auto styleClass : min_width.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Sizing::MinHeightData()
{
    std::string data = "Min Height ------------------------------------\n";
    for(auto styleClass : min_height.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Sizing::MaxWidthData()
{
    std::string data = "Max Width ------------------------------------\n";
    for(auto styleClass : max_width.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

