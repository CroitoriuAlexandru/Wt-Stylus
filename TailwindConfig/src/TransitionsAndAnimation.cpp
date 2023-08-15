#include "include/TransitionsAndAnimation.h"

using namespace Tailwind;

TransitionsAndAnimation::TransitionsAndAnimation()
{
    // transition-property
    transition_property = Propriety({
        StyleClass("transition-none", "transition-property: none;"),
        StyleClass("transition-all", "transition-property: all;"),
        StyleClass("transition-colors", "transition-property: background-color, border-color, color, fill, stroke;"),
        StyleClass("transition-opacity", "transition-property: opacity;"),
        StyleClass("transition-shadow", "transition-property: box-shadow;"),
        StyleClass("transition-transform", "transition-property: transform;"),
        StyleClass("transition", "transition-property: background-color, border-color, color, fill, stroke, opacity, box-shadow, transform;")
    }, "https://tailwindcss.com/docs/transition-property");

    // transition-duration
    transition_duration = Propriety({
        StyleClass("duration-0", "transition-duration: 0s;"),
        StyleClass("duration-75", "transition-duration: 75ms;"),
        StyleClass("duration-100", "transition-duration: 100ms;"),
        StyleClass("duration-150", "transition-duration: 150ms;"),
        StyleClass("duration-200", "transition-duration: 200ms;"),
        StyleClass("duration-300", "transition-duration: 300ms;"),
        StyleClass("duration-500", "transition-duration: 500ms;"),
        StyleClass("duration-700", "transition-duration: 700ms;"),
        StyleClass("duration-1000", "transition-duration: 1000ms;")
    }, "https://tailwindcss.com/docs/transition-duration");

    // transition-timing-function
    transition_timing_function = Propriety({
        StyleClass("ease-linear", "transition-timing-function: linear;"),
        StyleClass("ease-out", "transition-timing-function: cubic-bezier(0, 0, 0.2, 1);"),
        StyleClass("ease-in-out", "transition-timing-function: cubic-bezier(0.4, 0, 0.2, 1);"),
        StyleClass("ease-in", "transition-timing-function: cubic-bezier(0.4, 0, 1, 1);")
    }, "https://tailwindcss.com/docs/transition-timing-function");

    // transition-delay
    transition_delay = Propriety({
        StyleClass("delay-0", "transition-delay: 0s;"),
        StyleClass("delay-75", "transition-delay: 75ms;"),
        StyleClass("delay-100", "transition-delay: 100ms;"),
        StyleClass("delay-150", "transition-delay: 150ms;"),
        StyleClass("delay-200", "transition-delay: 200ms;"),
        StyleClass("delay-300", "transition-delay: 300ms;"),
        StyleClass("delay-500", "transition-delay: 500ms;"),
        StyleClass("delay-700", "transition-delay: 700ms;"),
        StyleClass("delay-1000", "transition-delay: 1000ms;")
    }, "https://tailwindcss.com/docs/transition-delay");

    StyleClass animation_none = StyleClass("animate-none", "animation: none;");
    StyleClass animation_spin = StyleClass("animate-spin", "animation: spin 1s linear infinite;");
    StyleClass animation_ping = StyleClass("animate-ping", "animation: ping 1s cubic-bezier(0, 0, 0.2, 1) infinite;");
    StyleClass animation_pulse = StyleClass("animate-pulse", "animation: pulse 2s cubic-bezier(0.4, 0, 0.6, 1) infinite;");
    StyleClass animation_bounce = StyleClass("animate-bounce", "animation: bounce 1s infinite;");

    animation = Propriety({animation_none, animation_spin, animation_ping, animation_pulse, animation_bounce}, "https://tailwindcss.com/docs/animation");

}

std::string TransitionsAndAnimation::TransitionPropertyData()
{
    std::string data = "Transition Property ------------------------------------\n";
    for(auto styleClass : transition_property.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string TransitionsAndAnimation::TransitionDurationData()
{
    std::string data = "Transition Duration ------------------------------------\n";
    for(auto styleClass : transition_duration.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string TransitionsAndAnimation::TransitionTimingFunctionData()
{
    std::string data = "Transition Timing Function ------------------------------------\n";
    for(auto styleClass : transition_timing_function.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string TransitionsAndAnimation::TransitionDelayData()
{
    std::string data = "Transition Delay ------------------------------------\n";
    for(auto styleClass : transition_delay.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string TransitionsAndAnimation::AnimationData()
{
    std::string data = "Animation ------------------------------------\n";
    for(auto styleClass : animation.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

