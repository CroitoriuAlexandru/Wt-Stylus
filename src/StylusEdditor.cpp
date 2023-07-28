#include "include/StylusEdditor.h"
#include <Wt/WTree.h>
#include <Wt/WApplication.h>
#include <Wt/WTemplate.h>
#include <Wt/WTreeNode.h>
#include <iostream>
#include <Wt/WCheckBox.h>
#include <Wt/WPushButton.h>


StylusEdditor::StylusEdditor()
{
	applicationWidthClass = 320;
	setStyleClass("min-w-fit w-[300px] bg-neutral-700");
	setMinimumSize(300, Wt::WLength(100, Wt::LengthUnit::ViewportHeight));
	setMaximumSize(Wt::WLength(500, Wt::LengthUnit::Pixel), Wt::WLength(100,Wt::LengthUnit::ViewportHeight));
	setThemeStyleEnabled(false);
	setOffsets(0, Wt::Side::Top | Wt::Side::Right | Wt::Side::Bottom);
	setOffsets(Wt::WLength::Auto, Wt::Side::Left);
	Wt::WApplication::instance()->root()->toggleStyleClass("mr-[" + std::to_string(applicationWidthClass) + "px]", true, true);
	stylusState_ = std::make_shared<StylusState>();

	// resized().connect(this, &StylusEdditor::dialogResized);

    // sourcePath_ += fileName;
    // templateName_ = templateName;

	// rejectWhenEscapePressed();
	setModal(false);
	setMovable(false);
	setResizable(true);
	setTitleBarEnabled(false);

	// titleBar()->clear();
	edditor_temp_ = contents()->addWidget(std::make_unique<Wt::WTemplate>(tr("stylus.edditor")));

	stylus_templates_ = edditor_temp_->bindWidget("templates.widget", std::make_unique<StylusTemplatesWidget>(stylusState_));
	stylus_templates_->templateSelected().connect(this, &StylusEdditor::setTemplate);

	// parseMessageAndDoc();
	createTitleBarControls();
    // createDialogContent();
	// createDialogTreeView();	

	setHidden(false, Wt::WAnimation(Wt::AnimationEffect::SlideInFromRight, Wt::TimingFunction::Linear, 350));
}	

void StylusEdditor::setTemplate(std::string fileName, std::string messageId)
{
	if(!stylus_templates_->parseMessageAndDoc(fileName, messageId)){
		std::cout << "\n\n StylusEdditor::setTemplate --- template already exists \n\n";
		auto not_found_text = edditor_temp_->bindWidget("tree-view", std::make_unique<Wt::WText>("arguments fileName or messageId are not found"));
		not_found_text->setStyleClass("text-red-400 font-bold");
		return;
	}


	toggleOutline(false);
	// updateFile();
	// updateView();
	
	elementClassEdditor_ = edditor_temp_->bindWidget("stylus.element.edditor", std::make_unique<ElementClassEdditor>());
	element_content_textarea_ = edditor_temp_->bindWidget("stylus.element.content", std::make_unique<Wt::WTextArea>());
	element_content_textarea_->setStyleClass("bg-neutral-900 text-neutral-100 rounded-md");
	titleBar()->setStyleClass("!p-0");
	element_content_textarea_->enterPressed().connect(this, [=](){
		stylusState_->selectedElement->ToElement()->SetText(element_content_textarea_->text().toUTF8().c_str());
		updateFile();
		updateView();
	});

	createDialogTreeView();
	elementClassEdditor_->styleChanged().connect(this, &StylusEdditor::saveStyles);
	updateFile();
	updateView();
}

void StylusEdditor::dialogResized(int width, int height)
{
	Wt::WApplication::instance()->root()->removeStyleClass("ml-[" + std::to_string(applicationWidthClass) + "px]");
	if(width > 500) width = 500;
	applicationWidthClass = width + 10;
	Wt::WApplication::instance()->root()->toggleStyleClass("ml-[" + std::to_string(applicationWidthClass) + "px]", true, true);
}


StylusEdditor::~StylusEdditor()
{
	toggleOutline(false);
	updateFile();
}

void StylusEdditor::createTitleBarControls()
{
	auto move_left_btn = edditor_temp_->bindWidget("move-left-btn", std::make_unique<Wt::WPushButton>());
	auto move_right_btn = edditor_temp_->bindWidget("move-right-btn", std::make_unique<Wt::WPushButton>());
	auto toggle_outline_checkbox = edditor_temp_->bindWidget("toggle-outline-checkbox", std::make_unique<Wt::WCheckBox>());
	auto theme_switcher_btn = edditor_temp_->bindWidget("theme-switcher-btn", createThemeSwitcher());

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

	toggle_outline_checkbox->setChecked(true);
	toggle_outline_checkbox->changed().connect(this, [=](){
		// toggle checkbox ? style
		if(toggle_outline_checkbox->isChecked()){
			outline_selected_on = true;
			toggle_outline_checkbox->toggleStyleClass("?", true, true);
		}else {
			outline_selected_on = false;
			toggle_outline_checkbox->toggleStyleClass("?", false, true);
		}
		// toggle element outline if present
		if(!stylusState_->selectedElement){
			std::cout << "\n\n StylusEdditor::toggleOutline --- error getting selected element \n\n";
			return;
		}
		if(toggle_outline_checkbox->isChecked()){
			toggleOutline();
		}else {
			toggleOutline(false);
		}
		updateFile();
		updateView();
	});
}

void StylusEdditor::createDialogTreeView()
{
	// std::cout << "\nStylusEdditor --- createDialogTreeView got called \n";
	auto treeView = edditor_temp_->bindWidget("tree-view", std::make_unique<StylusTreeView>(stylusState_));
	treeView->templateModified().connect(this, [=](){
		updateFile();
		updateView();
		// treeView->createTree();
		createDialogTreeView();
	});
	treeView->selectionChanged().connect(this, &StylusEdditor::nodeSelected);
	treeView->templateNodeSelected().connect(this, &StylusEdditor::tempNodeSelected);
	treeView->openTemplate().connect(this, &StylusEdditor::setTemplate);
	treeView->createTree();
}


void StylusEdditor::nodeSelected(tinyxml2::XMLNode* node)
{
	if(stylusState_->templateSelected)
	{
		std::cout << "\nStylusEdditor::nodeSelected --- templateSelected = FALSE \n";
		return;
	}
	// std::cout << "\nStylusEdditor::nodeSelected ";
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

void StylusEdditor::tempNodeSelected(tinyxml2::XMLNode* node)
{
	if(!stylusState_->templateSelected)
	{
		std::cout << "\nStylusEdditor::tempNodeSelected --- templateSelected = TRUE \n";
		return;
	}
	// std::cout << "\nStylusEdditor::tempNodeSelected ";
	std::string tempString = node->Value();
	auto startString = "${";
	toggleOutline(false);
	// tempString = ${mamaie class=""}
	auto variableName = tempString.substr(2, tempString.find(" ")-2);
	auto classes = tempString.substr(tempString.find("class=")+7);
	// remove "} from end of string
	classes = classes.substr(0, classes.size()-2);

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


void StylusEdditor::toggleOutline(bool on)
{
	// std::cout << "\nStylusEdditor --- toggleOutline got called \n";
	if(!stylusState_->selectedElement){
		std::cout << "\n\n StylusEdditor::toggleOutline --- error getting selected element \n\n";
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


void StylusEdditor::saveStyles(std::string newStyles)
{
	
	// std::cout << "\n\n newStyles: " << newStyles << "\n\n";
	auto styles = "? " + newStyles;
	stylusState_->selectedElement->ToElement()->SetAttribute("class", styles.c_str());
	updateFile();
	updateView();
}


// set element display from element xml
void StylusEdditor::updateDisplayElement(std::string classes, std::string content)
{
	element_content_textarea_->setText(content);
	elementClassEdditor_->setStyleClasses(classes);
}

// update file and view
void StylusEdditor::updateFile()
{
	// check if doc exists
	if(stylusState_->doc.Error()){
		std::cout << "\n\n StylusEdditor::updateFile --- error getting <messages> element \n\n";
		return;
	}
	stylusState_->doc.SaveFile(stylusState_->filePath.c_str());
}

void StylusEdditor::updateView()
{
	// std::cout << "\nStylusEdditor::updateView";
	auto app  = Wt::WApplication::instance();
	app->messageResourceBundle().keys("");
	app->refresh();
}

std::string StylusEdditor::cleanStringStartEnd(const std::string& input)
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
std::unique_ptr<Wt::WPushButton> StylusEdditor::createThemeSwitcher(){
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