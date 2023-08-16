#include "include/ElementClassEdditor.h"
#include "include/TailwindRegexp.h"
#include <Wt/WApplication.h>
#include <Wt/WAnimation.h>

std::vector<std::string> ElementClassEdditor::findAndRemoveMatches(std::regex regex, std::string& str) {
    
    std::regex_iterator<std::string::iterator> it(str.begin(), str.end(), regex);
    std::regex_iterator<std::string::iterator> end;
    std::string result = "";

    std::vector<std::string> matches;

    size_t lastPos = 0;
    while (it != end) {
        result += str.substr(lastPos, it->position() - lastPos);
        matches.push_back(it->str()); // Store deleted value in vector
        lastPos = it->position() + it->length();
        ++it;
    }
    // remove padding classes from classes string
    str = result + str.substr(lastPos, str.length() - lastPos);
    return matches;
}

std::string ElementClassEdditor::findAndRemoveMatche(std::regex regex, std::string& str) {
        
        std::regex_iterator<std::string::iterator> it(str.begin(), str.end(), regex);
        std::regex_iterator<std::string::iterator> end;
        std::string result = "";
    
        std::string match = "";
    
        size_t lastPos = 0;
        while (it != end) {
            result += str.substr(lastPos, it->position() - lastPos);
            match = it->str(); // Store deleted value in vector
            lastPos = it->position() + it->length();
            ++it;
        }
        // remove padding classes from classes string
        str = result + str.substr(lastPos, str.length() - lastPos);
        // clean start whitespace from match
        match = std::regex_replace(match, std::regex("^\\s+"), "");
        return match;
}


ElementClassEdditor::ElementClassEdditor()
    : WTemplate(tr("stylus-element-edditor"))
{
    tailwindConfig_ = std::make_shared<Config>();

    effectsWidget_ = bindWidget("effects-controls", std::make_unique<ElementEffectsWidget>(tailwindConfig_));
    spacingWidget_ = bindWidget("spacing-controls", std::make_unique<ElementSpacingWidget>(tailwindConfig_));
    sizingWidget_ = bindWidget("sizing-controls", std::make_unique<ElementSizingWidget>(tailwindConfig_));
    backgroundWidget_ = bindWidget("background-controls", std::make_unique<ElementBackgroundWidget>(tailwindConfig_));
    transformsWidget_ = bindWidget("transforms-controls", std::make_unique<ElementTransformsWidget>(tailwindConfig_));

    spacingWidget_->collapse();
    sizingWidget_->collapse();
    backgroundWidget_->collapse();
    effectsWidget_->collapse();

    transformsWidget_->styleChanged().connect(this, [=](){
        std::string newStyles = notFoundClasses + " ";
        transformsClasses = transformsWidget_->getStyles();
        if(sizingClasses != ""){ newStyles += sizingClasses + " "; }
        if(spacingClasses != ""){ newStyles += spacingClasses + " "; }
        if(backgroundClasses != ""){ newStyles += backgroundClasses + " "; }
        if(effectsClasses != ""){ newStyles += effectsClasses + " "; }
        if(transformsClasses != ""){ newStyles += transformsClasses + " "; }
        styleChanged_.emit(newStyles);
    });

    effectsWidget_->styleChanged().connect(this, [=](){
        std::string newStyles = notFoundClasses + " ";
        effectsClasses = effectsWidget_->getStyles();
        if(sizingClasses != ""){ newStyles += sizingClasses + " "; }
        if(spacingClasses != ""){ newStyles += spacingClasses + " "; }
        if(backgroundClasses != ""){ newStyles += backgroundClasses + " "; }
        if(effectsClasses != ""){ newStyles += effectsClasses + " "; }
        if(transformsClasses != ""){ newStyles += transformsClasses + " "; }
        styleChanged_.emit(newStyles);
    });

    spacingWidget_->styleChanged().connect(this, [=](){
        std::string newStyles = notFoundClasses + " ";
        spacingClasses = spacingWidget_->getStyles();
        if(sizingClasses != ""){ newStyles += sizingClasses + " "; }
        if(spacingClasses != ""){ newStyles += spacingClasses + " "; }
        if(backgroundClasses != ""){ newStyles += backgroundClasses + " "; }
        if(effectsClasses != ""){ newStyles += effectsClasses + " "; }
        if(transformsClasses != ""){ newStyles += transformsClasses + " "; }
        styleChanged_.emit(newStyles);
    });

    sizingWidget_->styleChanged().connect(this, [=](){
        std::string newStyles = notFoundClasses + " ";
        sizingClasses = sizingWidget_->getStyles();
        if(sizingClasses != ""){ newStyles += sizingClasses + " "; }
        if(spacingClasses != ""){ newStyles += spacingClasses + " "; }
        if(backgroundClasses != ""){ newStyles += backgroundClasses + " "; }
        if(effectsClasses != ""){ newStyles += effectsClasses + " "; }
        if(transformsClasses != ""){ newStyles += transformsClasses + " "; }
        styleChanged_.emit(newStyles);
    });

    backgroundWidget_->styleChanged().connect(this, [=](){
        std::string newStyles = notFoundClasses + " ";
        backgroundClasses = backgroundWidget_->getStyles();
        if(sizingClasses != ""){ newStyles += sizingClasses + " "; }
        if(spacingClasses != ""){ newStyles += spacingClasses + " "; }
        if(backgroundClasses != ""){ newStyles += backgroundClasses + " "; }
        if(effectsClasses != ""){ newStyles += effectsClasses + " "; }
        if(transformsClasses != ""){ newStyles += transformsClasses + " "; }
        styleChanged_.emit(newStyles);
    });

}

void ElementClassEdditor::setStyleClasses(std::string classes)
{
    auto save = classes;
    resetStyles();
    std::cout << "\n\n classes : " << classes << "\n\n";
    
    TransformsData transforms;
    transforms.scale = findAndRemoveMatches(tailwindConfig_->transforms.scale_regex, classes);
    transforms.rotate = findAndRemoveMatche(tailwindConfig_->transforms.rotate_regex, classes);
    transforms.translate = findAndRemoveMatches(tailwindConfig_->transforms.translate_regex, classes);
    transforms.skew = findAndRemoveMatches(tailwindConfig_->transforms.skew_regex, classes);
    transforms.transform_origin = findAndRemoveMatche(tailwindConfig_->transforms.origin_regex, classes);

    EffectsData effects;
    effects.boxShadow = findAndRemoveMatche(tailwindConfig_->effects.box_shadow_regex, classes);
    if(effects.boxShadow.find("shadow-inner") != std::string::npos){
        effects.boxShadowInner = true;
    }
    effects.opacity = findAndRemoveMatche(tailwindConfig_->effects.opacity_regex, classes);
    effects.boxShadowColor = findAndRemoveMatche(tailwindConfig_->effects.box_shadow_color_regex, classes);
    effects.mixBlendMode = findAndRemoveMatche(tailwindConfig_->effects.mix_blend_mode_regex, classes);
    effects.backgroundBlendMode = findAndRemoveMatche(tailwindConfig_->effects.bg_blend_mode_regex, classes);


    BackgroundData bgData;
    bgData.bg_image = findAndRemoveMatche(tailwindConfig_->backgrounds.background_image_regex, classes);
    if(bgData.bg_image != ""){
        bgData.bg_color_class = findAndRemoveMatche(tailwindConfig_->backgrounds.background_color_from_regex, classes);
        bgData.bg_color_from_step = findAndRemoveMatche(tailwindConfig_->backgrounds.background_color_from_step, classes);
        bgData.bg_color_via = findAndRemoveMatche(tailwindConfig_->backgrounds.background_color_via_regex, classes);
        bgData.bg_color_via_step = findAndRemoveMatche(tailwindConfig_->backgrounds.background_color_via_step, classes);
        bgData.bg_color_to = findAndRemoveMatche(tailwindConfig_->backgrounds.background_color_to_regex, classes);
        bgData.bg_color_to_step = findAndRemoveMatche(tailwindConfig_->backgrounds.background_color_to_step, classes);
    }else {
        bgData.bg_color_class = findAndRemoveMatche(tailwindConfig_->backgrounds.background_color_regexp, classes);
    }

    bgData.bg_attachment = findAndRemoveMatche(tailwindConfig_->backgrounds.background_attachment_regex, classes);
    bgData.bg_clip = findAndRemoveMatche(tailwindConfig_->backgrounds.background_clip_regex, classes);
    bgData.bg_origin = findAndRemoveMatche(tailwindConfig_->backgrounds.background_origin_regex, classes);
    bgData.bg_position = findAndRemoveMatche(tailwindConfig_->backgrounds.background_position_regex, classes);
    bgData.bg_repeat = findAndRemoveMatche(tailwindConfig_->backgrounds.background_repeat_regex, classes);
    bgData.bg_size = findAndRemoveMatche(tailwindConfig_->backgrounds.background_size_regex, classes);

    SpacingData spacing;
    spacing.padding = findAndRemoveMatches(tailwindConfig_->spacing.padding_regexp, classes);
    spacing.margin = findAndRemoveMatches(tailwindConfig_->spacing.margin_regexp, classes);
    spacing.space = findAndRemoveMatches(tailwindConfig_->spacing.space_regexp, classes);

    // create vector of classes for sizing
    SizingData sizing;
    sizing.minWidth = findAndRemoveMatche(tailwindConfig_->sizing.min_width_regex, classes);
    sizing.maxWidth = findAndRemoveMatche(tailwindConfig_->sizing.max_width_regex, classes);
    sizing.minHeight = findAndRemoveMatche(tailwindConfig_->sizing.min_height_regex, classes);
    sizing.maxHeight = findAndRemoveMatche(tailwindConfig_->sizing.max_height_regex, classes);
    sizing.width = findAndRemoveMatche(tailwindConfig_->sizing.width_regexp, classes);
    sizing.height = findAndRemoveMatche(tailwindConfig_->sizing.height_regexp, classes);

{

    // std::cout << "\n sizing width : <" << sizing.width << ">\n";
    // std::cout << "\n sizing min width : <" << sizing.minWidth << ">\n";
    // std::cout << "\n sizing max width : <" << sizing.maxWidth << ">\n";
    // std::cout << "\n sizing height : <" << sizing.height << ">\n";
    // std::cout << "\n sizing min height : <" << sizing.minHeight << ">\n";
    // std::cout << "\n sizing max height : <" << sizing.maxHeight << ">\n";

    for(auto& item : spacing.padding){
        std::cout << "padding item : <" << item << ">\n";
    }
    for(auto& item : spacing.margin){
        std::cout << "margin item : <" << item << ">\n";
    }
    for(auto& item : spacing.space){
        std::cout << "space item : <" << item << ">\n";
    }

    // std::cout << "background classes :\n";
    
    // std::cout << bgData.bg_attachment << "\n";
    // std::cout << bgData.bg_clip << "\n";
    // std::cout << bgData.bg_origin << "\n";
    // std::cout << bgData.bg_position << "\n";
    // std::cout << bgData.bg_repeat << "\n";
    // std::cout << bgData.bg_size << "\n";
    // std::cout << "<" << bgData.bg_image << ">\n";
   
    // std::cout << "<" << bgData.bg_color_class << ">\n";
    // std::cout << "<" << bgData.bg_color_via << ">\n";
    // std::cout << "<" << bgData.bg_color_to << ">\n";
    // std::cout << "<" << bgData.bg_color_from_step << ">\n";
    // std::cout << "<" << bgData.bg_color_via_step << ">\n";
    // std::cout << "<" << bgData.bg_color_to_step << ">\n";

    std::cout << "\n\n"; 
    // resetStyles();
}
    
    spacingWidget_->setClasses(spacing);
    sizingWidget_->setClasses(sizing);
    backgroundWidget_->setClasses(bgData);
    effectsWidget_->setClasses(effects);
    transformsWidget_->setClasses(transforms);

    spacingClasses = spacingWidget_->getStyles();
    sizingClasses = sizingWidget_->getStyles();
    backgroundClasses = backgroundWidget_->getStyles();
    effectsClasses = effectsWidget_->getStyles();
    transformsClasses = transformsWidget_->getStyles();

    notFoundClasses = std::regex_replace(classes, std::regex("^\\s+"), "");
    // std::cout << " effects box shadow <" << effects.boxShadow << ">\n";
    // std::cout << " effects box shadow inset <" << effects.boxShadowInner << ">\n";
    // std::cout << " effects opacity <" << effects.opacity << ">\n";
    // std::cout << " effects box shadow color <" << effects.boxShadowColor << ">\n";
    // std::cout << " effects mix blend mode <" << effects.mixBlendMode << ">\n";
    // std::cout << " effects background blend mode <" << effects.backgroundBlendMode << ">\n";
    // std::cout << "\n\n\n\n";
    std::cout << "\n\n classes from Element Class Edditor not found classes :" << notFoundClasses << "\n\n";

}

std::string ElementClassEdditor::getStyles()
{
    std::string styles = "";
    styles += backgroundWidget_->getStyles() + " ";
    styles += sizingWidget_->getStyles() + " ";
    styles += spacingWidget_->getStyles() + " ";
    styles += effectsWidget_->getStyles() + " ";
    styles += transformsWidget_->getStyles() + " ";
    styles += notFoundClasses;
    return styles;
}

void ElementClassEdditor::resetStyles()
{
    backgroundWidget_->resetStyles();
    sizingWidget_->resetStyles();
    spacingWidget_->resetStyles();
    effectsWidget_->resetStyles();
    transformsWidget_->resetStyles();
}
