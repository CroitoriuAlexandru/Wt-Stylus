#include "include/ElementSpacing.h"
#include <regex>
#include <Wt/WBreak.h>
#include <Wt/WPopupMenu.h>
#include <Wt/WMenuItem.h>

ElementSpacingWidget::ElementSpacingWidget(std::shared_ptr<Config> tailwindConfig)
	: tailwindConfig_(tailwindConfig)
{
	setStyleClass("min-w-fit max-w-[300px] !border-x-0 text-center !bg-neutral-700 !text-neutral-200 !border-neutral-900 px-1.5");
	setTitle("Spacing");
	titleBarWidget()->setStyleClass("flex items-center space-x-3 !border-b border-solid border-neutral-900 bg-neutral-800");
	setCollapsible(true);

	
	auto popupMenu = std::make_unique<Wt::WPopupMenu>();
	std::string menuItemsStyles = "p-2 m-1 hover:bg-neutral-800 hover:text-neutral-200";
	popupMenu->addItem("set test classes")->setStyleClass(menuItemsStyles);
	popupMenu->addItem("reset styles")->setStyleClass(menuItemsStyles);
	popupMenu->addSeparator()->setStyleClass("border border-solid border-neutral-900");

	auto padding_info = popupMenu->addItem("Info Padding");
	auto margin_info = popupMenu->addItem("Info Margin");
	auto space_info = popupMenu->addItem("Info Space between");
	
	Wt::WLink margin_link = Wt::WLink(tailwindConfig_->spacing.margin.docsLink_);
	Wt::WLink padding_link = Wt::WLink(tailwindConfig_->spacing.padding.docsLink_);
	Wt::WLink space_link = Wt::WLink(tailwindConfig_->spacing.space_x.docsLink_);

	margin_link.setTarget(Wt::LinkTarget::NewWindow);
	padding_link.setTarget(Wt::LinkTarget::NewWindow);
	space_link.setTarget(Wt::LinkTarget::NewWindow);

	margin_info->setLink(margin_link);
	padding_info->setLink(padding_link);
	space_info->setLink(space_link);

	margin_info->setStyleClass(menuItemsStyles);
	padding_info->setStyleClass(menuItemsStyles);
	space_info->setStyleClass(menuItemsStyles);

	popupMenu->setStyleClass("bg-neutral-700 text-neutral-200 border border-solid border-neutral-900");

	popupMenu->triggered().connect(this, [=](Wt::WMenuItem *item) {
		if(item->text().toUTF8().compare("set test classes") == 0){
			setCustomTestValues();
			styleChanged_.emit(getStyles());
		}else if(item->text().toUTF8().compare("reset styles") == 0){
			resetStyles();
			styleChanged_.emit(getStyles());
		}
	});

	auto popupBtn = titleBarWidget()->addWidget(std::make_unique<Wt::WPushButton>());
	popupBtn->setStyleClass("p-3 bg-cover bg-[url(resources/icons/hamburger.svg)] !ml-auto mr-2 ");
	popupBtn->setMenu(std::move(popupMenu));
	
	// prevent the click event from propagating to the parent because it is located in the title bar witch expands and collapse on click
	popupBtn->clicked().preventPropagation();
	auto centralWidget = setCentralWidget(std::make_unique<Wt::WContainerWidget>());

	auto margin_padding_general_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>())->setStyleClass("border-b border-solid border-neutral-800 w-full p-px my-1");
	auto directions_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>())->setStyleClass("border-b border-solid border-neutral-800 w-full p-px my-1");
	auto space_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	
	auto margin_wrapper = margin_padding_general_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto padding_wrapper = margin_padding_general_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());

	auto direction_first_wrapper = directions_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto direction_seccond_wrapper = directions_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto direction_third_wrapper = directions_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto direction_fourth_wrapper = directions_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());

	auto space_x_wrapper = space_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto space_y_wrapper = space_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());

//  space-x-2 
	centralWidget->setStyleClass("flex flex-col w-full max-w-[300px] p-1.5");

	margin_padding_general_wrapper->setStyleClass("flex space-x-2");
	margin_wrapper->setStyleClass("flex flex-col w-1/2 items-stretch");
	padding_wrapper->setStyleClass("flex flex-col w-1/2 items-stretch");

	directions_wrapper->setStyleClass("my-6 mx-auto px-4 min-h-[90px] w-4/5  border-[4px] border-dashed border-neutral-600 flex flex-col justify-between items-stretch");
	direction_first_wrapper->setStyleClass("flex mb-1 flex-col w-fit mx-auto -mt-7");
	direction_seccond_wrapper->setStyleClass("mb-1 flex justify-between -mx-12 space-x-6");
	direction_third_wrapper->setStyleClass("mb-1 flex justify-around -mx-8 space-x-1");
	direction_fourth_wrapper->setStyleClass("flex flex-col w-fit mx-auto -mb-7");

	space_wrapper->setStyleClass("flex");
	space_x_wrapper->setStyleClass("flex flex-col w-1/2 items-stretch");
	space_y_wrapper->setStyleClass("flex flex-col w-1/2 items-stretch");
	
	margin_wrapper->addWidget(std::make_unique<Wt::WText>("Margin"))->setStyleClass("font-bold text-neutral-400");
	padding_wrapper->addWidget(std::make_unique<Wt::WText>("Padding"))->setStyleClass("font-bold text-neutral-400");

	margin_all_widget_ = margin_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->spacing.margin));
	margin_x_widget_ = margin_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->spacing.margin_x));
	margin_y_widget_ = margin_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->spacing.margin_y));

	padding_all_widget_ = padding_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->spacing.padding));
	padding_x_widget_ = padding_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->spacing.padding_x));
	padding_y_widget_ = padding_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->spacing.padding_y));
	
	margin_top_widget_ = direction_first_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->spacing.margin_top));
	padding_top_widget_ = direction_first_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->spacing.padding_top));

	margin_left_widget_ = direction_seccond_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->spacing.margin_left));
	margin_right_widget_ = direction_seccond_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->spacing.margin_right));

	padding_left_widget_ = direction_third_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->spacing.padding_left));
	padding_right_widget_ = direction_third_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->spacing.padding_right));

	margin_bottom_widget_ = direction_fourth_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->spacing.margin_bottom));
	padding_bottom_widget_ = direction_fourth_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->spacing.padding_bottom));

	checkbox_space_x_reverse_ = space_x_wrapper->addWidget(std::make_unique<Wt::WCheckBox>("Space X Reverse"));
	checkbox_space_y_reverse_ = space_y_wrapper->addWidget(std::make_unique<Wt::WCheckBox>("Space Y Reverse"));

	checkbox_space_x_reverse_->setStyleClass("font-bold text-neutral-400");
	checkbox_space_y_reverse_->setStyleClass("font-bold text-neutral-400");

	space_y_widget_ = space_y_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->spacing.space_y));
	space_x_widget_ = space_x_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(tailwindConfig_->spacing.space_x));


	// set regular expresion for custom value p-[10px]
	padding_all_widget_->setCustomValueString("p-");
	padding_x_widget_->setCustomValueString("px-");
	padding_y_widget_->setCustomValueString("py-");
	padding_top_widget_->setCustomValueString("pt-");
	padding_right_widget_->setCustomValueString("pr-");
	padding_bottom_widget_->setCustomValueString("pb-");
	padding_left_widget_->setCustomValueString("pl-");


	margin_all_widget_->setCustomValueString("m-");
	margin_x_widget_->setCustomValueString("mx-");
	margin_y_widget_->setCustomValueString("my-");
	margin_top_widget_->setCustomValueString("mt-");
	margin_right_widget_->setCustomValueString("mr-");
	margin_bottom_widget_->setCustomValueString("mb-");
	margin_left_widget_->setCustomValueString("ml-");

	space_x_widget_->setCustomValueString("space-y-");
	space_y_widget_->setCustomValueString("space-x-");


	// signals for default classes for tailwind
	margin_all_widget_->classChanged().connect(this, [=](std::string className) { margin_all_class = className; styleChanged_.emit(getStyles()); });
	margin_x_widget_->classChanged().connect(this, [=](std::string className) { margin_x_class = className; styleChanged_.emit(getStyles()); });
	margin_y_widget_->classChanged().connect(this, [=](std::string className) { margin_y_class = className; styleChanged_.emit(getStyles()); });
	margin_top_widget_->classChanged().connect(this, [=](std::string className) { margin_top_class = className; styleChanged_.emit(getStyles()); });
	margin_right_widget_->classChanged().connect(this, [=](std::string className) { margin_right_class = className; styleChanged_.emit(getStyles()); });
	margin_bottom_widget_->classChanged().connect(this, [=](std::string className) { margin_bottom_class = className; styleChanged_.emit(getStyles()); });
	margin_left_widget_->classChanged().connect(this, [=](std::string className) { margin_left_class = className; styleChanged_.emit(getStyles()); });

	padding_all_widget_->classChanged().connect(this, [=](std::string className) { padding_all_class = className; styleChanged_.emit(getStyles()); });
	padding_x_widget_->classChanged().connect(this, [=](std::string className) { padding_x_class = className; styleChanged_.emit(getStyles()); });
	padding_y_widget_->classChanged().connect(this, [=](std::string className) { padding_y_class = className; styleChanged_.emit(getStyles()); });
	padding_top_widget_->classChanged().connect(this, [=](std::string className) { padding_top_class = className; styleChanged_.emit(getStyles()); });
	padding_right_widget_->classChanged().connect(this, [=](std::string className) { padding_right_class = className; styleChanged_.emit(getStyles()); });
	padding_bottom_widget_->classChanged().connect(this, [=](std::string className) { padding_bottom_class = className; styleChanged_.emit(getStyles()); });
	padding_left_widget_->classChanged().connect(this, [=](std::string className) { padding_left_class = className; styleChanged_.emit(getStyles()); });

	checkbox_space_x_reverse_->changed().connect(this, [=]() { styleChanged_.emit(getStyles()); });
	checkbox_space_y_reverse_->changed().connect(this, [=]() { styleChanged_.emit(getStyles()); });
};

std::string ElementSpacingWidget::getStyles()
{
	std::string elementClasses;
	bool activeClasses = false;


	if(padding_all_class.compare("none") != 0){ elementClasses += padding_all_class + " "; activeClasses = true; }
	if(padding_x_class.compare("none") != 0){ elementClasses += padding_x_class + " "; activeClasses = true; }
	if(padding_y_class.compare("none") != 0){ elementClasses += padding_y_class + " "; activeClasses = true; }
	if(padding_top_class.compare("none") != 0){ elementClasses += padding_top_class + " "; activeClasses = true; }
	if(padding_right_class.compare("none") != 0){ elementClasses += padding_right_class + " "; activeClasses = true; }
	if(padding_bottom_class.compare("none") != 0){ elementClasses += padding_bottom_class + " "; activeClasses = true; }
	if(padding_left_class.compare("none") != 0){ elementClasses += padding_left_class + " "; activeClasses = true; }

	if(margin_all_class.compare("none") != 0){ elementClasses += margin_all_class + " "; activeClasses = true; }
	if(margin_x_class.compare("none") != 0){ elementClasses += margin_x_class + " "; activeClasses = true; }
	if(margin_y_class.compare("none") != 0){ elementClasses += margin_y_class + " "; activeClasses = true; }
	if(margin_top_class.compare("none") != 0){ elementClasses += margin_top_class + " "; activeClasses = true; }
	if(margin_right_class.compare("none") != 0){ elementClasses += margin_right_class + " "; activeClasses = true; }
	if(margin_bottom_class.compare("none") != 0){ elementClasses += margin_bottom_class + " "; activeClasses = true; }
	if(margin_left_class.compare("none") != 0){ elementClasses += margin_left_class + " "; activeClasses = true; }

	if(space_x_class.compare("none") != 0){ elementClasses += space_x_class + " "; activeClasses = true; }
	if(space_y_class.compare("none") != 0){ elementClasses += space_y_class + " "; activeClasses = true; }

	if(checkbox_space_x_reverse_->isChecked()){ elementClasses += " space-x-reverse"; activeClasses = true; }
	if(checkbox_space_y_reverse_->isChecked()){ elementClasses += " space-y-reverse"; activeClasses = true; }

	if(activeClasses && isCollapsed()) expand();

	return elementClasses;
}

void ElementSpacingWidget::setClasses(SpacingData spacing)
{
	resetStyles();
	bool activeClasses;
	for(auto& padding_class : spacing.padding){
		if(padding_class.find("p-") != std::string::npos){
			activeClasses = setPaddingAll(padding_class);
		}else if(padding_class.find("py-") != std::string::npos){
			activeClasses = setPaddingY(padding_class);
		}else if(padding_class.find("px-") != std::string::npos){
			activeClasses = setPaddingX(padding_class);
		}else if(padding_class.find("pt-") != std::string::npos){
			activeClasses = setPaddingTop(padding_class);
		}else if(padding_class.find("pr-") != std::string::npos){
			activeClasses = setPaddingRight(padding_class);
		}else if(padding_class.find("pb-") != std::string::npos){
			activeClasses = setPaddingBottom(padding_class);
		}else if(padding_class.find("pl-") != std::string::npos){
			activeClasses = setPaddingLeft(padding_class);
		}
	}

	for(auto& margin_class : spacing.margin){
			activeClasses = setMarginAll(margin_class);
		if(margin_class.find("m-") != std::string::npos){
			activeClasses = setMarginAll(margin_class);
		}else if(margin_class.find("my-") != std::string::npos){
			activeClasses = setMarginY(margin_class);
		}else if(margin_class.find("mx-") != std::string::npos){
			activeClasses = setMarginX(margin_class);
		}else if(margin_class.find("mt-") != std::string::npos){
			activeClasses = setMarginTop(margin_class);
		}else if(margin_class.find("mr-") != std::string::npos){
			activeClasses = setMarginRight(margin_class);
		}else if(margin_class.find("mb-") != std::string::npos){
			activeClasses = setMarginBottom(margin_class);
		}else if(margin_class.find("ml-") != std::string::npos){
			activeClasses = setMarginLeft(margin_class);
		}
	}

	for(auto& space_class : spacing.space){

		if(space_class.find("space-x-") != std::string::npos){
			if(space_class.find("reverse") != std::string::npos){
				activeClasses = setSpaceXReverse(true);
			}else {
				activeClasses = setSpaceX(space_class);
			}
		}else if(space_class.find("space-y-") != std::string::npos){
			if(space_class.find("reverse") != std::string::npos){
				activeClasses = setSpaceYReverse(true);
			}else {
				activeClasses = setSpaceY(space_class);
			}
		}
	}

	if(!activeClasses) collapse();
}

void ElementSpacingWidget::resetStyles()
{
	setMarginAll("none");
	setMarginX("none");
	setMarginY("none");
	setMarginTop("none");
	setMarginRight("none");
	setMarginBottom("none");
	setMarginLeft("none");

	setPaddingAll("none");
	setPaddingX("none");
	setPaddingY("none");
	setPaddingTop("none");
	setPaddingRight("none");
	setPaddingBottom("none");
	setPaddingLeft("none");

	setSpaceX("none");
	setSpaceY("none");

	checkbox_space_x_reverse_->setChecked(false);
	checkbox_space_y_reverse_->setChecked(false);
}

void ElementSpacingWidget::setCustomTestValues()
{
	setMarginAll("m-[10px]");
	setMarginX("mx-[10px]");
	setMarginY("my-[10px]");
	setMarginTop("mt-[10px]");
	setMarginRight("mr-[10px]");
	setMarginBottom("mb-[10px]");
	setMarginLeft("ml-[10px]");

	setPaddingAll("p-[10px]");
	setPaddingX("px-[10px]");
	setPaddingY("py-[10px]");
	setPaddingTop("pt-[10px]");
	setPaddingRight("pr-[10px]");
	setPaddingBottom("pb-[10px]");
	setPaddingLeft("pl-[10px]");

	setSpaceX("space-x-[10px]");
	setSpaceY("space-y-[10px]");

	checkbox_space_x_reverse_->setChecked(false);
	checkbox_space_y_reverse_->setChecked(false);
}






bool ElementSpacingWidget::setMarginAll(std::string className)
{
	margin_all_class = className;
	margin_all_widget_->setValue(margin_all_class);

	if(className.compare("none") == 0) return false;
	else {
		expand();
		return true;
	}
}

bool ElementSpacingWidget::setMarginX(std::string className)
{
	margin_x_class = className;
	margin_x_widget_->setValue(margin_x_class);

	if(className.compare("none") == 0) return false;
	else {
		expand();
		return true;
	}
}

bool ElementSpacingWidget::setMarginY(std::string className)
{
	margin_y_class = className;
	margin_y_widget_->setValue(margin_y_class);

	if(className.compare("none") == 0) return false;
	else {
		expand();
		return true;
	}
}

bool ElementSpacingWidget::setMarginTop(std::string className)
{
	margin_top_class = className;
	margin_top_widget_->setValue(margin_top_class);

	if(className.compare("none") == 0) return false;
	else {
		expand();
		return true;
	}
}

bool ElementSpacingWidget::setMarginRight(std::string className)
{
	margin_right_class = className;
	margin_right_widget_->setValue(margin_right_class);

	if(className.compare("none") == 0) return false;
	else {
		expand();
		return true;
	}
}

bool ElementSpacingWidget::setMarginBottom(std::string className)
{
	margin_bottom_class = className;
	margin_bottom_widget_->setValue(margin_bottom_class);

	if(className.compare("none") == 0) return false;
	else {
		expand();
		return true;
	}
}

bool ElementSpacingWidget::setMarginLeft(std::string className)
{
	margin_left_class = className;
	margin_left_widget_->setValue(margin_left_class);

	if(className.compare("none") == 0) return false;
	else {
		expand();
		return true;
	}
}

bool ElementSpacingWidget::setPaddingAll(std::string className)
{
	padding_all_class = className;
	padding_all_widget_->setValue(padding_all_class);

	if(className.compare("none") == 0) return false;
	else {
		expand();
		return true;
	}
}

bool ElementSpacingWidget::setPaddingX(std::string className)
{
	padding_x_class = className;
	padding_x_widget_->setValue(padding_x_class);

	if(className.compare("none") == 0) return false;
	else {
		expand();
		return true;
	}
}

bool ElementSpacingWidget::setPaddingY(std::string className)
{
	padding_y_class = className;
	padding_y_widget_->setValue(padding_y_class);

	if(className.compare("none") == 0) return false;
	else {
		expand();
		return true;
	}
}

bool ElementSpacingWidget::setPaddingTop(std::string className)
{
	padding_top_class = className;
	padding_top_widget_->setValue(padding_top_class);

	if(className.compare("none") == 0) return false;
	else {
		expand();
		return true;
	}
}

bool ElementSpacingWidget::setPaddingRight(std::string className)
{
	padding_right_class = className;
	padding_right_widget_->setValue(padding_right_class);

	if(className.compare("none") == 0) return false;
	else {
		expand();
		return true;
	}
}

bool ElementSpacingWidget::setPaddingBottom(std::string className)
{
	padding_bottom_class = className;
	padding_bottom_widget_->setValue(padding_bottom_class);

	if(className.compare("none") == 0) return false;
	else {
		expand();
		return true;
	}
}

bool ElementSpacingWidget::setPaddingLeft(std::string className)
{
	padding_left_class = className;
	padding_left_widget_->setValue(padding_left_class);

	if(className.compare("none") == 0) return false;
	else {
		expand();
		return true;
	}
}

bool ElementSpacingWidget::setSpaceX(std::string className)
{
	space_x_class = className;
	space_x_widget_->setValue(space_x_class);

	if(className.compare("none") == 0) return false;
	else {
		expand();
		return true;
	}
}

bool ElementSpacingWidget::setSpaceY(std::string className)
{
	space_y_class = className;
	space_y_widget_->setValue(space_y_class);

	if(className.compare("none") == 0) return false;
	else {
		expand();
		return true;
	}
}

bool ElementSpacingWidget::setSpaceXReverse(bool checked)
{
	checkbox_space_x_reverse_->setChecked(checked);\
	if(checked) expand();
	return checked;
}

bool ElementSpacingWidget::setSpaceYReverse(bool checked)
{
	checkbox_space_y_reverse_->setChecked(checked);
	if(checked) expand();
	return checked;
}

