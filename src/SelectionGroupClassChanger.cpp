#include "include/SelectionGroupClassChanger.h"
#include <Wt/WApplication.h>

void SelectionGroupClassChanger::setCustom(bool custom)
{
	if(custom_start_.compare("none") == 0) return;
	if(custom){
		checkBox_custom_value_->setChecked(true);
		btns_container->hide();
		lineEdit_custom_value_->show();
		// lineEdit_custom_value_->setFocus();
		checkBox_custom_value_->toggleStyleClass("[&>span]:text-green-700", true, true);
	}else {
		checkBox_custom_value_->setChecked(false);
		lineEdit_custom_value_->hide();
		btns_container->show();
		// comboBox_class->setFocus();
		checkBox_custom_value_->toggleStyleClass("[&>span]:text-green-700", false, true);
	}

}

void SelectionGroupClassChanger::setCustomValueString(std::string custom_start)
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

	lineEdit_custom_value_->keyWentUp().connect(this, [=](Wt::WKeyEvent e){
		if(e.modifiers() == Wt::KeyboardModifier::Control)
		{
			if(e.key() == Wt::Key::Delete){
				// reset to default
                setValue(defaultValue);
				checkbox_important_->setChecked(false);
				checkbox_important_->toggleStyleClass("text-red-500", false, true);
				classChanged_.emit(getValue());
				// comboBox_class->setFocus();
			}else if (e.key() == Wt::Key::End){
				// toggle important
				if(checkbox_important_->isChecked()) {
					checkbox_important_->setChecked(false);
					checkbox_important_->toggleStyleClass("text-red-500", false, true);
				} else {
					checkbox_important_->setChecked(true);
					checkbox_important_->toggleStyleClass("text-red-500", true, true);
				}
			}else if (e.key() == Wt::Key::Home){
				// toggle custom value
				if(checkBox_custom_value_->isChecked()) {
					setCustom(false);
					// comboBox_class->setFocus(true);
				} else {
					setCustom(true);
					lineEdit_custom_value_->setFocus(true);
				}
			}

		}
		 if (e.key() == Wt::Key::Escape){
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
			classChanged_.emit(getValue());
		}
		lineEdit_custom_value_->setFocus();
	});
}


SelectionGroupClassChanger::SelectionGroupClassChanger(Propriety propriety, std::string title, std::string classRepeatName)
	: Wt::WContainerWidget(),
	group_(std::make_shared<Wt::WButtonGroup>()),
    propriety_(propriety)
{
	titleBar = addWidget(std::make_unique<Wt::WContainerWidget>());
	content = addWidget(std::make_unique<Wt::WContainerWidget>());

	setStyleClass("flex flex-col border border-solid pb-1 border-neutral-900");
	titleBar->setStyleClass("flex items-center font-bold text-neutral-400 text-sm");
	content->setStyleClass("flex flex-wrap items-center");

	titleBar->addWidget(std::make_unique<Wt::WText>(title));

    checkbox_important_ = titleBar->addWidget(std::make_unique<Wt::WCheckBox>("!"));
    lineEdit_custom_value_ = content->addWidget(std::make_unique<Wt::WLineEdit>());
    btn_reset_ = titleBar->addWidget(std::make_unique<Wt::WText>("↺"));
    checkBox_custom_value_ = titleBar->addWidget(std::make_unique<Wt::WCheckBox>("]"));
	
    titleBar->addWidget(std::make_unique<Wt::WText>(classRepeatName))->setStyleClass("me-2");
	
	btn_reset_->setThemeStyleEnabled(false);
	lineEdit_custom_value_->hide();
	lineEdit_custom_value_->disable();
	checkBox_custom_value_->hide();
	checkBox_custom_value_->disable();

	// set styles
	btn_reset_->setStyleClass("mr-auto hover:bg-neutral-800 text-center p-0.5 cursor-pointer");
	checkBox_custom_value_->setStyleClass("hover:bg-neutral-800 text-center p-0.5 [&>input]:hidden [&>span]:px-1 [&>span]:cursor-pointer [&>span]:m-0 [&>span]:py-0 [&>span]:hover:bg-neutral-95 rounded-md font-bold");
	
	checkbox_important_->setStyleClass("ml-auto hover:bg-neutral-800 text-center p-0.5 [&>input]:hidden [&>span]:px-1 [&>span]:text [&>span]:cursor-pointer [&>span]:m-0 [&>span]:py-0 [&>span]:hover:bg-neutral-950 rounded-md font-bold");
	lineEdit_custom_value_->setStyleClass("px-1 w-full grow rounded-md h-full bg-neutral-800 text-center appearance-none hover:bg-neutral-900 min-w-[70px]");
    

	std::string button_styles = 
	R"(
		flex w-fit h-fit cursor-pointer m-px p-px text-neutral-950 font-bold text-xs
		[&>span]:bg-cover [&>input]:hidden [&>span]:m-px [&>span]:rounded-md [&>span]:px-1
		[&>span]:bg-neutral-300 
		[&>span]:hover:bg-neutral-800 [&>span]:hover:text-neutral-50  
		[&>input:checked_+_span]:bg-neutral-800 [&>input:checked_+_span]:text-neutral-50 [&>input:checked_+_span]:ring
	)";

	if(classRepeatName.compare("") != 0){
		for(int index = 0; index < propriety.styleClasses_.size(); ++index){
			auto styleClass = propriety.styleClasses_[index];
			auto btn = content->addWidget(std::make_unique<Wt::WRadioButton>(""));
			btn->setStyleClass(button_styles);
			if(styleClass.className_.compare("none") == 0){
				btn->addStyleClass("[&>span]:bg-[url(resources/icons/red-cross.svg)] [&>span]:!p-2.5");
			}else {
				btn->setText(styleClass.className_.substr(classRepeatName.length()));
			}
			btn->clicked().connect(this, [=](){
                // classChanged_.emit(styleClass.className_);
				group_->setCheckedButton(btn);
			});
			group_->addButton(btn, index);
		}
	} else {
		for(int index = 0; index < propriety.styleClasses_.size(); ++index){
			auto styleClass = propriety.styleClasses_[index];
			auto btn = content->addWidget(std::make_unique<Wt::WRadioButton>(""));
			btn->setStyleClass(button_styles);
			if(styleClass.className_.compare("none") == 0){
				btn->addStyleClass("[&>span]:bg-[url(resources/icons/red-cross.svg)] [&>span]:!p-2");
			}else {
				btn->setText(styleClass.className_);
                
			}
			btn->clicked().connect(this, [=](){
				// classChanged_.emit(styleClass.className_);
                group_->setCheckedButton(btn);
			});
			group_->addButton(btn, index);
		}
	}

    btn_reset_->clicked().connect(this, [=](){
        setValue(defaultValue);
        classChanged_.emit(getValue());
    });

	checkbox_important_->clicked().connect(this, [=](){
		if(checkbox_important_->isChecked()){
			checkbox_important_->toggleStyleClass("text-red-500", true, true);
		}else {
			checkbox_important_->toggleStyleClass("text-red-500", false, true);
		}
		if(getValue().compare(defaultValue) != 0) classChanged_.emit(getValue());
	});

	group_->checkedChanged().connect(this, [=](Wt::WRadioButton *btn){
        group_->setCheckedButton(btn);
		classChanged_.emit(getValue());
	});
    setValue(defaultValue);
}


std::string SelectionGroupClassChanger::getValue()
{
	std::string selectedClass = "";

		if(custom_start_.compare("none") != 0 &&
			checkBox_custom_value_->isChecked() && 
			lineEdit_custom_value_->text().toUTF8() != ""
		){
			selectedClass = custom_start_ + "[" + lineEdit_custom_value_->valueText().toUTF8() + "]";
		}else{

			selectedClass = propriety_.styleClasses_[group_->checkedId()].className_;
		}	
		if(checkbox_important_->isChecked() && selectedClass.compare(defaultValue) != 0){
			selectedClass = "!" + selectedClass;
		}


return selectedClass;
}

void SelectionGroupClassChanger::setValue(std::string className)
{
	std::string reset = "res";
	if(className.compare("") == 0 || className.compare("none") == 0 || className.substr(className.length() - reset.length()) == reset)
	{   
        auto index = getIndesOfStringInVector(defaultValue, propriety_.styleClasses_);
		group_->setSelectedButtonIndex(index);

		checkbox_important_->setChecked(false);
		checkbox_important_->toggleStyleClass("text-red-500", false, true);
		if(custom_start_.compare("none") != 0){
			setCustom(false);
		}
		return;
	}
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
        auto index = getIndesOfStringInVector(className, propriety_.styleClasses_);
		group_->setSelectedButtonIndex(index);

	}
}

void SelectionGroupClassChanger::disable(bool disable)
{
	// if(disable)
	// {
	// 	for(auto btn : group_->buttons()){
    //         btn->disable();
    //     }
	// 	btn_reset_->disable();
	// 	checkBox_custom_value_->disable();
	// 	checkbox_important_->disable();
	// 	lineEdit_custom_value_->disable();
	// }else {
    //     for(auto btn : group_->buttons()){
    //         btn->enable();
    //     }
	// 	btn_reset_->enable();
	// 	checkBox_custom_value_->enable();
	// 	checkbox_important_->enable();
	// 	lineEdit_custom_value_->enable();
	// }
}















int SelectionGroupClassChanger::getIndesOfStringInVector(std::string str, std::vector<StyleClass> vec){
	for(int index = 0; index < vec.size(); ++index){
		if(vec[index].className_.compare(str) == 0) return index;
	}
	return 0;
}
