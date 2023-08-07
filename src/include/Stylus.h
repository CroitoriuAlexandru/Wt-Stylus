#pragma once
#include "StylusTreeView.h"
#include "AppDev.h"
#include "ElementClassEdditor.h"
#include "StylusTemplates.h"
#include "ElementContent.h"

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

struct TemplateData {
    std::string folderName;
    std::string fileName;
    std::string messageId;
};

class StylusEdditor : public Wt::WDialog
{
public:
    StylusEdditor(std::string templatesPath);
    ~StylusEdditor();
    std::string cleanStringStartEnd(const std::string& input);
    void setTemplate(std::string folderName, std::string fileName, std::string messageId, std::string widgetType, bool insideTemplate = false);
    std::vector<std::string> getXmlFils();
    std::unique_ptr<AppDev> createDevApp();
    Wt::Signal<>& appDevChanged() { return appDevChanged_; }
private:
    std::shared_ptr<StylusState> stylusState_;
    ElementClassEdditor* elementClassEdditor_;
    StylusTemplatesWidget* stylus_templates_;
    ElementContent* element_contents_;

    Wt::WTemplate* edditor_temp_;
    StylusTreeView* tree_view_;
    Wt::WTextArea* edditor_classes_raw_twxtarea_;

    std::vector<TemplateData> templates_data_;
    Wt::WPushButton* prev_temp_btn_;

    void createTitleBarControls();
    void createTreeView();
    
    void nodeSelected(tinyxml2::XMLNode* node);
    void updateDisplayElement(std::string classes, std::string content);
    
    void toggleOutline(bool on = true);
    bool outline_selected_on = true;    

    void saveStyles(std::string newStyles);

    bool isTemplateText(std::string text);
    
    void updateFile();
    void updateResources();
    std::string getTemplateValue(std::string templateText, std::string attribute);
    std::string changeTempateAttributeValue(std::string templateText, std::string attribute, std::string value);
    int applicationWidthClass;
    std::unique_ptr<Wt::WPushButton> createThemeSwitcher();
    Wt::Signal<> appDevChanged_;
    std::regex temp_pattern = std::regex("\\$\\{[\\w\\-.]+[ ]?(class=\"[^\"]*\")+[ ]?(folderName=\"[^\"]*\")+[ ]?(fileName=\"[^\"]*\")+[ ]?(messageId=\"[^\"]*\")+[ ]?(widgetType=\"[^\"]*\")\\}");

};