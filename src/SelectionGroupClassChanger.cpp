#include "include/SelectionGroupClassChanger.h"
#include <Wt/WApplication.h>
#include <Wt/WText.h>

SelectionGroupClassChanger::SelectionGroupClassChanger(Propriety propriety, std::string title, std::string classRepeatName)
	: Wt::WContainerWidget(),
	group_(std::make_shared<Wt::WButtonGroup>()),
    propriety_(propriety)
{
	titleBar = addWidget(std::make_unique<Wt::WContainerWidget>());
	if(propriety.styleClasses_.size() <= 5){
		content = titleBar->insertBefore(std::make_unique<Wt::WContainerWidget>(), checkbox_important_);
		content->setStyleClass("flex flex-wrap items-center");
	} else {
		content = addWidget(std::make_unique<Wt::WContainerWidget>());
	}
	setCanReceiveFocus(true);
	setStyleClass("flex flex-col border-b border-solid pb-1 border-neutral-900");
	titleBar->setStyleClass("flex items-center font-bold text-neutral-400 text-sm");
	content->setStyleClass("flex flex-wrap items-center");


	title_ = titleBar->insertWidget(0, std::make_unique<Wt::WAnchor>(title));

    checkbox_important_ = titleBar->addWidget(std::make_unique<Wt::WCheckBox>("!"));
    btn_reset_ = titleBar->addWidget(std::make_unique<Wt::WText>("↺"));
	
	btn_reset_->setThemeStyleEnabled(false);

	// set styles
	title_->setStyleClass("ml-1 mr-1");
	btn_reset_->setStyleClass("hover:bg-neutral-800 text-center text-white p-0.5 cursor-pointer");
	
	checkbox_important_->setStyleClass(" ml-auto hover:bg-neutral-800 text-center text-white p-0.5 [&>input]:hidden [&>span]:px-1 [&>span]:text [&>span]:cursor-pointer [&>span]:m-0 [&>span]:py-0 [&>span]:hover:bg-neutral-950 rounded-md font-bold");
    

	std::string button_styles = 
	R"(
		flex w-fit h-fit cursor-pointer m-px p-px text-neutral-950 font-bold text-[14px]
		[&>span]:bg-cover [&>input]:hidden [&>span]:m-px [&>span]:rounded-md [&>span]:px-1
		[&>span]:bg-neutral-300 
		[&>span]:hover:bg-neutral-800 [&>span]:hover:text-neutral-50  
		[&>input:checked_+_span]:bg-neutral-800 [&>input:checked_+_span]:text-neutral-50 [&>input:checked_+_span]:ring
	)";

	if(classRepeatName.compare("") != 0){
		// title_->setText(classRepeatName);
		for(int index = 0; index < propriety.styleClasses_.size(); ++index){
			auto styleClass = propriety.styleClasses_[index];
			auto btn = content->addWidget(std::make_unique<Wt::WRadioButton>(""));
			btn->setToolTip(Wt::WString().tr("tooltip-styleClasses").arg(styleClass.className_).arg("seccond argument"), Wt::TextFormat::UnsafeXHTML);

			btn->setStyleClass(button_styles);
			if(styleClass.className_.compare("none") == 0){
				btn->addStyleClass("[&>span]:bg-[url(resources/icons/red-cross.svg)] [&>span]:!p-2");
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


	selectedClass = propriety_.styleClasses_[group_->checkedId()].className_;

	if(checkbox_important_->isChecked() && selectedClass.compare(defaultValue) != 0){
		selectedClass = "!" + selectedClass;
	}


return selectedClass;
}

void SelectionGroupClassChanger::setValue(std::string className)
{
	if(className.compare("") == 0 || className.compare("none") == 0)
	{   
        auto index = getIndesOfStringInVector(defaultValue, propriety_.styleClasses_);
		group_->setSelectedButtonIndex(index);

		checkbox_important_->setChecked(false);
		checkbox_important_->toggleStyleClass("text-red-500", false, true);
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




	// std::cout << "\n\n default value :" << className << "\n\n";
	auto index = getIndesOfStringInVector(className, propriety_.styleClasses_);
	group_->setSelectedButtonIndex(index);

}

void SelectionGroupClassChanger::disable(bool disable)
{
	checkbox_important_->setDisabled(disable);
	for(auto btn : group_->buttons()){
		btn->setDisabled(disable);
	}
}


int SelectionGroupClassChanger::getIndesOfStringInVector(std::string str, std::vector<StyleClass> vec){
	for(int index = 0; index < vec.size(); ++index){
		if(vec[index].className_.compare(str) == 0) return index;
	}
	return 0;
}
