#include "include/Filters.h"

using namespace Tailwind;

Filters::Filters()
{
    // blur
    blur = Propriety(
        {
        StyleClass("blur-none", "filter: blur(0);"),
        StyleClass("blur-sm", "filter: blur(4px);"),
        StyleClass("blur-md", "filter: blur(12px);"),
        StyleClass("blur-lg", "filter: blur(16px);"),
        StyleClass("blur-xl", "filter: blur(24px);"),
        StyleClass("blur-2xl", "filter: blur(40px);"),
        StyleClass("blur-3xl", "filter: blur(64px);"),
        StyleClass("blur", "filter: blur(8px);"),
        }, "https://tailwindcss.com/docs/blur");

    // brightness
    brightness = Propriety(
        {
        StyleClass("brightness-0", "filter: brightness(0);"),
        StyleClass("brightness-50", "filter: brightness(0.5);"),
        StyleClass("brightness-75", "filter: brightness(0.75);"),
        StyleClass("brightness-90", "filter: brightness(0.9);"),
        StyleClass("brightness-95", "filter: brightness(0.95);"),
        StyleClass("brightness-100", "filter: brightness(1);"),
        StyleClass("brightness-105", "filter: brightness(1.05);"),
        StyleClass("brightness-110", "filter: brightness(1.1);"),
        StyleClass("brightness-125", "filter: brightness(1.25);"),
        StyleClass("brightness-150", "filter: brightness(1.5);"),
        StyleClass("brightness-200", "filter: brightness(2);")
        }, "https://tailwindcss.com/docs/brightness");

    // contrast
    contrast = Propriety({
        StyleClass("contrast-0", "filter: contrast(0);"),
        StyleClass("contrast-50", "filter: contrast(0.5);"),
        StyleClass("contrast-75", "filter: contrast(0.75);"),
        StyleClass("contrast-100", "filter: contrast(1);"),
        StyleClass("contrast-125", "filter: contrast(1.25);"),
        StyleClass("contrast-150", "filter: contrast(1.5);"),
        StyleClass("contrast-200", "filter: contrast(2);")
        }, "https://tailwindcss.com/docs/contrast");


    // droop shadow
    drop_shadow = Propriety({
        StyleClass("drop-shadow-sm", "filter: drop-shadow(0 1px 1px rgba(0,0,0,0.05));"),
        StyleClass("drop-shadow-md", "filter: drop-shadow(0 4px 6px rgba(0,0,0,0.1));"),
        StyleClass("drop-shadow-lg", "filter: drop-shadow(0 10px 15px rgba(0,0,0,0.1));"),
        StyleClass("drop-shadow-xl", "filter: drop-shadow(0 20px 25px rgba(0,0,0,0.1));"),
        StyleClass("drop-shadow-2xl", "filter: drop-shadow(0 25px 50px rgba(0,0,0,0.25));"),
        StyleClass("drop-shadow-none", "filter: drop-shadow(0 0 #0000);"),
        StyleClass("drop-shadow", "filter: drop-shadow(0 1px 2px rgba(0,0,0,0.1));")
        }, "https://tailwindcss.com/docs/drop-shadow");


    // grayscale
    grayscale = Propriety({
        StyleClass("grayscale-0", "filter: grayscale(0);"),
        StyleClass("grayscale", "filter: grayscale(100%);")
        }, "https://tailwindcss.com/docs/grayscale");

    //hue rotate
    hue_rotate = Propriety({
        StyleClass("hue-rotate-0", "filter: hue-rotate(0deg);"),
        StyleClass("hue-rotate-15", "filter: hue-rotate(15deg);"),
        StyleClass("hue-rotate-30", "filter: hue-rotate(30deg);"),
        StyleClass("hue-rotate-60", "filter: hue-rotate(60deg);"),
        StyleClass("hue-rotate-90", "filter: hue-rotate(90deg);"),
        StyleClass("hue-rotate-180", "filter: hue-rotate(180deg);")
        }, "https://tailwindcss.com/docs/hue-rotate");

    // invert
    invert = Propriety({
        StyleClass("invert-0", "filter: invert(0);"),
        StyleClass("invert", "filter: invert(100%);")
        }, "https://tailwindcss.com/docs/invert");

    // saturate
    saturate = Propriety({
        StyleClass("saturate-0", "filter: saturate(0);"),
        StyleClass("saturate-50", "filter: saturate(0.5);"),
        StyleClass("saturate-100", "filter: saturate(1);"),
        StyleClass("saturate-150", "filter: saturate(1.5);"),
        StyleClass("saturate-200", "filter: saturate(2);")
        }, "https://tailwindcss.com/docs/saturate");

    // sepia
    sepia = Propriety({
        StyleClass("sepia-0", "filter: sepia(0);"),
        StyleClass("sepia", "filter: sepia(100%);")
        }, "https://tailwindcss.com/docs/sepia");

    // backdrop blur
    backdrop_blur = Propriety({
        StyleClass("backdrop-blur-none", "backdrop-filter: blur(0);"),
        StyleClass("backdrop-blur-sm", "backdrop-filter: blur(4px);"),
        StyleClass("backdrop-blur-md", "backdrop-filter: blur(12px);"),
        StyleClass("backdrop-blur-lg", "backdrop-filter: blur(16px);"),
        StyleClass("backdrop-blur-xl", "backdrop-filter: blur(24px);"),
        StyleClass("backdrop-blur-2xl", "backdrop-filter: blur(40px);"),
        StyleClass("backdrop-blur-3xl", "backdrop-filter: blur(64px);"),
        StyleClass("backdrop-blur", "backdrop-filter: blur(8px);")
        }, "https://tailwindcss.com/docs/backdrop-blur");

    // backdrop brightness
    backdrop_brightness = Propriety({
        StyleClass("backdrop-brightness-0", "backdrop-filter: brightness(0);"),
        StyleClass("backdrop-brightness-50", "backdrop-filter: brightness(0.5);"),
        StyleClass("backdrop-brightness-75", "backdrop-filter: brightness(0.75);"),
        StyleClass("backdrop-brightness-90", "backdrop-filter: brightness(0.9);"),
        StyleClass("backdrop-brightness-95", "backdrop-filter: brightness(0.95);"),
        StyleClass("backdrop-brightness-100", "backdrop-filter: brightness(1);"),
        StyleClass("backdrop-brightness-105", "backdrop-filter: brightness(1.05);"),
        StyleClass("backdrop-brightness-110", "backdrop-filter: brightness(1.1);"),
        StyleClass("backdrop-brightness-125", "backdrop-filter: brightness(1.25);"),
        StyleClass("backdrop-brightness-150", "backdrop-filter: brightness(1.5);"),
        StyleClass("backdrop-brightness-200", "backdrop-filter: brightness(2);")
        }, "https://tailwindcss.com/docs/backdrop-brightness");
   

    // backdrop contrast
    backdrop_contrast = Propriety({
        StyleClass("backdrop-contrast-0", "backdrop-filter: contrast(0);"),
        StyleClass("backdrop-contrast-50", "backdrop-filter: contrast(0.5);"),
        StyleClass("backdrop-contrast-75", "backdrop-filter: contrast(0.75);"),
        StyleClass("backdrop-contrast-100", "backdrop-filter: contrast(1);"),
        StyleClass("backdrop-contrast-125", "backdrop-filter: contrast(1.25);"),
        StyleClass("backdrop-contrast-150", "backdrop-filter: contrast(1.5);"),
        StyleClass("backdrop-contrast-200", "backdrop-filter: contrast(2);")
        }, "https://tailwindcss.com/docs/backdrop-contrast");
   
   // backdrop contrast
    backdrop_grayscale = Propriety({
        StyleClass("backdrop-grayscale-0", "backdrop-filter: grayscale(0);"),
        StyleClass("backdrop-grayscale", "backdrop-filter: grayscale(100%);")
        }, "https://tailwindcss.com/docs/backdrop-grayscale");

    // backdrop grayscale
    backdrop_hue_rotate = Propriety({
        StyleClass("backdrop-hue-rotate-0", "backdrop-filter: hue-rotate(0deg);"),
        StyleClass("backdrop-hue-rotate-15", "backdrop-filter: hue-rotate(15deg);"),
        StyleClass("backdrop-hue-rotate-30", "backdrop-filter: hue-rotate(30deg);"),
        StyleClass("backdrop-hue-rotate-60", "backdrop-filter: hue-rotate(60deg);"),
        StyleClass("backdrop-hue-rotate-90", "backdrop-filter: hue-rotate(90deg);"),
        StyleClass("backdrop-hue-rotate-180", "backdrop-filter: hue-rotate(180deg);")
        }, "https://tailwindcss.com/docs/backdrop-hue-rotate");

    // backdrop invert
    backdrop_invert = Propriety({
        StyleClass("backdrop-invert-0", "backdrop-filter: invert(0);"),
        StyleClass("backdrop-invert", "backdrop-filter: invert(100%);")
        }, "https://tailwindcss.com/docs/backdrop-invert");

    // backdrop opacity
    backdrop_opacity = Propriety({
        StyleClass("backdrop-opacity-0", "backdrop-filter: opacity(0);"),
        StyleClass("backdrop-opacity-5", "backdrop-filter: opacity(0.05);"),
        StyleClass("backdrop-opacity-10", "backdrop-filter: opacity(0.1);"),
        StyleClass("backdrop-opacity-20", "backdrop-filter: opacity(0.2);"),
        StyleClass("backdrop-opacity-25", "backdrop-filter: opacity(0.25);"),
        StyleClass("backdrop-opacity-30", "backdrop-filter: opacity(0.3);"),
        StyleClass("backdrop-opacity-40", "backdrop-filter: opacity(0.4);"),
        StyleClass("backdrop-opacity-50", "backdrop-filter: opacity(0.5);"),
        StyleClass("backdrop-opacity-60", "backdrop-filter: opacity(0.6);"),
        StyleClass("backdrop-opacity-70", "backdrop-filter: opacity(0.7);"),
        StyleClass("backdrop-opacity-75", "backdrop-filter: opacity(0.75);"),
        StyleClass("backdrop-opacity-80", "backdrop-filter: opacity(0.8);"),
        StyleClass("backdrop-opacity-90", "backdrop-filter: opacity(0.9);"),
        StyleClass("backdrop-opacity-95", "backdrop-filter: opacity(0.95);"),
        StyleClass("backdrop-opacity-100", "backdrop-filter: opacity(1);")
        }, "https://tailwindcss.com/docs/backdrop-opacity");
    
    // backdrop saturate
    backdrop_saturate = Propriety({
        StyleClass("backdrop-saturate-0", "backdrop-filter: saturate(0);"),
        StyleClass("backdrop-saturate-50", "backdrop-filter: saturate(0.5);"),
        StyleClass("backdrop-saturate-100", "backdrop-filter: saturate(1);"),
        StyleClass("backdrop-saturate-150", "backdrop-filter: saturate(1.5);"),
        StyleClass("backdrop-saturate-200", "backdrop-filter: saturate(2);")
        }, "https://tailwindcss.com/docs/backdrop-saturate");
    
    // backdrop sepia
    backdrop_sepia = Propriety({
        StyleClass("backdrop-sepia-0", "backdrop-filter: sepia(0);"),
        StyleClass("backdrop-sepia", "backdrop-filter: sepia(100%);")
        }, "https://tailwindcss.com/docs/backdrop-sepia");
}

std::string Filters::BlurData()
{
    std::string data = "Blur ------------------------------------\n";
    for(auto styleClass : blur.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Filters::BrightnessData()
{
    std::string data = "Brightness ------------------------------------\n";
    for(auto styleClass : brightness.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Filters::ContrastData()
{
    std::string data = "Cntrast ------------------------------------\n";
    for(auto styleClass : contrast.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Filters::DropShadowData()
{
    std::string data = "Dop Shadow ------------------------------------\n";
    for(auto styleClass : drop_shadow.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Filters::GrayscaleData()
{
    std::string data = "Grayscale ------------------------------------\n";
    for(auto styleClass : grayscale.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Filters::HueRotateData()
{
    std::string data = "Hue Rotate ------------------------------------\n";
    for(auto styleClass : hue_rotate.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Filters::InvertData()
{
    std::string data = "invert ------------------------------------\n";
    for(auto styleClass : invert.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Filters::SaturateData()
{
    std::string data = "Saturate ------------------------------------\n";
    for(auto styleClass : saturate.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Filters::SepiaData()
{
    std::string data = "Sepia ------------------------------------\n";
    for(auto styleClass : sepia.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Filters::BackdropBlurData()
{
    std::string data = "Backdrop Blur ------------------------------------\n";
    for(auto styleClass : backdrop_blur.styleClasses_)
    {
        data += styleClass.className_ + "\n";
    }
    return data;
}

std::string Filters::BackdropBrightnessData()
{
    std::string data = "Backdrop Brightness ------------------------------------\n";
    for(auto styleClass : backdrop_brightness.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Filters::BackdropContrastData()
{
    std::string data = "Backdrop Contrast ------------------------------------\n";
    for(auto styleClass : backdrop_contrast.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Filters::BackdropGrayscaleData()
{
    std::string data = "Backdrop Grayscale ------------------------------------\n";
    for(auto styleClass : backdrop_grayscale.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Filters::BackdropHueRotateData()
{
    std::string data = "Backdrop Hue Rotate ------------------------------------\n";
    for(auto styleClass : backdrop_hue_rotate.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Filters::BackdropInvertData()
{
    std::string data = "Backdrop Invert ------------------------------------\n";
    for(auto styleClass : backdrop_invert.styleClasses_)
    {
        data += styleClass.className_ + "\n";
    }
    return data;
}

std::string Filters::BackdropOpacityData()
{
    std::string data = "Backdrop Opacity ------------------------------------\n";
    for(auto styleClass : backdrop_opacity.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Filters::BackdropSaturateData()
{
    std::string data = "Backdrop Saturate ------------------------------------\n";
    for(auto styleClass : backdrop_saturate.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Filters::BackdropSepiaData()
{
    std::string data = "Backdrop Sepia ------------------------------------\n";
    for(auto styleClass : backdrop_sepia.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

