#pragma once
#include "StylusTreeView.h"
#include "AppDev.h"
#include "ElementClassEdditor.h"
#include "StylusTemplates.h"
#include "VariableConfigurationWidget.h"

#include <Wt/WTextArea.h>
#include <Wt/WLineEdit.h>
#include <Wt/WString.h>
#include <Wt/WTreeNode.h>
#include <Wt/WTemplate.h>
#include "tinyxml2.h"
#include <Wt/WDialog.h>
#include <fstream>
#include <iostream>
#include <Wt/WStackedWidget.h>
#include <Wt/WCheckBox.h>

class StylusEdditor : public Wt::WDialog
{
public:
    StylusEdditor(std::string templatesPath);
    ~StylusEdditor();
    std::string cleanStringStartEnd(const std::string& input);
    void setTemplate(std::string folderName, std::string fileName, std::string messageId, std::string widgetType);
    std::vector<std::string> getXmlFils();
    std::unique_ptr<AppDev> createDevApp();
    Wt::Signal<>& appDevChanged() { return appDevChanged_; }
private:
    std::shared_ptr<StylusState> stylusState_;
    ElementClassEdditor* elementClassEdditor_;
    StylusTemplatesWidget* stylus_templates_;

    // this holds the textarea and the variable configuration widget
    Wt::WContainerWidget* element_content_;
    VariableConfigurationWidget* element_content_variable_configuration_;
    void changeSelectedText(std::string variableText);
    void createDialogVariableToText(std::string text, bool toText);
    Wt::WTextArea* element_content_textarea_;
    
    Wt::WCheckBox* toggle_variable_content_;

    Wt::WTemplate* edditor_temp_;



    void createTitleBarControls();
    void createTreeView();
    
    void nodeSelected(tinyxml2::XMLNode* node);
    void updateDisplayElement(std::string classes, std::string content);
    
    void toggleOutline(bool on = true);
    bool outline_selected_on = true;    

    void saveStyles(std::string newStyles);

    void updateFile();
    void updateResources();
    void dialogResized(int width, int height);
    int applicationWidthClass;
    std::unique_ptr<Wt::WPushButton> createThemeSwitcher();
    Wt::Signal<> appDevChanged_;
    std::regex temp_pattern = std::regex("\\$\\{[\\w\\-.]+[ ]?(class=\"[^\"]*\")+[ ]?(folderName=\"[^\"]*\")+[ ]?(fileName=\"[^\"]*\")+[ ]?(messageId=\"[^\"]*\")+[ ]?(widgetType=\"[^\"]*\")\\}");

};