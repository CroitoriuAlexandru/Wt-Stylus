#include "include/ElementBackground.h"
#include "include/ComboBoxes.h"
#include <iostream>
#include <regex>
#include <Wt/WApplication.h>

void StyleClassComboBox::setCustom(bool custom)
{
	// if(custom_start_.compare("none") == 0) return;
	if(custom){
		checkBox_custom_value_->setChecked(true);
		comboBox_class->hide();
		lineEdit_custom_value_->show();
		lineEdit_custom_value_->setFocus();
		checkBox_custom_value_->toggleStyleClass("[&>span]:text-green-700", true, true);
	}else {
		checkBox_custom_value_->setChecked(false);
		lineEdit_custom_value_->hide();
		comboBox_class->show();
		comboBox_class->setFocus();
		checkBox_custom_value_->toggleStyleClass("[&>span]:text-green-700", false, true);
	}

}

void StyleClassComboBox::setCustomValueString(std::string custom_start)
{
	custom_start_ = custom_start;

	lineEdit_custom_value_->show();
	checkBox_custom_value_->show();

	lineEdit_custom_value_->enable();
	checkBox_custom_value_->enable();
	

	checkBox_custom_value_->clicked().connect(this, [=](){
		if(checkBox_custom_value_->isChecked()){
			setCustom(true);
		}else{
			setCustom(false);
		}
	});

	lineEdit_custom_value_->keyWentUp().preventDefaultAction(true);

	lineEdit_custom_value_->keyWentUp().connect(this, [=](Wt::WKeyEvent e){
		if(e.modifiers() == Wt::KeyboardModifier::Control  && e.key() == Wt::Key::Z){
			if(lineEdit_custom_value_->valueText() == "") return;
			if(checkbox_important_->isChecked()) {
				checkbox_important_->setChecked(false);
				checkbox_important_->toggleStyleClass("text-red-500", false, true);
			} else {
				checkbox_important_->setChecked(true);
				checkbox_important_->toggleStyleClass("text-red-500", true, true);
			}
			classChanged_.emit(current_value);
		}else if(e.modifiers() == Wt::KeyboardModifier::Control  && e.key() == Wt::Key::X){
			if(custom_start_.compare("none") == 0) return;
			if(checkBox_custom_value_->isChecked()) {
				setCustom(false);
			} else {
				setCustom(true);
			}
		}else if (e.modifiers() == Wt::KeyboardModifier::Control  && e.key() == Wt::Key::Q){
			auto app = Wt::WApplication::instance();
			auto search_input = app->findWidget("search-input");
			if(search_input != nullptr) search_input->setFocus(true);
			else {
				app->findWidget("stylus")->setFocus(true);
			}
		}
	});

	lineEdit_custom_value_->enterPressed().connect(this, [=](){
		if(lineEdit_custom_value_->text().toUTF8() != ""){
			current_value = custom_start_ + "[" + lineEdit_custom_value_->valueText().toUTF8() + "]";
			if(checkbox_important_->isChecked()) current_value = "!" + current_value;
			classChanged_.emit(current_value);
			// lineEdit_custom_value_->setFocus(true);
		}
	});
}

StyleClassComboBox::StyleClassComboBox(Propriety propriety)
	: Wt::WContainerWidget()
{
	setStyleClass("flex justify-betwen items-center w-full text-sm py-0.5 rounded-sm");
	
	checkbox_important_ = addWidget(std::make_unique<Wt::WCheckBox>("!"));
	comboBox_class = addWidget(std::make_unique<Wt::WComboBox>());
	lineEdit_custom_value_ = addWidget(std::make_unique<Wt::WLineEdit>());
	btn_reset_ = addWidget(std::make_unique<Wt::WText>("↺"));
	checkBox_custom_value_ = addWidget(std::make_unique<Wt::WCheckBox>("]"));

	btn_reset_->setThemeStyleEnabled(false);
	
	lineEdit_custom_value_->hide();
	lineEdit_custom_value_->disable();
	checkBox_custom_value_->hide();
	checkBox_custom_value_->disable();

	// set styles
	btn_reset_->setStyleClass("hover:bg-neutral-800 text-center p-0.5 cursor-pointer");
	comboBox_class->setStyleClass("px-1 w-full grow rounded-md h-full bg-neutral-800 text-center appearance-none hover:bg-neutral-900 min-w-[70px]");
	checkBox_custom_value_->setStyleClass("hover:bg-neutral-800 text-center p-0.5 [&>input]:hidden [&>span]:px-1 [&>span]:text [&>span]:cursor-pointer [&>span]:m-0 [&>span]:py-0 [&>span]:hover:bg-neutral-95 rounded-md font-bold");
	
	checkbox_important_->setStyleClass("hover:bg-neutral-800 text-center p-0.5 [&>input]:hidden [&>span]:px-1 [&>span]:text [&>span]:cursor-pointer [&>span]:m-0 [&>span]:py-0 [&>span]:hover:bg-neutral-950 rounded-md font-bold");
	lineEdit_custom_value_->setStyleClass("px-1 w-full grow rounded-md h-full bg-neutral-800 text-center appearance-none hover:bg-neutral-900 min-w-[70px]");
	

	// setOptions(propriety);

	for(auto& styleClass : propriety.styleClasses_){
		comboBox_class->addItem(styleClass.className_);
	}
	
	btn_reset_->clicked().connect(this, [=](){
		checkBox_custom_value_->setChecked(false);
		setCustom(false);
		comboBox_class->setCurrentIndex(comboBox_class->findText(defaultValue, Wt::MatchFlag::StringExactly));
		checkbox_important_->setChecked(false);
		checkbox_important_->toggleStyleClass("text-red-500", false, true);
		classChanged_.emit(current_value);
	});


	checkbox_important_->clicked().connect(this, [=](){
		if(checkbox_important_->isChecked()){
			checkbox_important_->toggleStyleClass("text-red-500", true, true);
		}else {
			checkbox_important_->toggleStyleClass("text-red-500", false, true);
		}
		current_value = "!" + current_value;
		if(getValue().compare(defaultValue) != 0) classChanged_.emit(getValue());


	});


	// emit signal when something changes
	comboBox_class->sactivated().connect(this, [=](Wt::WString className){
		if(checkbox_important_->isChecked()) current_value = "!" + className.toUTF8();
		else current_value = className.toUTF8();
		classChanged_.emit(current_value);
	});


	classChanged_.connect(this, [=](){
		if(getValue().compare("none") == 0) 
			toggleStyleClass("bg-neutral-900", false);
			else 
			toggleStyleClass("bg-neutral-900", true);

		if(checkBox_custom_value_->isChecked()) lineEdit_custom_value_->setFocus();
		else comboBox_class->setFocus();
	});

	comboBox_class->keyWentUp().connect(this, [=](Wt::WKeyEvent e){
		if(e.modifiers() == Wt::KeyboardModifier::Control  && e.key() == Wt::Key::Z){
			if(comboBox_class->currentText() == "none") return;
			if(checkbox_important_->isChecked()) {
				checkbox_important_->setChecked(false);
				checkbox_important_->toggleStyleClass("text-red-500", false, true);
			} else {
				checkbox_important_->setChecked(true);
				checkbox_important_->toggleStyleClass("text-red-500", true, true);
			}
			classChanged_.emit(current_value);
		}else if(e.modifiers() == Wt::KeyboardModifier::Control  && e.key() == Wt::Key::X){
			if(custom_start_.compare("none") == 0) return;
			if(checkBox_custom_value_->isChecked()) {
				setCustom(false);
			} else {
				setCustom(true);
			}
		}else if (e.modifiers() == Wt::KeyboardModifier::Control  && e.key() == Wt::Key::Q){
			auto app = Wt::WApplication::instance();
			auto search_input = app->findWidget("search-input");
			if(search_input != nullptr) search_input->setFocus(true);
			else {
				app->findWidget("stylus")->setFocus(true);
			}
		}
	});

	setValue("none");
}

void StyleClassComboBox::setValue(std::string className)
{
	current_value = className;

	//  this is used by the search to reset styles to the default value 
	std::string reset = "res";
	if(className.compare("") == 0 || className.compare("none") == 0 || className.substr(className.length() - reset.length()) == reset)
	{
		comboBox_class->setCurrentIndex(comboBox_class->findText(defaultValue, Wt::MatchFlag::StringExactly));
		checkbox_important_->setChecked(false);
		checkbox_important_->toggleStyleClass("text-red-500", false, true);
		if(custom_start_.compare("none") != 0){
			checkBox_custom_value_->setChecked(false);
			setCustom(false);
		}
		toggleStyleClass("bg-neutral-900", false);
		return;
	}
	toggleStyleClass("bg-neutral-900", true);
	// check for ! at the start of the class
	if(className.find("!") != std::string::npos){
		// std::cout << "\n\n important value :" << className << "\n\n";
		checkbox_important_->setChecked(true);
		// comboBox_class->checkbox_important_->clicked().emit(Wt::WMouseEvent());
		className = className.substr(1, className.length()-1);
		checkbox_important_->toggleStyleClass("text-red-500", true);
	}


	if(className.find("]") != std::string::npos) {
		// std::cout << "\n\n custom value :" << className << "\n\n";
		checkBox_custom_value_->setChecked(true);
		checkBox_custom_value_->clicked().emit(Wt::WMouseEvent());
		// find the next '[' position in className
		int pos = className.find("[");
		if(pos != std::string::npos){
			// find the next ']' position in className
			int pos2 = className.find("]");
			if(pos2 != std::string::npos){
				// get the value between '[' and ']'
				std::string value = className.substr(pos+1, pos2-pos-1);
				lineEdit_custom_value_->setText(value);
			}
		}

	}else {
		// std::cout << "\n\n default value :" << className << "\n\n";
		checkBox_custom_value_->setChecked(false);
		checkBox_custom_value_->clicked().emit(Wt::WMouseEvent());
		comboBox_class->setCurrentIndex(comboBox_class->findText(className, Wt::MatchFlag::StringExactly));
		
	}
}

void StyleClassComboBox::disable(bool disable)
{
	if(disable)
	{
		comboBox_class->disable();
		btn_reset_->disable();
		checkBox_custom_value_->disable();
		checkbox_important_->disable();
		lineEdit_custom_value_->disable();
	}else {
		comboBox_class->enable();
		btn_reset_->enable();
		checkBox_custom_value_->enable();
		checkbox_important_->enable();
		lineEdit_custom_value_->enable();
	}
}


ColorSelecionWidget::ColorSelecionWidget(ProprietyColor proprietyColor, std::string title)
	: Wt::WContainerWidget(),
	colors_group(std::make_shared<Wt::WButtonGroup>())
{
	setStyleClass("mx-auto");
	auto colors_header = addWidget(std::make_unique<Wt::WContainerWidget>());
	auto opacity_wrapper = addWidget(std::make_unique<Wt::WContainerWidget>());
	auto colors_picker_wrapper = addWidget(std::make_unique<Wt::WContainerWidget>());

	colors_header->addWidget(std::make_unique<Wt::WText>(title))->setStyleClass("font-bold text-neutral-400");

	colors_header->setStyleClass("flex items-center ");
	colors_header->addWidget(std::make_unique<Wt::WText>("Opacity"))->setStyleClass("font-bold text-neutral-400 text-sm ml-auto mr-1");

	opacity_widget = colors_header->addWidget(std::make_unique<Wt::WSpinBox>());
	opacity_widget->setStyleClass("min-h-fit min-w-fit");

	opacity_widget->setRange(0, 100);
	opacity_widget->setSingleStep(5);
	opacity_widget->setStyleClass("bg-neutral-800 text-neutral-400 appearance-none hover:bg-neutral-900");

	auto colors_size = proprietyColor.styleClasses_.size();
	auto intensities_size = proprietyColor.intensity_.styleClasses_.size();
	int index = 0;
	auto row_wrapper = colors_picker_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());

	for(int i = 0; i < colors_size; ++i)
	{
		Wt::WString color_class = proprietyColor.styleClasses_[i].className_;

		if(	std::regex_match(proprietyColor.styleClasses_[i].className_, regex_def_classes) 
		|| color_class == "none") 
		{

		row_wrapper->setStyleClass("flex flex-row-reverse");
			auto btn = row_wrapper->addWidget(std::make_unique<Wt::WRadioButton>(""));
			btn->setStyleClass("flex w-fit h-fit cursor-pointer m-px mx-0.5 p-px");
			btn->addStyleClass("[&>span]:bg-cover [&>input]:hidden [&>span]:p-2.5 [&>span]:m-px [&>span]:rounded-md");
			btn->addStyleClass("[&>span]:bg-neutral-500 [&>span]:hover:bg-neutral-400 [&>input:checked_+_span]:bg-neutral-400");
			if(color_class == "none") {
				btn->addStyleClass("[&>span]:bg-[url(resources/icons/red-cross.svg)] ");
			}else {
				btn->addStyleClass("[&>span]:!p-0.5 mr-auto text-xs [&>span]:bg-neutral-900 [&>span]:text-semibold [&>span]:hover:bg-neutral-800 text-white [&>input:checked_+_span]:bg-neutral-400 [&>span]:text-center [&>input:checked_+_span]:text-black");
				std::string btn_text = color_class.toUTF8().substr(color_class.toUTF8().find("-")+1, color_class.toUTF8().length()-color_class.toUTF8().find("-")-1); 
				btn->setText(btn_text);

			}
			Wt::WString tooltip_text = "";

			colors_group->addButton(btn, index);
			colors_vector.push_back(color_class.toUTF8());
			++index;
			continue;
		}
		// a new row is created for each color
		row_wrapper = colors_picker_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
		row_wrapper->setStyleClass("flex");

		for(int intensity_i = 0; intensity_i < intensities_size; ++intensity_i)
		{
			std::string full_color_class = color_class.toUTF8() + "-" + proprietyColor.intensity_.styleClasses_[intensities_size-intensity_i-1].className_;
			auto btn = row_wrapper->addWidget(std::make_unique<Wt::WRadioButton>(""));
			Wt::WString tooltip_text = "not set yet";

			// substract the string from the first - position
			auto pos = color_class.toUTF8().find("-");
			std::string just_the_color = full_color_class.substr(pos+1, full_color_class.length()-pos-1);
			btn->setStyleClass("flex w-fit h-fit cursor-pointer");
			btn->addStyleClass("[&>input]:hidden [&>span]:px-3 [&>span]:py-1 [&>span]:m-px");
			btn->addStyleClass("[&>span]:bg-"+just_the_color+" [&>span]:hover:ring [&>input:checked_+_span]:ring-4 [&>input:checked_+_span]:ring-black [&>input:checked_+_span]:z-50");

			btn->setToolTip(Wt::WString().tr("tooltip-styleClasses").arg(tooltip_text).arg(full_color_class), Wt::TextFormat::UnsafeXHTML);

			colors_group->addButton(btn, index);
			colors_vector.push_back(full_color_class);
			++index;
			
		}
	}
	for(auto color : colors_vector){
		// std::cout << "\n color: " << color << "\n";
	}
	colors_group->checkedChanged().connect(this, [=](){ classChanged_.emit(current_value);});
	opacity_widget->valueChanged().connect(this, [=](){ 
		if(opacity_widget->value() > 100) opacity_widget->setValue(100); classChanged_.emit(current_value);
	});
	opacity_widget->enterPressed().connect(this, [=](){ 
		if(opacity_widget->value() > 100) opacity_widget->setValue(100); classChanged_.emit(current_value);
		 opacity_widget->setFocus();
	});

}


int ColorSelecionWidget::getIndexOfStringInVector(std::string str, std::vector<std::string> vec){
	for(int index = 0; index < vec.size(); ++index){
		if(vec[index].compare(str) == 0) return index;
	}
	return 0;
}

void ColorSelecionWidget::setValue(std::string className)
{
	std::cout << "\n\n className: " << className << "\n\n";
	current_value = className;
	if(className.compare("none") == 0) {
		colors_group->button(5)->setChecked(true);
		opacity_widget->setValue(100);
		colors_group->seedId(0);
		return;
	}
		
	std::string class_name = className.substr(0, className.find("/"));
	int index = getIndexOfStringInVector(className.substr(0, className.find("/")), colors_vector);
	std::string color_class_name = colors_vector[index];
	// std::cout << "\n class name:" << class_name << "\n\n";
	// std::cout << "\n class from vector: " << color_class_name << "\n";
	colors_group->button(index)->setChecked(true);

	if(className.find("/") != std::string::npos){
		std::string opacity = className.substr(className.find("/")+1, className.length()-className.find("/")-1);
		opacity_widget->setValue(std::stoi(opacity));
	}
}

std::string ColorSelecionWidget::getValue()
{
	std::string selectedClass = colors_vector[colors_group->checkedId()];
	if(selectedClass.compare("none") == 0) {
		return selectedClass;
	}
	int opacity_value = opacity_widget->value();
	if(opacity_value != 100){
		if(opacity_value % 5 != 0) opacity_value = opacity_value - (opacity_value % 5);
		opacity_widget->setValue(opacity_value);
		selectedClass += "/" + std::to_string(opacity_widget->value());
	} 
	return selectedClass;
}
