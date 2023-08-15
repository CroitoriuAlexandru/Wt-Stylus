#include "include/Typography.h"

using namespace Tailwind;

Typography::Typography(std::vector<std::string> spacing_variants)
{
    // font-size
    font_family = Propriety({
        StyleClass("font-sans", "font-family: ui-sans-serif, system-ui, -apple-system, BlinkMacSystemFont, \"Segoe UI\", Roboto, \"Helvetica Neue\", Arial, \"Noto Sans\", sans-serif, \"Apple Color Emoji\", \"Segoe UI Emoji\", \"Segoe UI Symbol\", \"Noto Color Emoji\";"),
        StyleClass("font-serif", "font-family: ui-serif, Georgia, Cambria, \"Times New Roman\", Times, serif;"),
        StyleClass("font-mono", "font-family: ui-monospace, SFMono-Regular, Menlo, Monaco, Consolas, \"Liberation Mono\", \"Courier New\", monospace;")
    }, "https://tailwindcss.com/docs/font-family");

    // font-size
    font_size = Propriety({
        StyleClass("text-xs", "font-size: 0.75rem; /* 12px */ line-height: 1rem; /* 16px */"),
        StyleClass("text-sm", "font-size: 0.875rem; /* 14px */ line-height: 1.25rem; /* 20px */"),
        StyleClass("text-base", "font-size: 1rem; /* 16px */ line-height: 1.5rem; /* 24px */"),
        StyleClass("text-lg", "font-size: 1.125rem; /* 18px */ line-height: 1.75rem; /* 28px */"),
        StyleClass("text-xl", "font-size: 1.25rem; /* 20px */ line-height: 1.75rem; /* 28px */"),
        StyleClass("text-2xl", "font-size: 1.5rem; /* 24px */ line-height: 2rem; /* 32px */"),
        StyleClass("text-3xl", "font-size: 1.875rem; /* 30px */ line-height: 2.25rem; /* 36px */"),
        StyleClass("text-4xl", "font-size: 2.25rem; /* 36px */ line-height: 2.5rem; /* 40px */"),
        StyleClass("text-5xl", "font-size: 3rem; /* 48px */ line-height: 1;"),
        StyleClass("text-6xl", "font-size: 3.75rem; /* 60px */ line-height: 1;"),
        StyleClass("text-7xl", "font-size: 4.5rem; /* 72px */ line-height: 1;"),
        StyleClass("text-8xl", "font-size: 6rem; /* 96px */ line-height: 1;"),
        StyleClass("text-9xl", "font-size: 8rem; /* 128px */ line-height: 1;")
    }, "https://tailwindcss.com/docs/font-size");

    // font-smoothing
    font_smoothing = Propriety({
        StyleClass("antialiased", " -webkit-font-smoothing: antialiased; -moz-osx-font-smoothing: grayscale;"),
        StyleClass("subpixel-antialiased", "-webkit-font-smoothing: auto; -moz-osx-font-smoothing: auto;")
    }, "https://tailwindcss.com/docs/font-smoothing");

    // font-style
    font_style = Propriety({
        StyleClass("italic", "font-style: italic;"),
        StyleClass("not-italic", "font-style: normal;")
    }, "https://tailwindcss.com/docs/font-style");

    // font-weight
    font_weight = Propriety({
        StyleClass("font-thin", "font-weight: 100;"),
        StyleClass("font-extralight", "font-weight: 200;"),
        StyleClass("font-light", "font-weight: 300;"),
        StyleClass("font-normal", "font-weight: 400;"),
        StyleClass("font-medium", "font-weight: 500;"),
        StyleClass("font-semibold", "font-weight: 600;"),
        StyleClass("font-bold", "font-weight: 700;"),
        StyleClass("font-extrabold", "font-weight: 800;"),
        StyleClass("font-black", "font-weight: 900;")
    }, "https://tailwindcss.com/docs/font-weight");

    // font variant numeric
    font_variant_numeric = Propriety({
        StyleClass("normal-nums", "font-variant-numeric: normal;"),
        StyleClass("ordinal", "font-variant-numeric: ordinal;"),
        StyleClass("slashed-zero", "font-variant-numeric: slashed-zero;"),
        StyleClass("lining-nums", "font-variant-numeric: lining-nums;"),
        StyleClass("oldstyle-nums", "font-variant-numeric: oldstyle-nums;"),
        StyleClass("proportional-nums", "font-variant-numeric: proportional-nums;"),
        StyleClass("tabular-nums", "font-variant-numeric: tabular-nums;"),
        StyleClass("diagonal-fractions", "font-variant-numeric: diagonal-fractions;"),
        StyleClass("stacked-fractions", "font-variant-numeric: stacked-fractions;")
    }, "https://tailwindcss.com/docs/font-variant-numeric");

    // letter-spacing
    letter_spacing = Propriety({
        StyleClass("tracking-tighter", "letter-spacing: -0.05em;"),
    StyleClass("tracking-tight", "letter-spacing: -0.025em;"),
    StyleClass("tracking-normal", "letter-spacing: 0;"),
    StyleClass("tracking-wide", "letter-spacing: 0.025em;"),
    StyleClass("tracking-wider", "letter-spacing: 0.05em;"),
    StyleClass("tracking-widest", "letter-spacing: 0.1em;"),
    }, "https://tailwindcss.com/docs/letter-spacing");

    // line-clamp
    line_clamp = Propriety({
        StyleClass("line-clamp-1", "display: -webkit-box; -webkit-box-orient: vertical; -webkit-line-clamp: 1;"),
        StyleClass("line-clamp-2", "display: -webkit-box; -webkit-box-orient: vertical; -webkit-line-clamp: 2;"),
        StyleClass("line-clamp-3", "display: -webkit-box; -webkit-box-orient: vertical; -webkit-line-clamp: 3;"),
        StyleClass("line-clamp-4", "display: -webkit-box; -webkit-box-orient: vertical; -webkit-line-clamp: 4;"),
        StyleClass("line-clamp-5", "display: -webkit-box; -webkit-box-orient: vertical; -webkit-line-clamp: 5;"),
        StyleClass("line-clamp-6", "display: -webkit-box; -webkit-box-orient: vertical; -webkit-line-clamp: 6;"),
        StyleClass("line-clamp-none", "display: block;")
    }, "https://tailwindcss.com/docs/line-clamp");

    // list-height
    line_height = Propriety({
        StyleClass("leading-10", "line-height: 1.125rem; /* 18px */"),
        StyleClass("leading-9", "line-height: 1rem; /* 16px */"),
        StyleClass("leading-8", "line-height: 0.875rem; /* 14px */"),
        StyleClass("leading-7", "line-height: 0.75rem; /* 12px */"),
        StyleClass("leading-6", "line-height: 0.625rem; /* 10px */"),
        StyleClass("leading-5", "line-height: 0.5rem; /* 8px */"),
        StyleClass("leading-4", "line-height: 0.375rem; /* 6px */"),
        StyleClass("leading-3", "line-height: 0.25rem; /* 4px */"),
        StyleClass("leading-none", "line-height: 1;"),
        StyleClass("leading-tight", "line-height: 1.25;"),
        StyleClass("leading-snug", "line-height: 1.375;"),
        StyleClass("leading-normal", "line-height: 1.5;"),
        StyleClass("leading-relaxed", "line-height: 1.625;"),
        StyleClass("leading-loose", "line-height: 2;")
    }, "https://tailwindcss.com/docs/line-height");

    // list-style-image
    list_style_image = Propriety({
        StyleClass("list_image_none", "list-style-type: none;")
    }, "https://tailwindcss.com/docs/list-style-image");

    // list-style-position
    list_style_position = Propriety({
        StyleClass("list_inside", "list-style-position: inside;"),
        StyleClass("list_outside", "list-style-position: outside;")
    }, "https://tailwindcss.com/docs/list-style-position");

    // list-style-type
    list_style_type = Propriety({
        StyleClass("list_none", "list-style-type: none;"),
        StyleClass("list_disc", "list-style-type: disc;"),
        StyleClass("list_decimal", "list-style-type: decimal;")
    }, "https://tailwindcss.com/docs/list-style-type");

    // text align
    text_align = Propriety({
        StyleClass("text-left", "text-align: left;"),
        StyleClass("text-center", "text-align: center;"),
        StyleClass("text-right", "text-align: right;"),
        StyleClass("text-justify", "text-align: justify;"),
        StyleClass("text-start", "text-align: start;"),
        StyleClass("text-end", "text-align: end;")
    }, "https://tailwindcss.com/docs/text-align");

    // text decoration
    text_decoration = Propriety({
        StyleClass("underline", "text-decoration: underline;"),
        StyleClass("overline", "text-decoration: overline;"),
        StyleClass("line-through", "text-decoration: line-through;"),
        StyleClass("no-underline", "text-decoration: none;")
    }, "https://tailwindcss.com/docs/text-decoration");

    // text decoration style 
    text_decoration_style = Propriety({
        StyleClass("decoration-solid", "text-decoration-style: solid;"),
        StyleClass("decoration-double", "text-decoration-style: double;"),
        StyleClass("decoration-dotted", "text-decoration-style: dotted;"),
        StyleClass("decoration-dashed", "text-decoration-style: dashed;"),
        StyleClass("decoration-wavy", "text-decoration-style: wavy;")
    }, "https://tailwindcss.com/docs/text-decoration-style");

    // text decoration thikness
    text_decoration_thikness = Propriety({
        StyleClass("decoration-auto", "text-decoration-thickness: auto;"),
        StyleClass("decoration-from-font", "text-decoration-thickness: from-font;"),
        StyleClass("decoration-0", "text-decoration-thickness: 0;"),
        StyleClass("decoration-1", "text-decoration-thickness: 1;"),
        StyleClass("decoration-2", "text-decoration-thickness: 2;"),
        StyleClass("decoration-4", "text-decoration-thickness: 4;"),
        StyleClass("decoration-8", "text-decoration-thickness: 8;")
    }, "https://tailwindcss.com/docs/text-decoration-thickness");

    // text underline offset
    // StyleClass underline_offset_auto =  
    // StyleClass underline_offset_0 =     
    // StyleClass underline_offset_1 =     
    // StyleClass underline_offset_2 =     
    // StyleClass underline_offset_4 =     
    // StyleClass underline_offset_8 =     
    text_underline_offset = Propriety({
        StyleClass("underline-offset-auto", "text-underline-offset: auto;"),
        StyleClass("underline-offset-0", "text-underline-offset: 0;"),
        StyleClass("underline-offset-1", "text-underline-offset: 1;"),
        StyleClass("underline-offset-2", "text-underline-offset: 2;"),
        StyleClass("underline-offset-4", "text-underline-offset: 4;"),
        StyleClass("underline-offset-8", "text-underline-offset: 8;")
    }, "https://tailwindcss.com/docs/text-underline-offset");

    // text transform
    text_transform = Propriety({
        StyleClass("uppercase", "text-transform: uppercase;"),
        StyleClass("lowercase", "text-transform: lowercase;"),
        StyleClass("capitalize", "text-transform: capitalize;"),
        StyleClass("normal-case", "text-transform: none;")
    }, "https://tailwindcss.com/docs/text-transform");

    // text overflow
    text_overflow = Propriety({
        StyleClass("truncate", "overflow: hidden; text-overflow: ellipsis; white-space: nowrap;"),
        StyleClass("text-ellipsis", "text-overflow: ellipsis;"),
        StyleClass("text-clip", "text-overflow: clip;")
    }, "https://tailwindcss.com/docs/text-overflow");

    // text indent
    text_indent = Propriety({}, "https://tailwindcss.com/docs/text-indent");
    for(auto size : spacing_variants)
    {
        text_indent.styleClasses_.push_back(StyleClass("indent-" + size, ""));
    }

    // vertical align
    vertical_align = Propriety({
        StyleClass("align-baseline", "vertical-align: baseline;"),
        StyleClass("align-top", "vertical-align: top;"),
        StyleClass("align-middle", "vertical-align: middle;"),
        StyleClass("align-bottom", "vertical-align: bottom;"),
        StyleClass("align-text-top", "vertical-align: text-top;"),
        StyleClass("align-text-bottom", "vertical-align: text-bottom;"),
        StyleClass("align-sub", "vertical-align: sub;"),
        StyleClass("align-super", "vertical-align: super;")
    }, "https://tailwindcss.com/docs/vertical-align");

    // whitespace
    whitespace = Propriety({
        StyleClass("whitespace-normal", "white-space: normal;"),
        StyleClass("whitespace-nowrap", "white-space: nowrap;"),
        StyleClass("whitespace-pre-line", "white-space: pre-line;"),
        StyleClass("whitespace-pre-wrap", "white-space: pre-wrap;"),
        StyleClass("whitespace-pre", "white-space: pre;"),
        StyleClass("whitespace-break-spaces", "white-space: break-spaces;")
    }, "https://tailwindcss.com/docs/whitespace");

    // word break
    // StyleClass break_normal =
    // StyleClass break_words = 
    // StyleClass break_all =   
    // StyleClass break_keep =  
    word_break = Propriety({
        StyleClass("break-normal", "overflow-wrap: normal; word-break: normal;"),
        StyleClass("break-words", "overflow-wrap: break-word;"),
        StyleClass("break-all", "word-break: break-all;"),
        StyleClass("break-keep", "word-break: keep-all;")
    }, "https://tailwindcss.com/docs/word-break");

    // hyphens
    hyphens = Propriety({
        StyleClass("hyphens-none", "hyphens: none;"),
        StyleClass("hyphens-manual", "hyphens: manual;"),
        StyleClass("hyphens-auto", "hyphens: auto;")
    }, "https://tailwindcss.com/docs/hyphens");

    // content
    content = Propriety({
        StyleClass("content-none", "content: none;"),
    }, "https://tailwindcss.com/docs/content");

}

std::string Typography::FontFamilyData()
{
    std::string data = "Font Family ------------------------------------\n";
    for(auto styleClass : font_family.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Typography::FontSizeData()
{
    std::string data = "Font Size ------------------------------------\n";
    for(auto styleClass : font_size.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Typography::FontSmoothingData()
{
    std::string data = "Font Smoothing ------------------------------------\n";
    for(auto styleClass : font_smoothing.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Typography::FontStyleData()
{
    std::string data = "Font Style ------------------------------------\n";
    for(auto styleClass : font_style.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Typography::FontWeightData()
{
    std::string data = "Font Weight ------------------------------------\n";
    for(auto styleClass : font_weight.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Typography::FontVariantNumericData()
{
    std::string data = "Font Variant Numeric ------------------------------------\n";
    for(auto styleClass : font_variant_numeric.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Typography::LetterSpacingData()
{
    std::string data = "Letter Spacing ------------------------------------\n";
    for(auto styleClass : letter_spacing.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }

    return data;
}

std::string Typography::LineClampData()
{
    std::string data = "Line Clamp ------------------------------------\n";
    for(auto styleClass : line_clamp.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Typography::LineHeightData()
{
    std::string data = "Line Height ------------------------------------\n";
    for(auto styleClass : line_height.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Typography::ListStyleImageData()
{
    std::string data =  "List Style Image ------------------------------------\n";
    for(auto styleClass : list_style_image.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Typography::ListStylePositionData()
{
    std::string data = "List Style Position ------------------------------------\n";
    for(auto styleClass : list_style_position.styleClasses_)
    {
        data += styleClass.className_ + " ";
    }
    return data;
}

std::string Typography::ListStyleTypeData()
{
    std::string data = "List Style Type ------------------------------------\n";
    for(auto styleClass : list_style_type.styleClasses_)
    {
        data += styleClass.className_ + " ";

    }
    return data;
}

std::string Typography::TextAlignData()
{
    std::string data = "Text Align ------------------------------------\n";
    for(auto styleClass : text_align.styleClasses_)
    {
        data += styleClass.className_ + " ";

    }
    return data;
}

std::string Typography::TextDecorationData()
{
    std::string data = "Text Decoration ------------------------------------\n";
    for(auto styleClass : text_decoration.styleClasses_)
    {
        data += styleClass.className_ + " ";

    }
    return data;
}

std::string Typography::TextDecorationStyleData()
{
    std::string data = "Text Decoration Style ------------------------------------\n";
    for(auto styleClass : text_decoration_style.styleClasses_)
    {
        data += styleClass.className_ + " ";

    }
    return data;
}

std::string Typography::TextDecorationThiknessData()
{
    std::string data = "Text Decoration Thikness ------------------------------------\n";
    for(auto styleClass : text_decoration_thikness.styleClasses_)
    {
        data += styleClass.className_ + " ";

    }

    return data;
}

std::string Typography::TextUnderlineOffsetData()
{
    std::string data = "Text Underline Offset ------------------------------------\n";
    for(auto styleClass : text_underline_offset.styleClasses_)
    {
        data += styleClass.className_ + " ";

    }
    return data;
}

std::string Typography::TextTransformData()
{
    std::string data = "Text Transform ------------------------------------\n";
    for(auto styleClass : text_transform.styleClasses_)
    {
        data += styleClass.className_ + " ";

    }
    return data;
}

std::string Typography::TextOverflowData()
{
    std::string data = "Text Overflow ------------------------------------\n";
    for(auto styleClass : text_overflow.styleClasses_)
    {
        data += styleClass.className_ + " ";

    }
    return data;
}

std::string Typography::TextIndentData()
{
    std::string data = "Text Indent ------------------------------------\n";
    for(auto styleClass : text_indent.styleClasses_)
    {
        data += styleClass.className_ + " ";

    }
    return data;
}

std::string Typography::VerticalAlignData()
{
    std::string data = "Vertical Align ------------------------------------\n";
    for(auto styleClass : vertical_align.styleClasses_)
    {
        data += styleClass.className_ + " ";

    }
    return data;
}

std::string Typography::WhitespaceData()
{
    std::string data = "Whitespace ------------------------------------\n";
    for(auto styleClass : whitespace.styleClasses_)
    {
        data += styleClass.className_ + " ";

    }
    return data;
}

std::string Typography::WordBreakData()
{
    std::string data = "Word Break ------------------------------------\n";
    for(auto styleClass : word_break.styleClasses_)
    {
        data += styleClass.className_ + " ";

    }

    return data;
}

std::string Typography::HyphensData()
{
    std::string data = "Hyphens ------------------------------------\n";
    for(auto styleClass : hyphens.styleClasses_)
    {
        data += styleClass.className_ + " ";

    }

    return data;
}

std::string Typography::ContentData()
{
    std::string data = "Content ------------------------------------\n";
    for(auto styleClass : content.styleClasses_)
    {
        data += styleClass.className_ + " ";

    }

    return data;
}

