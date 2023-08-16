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

void StylusEdditor::createKeybordShortcuts()
{
	Wt::WApplication::instance()->globalKeyPressed().connect(this, [=](Wt::WKeyEvent e){
		if(e.key() == Wt::Key::Key_7){
			sidebar_left_hamburger->clicked().emit(Wt::WMouseEvent());
		}
		if(e.key() == Wt::Key::Key_9){
			sidebar_right_hamburger->clicked().emit(Wt::WMouseEvent());
		}
	});
}


StylusEdditor::StylusEdditor(std::string templatesPath)
	:	WTemplate(tr("stylus")),
	sidebar_left(bindWidget("sidebar-left", std::make_unique<Wt::WTemplate>(Wt::WString::tr("sidebar-left")))),
	sidebar_right(bindWidget("sidebar-right", std::make_unique<Wt::WTemplate>(Wt::WString::tr("sidebar-right")))),
	menu_bar(bindWidget("menu-bar", std::make_unique<Wt::WTemplate>(Wt::WString::tr("menu-bar")))),
	template_view(bindWidget("template-view", std::make_unique<Wt::WTemplate>(Wt::WString::tr("template-view")))),
	stylusState_(std::make_shared<StylusState>()),
	xml_file_path(templatesPath)
{
	// templates widget
	stylus_templates_ = sidebar_left->bindWidget("folder-templates-view", std::make_unique<StylusTemplatesWidget>(templatesPath, stylusState_));
	sidebar_left_hamburger = template_view->bindWidget("toggle-sidebar-left", std::make_unique<Wt::WTemplate>(Wt::WString::tr("hamburger-menu")));
	sidebar_right_hamburger = template_view->bindWidget("toggle-sidebar-right", std::make_unique<Wt::WTemplate>(Wt::WString::tr("hamburger-menu")));

	sidebar_left_hamburger->clicked().connect(this, [=](){
		if(sidebar_left->hasStyleClass("-ml-[300px]")){
			sidebar_left->toggleStyleClass("-ml-[300px]", false);
		}else{
			sidebar_left->toggleStyleClass("-ml-[300px]", true);
		}
	});

	sidebar_right_hamburger->clicked().connect(this, [=](){
		if(sidebar_right->hasStyleClass("-mr-[300px]")){
			sidebar_right->toggleStyleClass("-mr-[300px]", false);
		}else{
			sidebar_right->toggleStyleClass("-mr-[300px]", true);
		}
	});

	tree_view_ = sidebar_left->bindWidget("selected-template-tree-view", std::make_unique<StylusTreeView>(stylusState_));
	tree_view_->selectionChanged().connect(this, &StylusEdditor::nodeSelected);
	tree_view_->openTemplate().connect(this, &StylusEdditor::setTemplate);

	// style classes widget
	elementClassEdditor_ = sidebar_right->bindWidget("element-classes-edditor", std::make_unique<ElementClassEdditor>());
	element_contents_ = sidebar_left->bindWidget("element-content-edditor", std::make_unique<ElementContent>());
	element_contents_->setFoldersData(stylus_templates_->folders_data_);
	element_contents_->contentChanged().connect(this, [=](){
		stylusState_->selectedElement->ToElement()->SetText(element_contents_->getData().c_str());
		updateFile();
		updateResources();
	});

	elementClassEdditor_->styleChanged().connect(this, &StylusEdditor::saveStyles);
	element_contents_->refreshDevApp().connect(this, [=](){
		createDevApp();
		tree_view_->createTree();

	});
	stylus_templates_->templateSelected().connect(this, &StylusEdditor::setTemplate);

	prev_temp_btn_ = sidebar_left->bindWidget("prev-temp-controler", std::make_unique<Wt::WPushButton>("prev template"));
	std::string btn_classes = Wt::WString::tr("button-dark").toUTF8() + "!m-0.5 !p-1 text-xs";
    prev_temp_btn_->setStyleClass(btn_classes);
	prev_temp_btn_->disable();
	prev_temp_btn_->clicked().connect(this, [=](){
		if(templates_data_.size() > 1){
			templates_data_.pop_back();
			auto tempData = templates_data_[templates_data_.size() - 1];
			templates_data_.pop_back();
			setTemplate(tempData.folderName, tempData.fileName, tempData.messageId, "template", true);
		}
	});

	createTitleBarControls();
	createKeybordShortcuts();
}

void StylusEdditor::createTitleBarControls()
{
	toggle_outline_checkbox = sidebar_left->bindWidget("toggle-outline-checkbox", std::make_unique<Wt::WCheckBox>());
	auto theme_switcher_btn = sidebar_left->bindWidget("theme-switcher-btn", createThemeSwitcher());
	
	toggle_outline_checkbox->toggleStyleClass("?", true, true);

	toggle_outline_checkbox->setChecked(true);
	toggle_outline_checkbox->changed().connect(this, [=](){
		// toggle checkbox ? style
		if(toggle_outline_checkbox->isChecked()){
			toggle_outline_checkbox->toggleStyleClass("?", true, true);
		}else {
			toggle_outline_checkbox->toggleStyleClass("?", false, true);
		}
		if(!stylusState_->selectedElement){
			// std::cout << "\n\n StylusEdditor::toggleOutline --- error getting selected element \n\n";
			return;
		}
		// toggle element outline if present
		if(toggle_outline_checkbox->isChecked()){
			toggleOutline();
		}else {
			toggleOutline(false);
		}
		updateFile();
		updateResources();
	});
}

void StylusEdditor::createDevApp()
{
		template_view->bindWidget("app-dev-template", std::make_unique<AppDev>(stylusState_->selectedTemplate->ToElement()->Attribute("id")));
}

void StylusEdditor::setTemplate(std::string folderName, std::string fileName, std::string messageId, std::string widgetType, bool insideTemplate)
{

	if(!stylus_templates_->parseMessageAndDoc(folderName, fileName, messageId)){
		auto not_found_text = sidebar_left->bindWidget("selected-template-tree-view", std::make_unique<Wt::WText>("arguments fileName or messageId are not found"));
		not_found_text->setStyleClass("text-red-400 font-bold");
		return;
	}

	updateResources();
	updateFile();
	tree_view_->createTree();

	if(insideTemplate){
		templates_data_.push_back({folderName, fileName, messageId});
		prev_temp_btn_->enable();
	}else {
		templates_data_.clear();
		templates_data_.push_back({folderName, fileName, messageId});
		prev_temp_btn_->disable();
		createDevApp();
	}
	// std::cout << "\n\n stylus file path: " << stylusState_->filePath << "\n\n";

}


StylusEdditor::~StylusEdditor()
{
	toggleOutline(false);
	updateFile();
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

		stylusState_->selectedElement->SetValue(newText.c_str());
		createDevApp();
	}else if(toggle_outline_checkbox->isChecked()) {
		toggleOutline(false);
	}
	std::string elem_classes;
	std::string elem_content;
	stylusState_->selectedElement = node;

	if(!node->ToElement()){
		auto text = node->Value();
		auto classes = getTemplateValue(text, "class");
		elem_classes = classes;
		auto newText = changeTempateAttributeValue(text, "class", "? " + classes);
		node->SetValue(newText.c_str());
		updateFile();
		updateResources();
		createDevApp();
	}else if(toggle_outline_checkbox->isChecked()){
		toggleOutline(true);
		elem_classes = cleanStringStartEnd(stylusState_->selectedElement->ToElement()->Attribute("class"));
		elem_content = stylusState_->selectedElement->ToElement()->GetText();
		updateFile();
		updateResources();
	}
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
			auto tempText = stylusState_->selectedElement->Value();
			auto classes = getTemplateValue(tempText, "class");
			classes = cleanStringStartEnd(classes);
			auto newText = changeTempateAttributeValue(tempText, "class", newStyles);
			stylusState_->selectedElement->SetValue(newText.c_str());
			updateFile();
			updateResources();
			createDevApp();
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
			createDevApp();
		}else {
			newStyles = cleanStringStartEnd(stylusState_->selectedElement->ToElement()->Attribute("class"));
			stylusState_->selectedElement->ToElement()->SetAttribute("class", newStyles.c_str());
		}
	}

}


void StylusEdditor::saveStyles(std::string newStyles)
{
	std::string styles = "";
	if(toggle_outline_checkbox->isChecked()){
		styles = "? ";
	}
	styles += newStyles;
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
			createDevApp();
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
	// remove ? from start
	while(newString[0] == '?'){
		newString.erase(0, 1);
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
	// std::cout << "\n\n newString: " << newString << "\n\n";
	return newString;
}

// create theme switcher light/dark mode
std::unique_ptr<Wt::WPushButton> StylusEdditor::createThemeSwitcher(){
    bool darkMode = false;
    auto theme_switcher = std::make_unique<Wt::WPushButton>();

	// theme_switcher->setTextFormat(Wt::TextFormat::XHTML);
	theme_switcher->addStyleClass("bg-[url(resources/icons/sun.svg)] !p-3 !my-0 !ms-0 bg-cover bg-no-repeat inline  cursor-pointer");
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
