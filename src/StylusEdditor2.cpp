#include "include/StylusEdditor2.h"
#include <Wt/WTree.h>
#include <Wt/WApplication.h>
#include <Wt/WTemplate.h>
#include <Wt/WTreeNode.h>
#include <iostream>
#include <Wt/WCheckBox.h>
#include <Wt/WPushButton.h>

void removeTextBetweenElements(tinyxml2::XMLNode* node) {
    if (node == nullptr) {
        return;
    }

    tinyxml2::XMLNode* child = node->FirstChild();
    while (child != nullptr) {
        if (child->ToElement() != nullptr) {
            // Recursively process child elements
            removeTextBetweenElements(child);

            // Add class and text value if they don't exist
            tinyxml2::XMLElement* element = child->ToElement();
            if (element->Attribute("class") == nullptr) {
                element->SetAttribute("class", "");
            }
            if (element->GetText() == nullptr) {
                element->SetText("");
            }

            // Add content if the element is not self-closing
            if (!element->NoChildren()) {
                tinyxml2::XMLNode* content = element->FirstChild();
                if (content == nullptr) {
                    element->InsertFirstChild(element->GetDocument()->NewText(""));
                }
            }
        } else if (child->ToText() != nullptr) {
            // Remove the text node if it's not inside an element
            tinyxml2::XMLNode* parent = child->Parent();
            if (parent != nullptr && parent->ToElement() == nullptr) {
                parent->DeleteChild(child);
            }
        }
        child = child->NextSibling();
    }
}

StylusEdditor2::StylusEdditor2(std::string fileName, std::string templateName, Wt::WTemplate* parent_template)
{
	applicationWidthClass = 250;
	setStyleClass("min-w-fit w-[240px] bg-neutral-700");
	setMinimumSize(300, Wt::WLength(100, Wt::LengthUnit::ViewportHeight));
	setMaximumSize(Wt::WLength(500, Wt::LengthUnit::Pixel), Wt::WLength(100,Wt::LengthUnit::ViewportHeight));
	setThemeStyleEnabled(false);
	setOffsets(0, Wt::Side::Top | Wt::Side::Right | Wt::Side::Bottom);
	setOffsets(Wt::WLength::Auto, Wt::Side::Left);
	Wt::WApplication::instance()->root()->toggleStyleClass("mr-[" + std::to_string(applicationWidthClass) + "px]", true, true);
	// resized().connect(this, &StylusEdditor2::dialogResized);

    sourcePath_ += fileName;
    templateName_ = templateName;

	// rejectWhenEscapePressed();
	setModal(false);
	setMovable(false);
	setResizable(true);
	setTitleBarEnabled(false);

	// titleBar()->clear();
	treeview_temp_ = contents()->addWidget(std::make_unique<Wt::WTemplate>(tr("stylus2.edditor")));
	elementClassEdditor_ = treeview_temp_->bindWidget("stylus2.element.edditor", std::make_unique<ElementClassEdditor>());
	element_content_textarea_ = treeview_temp_->bindWidget("stylus2.element.content", std::make_unique<Wt::WTextArea>());
	element_content_textarea_->setStyleClass("bg-neutral-900 text-neutral-100 rounded-md");
	titleBar()->setStyleClass("!p-0");
	element_content_textarea_->enterPressed().connect(this, [=](){
		stylusState_->selectedElement->ToElement()->SetText(element_content_textarea_->text().toUTF8().c_str());
		updateFile();
		updateView();
	});
	
	parseMessageAndDoc();
	createTitleBarControls();
    createDialogContent();
	createDialogTreeView();
	
	updateFile();
	updateView();
	
	setHidden(false, Wt::WAnimation(Wt::AnimationEffect::SlideInFromRight, Wt::TimingFunction::Linear, 350));


}

void StylusEdditor2::setTemplate(std::string fileName, std::string templateName)
{
	sourcePath_ = "resources/xml/" + fileName;
	templateName_ = templateName;
	parseMessageAndDoc();
	createDialogTreeView();
	updateFile();
	updateView();
}

void StylusEdditor2::dialogResized(int width, int height)
{
	Wt::WApplication::instance()->root()->removeStyleClass("ml-[" + std::to_string(applicationWidthClass) + "px]");
	if(width > 500) width = 500;
	applicationWidthClass = width + 10;
	Wt::WApplication::instance()->root()->toggleStyleClass("ml-[" + std::to_string(applicationWidthClass) + "px]", true, true);
}


// get the correct message from the xml file and template id (message id)
void StylusEdditor2::parseMessageAndDoc()
{
	// std::cout << "\n StylusEdditor2::parseMessageAndDoc with path " << sourcePath_ << "\n";
	stylusState_ = std::make_shared<StylusState>();
	auto result = stylusState_->doc.LoadFile(sourcePath_.toUTF8().c_str());
	if(result != tinyxml2::XML_SUCCESS){
		std::cout << "\n StylusEdditor2::parseMessageAndDoc error opening xml file --- ";
		std::cout << " file path: " << sourcePath_.toUTF8() << "\n";
		return;
	}
	tinyxml2::XMLElement* root = stylusState_->doc.RootElement();
	if(!root) {
		std::cout << "\n\n StylusEdditor2::parseMessageAndDoc error getting <messages> element \n\n";
		return;
	}
	stylusState_->selectedTemplate = root->FirstChildElement("message");
	while(stylusState_->selectedTemplate->ToElement()->Attribute("id") != templateName_.toUTF8()){
		stylusState_->selectedTemplate = stylusState_->selectedTemplate->NextSiblingElement("message");
	}
	removeTextBetweenElements(stylusState_->selectedTemplate);
}

StylusEdditor2::~StylusEdditor2()
{
	toggleOutline(false);
}

void StylusEdditor2::createTitleBarControls()
{
	auto move_left_btn = treeview_temp_->bindWidget("move-left-btn", std::make_unique<Wt::WPushButton>());
	auto move_right_btn = treeview_temp_->bindWidget("move-right-btn", std::make_unique<Wt::WPushButton>());
	auto theme_switcher_btn = treeview_temp_->bindWidget("theme-switcher-btn", createThemeSwitcher());
	auto refresh_btn = treeview_temp_->bindWidget("refresh-btn", std::make_unique<Wt::WPushButton>());

	move_left_btn->setDisabled(true);

	move_left_btn->clicked().connect(this, [=](){
		move_left_btn->setDisabled(true);
		move_right_btn->setDisabled(false);
		setOffsets(0, Wt::Side::Top | Wt::Side::Left | Wt::Side::Bottom);
		setOffsets(Wt::WLength::Auto, Wt::Side::Right);
		Wt::WApplication::instance()->root()->toggleStyleClass("ml-[" + std::to_string(applicationWidthClass) + "px]", true, true);
		Wt::WApplication::instance()->root()->toggleStyleClass("mr-[" + std::to_string(applicationWidthClass) + "px]", false, true);
	});

	move_right_btn->clicked().connect(this, [=](){
		move_left_btn->setDisabled(false);
		move_right_btn->setDisabled(true);
		setOffsets(0, Wt::Side::Top | Wt::Side::Right | Wt::Side::Bottom);
		setOffsets(Wt::WLength::Auto, Wt::Side::Left);
		// Wt::WApplication::instance()->root()->toggleStyleClass(applicationWidthClass, false, true);
		Wt::WApplication::instance()->root()->toggleStyleClass("mr-[" + std::to_string(applicationWidthClass) + "px]", true, true);
		Wt::WApplication::instance()->root()->toggleStyleClass("ml-[" + std::to_string(applicationWidthClass) + "px]", false, true);
	});

	refresh_btn->clicked().connect(this, [=](){
		updateFile();
		updateView();
	});

}

void StylusEdditor2::createDialogTreeView()
{
	// std::cout << "\nStylusEdditor2 --- createDialogTreeView got called \n";
	auto treeView = treeview_temp_->bindWidget("tree-view", std::make_unique<StylusTreeView>(stylusState_));
	treeView->templateModified().connect(this, [=](){
		updateFile();
		updateView();
		// treeView->createTree();
		createDialogTreeView();
	});
	treeView->selectionChanged().connect(this, &StylusEdditor2::nodeSelected);
	treeView->templateNodeSelected().connect(this, &StylusEdditor2::tempNodeSelected);
	treeView->openTemplate().connect(this, &StylusEdditor2::setTemplate);
	treeView->createTree();
}

void StylusEdditor2::createDialogContent()
{
	 elementClassEdditor_->styleChanged().connect(this, &StylusEdditor2::saveStyles);

}

void StylusEdditor2::nodeSelected(tinyxml2::XMLNode* node)
{
	if(stylusState_->templateSelected)
	{
		std::cout << "\nStylusEdditor2::nodeSelected --- templateSelected = FALSE \n";
		return;
	}
	// std::cout << "\nStylusEdditor2::nodeSelected ";
	if(outline_selected_on){
		toggleOutline(false);
		stylusState_->selectedElement = node->ToElement();
		toggleOutline(true);
		updateFile();
		updateView();
	}else {
		stylusState_->selectedElement = node->ToElement();
	}
	auto elem_classes = cleanStringStartEnd(stylusState_->selectedElement->ToElement()->Attribute("class"));
	auto elem_content = stylusState_->selectedElement->ToElement()->GetText();

	updateDisplayElement(elem_classes, elem_content);
}

void StylusEdditor2::tempNodeSelected(tinyxml2::XMLNode* node)
{
	if(!stylusState_->templateSelected)
	{
		std::cout << "\nStylusEdditor2::tempNodeSelected --- templateSelected = TRUE \n";
		return;
	}
	// std::cout << "\nStylusEdditor2::tempNodeSelected ";
	std::string tempString = node->Value();
	auto startString = "${";
	toggleOutline(false);
	// tempString = ${mamaie class=""}
	auto variableName = tempString.substr(2, tempString.find(" ")-2);
	auto classes = tempString.substr(tempString.find("class=")+7);
	// remove "} from end of string
	classes = classes.substr(0, classes.size()-2);

	auto tempUpdated = startString + variableName + " class=\"? " + classes + "\"}";
	std::cout << "\n\n tempUpdated: " << tempUpdated << "\n\n";
	node->SetValue(tempUpdated.c_str());
	// std::cout << "\n\n tempNodeSelected: " << tempString << "\n\n";
	// std::cout << "\n\n variableName: " << variableName << "\n\n";
	// std::cout << "\n\n styleClasses: " << classes << "\n\n";
	// stylusState_->selectedElement = node;

	updateFile();
	updateView();
	updateDisplayElement(classes, variableName);
	updateView();
	updateFile();
	updateView();
}


void StylusEdditor2::toggleOutline(bool on)
{
	// std::cout << "\nStylusEdditor2 --- toggleOutline got called \n";
	if(!stylusState_->selectedElement){
		std::cout << "\n\n StylusEdditor2::toggleOutline --- error getting selected element \n\n";
		return;
	}
	std::string currentStyles = cleanStringStartEnd(stylusState_->selectedElement->ToElement()->Attribute("class"));

	if(on){
		currentStyles = "? " + currentStyles;
	}else {
		currentStyles = cleanStringStartEnd(currentStyles);
	}

	stylusState_->selectedElement->ToElement()->SetAttribute("class", currentStyles.c_str());

}


void StylusEdditor2::saveStyles(std::string newStyles)
{
	
	// std::cout << "\n\n newStyles: " << newStyles << "\n\n";
	auto styles = "? " + newStyles;
	stylusState_->selectedElement->ToElement()->SetAttribute("class", styles.c_str());
	updateFile();
	updateView();
}


// set element display from element xml
void StylusEdditor2::updateDisplayElement(std::string classes, std::string content)
{
	element_content_textarea_->setText(content);
	elementClassEdditor_->setStyleClasses(classes);
}

// update file and view
void StylusEdditor2::updateFile()
{
	// std::cout << "\nStylusEdditor2::updateFile";
	stylusState_->doc.SaveFile(sourcePath_.toUTF8().c_str());
}

void StylusEdditor2::updateView()
{
	// std::cout << "\nStylusEdditor2::updateView";
	auto app  = Wt::WApplication::instance();
	app->messageResourceBundle().keys("");
	app->refresh();
}

std::string StylusEdditor2::cleanStringStartEnd(const std::string& input)
{
	std::string newString = input;
	auto found = newString.find("?");
	while(found != std::string::npos){
		newString.erase(found, 1);
		found = newString.find("?");
	}
	// remove newline from start
	while(newString[0] == '\n'){
		newString.erase(0, 1);
	}
	// remove newline from the end
	while(newString[newString.size() - 1] == '\n'){
		newString.erase(newString.size() - 1, 1);
	}
	// remove whitespace from start
	while(newString[0] == ' '){
		newString.erase(0, 1);
	}
	// remove whitespace from the end
	while(newString[newString.size() - 1] == ' '){
		newString.erase(newString.size() - 1, 1);
	}
	return newString;
}

// create theme switcher light/dark mode
std::unique_ptr<Wt::WPushButton> StylusEdditor2::createThemeSwitcher(){
    bool darkMode = false;
    auto theme_switcher = std::make_unique<Wt::WPushButton>("");

	// theme_switcher->setTextFormat(Wt::TextFormat::XHTML);
	theme_switcher->addStyleClass("bg-[url(resources/icons/sun.svg)]");
	Wt::WApplication::instance()->setHtmlClass("");

	auto theme_switcher_ptr = theme_switcher.get();

	// theme switcher toggle dark/light mode
    theme_switcher_ptr->clicked().connect(this, [=](){
        bool darkMode = Wt::WApplication::instance()->htmlClass() == "dark";
        std::cout << "\n\n dark mode: " << !darkMode << "\n\n";
        if(!darkMode){
			theme_switcher_ptr->removeStyleClass("bg-[url(resources/icons/sun.svg)]");
			theme_switcher_ptr->addStyleClass("bg-[url(resources/icons/moon.svg)]");
            Wt::WApplication::instance()->setHtmlClass("dark");
         }else {
			theme_switcher_ptr->removeStyleClass("bg-[url(resources/icons/moon.svg)]");
			theme_switcher_ptr->addStyleClass("bg-[url(resources/icons/sun.svg)]");
            Wt::WApplication::instance()->setHtmlClass("");
        }
    });
	return theme_switcher;
}