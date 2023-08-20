#include "include/Accessibility.h"

using namespace Tailwind;

Accessibility::Accessibility()
{
    // Screen Readers
    screen_readers = Propriety({
        StyleClass("none", "display: none;"),
        StyleClass("sr-only", "position: absolute; width: 1px; height: 1px; padding: 0; margin: -1px; overflow: hidden; clip: rect(0, 0, 0, 0); white-space: nowrap; border-width: 0;"),
        StyleClass("not-sr-only", "position: static; width: auto; height: auto; padding: 0; margin: 0; overflow: visible; clip: auto; white-space: normal;")
    }, "https://tailwindcss.com/docs/screen-readers");
}

std::string Accessibility::screenReadersData()
{
    std::string data = " ";
    for(auto styleClass : screen_readers.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    data += "\n ";
    return data;
}