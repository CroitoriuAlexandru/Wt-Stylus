#pragma once
#include "ElementFlexAndGrid.h"
#include "ElementSpacing.h"
#include "ElementSizing.h"
#include "ElementBackground.h"
#include "ElementLayout.h"

#include <Wt/WTemplate.h>
#include <Wt/WSignal.h>
#include <regex>
#include <boost/regex.hpp>

class ElementClassEdditor : public Wt::WTemplate
{
public:
    ElementClassEdditor();

    void setStyleClasses(std::string classes);
    Wt::Signal<std::string> &styleChanged() { return styleChanged_; }

    void resetStyles();

    std::shared_ptr<Config> tailwindConfig_;

    std::string getStyles();

    ElementFlexAndGridWidget *flexAndGridWidget_;
    ElementBackgroundWidget *backgroundWidget_;
    ElementSpacingWidget *spacingWidget_;
    ElementSizingWidget *sizingWidget_;
    ElementLayoutWidget *layoutWidget_;

private:
    std::vector<std::string> findAndRemoveMatches(std::regex regex, std::string& str);
    std::vector<std::string> findAndRemoveMatches(boost::regex regex, std::string& str);
    std::string findAndRemoveMatche(std::regex regex, std::string& str);
    std::string findAndRemoveMatche(boost::regex regex, std::string& str);

    std::string notFoundClasses = "";
    std::string flexAndGridClasses = "";
    std::string backgroundClasses = "";
    std::string spacingClasses = "";
    std::string sizingClasses = "";
    std::string layoutClasses = "";
    
    Wt::Signal<std::string> styleChanged_;

};
