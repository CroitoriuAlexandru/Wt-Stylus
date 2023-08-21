#include "include/Svg.h"

using namespace Tailwind;

Svg::Svg()
{
    // stroke width
    stroke_width = Propriety({
        StyleClass("none", ""),
        StyleClass("stroke-0", "stroke-width: 0;"),
        StyleClass("stroke-1", "stroke-width: 1;"),
        StyleClass("stroke-2", "stroke-width: 2;"),
    }, "https://tailwindcss.com/docs/stroke-width");
}

std::vector<std::string> Svg::search_data()
{
    std::vector<std::string> data = {};
    for(auto styleClass : stroke_width.styleClasses_){
        data.push_back("svg/" + styleClass.className_);
    }
    return data;
}

std::string Svg::strokeWidthData()
{
    std::string data = " ";
    for(auto styleClass : stroke_width.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    return data;
}