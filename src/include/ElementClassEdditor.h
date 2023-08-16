#pragma once
#include "ElementSpacing.h"
#include "ElementSizing.h"
#include "ElementBackground.h"
#include "ElementEffects.h"
#include "ElementTransforms.h"

#include <Wt/WTemplate.h>
#include <Wt/WSignal.h>
#include <regex>

class ElementClassEdditor : public Wt::WTemplate
{
public:
    ElementClassEdditor();

    void setStyleClasses(std::string classes);
    Wt::Signal<std::string> &styleChanged() { return styleChanged_; }

    void resetStyles();
    Wt::WPushButton* spacing_btn_display;
    Wt::WPushButton* sizing_btn_display;
    Wt::WPushButton* background_btn_display;

    std::string getStyles();
private:
    std::vector<std::string> findAndRemoveMatches(std::regex regex, std::string& str);
    std::string findAndRemoveMatche(std::regex regex, std::string& str);

    ElementBackgroundWidget *backgroundWidget_;
    ElementSpacingWidget *spacingWidget_;
    ElementSizingWidget *sizingWidget_;
    ElementEffectsWidget *effectsWidget_;
    ElementTransformsWidget *transformsWidget_;

    std::string notFoundClasses = "";
    std::string backgroundClasses = "";
    std::string spacingClasses = "";
    std::string sizingClasses = "";
    std::string effectsClasses = "";
    std::string transformsClasses = "";
    
    Wt::Signal<std::string> styleChanged_;
    std::shared_ptr<Config> tailwindConfig_;

};
