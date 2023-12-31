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
enum SearchOption
{
    Classes = 10,
    Folders = 11,
    Focus = 12,
};
struct TemplateData {
    std::string folderName;
    std::string fileName;
    std::string messageId;
};

class StylusEdditor : public Wt::WTemplate
{
public:
    StylusEdditor(std::string templatesPath);
    ~StylusEdditor();
    std::string cleanStringStartEnd(const std::string& input);
    void setTemplate(std::string folderName, std::string fileName, std::string messageId, std::string widgetType, bool insideTemplate = false);
    
private:
    void createSearchDialog();
    void setSearchOptions(Wt::WSuggestionPopup *sp,Wt::WDialog *dialog, Wt::WLineEdit *lineEdit, SearchOption searchOption);
    void createTitleBarControls();
    std::string xml_file_path;
    void createDevApp();
    void createKeybordShortcuts();
    Wt::WTemplate* sidebar_left ;
    Wt::WTemplate* sidebar_right;
    Wt::WTemplate* menu_bar;
    Wt::WTemplate* template_view;

    Wt::WTemplate* sidebar_left_hamburger;
    Wt::WTemplate* sidebar_right_hamburger;

    ElementClassEdditor* elementClassEdditor_;
    StylusTemplatesWidget* stylus_templates_;
    ElementContent* element_contents_;

    Wt::WTemplate* edditor_temp_;
    StylusTreeView* tree_view_;
    Wt::WTextArea* edditor_classes_raw_twxtarea_;

    std::vector<TemplateData> templates_data_;
    Wt::WPushButton* prev_temp_btn_;

    std::shared_ptr<StylusState> stylusState_;
    
    void nodeSelected(tinyxml2::XMLNode* node);
    void updateDisplayElement(std::string classes, std::string content);
    
    void toggleOutline(bool on = true);
    Wt::WCheckBox* toggle_outline_checkbox;

    void saveStyles(std::string newStyles);

    bool isTemplateText(std::string text);
    
    void updateFile();
    void updateResources();
    std::string getTemplateValue(std::string templateText, std::string attribute);
    std::string changeTempateAttributeValue(std::string templateText, std::string attribute, std::string value);
    int applicationWidthClass;
    std::unique_ptr<Wt::WPushButton> createThemeSwitcher();
    std::regex temp_pattern = std::regex("\\$\\{[\\w\\-.]+[ ]?(class=\"[^\"]*\")+[ ]?(folderName=\"[^\"]*\")+[ ]?(fileName=\"[^\"]*\")+[ ]?(messageId=\"[^\"]*\")+[ ]?(widgetType=\"[^\"]*\")\\}");

};