#include "include/ElementSpacing.h"
#include <regex>
#include <Wt/WBreak.h>

ElementSpacingWidget::ElementSpacingWidget(std::shared_ptr<Config> tailwindConfig)
	: tailwindConfig_(tailwindConfig)
{
	setStyleClass("min-w-fit max-w-[300px] !border-x-0 text-center !bg-neutral-700 !text-neutral-200 !border-neutral-900");
	setTitle("Spacing");
	titleBarWidget()->setStyleClass("flex items-center space-x-3 !border-b border-solid border-neutral-900");
	setCollapsible(true);

	auto resetBtn = titleBarWidget()->addWidget(std::make_unique<Wt::WText>());
	auto testBtn = titleBarWidget()->addWidget(std::make_unique<Wt::WText>());

	std::string buttons_styles ="p-2 m-px bg-cover ";
	
	resetBtn->setStyleClass(buttons_styles + "bg-[url(resources/icons/refresh.svg)] !ml-auto");
	testBtn->setStyleClass(buttons_styles + "bg-[url(resources/icons/experimental-glass.svg)] !mr-2");

	resetBtn->clicked().connect([=](){ resetStyles(); styleChanged_.emit(); isCollapsed() ? expand() : collapse();});
	testBtn->clicked().connect([=](){ setCustomTestValues(); styleChanged_.emit(); isCollapsed() ? expand() : collapse(); });

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

	margin_all_widget_ = margin_wrapper->addWidget(std::make_unique<StyleClassComboBox>(tailwindConfig_->spacing.margin));
	margin_vertical_widget_ = margin_wrapper->addWidget(std::make_unique<StyleClassComboBox>(tailwindConfig_->spacing.margin_x));
	margin_horizontal_widget_ = margin_wrapper->addWidget(std::make_unique<StyleClassComboBox>(tailwindConfig_->spacing.margin_y));

	padding_all_widget_ = padding_wrapper->addWidget(std::make_unique<StyleClassComboBox>(tailwindConfig_->spacing.padding));
	padding_vertical_widget_ = padding_wrapper->addWidget(std::make_unique<StyleClassComboBox>(tailwindConfig_->spacing.padding_x));
	padding_horizontal_widget_ = padding_wrapper->addWidget(std::make_unique<StyleClassComboBox>(tailwindConfig_->spacing.padding_y));
	
	margin_top_widget_ = direction_first_wrapper->addWidget(std::make_unique<StyleClassComboBox>(tailwindConfig_->spacing.margin_top));
	padding_top_widget_ = direction_first_wrapper->addWidget(std::make_unique<StyleClassComboBox>(tailwindConfig_->spacing.padding_top));

	margin_left_widget_ = direction_seccond_wrapper->addWidget(std::make_unique<StyleClassComboBox>(tailwindConfig_->spacing.margin_left));
	margin_right_widget_ = direction_seccond_wrapper->addWidget(std::make_unique<StyleClassComboBox>(tailwindConfig_->spacing.margin_right));

	padding_left_widget_ = direction_third_wrapper->addWidget(std::make_unique<StyleClassComboBox>(tailwindConfig_->spacing.padding_left));
	padding_right_widget_ = direction_third_wrapper->addWidget(std::make_unique<StyleClassComboBox>(tailwindConfig_->spacing.padding_right));

	margin_bottom_widget_ = direction_fourth_wrapper->addWidget(std::make_unique<StyleClassComboBox>(tailwindConfig_->spacing.margin_bottom));
	padding_bottom_widget_ = direction_fourth_wrapper->addWidget(std::make_unique<StyleClassComboBox>(tailwindConfig_->spacing.padding_bottom));

	checkbox_space_x_reverse_ = space_x_wrapper->addWidget(std::make_unique<Wt::WCheckBox>("Space X Reverse"));
	checkbox_space_y_reverse_ = space_y_wrapper->addWidget(std::make_unique<Wt::WCheckBox>("Space Y Reverse"));

	checkbox_space_x_reverse_->setStyleClass("font-bold text-neutral-400");
	checkbox_space_y_reverse_->setStyleClass("font-bold text-neutral-400");

	space_y_widget_ = space_y_wrapper->addWidget(std::make_unique<StyleClassComboBox>(tailwindConfig_->spacing.space_y));
	space_x_widget_ = space_x_wrapper->addWidget(std::make_unique<StyleClassComboBox>(tailwindConfig_->spacing.space_x));


	// set regular expresion for custom value p-[10px]
	padding_all_widget_->setCustomValueString("p-");
	padding_vertical_widget_->setCustomValueString("px-");
	padding_horizontal_widget_->setCustomValueString("py-");
	padding_top_widget_->setCustomValueString("pt-");
	padding_right_widget_->setCustomValueString("pr-");
	padding_bottom_widget_->setCustomValueString("pb-");
	padding_left_widget_->setCustomValueString("pl-");


	margin_all_widget_->setCustomValueString("m-");
	margin_vertical_widget_->setCustomValueString("mx-");
	margin_horizontal_widget_->setCustomValueString("my-");
	margin_top_widget_->setCustomValueString("mt-");
	margin_right_widget_->setCustomValueString("mr-");
	margin_bottom_widget_->setCustomValueString("mb-");
	margin_left_widget_->setCustomValueString("ml-");

	space_x_widget_->setCustomValueString("space-y-");
	space_y_widget_->setCustomValueString("space-x-");


	// signals for default classes for tailwind
	padding_all_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });
	padding_vertical_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });
	padding_horizontal_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });
	padding_top_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });
	padding_right_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });
	padding_bottom_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });
	padding_left_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });	

	margin_all_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });
	margin_vertical_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });
	margin_horizontal_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });
	margin_top_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });
	margin_right_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });
	margin_bottom_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });
	margin_left_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });

	space_x_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });
	space_y_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });

	checkbox_space_x_reverse_->changed().connect(this, [=]() { styleChanged_.emit(); });
	checkbox_space_y_reverse_->changed().connect(this, [=]() { styleChanged_.emit(); });
};

std::string ElementSpacingWidget::getStyles()
{
	std::string elementClasses;
	bool activeClasses = false;

	if(padding_all_widget_->getValue().compare("none") != 0){ elementClasses += " " + padding_all_widget_->getValue(); activeClasses = true;}
	if(padding_vertical_widget_->getValue().compare("none") != 0){ elementClasses += " " + padding_vertical_widget_->getValue(); activeClasses = true;}
	if(padding_horizontal_widget_->getValue().compare("none") != 0){ elementClasses += " " + padding_horizontal_widget_->getValue(); activeClasses = true;}
	if(padding_top_widget_->getValue().compare("none") != 0){ elementClasses += " " + padding_top_widget_->getValue(); activeClasses = true;}
	if(padding_right_widget_->getValue().compare("none") != 0){ elementClasses += " " + padding_right_widget_->getValue(); activeClasses = true;}
	if(padding_bottom_widget_->getValue().compare("none") != 0){ elementClasses += " " + padding_bottom_widget_->getValue(); activeClasses = true;}
	if(padding_left_widget_->getValue().compare("none") != 0){ elementClasses += " " + padding_left_widget_->getValue(); activeClasses = true;}

	if(margin_all_widget_->getValue().compare("none") != 0){ elementClasses += " " + margin_all_widget_->getValue(); activeClasses = true;}
	if(margin_vertical_widget_->getValue().compare("none") != 0){ elementClasses += " " + margin_vertical_widget_->getValue(); activeClasses = true;}
	if(margin_horizontal_widget_->getValue().compare("none") != 0){ elementClasses += " " + margin_horizontal_widget_->getValue(); activeClasses = true;}
	if(margin_top_widget_->getValue().compare("none") != 0){ elementClasses += " " + margin_top_widget_->getValue(); activeClasses = true;}
	if(margin_right_widget_->getValue().compare("none") != 0){ elementClasses += " " + margin_right_widget_->getValue(); activeClasses = true;}
	if(margin_bottom_widget_->getValue().compare("none") != 0){ elementClasses += " " + margin_bottom_widget_->getValue(); activeClasses = true;}
	if(margin_left_widget_->getValue().compare("none") != 0){ elementClasses += " " + margin_left_widget_->getValue(); activeClasses = true;}


	if(space_x_widget_->getValue().compare("none") != 0){ elementClasses += " " + space_x_widget_->getValue(); activeClasses = true;}
	if(space_y_widget_->getValue().compare("none") != 0){ elementClasses += " " + space_y_widget_->getValue(); activeClasses = true;}
	if(checkbox_space_x_reverse_->isChecked()){ elementClasses += " space-x-reverse"; activeClasses = true; }
	if(checkbox_space_y_reverse_->isChecked()){ elementClasses += " space-y-reverse"; activeClasses = true; }

	if(activeClasses) expand();
	else collapse();

	return elementClasses;
}

void ElementSpacingWidget::setClasses(SpacingData spacing)
{
	bool activeClasses = false;
	// resetStyles();
	// std::cout << "\nElementSpacingWidget::setStyleClasses \n";
	for(auto& padding_class : spacing.padding){
		if(padding_class.compare("none") != 0) activeClasses = true;

		if(padding_class.find("p-") != std::string::npos){
			padding_all_widget_->setValue(padding_class);
		}else if(padding_class.find("py-") != std::string::npos){
			padding_horizontal_widget_->setValue(padding_class);
		}else if(padding_class.find("px-") != std::string::npos){
			padding_vertical_widget_->setValue(padding_class);
		}else if(padding_class.find("pt-") != std::string::npos){
			padding_top_widget_->setValue(padding_class);
		}else if(padding_class.find("pr-") != std::string::npos){
			padding_right_widget_->setValue(padding_class);
		}else if(padding_class.find("pb-") != std::string::npos){
			padding_bottom_widget_->setValue(padding_class);
		}else if(padding_class.find("pl-") != std::string::npos){
			padding_left_widget_->setValue(padding_class);
		}
	}

	for(auto& margin_class : spacing.margin){
		if(margin_class.compare("none") != 0) activeClasses = true;
		
		if(margin_class.find("m-") != std::string::npos){
			margin_all_widget_->setValue(margin_class);
		}else if(margin_class.find("my-") != std::string::npos){
			margin_horizontal_widget_->setValue(margin_class);
		}else if(margin_class.find("mx-") != std::string::npos){
			margin_vertical_widget_->setValue(margin_class);
		}else if(margin_class.find("mt-") != std::string::npos){
			margin_top_widget_->setValue(margin_class);
		}else if(margin_class.find("mr-") != std::string::npos){
			margin_right_widget_->setValue(margin_class);
		}else if(margin_class.find("mb-") != std::string::npos){
			margin_bottom_widget_->setValue(margin_class);
		}else if(margin_class.find("ml-") != std::string::npos){
			margin_left_widget_->setValue(margin_class);
		}
	}

	for(auto& space_class : spacing.space){
		if(space_class.compare("none") != 0) activeClasses = true;

		if(space_class.find("space-x-") != std::string::npos){
			if(space_class.find("reverse") != std::string::npos){
				checkbox_space_x_reverse_->setChecked(true);
			}else {
				space_x_widget_->setValue(space_class);
			}
		}else if(space_class.find("space-y-") != std::string::npos){
			if(space_class.find("reverse") != std::string::npos){
				checkbox_space_y_reverse_->setChecked(true);
			}else {
				space_y_widget_->setValue(space_class);
			}
		}
	}

	if(activeClasses) expand();
	else collapse();
}

void ElementSpacingWidget::resetStyles()
{
	// std::cout << "\n\n resetStyleClasses";
	padding_all_widget_->setValue();
	padding_vertical_widget_->setValue();
	padding_horizontal_widget_->setValue();
	padding_top_widget_->setValue();
	padding_right_widget_->setValue();
	padding_bottom_widget_->setValue();
	padding_left_widget_->setValue();
	
	margin_all_widget_->setValue();
	margin_vertical_widget_->setValue();
	margin_horizontal_widget_->setValue();
	margin_top_widget_->setValue();
	margin_right_widget_->setValue();
	margin_bottom_widget_->setValue();
	margin_left_widget_->setValue();

	space_x_widget_->setValue();
	space_y_widget_->setValue();
	
	checkbox_space_x_reverse_->setChecked(false);
	checkbox_space_y_reverse_->setChecked(false);
}

void ElementSpacingWidget::setCustomTestValues()
{
	margin_all_widget_->setValue("m-10");
	margin_vertical_widget_->setValue("mx-auto");
	margin_horizontal_widget_->setValue("my-6");
	margin_top_widget_->setValue("mt-2");
	margin_right_widget_->setValue("mr-2");
	margin_bottom_widget_->setValue("mb-2");
	margin_left_widget_->setValue("ml-[10px]");

	padding_all_widget_->setValue("p-10");
	padding_vertical_widget_->setValue("px-4");
	padding_horizontal_widget_->setValue("py-6");
	padding_top_widget_->setValue("pt-[30px]");
	padding_right_widget_->setValue("pr-2");
	padding_bottom_widget_->setValue("pb-2");
	padding_left_widget_->setValue("pl-2");

	space_x_widget_->setValue("space-x-4");
	space_y_widget_->setValue("space-y-4");

	checkbox_space_x_reverse_->setChecked(true);
	checkbox_space_y_reverse_->setChecked(true);
}
