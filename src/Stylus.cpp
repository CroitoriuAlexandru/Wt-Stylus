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
#include <Wt/WSuggestionPopup.h>

void StylusEdditor::createKeybordShortcuts()
{

	Wt::WApplication::instance()->globalKeyWentDown().connect(this, [=](Wt::WKeyEvent e){
		if(e.key() == Wt::Key::Key_7){
			sidebar_left_hamburger->clicked().emit(Wt::WMouseEvent());
		}
		if(e.key() == Wt::Key::Key_9){
			sidebar_right_hamburger->clicked().emit(Wt::WMouseEvent());
		}
		if(e.modifiers() == Wt::KeyboardModifier::Control && e.key() == Wt::Key::Down){
			std::cout << "\n\n select next sibling \n\n";
			if(stylusState_->selectedElement){
				auto nextElement = stylusState_->selectedElement->NextSiblingElement();
				if(nextElement){
					nodeSelected(nextElement);
					tree_view_->createTree();
				}else if(stylusState_->selectedElement->FirstChildElement()){
					nodeSelected(stylusState_->selectedElement->FirstChildElement());
					tree_view_->createTree();
				}else {
					auto parent = stylusState_->selectedElement->Parent();
					while(parent != stylusState_->selectedTemplate){
						if(parent->NextSiblingElement()){
							nodeSelected(parent->NextSiblingElement());
							tree_view_->createTree();
							break;
						}
						parent = parent->Parent();
					}
				}
			}
		}
		if(e.modifiers() == Wt::KeyboardModifier::Control && e.key() == Wt::Key::Up){
			std::cout << "\n\n select previous sibling \n\n";
			if(stylusState_->selectedElement){
				auto prevElement = stylusState_->selectedElement->PreviousSiblingElement();
				if(prevElement){
					nodeSelected(prevElement);
					tree_view_->createTree();
				}else if (stylusState_->selectedElement->Parent() != stylusState_->selectedTemplate){
					nodeSelected(stylusState_->selectedElement->Parent());
					tree_view_->createTree();
				}
			}
		}
		if(e.modifiers() == Wt::KeyboardModifier::Control && e.key() == Wt::Key::Left){
			std::cout << "\n\n select parent \n\n";
			if(stylusState_->selectedElement){
				auto parentElement = stylusState_->selectedElement->Parent();
				if(stylusState_->selectedElement->Parent() != stylusState_->selectedTemplate){
					nodeSelected(parentElement);
					tree_view_->createTree();
				}
			}
		}
		if(e.modifiers() == Wt::KeyboardModifier::Control && e.key() == Wt::Key::Right){
			std::cout << "\n\n select first child \n\n";
			if(stylusState_->selectedElement){
				auto childElement = stylusState_->selectedElement->FirstChildElement();
				if(childElement){
					nodeSelected(childElement);
					tree_view_->createTree();
				}
			}
		}
		if(e.modifiers() == Wt::KeyboardModifier::Control && e.key() == Wt::Key::D){
			std::cout << "\n\n Delete element \n\n";
			auto element = stylusState_->selectedElement;
			if(element && element != stylusState_->selectedTemplate){
				if(element->PreviousSiblingElement()){
					toggleOutline(false);
					stylusState_->selectedElement = element->PreviousSiblingElement();
					toggleOutline(true);
				}else if (element->Parent() != stylusState_->selectedTemplate && element != stylusState_->selectedTemplate){
					toggleOutline(false);
					stylusState_->selectedElement = element->Parent();
					toggleOutline(true);
				}

				tree_view_->removeElement(element->ToElement());
				updateResources();
				tree_view_->createTree();
			}
		}
		if(e.modifiers() == Wt::KeyboardModifier::Control && e.key() == Wt::Key::A){
			std::cout << "\n\n Add Sibling up \n\n";
			if(stylusState_->selectedElement){
				tree_view_->addSiblingElementBefore(stylusState_->selectedElement->ToElement());
				tree_view_->createTree();
			}
		}
		if(e.modifiers() == Wt::KeyboardModifier::Control && e.key() == Wt::Key::S){
			std::cout << "\n\n Add Sibling down \n\n";
			if(stylusState_->selectedElement){
				tree_view_->addSiblingElementAfter(stylusState_->selectedElement->ToElement());
				tree_view_->createTree();
			}
		}
		if(e.modifiers() == Wt::KeyboardModifier::Control && e.key() == Wt::Key::Z){
			std::cout << "\n\n Add Child first \n\n";
			if(stylusState_->selectedElement){
				tree_view_->addChildElementFirst(stylusState_->selectedElement->ToElement());
				tree_view_->createTree();
			}
		}
		if(e.modifiers() == Wt::KeyboardModifier::Control && e.key() == Wt::Key::X){
			std::cout << "\n\n Add Child last \n\n";
			if(stylusState_->selectedElement){
				tree_view_->addChildElementLast(stylusState_->selectedElement->ToElement());
				tree_view_->createTree();
			}
		}




		if(e.modifiers() == Wt::KeyboardModifier::Shift && e.key() == Wt::Key::Up){
			std::cout << "\n\n Move element up \n\n";
			if(stylusState_->selectedElement){
				tree_view_->moveElementUp(stylusState_->selectedElement->ToElement());
				tree_view_->createTree();
			}
		}
		if(e.modifiers() == Wt::KeyboardModifier::Shift && e.key() == Wt::Key::Down){
			std::cout << "\n\n Move element down \n\n";
			if(stylusState_->selectedElement){
				tree_view_->moveElementDown(stylusState_->selectedElement->ToElement());
				tree_view_->createTree();
			}
		}
		if(e.modifiers() == Wt::KeyboardModifier::Shift && e.key() == Wt::Key::Right){
			std::cout << "\n\n Move element right \n\n";
			if(stylusState_->selectedElement){
				tree_view_->moveElementRight(stylusState_->selectedElement->ToElement());
				tree_view_->createTree();
			}
		}
		if(e.modifiers() == Wt::KeyboardModifier::Control && e.key() == Wt::Key::C){
			std::cout << "\n\n Copy element \n\n";
			if(stylusState_->selectedElement){
				stylusState_->copyNode = stylusState_->selectedElement->DeepClone(&stylusState_->doc);
			}
		}
		if(e.modifiers() == Wt::KeyboardModifier::Control && e.key() == Wt::Key::V){
			std::cout << "\n\n Paste element \n\n";
			toggleOutline(false);
			if(stylusState_->selectedElement && stylusState_->copyNode){
				tree_view_->addSiblingElementAfter(stylusState_->selectedElement->ToElement(), stylusState_->copyNode->ToElement());
				tree_view_->createTree();
			}
		}


		if(e.modifiers() == Wt::KeyboardModifier::Control && e.key() == Wt::Key::Space){
			std::cout << "\n\n Focus on element contents \n\n";
			element_contents_->element_content_textarea->setFocus(true);
		}

		if(e.modifiers() == Wt::KeyboardModifier::Control && e.key() == Wt::Key::Q){
			std::cout << "\n\n launch search dialog \n\n";
			createSearchDialog();
		}

		if(e.modifiers() == Wt::KeyboardModifier::Control && e.key() == Wt::Key::B){
			if(Wt::WApplication::instance()->globalKeyWentDown().propagationPrevented()){
				std::cout << "\n\n propagation not prevented \n\n";
				Wt::WApplication::instance()->globalKeyWentDown().preventDefaultAction(false);
				Wt::WApplication::instance()->globalKeyWentDown().preventPropagation(false);
			}else {
				std::cout << "\n\n propagation Prevented \n\n";
				Wt::WApplication::instance()->globalKeyWentDown().preventDefaultAction(true);
				Wt::WApplication::instance()->globalKeyWentDown().preventPropagation(true);
			}
		}
	});
}

void StylusEdditor::createSearchDialog()
{
	if(Wt::WApplication::instance()->findWidget("search-dialog"))
	{
		Wt::WApplication::instance()->findWidget("search-input")->setFocus(true);
		return;
	}
	auto dialog = Wt::WApplication::instance()->root()->addChild(std::make_unique<Wt::WDialog>("title"));
	dialog->setObjectName("search-dialog");
	// dialog->setTitleBarEnabled(false);
	dialog->rejectWhenEscapePressed(true);
	dialog->setModal(false);
	dialog->setMovable(false);
	dialog->setResizable(false);
	dialog->setOffsets(100, Wt::Side::Top);
	dialog->setWidth(400);
	dialog->setStyleClass("text-center !border-0 !bg-transparent !p-0 !m-0 !rounded-none !shadow-none ");
	dialog->contents()->setStyleClass("max-w-full");
	// Set options for email address suggestions:
	Wt::WSuggestionPopup::Options options;
	options.highlightBeginTag = "<span class=\"highlight\">";
	options.highlightEndTag = "</span>";
	// options.listSeparator = " | ";
	// options.whitespace = "/";
	options.wordSeparators = " | ";
	// options.appendReplacedText = "/";

	auto sp = dialog->contents()->addChild(
      std::make_unique<Wt::WSuggestionPopup>(
            Wt::WSuggestionPopup::generateMatcherJS(options),
            Wt::WSuggestionPopup::generateReplacerJS(options)));

	auto lineEdit = dialog->contents()->addWidget(std::make_unique<Wt::WLineEdit>());
	lineEdit->keyWentDown().preventDefaultAction(true);
	lineEdit->keyWentDown().connect(this, [=](Wt::WKeyEvent e){
		if(e.modifiers() == Wt::KeyboardModifier::Control &&e.key() == Wt::Key::Z){
			lineEdit->setText("");
			setSearchOptions(sp, dialog, lineEdit, SearchOption::Folders);
		}else if (e.modifiers() == Wt::KeyboardModifier::Control &&e.key() == Wt::Key::X){
			lineEdit->setText("");
			setSearchOptions(sp, dialog, lineEdit, SearchOption::Classes);
		}else if (e.modifiers() == Wt::KeyboardModifier::Control &&e.key() == Wt::Key::C){
			lineEdit->setText("");
			setSearchOptions(sp, dialog, lineEdit, SearchOption::Focus);
		}
	});
	lineEdit->keyWentDown().preventDefaultAction(false);
	lineEdit->setObjectName("search-input");
	lineEdit->setStyleClass("bg-gray-50 border border-gray-300 text-gray-900 text-sm rounded-lg p-2.5 w-full max-w-full");
	lineEdit->setPlaceholderText("Search");
	sp->setStyleClass("flex wrap");
	sp->forEdit(lineEdit, Wt::PopupTrigger::Editing);
	
	sp->activated().connect(this, [=](){
		auto text = lineEdit->text().toUTF8();
		if(text[0] == '@'){
			text = text.substr(4);

			std::string folderName = "";
			std::string fileName = "";
			std::string messageId = "";
			auto pos = text.find("|");
			if(pos != std::string::npos){
			folderName = text.substr(0, pos-1);
			text = text.substr(pos + 2);
			}
			pos = text.find("|");
			if(pos != std::string::npos){
				fileName = text.substr(0, pos-1);
			}
			messageId = text.substr(pos + 2);

			setTemplate(folderName, fileName, messageId, "template", true);
			createDevApp();
	
		}else if (text[0] == '!'){
			text = text.substr(4);
			std::cout << "\n\n text: <" << text << ">\n\n";
			auto pos = text.find("|");
			std::string styleCathegory = text.substr(0, pos-1);
			pos = text.find("|");
			std::string styleClass = text.substr(pos + 2);

			std::cout << "\n\n styleCathegory: <" << styleCathegory << ">\n\n";
			std::cout << "\n\n styleClass: <" << styleClass << ">\n\n";
			if(styleCathegory.compare("spacing") == 0){
				if(styleClass.compare("reset") == 0){
					elementClassEdditor_->spacingWidget_->resetStyles();
				}else if(styleClass.find("p-") != std::string::npos){
					elementClassEdditor_->spacingWidget_->padding_all_widget_->setValue(styleClass);
				}else if(styleClass.find("py-") != std::string::npos){
					elementClassEdditor_->spacingWidget_->padding_horizontal_widget_->setValue(styleClass);
				}else if(styleClass.find("px-") != std::string::npos){
					elementClassEdditor_->spacingWidget_->padding_vertical_widget_->setValue(styleClass);
				}else if(styleClass.find("pt-") != std::string::npos){
					elementClassEdditor_->spacingWidget_->padding_top_widget_->setValue(styleClass);
				}else if(styleClass.find("pr-") != std::string::npos){
					elementClassEdditor_->spacingWidget_->padding_right_widget_->setValue(styleClass);
				}else if(styleClass.find("pb-") != std::string::npos){
					elementClassEdditor_->spacingWidget_->padding_bottom_widget_->setValue(styleClass);
				}else if(styleClass.find("pl-") != std::string::npos){
					elementClassEdditor_->spacingWidget_->padding_left_widget_->setValue(styleClass);
				}else if(styleClass.find("m-") != std::string::npos){
					elementClassEdditor_->spacingWidget_->margin_all_widget_->setValue(styleClass);
				}else if(styleClass.find("my-") != std::string::npos){
					elementClassEdditor_->spacingWidget_->margin_horizontal_widget_->setValue(styleClass);
				}else if(styleClass.find("mx-") != std::string::npos){
					elementClassEdditor_->spacingWidget_->margin_vertical_widget_->setValue(styleClass);
				}else if(styleClass.find("mt-") != std::string::npos){
					elementClassEdditor_->spacingWidget_->margin_top_widget_->setValue(styleClass);
				}else if(styleClass.find("mr-") != std::string::npos){
					elementClassEdditor_->spacingWidget_->margin_right_widget_->setValue(styleClass);
				}else if(styleClass.find("mb-") != std::string::npos){
					elementClassEdditor_->spacingWidget_->margin_bottom_widget_->setValue(styleClass);
				}else if(styleClass.find("ml-") != std::string::npos){
					elementClassEdditor_->spacingWidget_->margin_left_widget_->setValue(styleClass);
				}else if(styleClass.find("space-x-") != std::string::npos){
					if(styleClass.find("reverse-res") != std::string::npos){
						elementClassEdditor_->spacingWidget_->checkbox_space_x_reverse_->setChecked(false);
					}else if(styleClass.find("reverse") != std::string::npos){
						elementClassEdditor_->spacingWidget_->checkbox_space_x_reverse_->setChecked(true);
					}else {
						elementClassEdditor_->spacingWidget_->space_x_widget_->setValue(styleClass);
					}

				}else if(styleClass.find("space-y-") != std::string::npos){
					if(styleClass.find("reverse-res") != std::string::npos){
						elementClassEdditor_->spacingWidget_->checkbox_space_y_reverse_->setChecked(false);
					}else if(styleClass.find("reverse") != std::string::npos){
						elementClassEdditor_->spacingWidget_->checkbox_space_y_reverse_->setChecked(true);
					}else {
						elementClassEdditor_->spacingWidget_->space_y_widget_->setValue(styleClass);
					}
				}
				elementClassEdditor_->spacingWidget_->styleChanged().emit();
			}else if(styleCathegory.compare("sizing") == 0){
				
				if(styleClass.find("min-w-") != std::string::npos){
					elementClassEdditor_->sizingWidget_->minWidth_widget_->setValue(styleClass);
				}else if(styleClass.find("min-h-") != std::string::npos){
					elementClassEdditor_->sizingWidget_->minHeight_widget_->setValue(styleClass);
				}else if(styleClass.find("max-w-") != std::string::npos){
					elementClassEdditor_->sizingWidget_->maxWidth_widget_->setValue(styleClass);
				}else if(styleClass.find("max-h-") != std::string::npos){
					elementClassEdditor_->sizingWidget_->maxHeight_widget_->setValue(styleClass);
				}else if(styleClass.find("w-") != std::string::npos){
					elementClassEdditor_->sizingWidget_->width_widget_->setValue(styleClass);
				}else if(styleClass.find("h-") != std::string::npos){
					elementClassEdditor_->sizingWidget_->height_widget_->setValue(styleClass);
				}
				elementClassEdditor_->sizingWidget_->styleChanged().emit();
			}else if (styleCathegory.compare("backgrounds") == 0){
				if(styleClass.compare("reset") == 0){
					elementClassEdditor_->backgroundWidget_->resetStyles();
				}else if(boost::regex_match(styleClass, elementClassEdditor_->tailwindConfig_->backgrounds.background_color_regex)){
					elementClassEdditor_->backgroundWidget_->comboBox_color->setValue(styleClass);
				}
			}
		}
		lineEdit->setText("");
		lineEdit->setFocus(true);
	});
	dialog->finished().connect(this, [=](Wt::DialogCode code) {
		if(code == Wt::DialogCode::Accepted){
			std::cout << "\n\n accepted \n\n";
		}else {
			std::cout << "\n\n rejected \n\n";
		}
		Wt::WApplication::instance()->root()->removeChild(dialog);
	});
	dialog->animateShow(Wt::WAnimation(Wt::AnimationEffect::Fade, Wt::TimingFunction::EaseInOut, 250));
	setSearchOptions(sp, dialog, lineEdit, SearchOption::Classes);
}


void StylusEdditor::setSearchOptions(Wt::WSuggestionPopup *sp, Wt::WDialog *dialog, Wt::WLineEdit *lineEdit, SearchOption searchOption)
{
	sp->clearSuggestions();
	if(searchOption == SearchOption::Folders){
		dialog->setWindowTitle("Chose Template");
		for(auto& folder : stylus_templates_->folders_data_){
			auto option = "";
			for(auto& file : folder.xmlFiles){
				for(auto& message : file.messages){
					sp->addSuggestion("@ | " + folder.folderName + " | " + file.fileName + " | " + message);
				}
			}
		}
	}else if(searchOption == SearchOption::Classes){
		dialog->setWindowTitle("Set Style Classes");
		auto sizing_data = elementClassEdditor_->tailwindConfig_->sizing.search_data();
		auto spacing_data = elementClassEdditor_->tailwindConfig_->spacing.search_data();
		auto backgrounds_data = elementClassEdditor_->tailwindConfig_->backgrounds.search_data();

		sp->addSuggestion("! | sizing | reset");
		for(int i = 0; i < sizing_data.size(); i++){
			auto sizingData = sizing_data[i];
			if(sizingData.compare("sizing | none") == 0){
				sizingData = sizing_data[i+1];
				auto pos = sizingData.find_last_of("-");
				sizingData = sizingData.substr(0, pos);
				std::string text = "! | " + sizingData + "-res";
				sp->addSuggestion(text);
			}else {
				sp->addSuggestion("! | " + sizingData);
			}
		}

		sp->addSuggestion("! | spacing | reset");
		for(int i = 0; i < spacing_data.size(); i++){
			auto spacingData = spacing_data[i];
			if(spacingData.compare("spacing | none") == 0){
				spacingData = spacing_data[i+1];
				auto pos = spacingData.find_last_of("-");
				spacingData = spacingData.substr(0, pos);
				std::string text = "! | " + spacingData + "-res";
				sp->addSuggestion(text);
			}else if(spacingData.compare("spacing/space-x-reverse") == 0){
				sp->addSuggestion("! | spacing/space-x-reverse-res");
				sp->addSuggestion("! | " + spacingData);
			}else if(spacingData.compare("spacing/space-y-reverse") == 0){
				sp->addSuggestion("! | spacing/space-y-reverse-res");
				sp->addSuggestion("! | " + spacingData);
			}else{
				sp->addSuggestion("! | " + spacingData);
			}
		}

		sp->addSuggestion("! | backgrounds | reset");
		for(int i = 0; i < backgrounds_data.size(); i++){
			auto backgroundsData = backgrounds_data[i];
			if(backgroundsData.compare("backgrounds | none") == 0){
				backgroundsData = backgrounds_data[i+1];
				auto pos = backgroundsData.find_last_of(" | ");
				backgroundsData = backgroundsData.substr(0, pos);
				std::string text = "! | " + backgroundsData + "-res";
				sp->addSuggestion(text);
			}else {
				sp->addSuggestion("! | " + backgroundsData);
			}
		}
	}else if(searchOption == SearchOption::Focus){

	}else if(searchOption == SearchOption::ColorIntensity){
		auto intensity_variants = elementClassEdditor_->tailwindConfig_->color_intensity_VARIANTS;
		auto currentText = lineEdit->text().toUTF8();
		for(auto& variant : intensity_variants){
			sp->addSuggestion("! | backgrounds | " + currentText +"-"+ variant);
		}
	}else if(searchOption == SearchOption::ColorOpacity){
		auto opacity_variants = elementClassEdditor_->tailwindConfig_->color_opacity_VARIANTS;
		auto currentText = lineEdit->text().toUTF8();
		for(auto& variant : opacity_variants){
			sp->addSuggestion("! | backgrounds | " + currentText +"-"+ variant);
		}
	}
	
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
    prev_temp_btn_->setStyleClass("block cursor-pointer rounded-lg border-0 p-1 bg-neutral-900 hover:bg-neutral-800");
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
