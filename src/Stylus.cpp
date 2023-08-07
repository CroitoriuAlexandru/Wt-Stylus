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
	edditor_temp_->setCondition("controls-view", true);

	tree_view_ = edditor_temp_->bindWidget("tree-view", std::make_unique<StylusTreeView>(stylusState_));
	tree_view_->selectionChanged().connect(this, &StylusEdditor::nodeSelected);
	tree_view_->openTemplate().connect(this, &StylusEdditor::setTemplate);
	// edditor_temp_->bindEmpty("tree-view");
	// templates widget
	stylus_templates_ = edditor_temp_->bindWidget("templates.widget", std::make_unique<StylusTemplatesWidget>(templatesPath, stylusState_));
	
	// style classes widget
	elementClassEdditor_ = edditor_temp_->bindWidget("stylus.element.edditor", std::make_unique<ElementClassEdditor>());
	elementClassEdditor_->styleChanged().connect(this, &StylusEdditor::saveStyles);
	element_contents_ = edditor_temp_->bindWidget("stylus.element.content", std::make_unique<ElementContent>());
	element_contents_->setFoldersData(stylus_templates_->folders_data_);
	element_contents_->contentChanged().connect(this, [=](){
		stylusState_->selectedElement->ToElement()->SetText(element_contents_->getData().c_str());
		updateFile();
		updateResources();
	});

	element_contents_->refreshDevApp().connect(this, [=](){
		createTreeView();
		appDevChanged_.emit();
	});

	stylus_templates_->templateSelected().connect(this, &StylusEdditor::setTemplate);

	createTitleBarControls();


	auto toggle_class_view = edditor_temp_->bindWidget("toggle-class-view", std::make_unique<Wt::WCheckBox>("class text"));
	edditor_classes_raw_twxtarea_ = edditor_temp_->bindWidget("textarea-classes-text-raw", std::make_unique<Wt::WTextArea>(""));
	toggle_class_view->changed().connect(this, [=](){
		if(toggle_class_view->isChecked()){
			std::string classes = elementClassEdditor_->getStyles();
			edditor_classes_raw_twxtarea_->setText(classes	);
			edditor_temp_->setCondition("text-view", true);
			edditor_temp_->setCondition("controls-view", false);
		}else {
			edditor_temp_->setCondition("text-view", false);
			edditor_temp_->setCondition("controls-view", true);
		}
	});

	prev_temp_btn_ = edditor_temp_->bindWidget("prev-temp-controler", std::make_unique<Wt::WPushButton>("prev template"));
	std::string btn_classes = Wt::WString::tr("button-dark").toUTF8() + "!m-0.5 !p-1";
    prev_temp_btn_->setStyleClass(btn_classes);
	prev_temp_btn_->disable();
	prev_temp_btn_->clicked().connect(this, [=](){
		if(templates_data_.size() > 1){
			templates_data_.pop_back();
			auto tempData = templates_data_[templates_data_.size() - 1];
			templates_data_.pop_back();
			setTemplate(tempData.folderName, tempData.fileName, tempData.messageId, "template", true);
			if(templates_data_.size() == 1){
				prev_temp_btn_->disable();
			}
		}
	
	});


	setHidden(false, Wt::WAnimation(Wt::AnimationEffect::SlideInFromRight, Wt::TimingFunction::Linear, 350));
}

std::unique_ptr<AppDev> StylusEdditor::createDevApp()
{
	std::unique_ptr<AppDev> app = std::make_unique<AppDev>(stylusState_->selectedTemplate->ToElement()->Attribute("id"));
	return app;
}

void StylusEdditor::setTemplate(std::string folderName, std::string fileName, std::string messageId, std::string widgetType, bool insideTemplate)
{
	toggleOutline(false);

	if(insideTemplate){
		templates_data_.push_back({folderName, fileName, messageId});
		if(templates_data_.size() > 0){
			prev_temp_btn_->enable();
			if(templates_data_.size() > 1)
				prev_temp_btn_->setText(templates_data_[templates_data_.size() - 2].messageId);
			else
				prev_temp_btn_->setText("prev template");
		}
	}else {
		templates_data_.clear();
		templates_data_.push_back({folderName, fileName, messageId});
		appDevChanged_.emit();
		prev_temp_btn_->disable();
		prev_temp_btn_->setText("prev template");
	}


	if(!stylus_templates_->parseMessageAndDoc(folderName, fileName, messageId)){
		// std::cout << "\n\n StylusEdditor::setTemplate --- template already exists \n\n";
		auto not_found_text = edditor_temp_->bindWidget("tree-view", std::make_unique<Wt::WText>("arguments fileName or messageId are not found"));
		not_found_text->setStyleClass("text-red-400 font-bold");
		return;
	}

	tree_view_->createTree();
	updateFile();
	updateResources();
	
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
	treeView->selectionChanged().connect(this, &StylusEdditor::nodeSelected);
	treeView->openTemplate().connect(this, &StylusEdditor::setTemplate);
	treeView->createTree();
}


void StylusEdditor::nodeSelected(tinyxml2::XMLNode* node)
{
	element_contents_->resetData();
	// toggle outline if selected element is not Template text
	if(stylusState_->selectedElement && !stylusState_->selectedElement->ToElement()){
		auto text = stylusState_->selectedElement->Value();
		auto classes = getTemplateValue(text, "class");
		classes = cleanStringStartEnd(classes);
		auto newText = changeTempateAttributeValue(text, "class", classes);
			
		std::cout << "\n\n text :" << text << "\n";
		std::cout << "classes :" << classes << "\n";
		std::cout << "newText :" << newText << "\n\n";

		stylusState_->selectedElement->SetValue(newText.c_str());
		appDevChanged_.emit();
	}else {
		toggleOutline(false);
	}
	std::string elem_classes;
	std::string elem_content;
	stylusState_->selectedElement = node;

	if(!node->ToElement()){
		std::cout << "\n\n selected node is text\n";
		auto text = node->Value();
		auto classes = getTemplateValue(text, "class");
		elem_classes = classes;
		auto newText = changeTempateAttributeValue(text, "class", "? " + classes);
		node->SetValue(newText.c_str());
		updateFile();
		updateResources();
		appDevChanged_.emit();
	}else {
		toggleOutline(true);
		elem_classes = cleanStringStartEnd(stylusState_->selectedElement->ToElement()->Attribute("class"));
		elem_content = stylusState_->selectedElement->ToElement()->GetText();
		updateFile();
		updateResources();
	}
	// std::cout << "\n\n elem_classes: " << elem_classes << "\n\n";

	updateDisplayElement(elem_classes, elem_content);


}

std::string StylusEdditor::getTemplateValue(std::string templateText, std::string attribute)
{
	std::string result = "";
	auto pos = templateText.find(attribute + "=\"");
	if(pos != std::string::npos){
		result = templateText.substr(pos + 7, templateText.find("\"", pos + 7) - pos - 7);
		templateText = templateText.substr(0, pos) + templateText.substr(templateText.find("\"", pos + 7) + 2);
	}
	// std::cout << "\n\n result: " << result << "\n\n";
	// std::cout << "\n\n templateText: " << templateText << "\n\n";
	return result; 

}

std::string StylusEdditor::changeTempateAttributeValue(std::string templateText, std::string attribute, std::string value)
{
	std::string result = "";
	auto pos = templateText.find(attribute + "=\"");
	if(pos != std::string::npos){
		result = templateText.substr(pos + 7, templateText.find("\"", pos + 7) - pos - 7);
		templateText = templateText.substr(0, pos) + attribute + "=\"" + value + "\" " + templateText.substr(templateText.find("\"", pos + 7) + 2);
	}
	// std::cout << "\n\n result: " << result << "\n\n";
	// std::cout << "\n\n templateText: " << templateText << "\n\n";
	return templateText;
}




void StylusEdditor::toggleOutline(bool on)
{
	// std::cout << "\nStylusEdditor --- toggleOutline got called \n";
	if(!stylusState_->selectedElement){

		// std::cout << "\n\n StylusEdditor::toggleOutline --- error getting selected element \n\n";
		return;
	}
	std::string newStyles = ""; 
	if(on){
		newStyles = "? ";
		// if selected element is template
		if(isTemplateText(stylusState_->selectedElement->Value())){
			std::cout << "\n\n StylusEdditor::toggleOutline --- selected element is template \n\n";
			auto tempText = stylusState_->selectedElement->Value();
			auto classes = getTemplateValue(tempText, "class");
			classes = cleanStringStartEnd(classes);
			auto newText = changeTempateAttributeValue(tempText, "class", newStyles);
			stylusState_->selectedElement->SetValue(newText.c_str());
			updateFile();
			updateResources();
			appDevChanged_.emit();
		}else {
			
			newStyles += cleanStringStartEnd(stylusState_->selectedElement->ToElement()->Attribute("class"));
			stylusState_->selectedElement->ToElement()->SetAttribute("class", newStyles.c_str());
		}
	}else {
		if(isTemplateText(stylusState_->selectedElement->Value())){
			auto tempText = stylusState_->selectedElement->Value();
			auto classes = getTemplateValue(tempText, "class");
			classes = cleanStringStartEnd(classes);
			auto newText = changeTempateAttributeValue(tempText, "class", classes);
			stylusState_->selectedElement->SetValue(newText.c_str());
			updateFile();
			updateResources();
			appDevChanged_.emit();
		}else {
			newStyles = cleanStringStartEnd(stylusState_->selectedElement->ToElement()->Attribute("class"));
			stylusState_->selectedElement->ToElement()->SetAttribute("class", newStyles.c_str());
		}
	}

	// stylusState_->selectedElement->ToElement()->SetAttribute("class", currentStyles.c_str());

}


void StylusEdditor::saveStyles(std::string newStyles)
{
	auto styles = "? " + newStyles;
	std::cout << "\nStylusEdditor::saveStyles --- new styles: " << styles << "\n";
	if(stylusState_->selectedElement && !stylusState_->selectedElement->ToElement())
	{
		std::string tempText = stylusState_->selectedElement->Value();
		std::cout << "\n\n tempText: " << tempText << "\n\n";
		if(isTemplateText(tempText)){
			std::cout << "\n\n tempText is template text \n\n";
			std::string newTemp = changeTempateAttributeValue(tempText, "class", styles);
			stylusState_->selectedElement->SetValue(newTemp.c_str());
			updateFile();
			updateResources();
			appDevChanged_.emit();
		}

	}else 
	{
		stylusState_->selectedElement->ToElement()->SetAttribute("class", styles.c_str());
		updateFile();
		updateResources();
	}

}

bool StylusEdditor::isTemplateText(std::string text)
{
	if(std::regex_search(text, temp_pattern)){
		return true;
	}
	return false;
}


// set element display from element xml
void StylusEdditor::updateDisplayElement(std::string classes, std::string content)
{
	elementClassEdditor_->setStyleClasses(classes);
	element_contents_->setData(content);
}

// update file and view
void StylusEdditor::updateFile()
{
	// check if doc exists
	if(stylusState_->doc.Error()){
		// std::cout << "\n\n StylusEdditor::updateFile --- error getting <messages> element \n\n";
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

// used by the application to get message resources with the paths returned from here
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
	// std::cout << "\n\n";
	// for(auto xmlFile : xmlFiles)
	// {
	// 	std::cout << "\n xmlFile: " << xmlFile << "";
	// }
	// std::cout << "\n\n";

	return xmlFiles;
}
