#include "include/Stylus.h"
#include <Wt/WTree.h>
#include <Wt/WApplication.h>
#include <Wt/WTemplate.h>
#include <Wt/WTreeNode.h>
#include <iostream>
#include <Wt/WCheckBox.h>
#include <Wt/WPushButton.h>
#include <Wt/WLabel.h>
#include <regex>

StylusEdditor::StylusEdditor(std::string templatesPath)
{
	applicationWidthClass = 300;
	setStyleClass("min-w-fit w-[300px] max-h-screen h-screen min-h-screen bg-neutral-700 transition-spacing duration-300 ease-in-out");
	// setMinimumSize(300, Wt::WLength(100, Wt::LengthUnit::ViewportHeight));
	// setMaximumSize(Wt::WLength(500, Wt::LengthUnit::Pixel), Wt::WLength(100,Wt::LengthUnit::ViewportHeight));
	setThemeStyleEnabled(false);
	setOffsets(0, Wt::Side::Top | Wt::Side::Right | Wt::Side::Bottom);
	setOffsets(Wt::WLength::Auto, Wt::Side::Left);
	Wt::WApplication::instance()->root()->toggleStyleClass("mr-[" + std::to_string(applicationWidthClass) + "px]", true, true);
	stylusState_ = std::make_shared<StylusState>();

	setModal(false);
	setMovable(false);
	setResizable(true);
	setTitleBarEnabled(false);

	// titleBar()->clear();
	edditor_temp_ = contents()->addWidget(std::make_unique<Wt::WTemplate>(tr("stylus.edditor")));
	edditor_temp_->bindEmpty("tree-view");
	edditor_temp_->bindEmpty("stylus.element.edditor");
	edditor_temp_->bindEmpty("stylus.element.content");
	stylus_templates_ = edditor_temp_->bindWidget("templates.widget", std::make_unique<StylusTemplatesWidget>(templatesPath, stylusState_));
	stylus_templates_->templateSelected().connect(this, &StylusEdditor::setTemplate);

	// parseMessageAndDoc();
	createTitleBarControls();
    // createDialogContent();
	// createTreeView();	

	setHidden(false, Wt::WAnimation(Wt::AnimationEffect::SlideInFromRight, Wt::TimingFunction::Linear, 350));
}

std::unique_ptr<AppDev> StylusEdditor::createDevApp()
{
	std::unique_ptr<AppDev> app = std::make_unique<AppDev>(stylusState_->selectedTemplate->ToElement()->Attribute("id"));

	return app;
}


void StylusEdditor::createDialogVariableToText(std::string text, bool toText)
{
	auto dialog = Wt::WApplication::instance()->root()->addChild(std::make_unique<Wt::WDialog>());
	dialog->setModal(false);
	dialog->setMovable(false);
	dialog->setResizable(false);
	dialog->setTitleBarEnabled(false);
	dialog->contents()->setStyleClass("flex flex-col justify-center items-center p-2");
	dialog->setOffsets(Wt::WLength::Auto, Wt::Side::Top | Wt::Side::Right | Wt::Side::Bottom | Wt::Side::Left);
	dialog->rejectWhenEscapePressed();

	if(toText){
		dialog->contents()->addWidget(std::make_unique<Wt::WText>("Are you sure tou want to change the template variable to a text ?"));
	}else {
		dialog->contents()->addWidget(std::make_unique<Wt::WText>("Are you sure tou want to change the text to a template variable ?"));
	}

	auto yes_btn = dialog->contents()->addWidget(std::make_unique<Wt::WPushButton>("Yes"));
	auto no_btn = dialog->contents()->addWidget(std::make_unique<Wt::WPushButton>("No"));

	yes_btn->clicked().connect(dialog, &Wt::WDialog::accept);
	no_btn->clicked().connect(dialog, &Wt::WDialog::reject);

	dialog->finished().connect(this, [=](Wt::DialogCode code){
		if(code == Wt::DialogCode::Accepted){
			std::cout << "\n\n StylusEdditor::createDialogVariableToText --- accepted \n\n";
			stylusState_->selectedElement->ToElement()->SetText(text.c_str());
			updateFile();
			updateResources();
			createTreeView();
			appDevChanged_.emit();
		}else {
			std::cout << "\n\n StylusEdditor::createDialogVariableToText --- rejected \n\n";
		}
	});
	dialog->animateShow(Wt::WAnimation(Wt::AnimationEffect::Fade, Wt::TimingFunction::Linear, 350));

}

void StylusEdditor::setTemplate(std::string folderName, std::string fileName, std::string messageId, std::string widgetType)
{
	// std::cout << "\n\n Stylus Edditor set template with data :\n" << "folderName: <" << folderName << ">\nfileName: <" << fileName << ">\nmessageId: <" << messageId << ">\n\n";
	// toggleOutline(false);
	// updateFile();

	if(!stylus_templates_->parseMessageAndDoc(folderName, fileName, messageId)){
		std::cout << "\n\n StylusEdditor::setTemplate --- template already exists \n\n";
		auto not_found_text = edditor_temp_->bindWidget("tree-view", std::make_unique<Wt::WText>("arguments fileName or messageId are not found"));
		not_found_text->setStyleClass("text-red-400 font-bold");
		return;
	}

	// updateResources();
	elementClassEdditor_ = edditor_temp_->bindWidget("stylus.element.edditor", std::make_unique<ElementClassEdditor>());
	
	// element content text or variable
	element_content_ = edditor_temp_->bindWidget("stylus.element.content", std::make_unique<Wt::WContainerWidget>());
	toggle_variable_content_ = edditor_temp_->bindWidget("toggle-variable-content", std::make_unique<Wt::WCheckBox>());
	auto contents_wrapper = element_content_->addWidget(std::make_unique<Wt::WContainerWidget>());
	element_content_textarea_ = contents_wrapper->addWidget(std::make_unique<Wt::WTextArea>());
	element_content_variable_configuration_ = contents_wrapper->addWidget(std::make_unique<VariableConfigurationWidget>(stylus_templates_->folders_data_));	

	// element content template variable configuration
	element_content_variable_configuration_->variableSaved().connect(this, [=](){
		auto text = element_content_variable_configuration_->getData();
		changeSelectedText(text);
	});

	// element content textarea
	element_content_textarea_->setStyleClass("bg-neutral-900 text-neutral-100 rounded-md w-full");
	titleBar()->setStyleClass("!p-0");
	element_content_textarea_->enterPressed().connect(this, [=](){
		auto text = element_content_textarea_->text().toUTF8();
		changeSelectedText(text);
		element_content_textarea_->setFocus();
	});

	toggle_variable_content_->changed().connect(this, [=](){
		if(toggle_variable_content_->isChecked()){
			element_content_textarea_->setHidden(true);
			element_content_variable_configuration_->setHidden(false);
		}else {
			element_content_textarea_->setHidden(false);
			element_content_variable_configuration_->setHidden(true);
		}
	});

	createTreeView();
	elementClassEdditor_->styleChanged().connect(this, &StylusEdditor::saveStyles);
	updateFile();
	updateResources();
}

void StylusEdditor::changeSelectedText(std::string variableText)
{
	auto selectedText = stylusState_->selectedElement->ToElement()->GetText();
	if(std::regex_search(selectedText, temp_pattern) && !std::regex_search(variableText, temp_pattern) ||
		!std::regex_search(selectedText, temp_pattern) && std::regex_search(variableText, temp_pattern)){
		std::cout << "\n\n StylusEdditor::changeSelectedText --- variable to text or text to variable \n\n";
		createDialogVariableToText(variableText, true);
	}else if(std::regex_search(selectedText, temp_pattern) && std::regex_search(variableText, temp_pattern)){
		std::cout << "\n\n StylusEdditor::changeSelectedText --- variable to variable \n\n";
		stylusState_->selectedElement->ToElement()->SetText(variableText.c_str());
		updateFile();
		appDevChanged_.emit();
		updateResources();
		createTreeView();
	}else {
		std::cout << "\n\n StylusEdditor::changeSelectedText --- text to text \n\n";
		stylusState_->selectedElement->ToElement()->SetText(variableText.c_str());
		updateFile();
		updateResources();
	}
	



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

	// move_left_btn->setDisabled(true);

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
			// std::cout << "\n\n StylusEdditor::toggleOutline --- error getting selected element \n\n";
			return;
		}
		if(toggle_outline_checkbox->isChecked()){
			toggleOutline();
		}else {
			toggleOutline(false);
		}
		updateFile();
		updateResources();
	});
}

void StylusEdditor::createTreeView()
{
	// std::cout << "\nStylusEdditor --- createTreeView got called \n";
	auto treeView = edditor_temp_->bindWidget("tree-view", std::make_unique<StylusTreeView>(stylusState_));
	treeView->templateModified().connect(this, [=](){
		updateFile();
		updateResources();
		// treeView->createTree();
		createTreeView();
	});
	treeView->selectionChanged().connect(this, &StylusEdditor::nodeSelected);
	treeView->openTemplate().connect(this, &StylusEdditor::setTemplate);
	treeView->createTree();
}


void StylusEdditor::nodeSelected(tinyxml2::XMLNode* node)
{

	// std::cout << "\nStylusEdditor::nodeSelected ";
	if(outline_selected_on){
		toggleOutline(false);
		stylusState_->selectedElement = node->ToElement();
		toggleOutline(true);
		updateFile();
		updateResources();
	}else {
		stylusState_->selectedElement = node->ToElement();
	}
	auto elem_classes = cleanStringStartEnd(stylusState_->selectedElement->ToElement()->Attribute("class"));
	auto elem_content = stylusState_->selectedElement->ToElement()->GetText();

	updateDisplayElement(elem_classes, elem_content);
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
	updateResources();
}


// set element display from element xml
void StylusEdditor::updateDisplayElement(std::string classes, std::string content)
{
	elementClassEdditor_->setStyleClasses(classes);
	
	// reset text contents of element
	element_content_variable_configuration_->resetData();
	element_content_textarea_->setText("");

	if(std::regex_search(content, temp_pattern)){
		element_content_variable_configuration_->setData(content);
		// toggle_variable_content_->setHidden(true);
		toggle_variable_content_->setChecked(true);
		toggle_variable_content_->changed().emit();	
	}else {
		element_content_textarea_->setText(content);
		// toggle_variable_content_->setHidden(false);
		toggle_variable_content_->setChecked(false);
		toggle_variable_content_->changed().emit();
	}
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

void StylusEdditor::updateResources()
{
	// std::cout << "\nStylusEdditor::updateResources";
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
        // std::cout << "\n\n dark mode: " << !darkMode << "\n\n";
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

std::vector<std::string> StylusEdditor::getXmlFils()
{
	std::vector<std::string> xmlFiles;
	
	auto path = stylus_templates_->xml_folder_path;
	for(auto folderData : stylus_templates_->folders_data_)
	{
		for(auto xmlFileData : folderData.xmlFiles)
		{
			// remove .xml from end of string
			auto fileName = xmlFileData.fileName.substr(0, xmlFileData.fileName.size()-4);
			xmlFiles.push_back(path + folderData.folderName + "/" + fileName);
		}
	}


	return xmlFiles;
}
