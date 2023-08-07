#pragma once
#include <Wt/WTree.h>
#include <Wt/WTreeNode.h>
#include <Wt/WComboBox.h>
#include <Wt/WPushButton.h>

#include <regex>
#include "tinyxml2.h"
#include <Wt/WSignal.h>

struct StylusState {
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLNode* selectedTemplate;
    tinyxml2::XMLNode* selectedElement;
    std::string filePath;
};

class TreeNode : public Wt::WTreeNode
{
public:
    TreeNode(const Wt::WString& labelText, std::unique_ptr<Wt::WIconPair> labelIcon = nullptr);
    void setTemplateNode(bool isTemplateNode);
    Wt::WPushButton* move_up_btn;
    Wt::WPushButton* move_down_btn;
    Wt::WPushButton* move_right_btn;
    Wt::WPushButton* add_sibling_after_btn;
    Wt::WPushButton* add_sibling_before_btn;
    Wt::WPushButton* add_child_first_btn;
    Wt::WPushButton* add_child_last_btn;
    Wt::WPushButton* remove_btn;
    Wt::WPushButton* open_template_btn;
private:
};


class StylusTreeView : public Wt::WTree
{
public:
    StylusTreeView(std::shared_ptr<StylusState> stylusState);
    ~StylusTreeView();
    Wt::WTreeNode* selectedTreeNode;
    bool selectedNodeFound;
    
    // Wt::Signal<>& templateModified() { return templateModified_; }
    Wt::Signal<tinyxml2::XMLNode*>& selectionChanged() { return selectionChanged_; }
    Wt::Signal<std::string, std::string, std::string, std::string, bool>& openTemplate() { return openTemplate_; }

    void createTree();
    std::unique_ptr<TreeNode> createNodeTree(tinyxml2::XMLElement* element);
    std::unique_ptr<TreeNode> createTemplateNode(tinyxml2::XMLNode* textNode);

    // \$\{[\w\-.]+[ ]?(class=\"[^\"]*\")+[ ]?(folderName=\"[^\"]*\")+[ ]?(fileName=\"[^\"]*\")+[ ]?(messageId=\"[^\"]*\")+[ ]?(widgetType=\"[^\"]*\")\}
    std::regex template_regexp = std::regex("\\$\\{[\\w\\-.]+[ ]?(class=\"[^\"]*\")+[ ]?(folderName=\"[^\"]*\")+[ ]?(fileName=\"[^\"]*\")+[ ]?(messageId=\"[^\"]*\")+[ ]?(widgetType=\"[^\"]*\")\\}");
private:
    std::shared_ptr<StylusState> stylusState_;


    void moveElementUp(tinyxml2::XMLElement* element);
    void moveElementDown(tinyxml2::XMLElement* element);
    void moveElementRight(tinyxml2::XMLElement* element);
    void addSiblingElementAfter(tinyxml2::XMLElement* element, tinyxml2::XMLElement* newElement = nullptr);
    void addSiblingElementBefore(tinyxml2::XMLElement* element, tinyxml2::XMLElement* newElement = nullptr);
    void addChildElementFirst(tinyxml2::XMLElement* element, tinyxml2::XMLElement* newElement = nullptr);
    void addChildElementLast(tinyxml2::XMLElement* element, tinyxml2::XMLElement* newElement = nullptr);
    void removeElement(tinyxml2::XMLElement* element);

    // Wt::Signal<> templateModified_;
    Wt::Signal<tinyxml2::XMLNode*> selectionChanged_;
    // folderName, fileName, messageId, widgetType
    Wt::Signal<std::string, std::string, std::string, std::string, bool> openTemplate_;
};