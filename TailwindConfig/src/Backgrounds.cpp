#include "include/Backgrounds.h"

using namespace Tailwind;

Backgrounds::Backgrounds()
{
    // background attachment
    StyleClass bg_fixed = StyleClass("bg-fixed", "background-attachment: fixed;");
    StyleClass bg_local = StyleClass("bg-local", "background-attachment: local;");
    StyleClass bg_scroll = StyleClass("bg-scroll", "background-attachment: scroll;");
    background_attachment = Propriety({bg_fixed, bg_local, bg_scroll}, "https://tailwindcss.com/docs/background-attachment");

    // background clip
    StyleClass bg_clip_border = StyleClass("bg-clip-border", "background-clip: border-box;");
    StyleClass bg_clip_padding = StyleClass("bg-clip-padding", "background-clip: padding-box;");
    StyleClass bg_clip_content = StyleClass("bg-clip-content", "background-clip: content-box;");
    StyleClass bg_clip_text = StyleClass("bg-clip-text", "background-clip: text;");
    background_clip = Propriety({bg_clip_border, bg_clip_padding, bg_clip_content, bg_clip_text}, "https://tailwindcss.com/docs/background-clip");

    // background origin
    StyleClass bg_origin_border = StyleClass("bg-origin-border", "background-origin: border-box;");
    StyleClass bg_origin_padding = StyleClass("bg-origin-padding", "background-origin: padding-box;");
    StyleClass bg_origin_content = StyleClass("bg-origin-content", "background-origin: content-box;");
    background_origin = Propriety({bg_origin_border, bg_origin_padding, bg_origin_content}, "https://tailwindcss.com/docs/background-origin");

    // background position
    StyleClass bg_right_bottom = StyleClass("bg-right-bottom", "background-position: right bottom;");
    StyleClass bg_right_top = StyleClass("bg-right-top", "background-position: right top;");
    StyleClass bg_left_bottom = StyleClass("bg-left-bottom", "background-position: left bottom;");
    StyleClass bg_left_top = StyleClass("bg-left-top", "background-position: left top;");
    StyleClass bg_top = StyleClass("bg-top", "background-position: top;");
    StyleClass bg_right = StyleClass("bg-right", "background-position: right;");
    StyleClass bg_bottom = StyleClass("bg-bottom", "background-position: bottom;");
    StyleClass bg_left = StyleClass("bg-left", "background-position: left;");
    StyleClass bg_center = StyleClass("bg-center", "background-position: center;");
    background_position = Propriety({bg_right_bottom, bg_right_top, bg_left_bottom, bg_left_top, bg_top, bg_right, bg_bottom, bg_left, bg_center}, "https://tailwindcss.com/docs/background-position");

    // background repeat
    StyleClass bg_repeat_round = StyleClass("bg-repeat-round", "background-repeat: repeat-round;");
    StyleClass bg_repeat_space = StyleClass("bg-repeat-space", "background-repeat: repeat-space;");
    StyleClass bg_no_repeat = StyleClass("bg-no-repeat", "background-repeat: no-repeat;");
    StyleClass bg_repeat_x = StyleClass("bg-repeat-x", "background-repeat: repeat-x;");
    StyleClass bg_repeat_y = StyleClass("bg-repeat-y", "background-repeat: repeat-y;");
    StyleClass bg_repeat = StyleClass("bg-repeat", "background-repeat: repeat;");
    background_repeat = Propriety({bg_repeat_round, bg_repeat_space, bg_no_repeat, bg_repeat_x, bg_repeat_y, bg_repeat}, "https://tailwindcss.com/docs/background-repeat");

    // background size
    StyleClass bg_auto = StyleClass("bg-auto", "background-size: auto;");
    StyleClass bg_cover = StyleClass("bg-cover", "background-size: cover;");
    StyleClass bg_contain = StyleClass("bg-contain", "background-size: contain;");
    background_size = Propriety({bg_auto, bg_cover, bg_contain}, "https://tailwindcss.com/docs/background-size");

    // background image
    StyleClass bg_none = StyleClass("bg-none", "none");
    StyleClass gradient_to_tl = StyleClass("gradient-to-tl", "linear-gradient(to top left, var(--tw-gradient-stops))");
    StyleClass gradient_to_tr = StyleClass("gradient-to-tr", "linear-gradient(to top right, var(--tw-gradient-stops))");
    StyleClass gradient_to_bl = StyleClass("gradient-to-bl", "linear-gradient(to bottom left, var(--tw-gradient-stops))");
    StyleClass gradient_to_br = StyleClass("gradient-to-br", "linear-gradient(to bottom right, var(--tw-gradient-stops))");
    StyleClass gradient_to_t = StyleClass("gradient-to-t", "linear-gradient(to top, var(--tw-gradient-stops))");
    StyleClass gradient_to_r = StyleClass("gradient-to-r", "linear-gradient(to right, var(--tw-gradient-stops))");
    StyleClass gradient_to_b = StyleClass("gradient-to-b", "linear-gradient(to bottom, var(--tw-gradient-stops))");
    StyleClass gradient_to_l = StyleClass("gradient-to-l", "linear-gradient(to left, var(--tw-gradient-stops))");

    background_image = Propriety(
        {bg_none, 
        gradient_to_tl,
        gradient_to_tr,
        gradient_to_bl,
        gradient_to_br,
        gradient_to_t,
        gradient_to_r,
        gradient_to_b,
        gradient_to_l}, "https://tailwindcss.com/docs/background-image");

}

std::string Backgrounds::BackgroundAttachmentData()
{
    std::string data = "Background Attachment ------------------------------------\n";
    for(auto styleClass : background_attachment.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Backgrounds::BackgroundClipData()
{
    std::string data = "Background Clip ------------------------------------\n";
    for(auto styleClass : background_clip.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Backgrounds::BackgroundOriginData()
{
    std::string data = "Background Origin ------------------------------------\n";
    for(auto styleClass : background_origin.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Backgrounds::BackgroundPositionData()
{
    std::string data = "Background Position ------------------------------------\n";
    for(auto styleClass : background_position.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Backgrounds::BackgroundRepeatData()
{
    std::string data = "Background Repeat ------------------------------------\n";
    for(auto styleClass : background_repeat.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Backgrounds::BackgroundSizeData()
{
    std::string data = "Background Size ------------------------------------\n";
    for(auto styleClass : background_size.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Backgrounds::BackgroundImageData()
{
    std::string data = "Background Image ------------------------------------\n";
    for(auto styleClass : background_image.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}
