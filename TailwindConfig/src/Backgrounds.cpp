#include "include/Backgrounds.h"

using namespace Tailwind;

Backgrounds::Backgrounds(   std::vector<std::string> colors_default_variants, 
                            std::vector<std::string> colors_variants, 
                            Propriety color_intensity_propriety, 
                            Propriety color_opacity_propriety, 
                            std::vector<std::string> gradient_stops_variants)
:   colors_default_variants(colors_default_variants)
{
    // background attachment

    background_attachment = Propriety({
        StyleClass("none", ""),
        StyleClass("bg-fixed", "background-attachment: fixed;"),
        StyleClass("bg-local", "background-attachment: local;"),
        StyleClass("bg-scroll", "background-attachment: scroll;")
    }, "https://tailwindcss.com/docs/background-attachment");

    // background clip
    background_clip = Propriety({
        StyleClass("none", ""),
        StyleClass("bg-clip-border", "background-clip: border-box;"),
        StyleClass("bg-clip-padding", "background-clip: padding-box;"),
        StyleClass("bg-clip-content", "background-clip: content-box;"),
        StyleClass("bg-clip-text", "background-clip: text;")
    }, "https://tailwindcss.com/docs/background-clip");

    // background color
    auto background_color_propriety = Propriety({}, "https://tailwindcss.com/docs/background-color");
    auto background_color_from_propriety = Propriety({}, "https://tailwindcss.com/docs/background-color");
    auto background_color_via_propriety = Propriety({}, "https://tailwindcss.com/docs/background-color");
    auto background_color_to_propriety = Propriety({}, "https://tailwindcss.com/docs/background-color");


    background_color = ProprietyColor(background_color_propriety, color_intensity_propriety, color_opacity_propriety);
    background_color_from = ProprietyColor(background_color_from_propriety, color_intensity_propriety, color_opacity_propriety);
    background_color_via = ProprietyColor(background_color_via_propriety, color_intensity_propriety, color_opacity_propriety);
    background_color_to = ProprietyColor(background_color_to_propriety, color_intensity_propriety, color_opacity_propriety);
    for(auto color : colors_default_variants)
    {
        background_color.styleClasses_.push_back(StyleClass("bg-" + color, ""));
        background_color_from.styleClasses_.push_back(StyleClass("from-" + color, ""));
        background_color_via.styleClasses_.push_back(StyleClass("via-" + color, ""));
        background_color_to.styleClasses_.push_back(StyleClass("to-" + color, ""));
    }
    background_color.styleClasses_.push_back(StyleClass("none", ""));
    background_color_from.styleClasses_.push_back(StyleClass("none", ""));
    background_color_via.styleClasses_.push_back(StyleClass("none", ""));
    background_color_to.styleClasses_.push_back(StyleClass("none", ""));

    for(auto color : colors_variants)
    {
        background_color.styleClasses_.push_back(StyleClass("bg-" + color, ""));
        background_color_from.styleClasses_.push_back(StyleClass("from-" + color, ""));
        background_color_via.styleClasses_.push_back(StyleClass("via-" + color, ""));
        background_color_to.styleClasses_.push_back(StyleClass("to-" + color, ""));
    }

    // background origin
    background_origin = Propriety({
        StyleClass("none", ""),
        StyleClass("bg-origin-border", "background-origin: border-box;"),
        StyleClass("bg-origin-padding", "background-origin: padding-box;"),
        StyleClass("bg-origin-content", "background-origin: content-box;")
    }, "https://tailwindcss.com/docs/background-origin");

    // background position
    background_position = Propriety({
        StyleClass("none", ""),
        StyleClass("bg-right-bottom", "background-position: right bottom;"),
        StyleClass("bg-right-top", "background-position: right top;"),
        StyleClass("bg-left-bottom", "background-position: left bottom;"),
        StyleClass("bg-left-top", "background-position: left top;"),
        StyleClass("bg-top", "background-position: top;"),
        StyleClass("bg-right", "background-position: right;"),
        StyleClass("bg-bottom", "background-position: bottom;"),
        StyleClass("bg-left", "background-position: left;"),
        StyleClass("bg-center", "background-position: center;")
    }, "https://tailwindcss.com/docs/background-position");

    // background repeat
    background_repeat = Propriety({
        StyleClass("none", ""),
        StyleClass("bg-repeat-round", "background-repeat: repeat-round;"),
        StyleClass("bg-repeat-space", "background-repeat: repeat-space;"),
        StyleClass("bg-no-repeat", "background-repeat: no-repeat;"),
        StyleClass("bg-repeat-x", "background-repeat: repeat-x;"),
        StyleClass("bg-repeat-y", "background-repeat: repeat-y;"),
        StyleClass("bg-repeat", "background-repeat: repeat;")
    }, "https://tailwindcss.com/docs/background-repeat");

    // background size
    background_size = Propriety({
        StyleClass("none", ""),
        StyleClass("bg-auto", "background-size: auto;"),
        StyleClass("bg-cover", "background-size: cover;"),
        StyleClass("bg-contain", "background-size: contain;")
    }, "https://tailwindcss.com/docs/background-size");

    // background image
    background_image = Propriety(
        {
            StyleClass("none", ""),
            StyleClass("bg-none", "none"),
            StyleClass("bg-gradient-to-tl", "background-image: linear-gradient(to top left, var(--tw-gradient-stops));"),
            StyleClass("bg-gradient-to-tr", "background-image: linear-gradient(to top right, var(--tw-gradient-stops));"),
            StyleClass("bg-gradient-to-bl", "background-image: linear-gradient(to bottom left, var(--tw-gradient-stops));"),
            StyleClass("bg-gradient-to-br", "background-image: linear-gradient(to bottom right, var(--tw-gradient-stops));"),
            StyleClass("bg-gradient-to-t", "background-image: linear-gradient(to top, var(--tw-gradient-stops));"),
            StyleClass("bg-gradient-to-r", "background-image: linear-gradient(to right, var(--tw-gradient-stops));"),
            StyleClass("bg-gradient-to-b", "background-image: linear-gradient(to bottom, var(--tw-gradient-stops));"),
            StyleClass("bg-gradient-to-l", "background-image: linear-gradient(to left, var(--tw-gradient-stops));")
        }, "https://tailwindcss.com/docs/background-image");

    // gradient stops
    for(auto stop : gradient_stops_variants)
    {
        gradient_stops_from.styleClasses_.push_back(StyleClass("from-" + stop, ""));
        gradient_stops_via.styleClasses_.push_back(StyleClass("via-" + stop, ""));
        gradient_stops_to.styleClasses_.push_back(StyleClass("to-" + stop, ""));
    }
}

std::vector<std::string> Backgrounds::search_data()
{
    std::vector<std::string> data = {"backgrounds | reset"};
    for(auto styleClass : background_attachment.styleClasses_)
    {
        data.push_back("backgrounds | " + styleClass.className_);
    }
    for(auto styleClass : background_clip.styleClasses_)
    {
        data.push_back("backgrounds | " + styleClass.className_);
    }
    for(auto styleClass : background_color.styleClasses_)
    {
        if(styleClass.className_ == "none"){
            data.push_back("backgrounds | " + std::string("bg-res"));
            continue;
        }
        data.push_back("backgrounds | " + styleClass.className_);
    }
    for(auto styleClass : background_color_from.styleClasses_)
    {
        data.push_back("backgrounds | " + styleClass.className_);
    }
    for(auto styleClass : background_color_via.styleClasses_)
    {
        data.push_back("backgrounds | " + styleClass.className_);
    }
    for(auto styleClass : background_color_to.styleClasses_)
    {
        data.push_back("backgrounds | " + styleClass.className_);
    }
    for(auto styleClass : background_origin.styleClasses_)
    {
        data.push_back("backgrounds | " + styleClass.className_);
    }
    for(auto styleClass : background_position.styleClasses_)
    {
        data.push_back("backgrounds | " + styleClass.className_);
    }
    for(auto styleClass : background_repeat.styleClasses_)
    {
        data.push_back("backgrounds | " + styleClass.className_);
    }
    for(auto styleClass : background_size.styleClasses_)
    {
        data.push_back("backgrounds | " + styleClass.className_);
    }
    for(auto styleClass : background_image.styleClasses_)
    {
        data.push_back("backgrounds | " + styleClass.className_);
    }
    for(auto styleClass : gradient_stops_from.styleClasses_)
    {
        data.push_back("backgrounds | " + styleClass.className_);
    }
    for(auto styleClass : gradient_stops_via.styleClasses_)
    {
        data.push_back("backgrounds | " + styleClass.className_);
    }
    for(auto styleClass : gradient_stops_to.styleClasses_)
    {
        data.push_back("backgrounds | " + styleClass.className_);
    }
return data;
}


std::string Backgrounds::backgroundAttachmentData()
{
    std::string data = " ";
    for(auto styleClass : background_attachment.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    return data;
}

std::string Backgrounds::backgroundClipData()
{
    std::string data = " ";
    for(auto styleClass : background_clip.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    return data;
}

std::string Backgrounds::backgroundColorData()
{
    std::string data = " ";
    for(auto styleClass : background_color.styleClasses_)
    {
        data += styleClass.className_ + "-500";
    }
    data += "\n ";
    for(auto styleClass : background_color_from.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    for(auto styleClass : background_color_from.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    for(auto styleClass : background_color_via.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    return data;
}

std::string Backgrounds::backgroundOriginData()
{
    std::string data = " ";
    for(auto styleClass : background_origin.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    return data;
}

std::string Backgrounds::backgroundPositionData()
{
    std::string data = " ";
    for(auto styleClass : background_position.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    return data;
}

std::string Backgrounds::backgroundRepeatData()
{
    std::string data = " ";
    for(auto styleClass : background_repeat.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    return data;
}

std::string Backgrounds::backgroundSizeData()
{
    std::string data = " ";
    for(auto styleClass : background_size.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    return data;
}

std::string Backgrounds::backgroundImageData()
{
    std::string data = " ";
    for(auto styleClass : background_image.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    return data;
}

std::string Backgrounds::gradientStopsData()
{
    std::string data = " ";
    for(auto styleClass : gradient_stops_from.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    for(auto styleClass : gradient_stops_via.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    for(auto styleClass : gradient_stops_to.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    return data;
}