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


    spacingWidget_ = bindWidget("spacing-controls", std::make_unique<ElementSpacingWidget>());
    sizingWidget_ = bindWidget("sizing-controls", std::make_unique<ElementSizingWidget>());
    backgroundWidget_ = bindWidget("background-controls", std::make_unique<ElementBackgroundWidget>());

    spacingWidget_->addStyleClass("w-[300px]");
    sizingWidget_->addStyleClass("w-[300px]");
    backgroundWidget_->addStyleClass("w-[300px]");


    spacingWidget_->styleChanged().connect(this, [=](){
        std::string newStyles = notFoundClasses + " ";
        spacingClasses = spacingWidget_->getStyles();
        newStyles += backgroundClasses + " ";
        newStyles += sizingClasses + " ";
        newStyles += spacingClasses + " ";
        styleChanged_.emit(newStyles); 
    });

    sizingWidget_->styleChanged().connect(this, [=](){
        std::string newStyles = notFoundClasses + " ";
        sizingClasses = sizingWidget_->getStyles();
        newStyles += backgroundClasses + " ";
        newStyles += sizingClasses + " ";
        newStyles += spacingClasses + " ";
        styleChanged_.emit(newStyles);
    });

    backgroundWidget_->styleChanged().connect(this, [=](){
        std::string newStyles = notFoundClasses + " ";
        backgroundClasses = backgroundWidget_->getStyles();
        newStyles += backgroundClasses + " ";
        newStyles += sizingClasses + " ";
        newStyles += spacingClasses + " ";
        styleChanged_.emit(newStyles);
    });

}

void ElementClassEdditor::setStyleClasses(std::string classes)
{
    // clean any multiple whitespaces from the string
    // classes = std::regex_replace(classes, std::regex("\\s+"), " ");
    // std::cout << "\n\n classes from Element Class Edditor :" << classes << "\n\n";
    // create vector of classes for spacing
        // create vector of classes for background
    auto save = classes;
    resetStyles();

    // std::cout << "\n\n\n before background removal - <" << classes << ">\n";
    BackgroundData bgData;
    bgData.bg_image = findAndRemoveMatche(background_image_regex, classes);
    if(bgData.bg_image != ""){
        bgData.bg_color_class = findAndRemoveMatche(background_color_from_regex, classes);
        // std::cout << "classes before-from-step: <" << classes << ">\n";
        bgData.bg_color_from_step = findAndRemoveMatche(background_color_from_step, classes);
        // std::cout << "classes after-from-step: <" << classes << ">\n";
        bgData.bg_color_via = findAndRemoveMatche(background_color_via_regex, classes);
        bgData.bg_color_via_step = findAndRemoveMatche(background_color_via_step, classes);
        bgData.bg_color_to = findAndRemoveMatche(background_color_to_regex, classes);
        bgData.bg_color_to_step = findAndRemoveMatche(background_color_to_step, classes);
    }else {
        bgData.bg_color_class = findAndRemoveMatche(background_color_regexp, classes);
    }
    bgData.bg_attachment = findAndRemoveMatche(background_attachment_regex, classes);
    bgData.bg_clip = findAndRemoveMatche(background_clip_regex, classes);
    bgData.bg_origin = findAndRemoveMatche(background_origin_regex, classes);
    bgData.bg_position = findAndRemoveMatche(background_position_regex, classes);
    bgData.bg_repeat = findAndRemoveMatche(background_repeat_regex, classes);
    bgData.bg_size = findAndRemoveMatche(background_size_regex, classes);


    // std::cout << "\n\n\n before spacing removal - <" << classes << ">\n";

    SpacingData spacing;
    spacing.padding = findAndRemoveMatches(padding_regexp, classes);
    spacing.margin = findAndRemoveMatches(margin_regexp, classes);
    spacing.space = findAndRemoveMatches(space_regexp, classes);

    // create vector of classes for sizing
    SizingData sizing;
    sizing.width = findAndRemoveMatche(width_regexp, classes);
    sizing.minWidth = findAndRemoveMatche(minWidth_regex, classes);
    sizing.maxWidth = findAndRemoveMatche(maxWidth_regex, classes);
    sizing.height = findAndRemoveMatche(height_regexp, classes);
    sizing.minHeight = findAndRemoveMatche(minHeight_regex, classes);
    sizing.maxHeight = findAndRemoveMatche(maxHeight_regex, classes);


    std::cout << "\n sizing width : <" << sizing.width << ">\n";
    std::cout << "\n sizing min width : <" << sizing.minWidth << ">\n";
    std::cout << "\n sizing max width : <" << sizing.maxWidth << ">\n";
    std::cout << "\n sizing height : <" << sizing.height << ">\n";
    std::cout << "\n sizing min height : <" << sizing.minHeight << ">\n";
    std::cout << "\n sizing max height : <" << sizing.maxHeight << ">\n";
    

    // bool spacing_has
    

    // remove whitespace from start of classes string and store it in notFoundClasses
    // std::cout << "\n\n classes from Element Class Edditor not found classes :" << notFoundClasses << "\n\n";
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



    // std::cout << "\n\n"; 
    // resetStyles();
    
    spacingWidget_->setClasses(spacing);
    sizingWidget_->setClasses(sizing);
    backgroundWidget_->setClasses(bgData);

    spacingClasses = spacingWidget_->getStyles();
    sizingClasses = sizingWidget_->getStyles();
    backgroundClasses = backgroundWidget_->getStyles();

    notFoundClasses = std::regex_replace(classes, std::regex("^\\s+"), "");


}

std::string ElementClassEdditor::getStyles()
{
    std::string styles = "";
    styles += backgroundWidget_->getStyles() + " ";
    styles += sizingWidget_->getStyles() + " ";
    styles += spacingWidget_->getStyles() + " ";
    styles += notFoundClasses;
    return styles;
}

void ElementClassEdditor::resetStyles()
{
    backgroundWidget_->resetStyles();
    sizingWidget_->resetStyles();
    spacingWidget_->resetStyles();
}
