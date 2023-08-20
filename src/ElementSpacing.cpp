#include "include/ElementSpacing.h"
#include <regex>

ElementSpacingWidget::ElementSpacingWidget(std::shared_ptr<Config> tailwindConfig)
	: tailwindConfig_(tailwindConfig)
{
	setStyleClass("min-w-fit max-w-[300px] !border-x-0 text-center !bg-neutral-700 !text-neutral-200");
	setTitle("Spacing");
	titleBarWidget()->setStyleClass("flex items-center space-x-3 !border-b border-solid border-neutral-500");
	setCollapsible(true);
	content_temp = setCentralWidget(std::make_unique<Wt::WTemplate>(tr("stylus-spacing-template")));

	auto resetBtn = titleBarWidget()->addWidget(std::make_unique<Wt::WText>());
	auto testBtn = titleBarWidget()->addWidget(std::make_unique<Wt::WText>());

	std::string buttons_styles ="p-2 m-px bg-cover ";
	
	resetBtn->setStyleClass(buttons_styles + "bg-[url(resources/icons/refresh.svg)] !ml-auto");
	testBtn->setStyleClass(buttons_styles + "bg-[url(resources/icons/experimental-glass.svg)] !mr-2");

	resetBtn->clicked().connect([=](){ resetStyles(); styleChanged_.emit(); isCollapsed() ? expand() : collapse();});
	testBtn->clicked().connect([=](){ setCustomTestValues(); styleChanged_.emit(); isCollapsed() ? expand() : collapse(); });



	margin_all_widget_ = content_temp->bindWidget("margin.all.control", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig_->spacing.margin));
	margin_vertical_widget_ = content_temp->bindWidget("margin.vertical.control", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig_->spacing.margin_x));
	margin_horizontal_widget_ = content_temp->bindWidget("margin.horizontal.control", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig_->spacing.margin_y));
	margin_top_widget_ = content_temp->bindWidget("margin.top.control", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig_->spacing.margin_top));
	margin_right_widget_ = content_temp->bindWidget("margin.right.control", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig_->spacing.margin_right));
	margin_bottom_widget_ = content_temp->bindWidget("margin.bottom.control", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig_->spacing.margin_bottom));
	margin_left_widget_ = content_temp->bindWidget("margin.left.control", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig_->spacing.margin_left));

	padding_all_widget_ = content_temp->bindWidget("padding.all.control", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig_->spacing.padding));
	padding_vertical_widget_ = content_temp->bindWidget("padding.vertical.control", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig_->spacing.padding_x));
	padding_horizontal_widget_ = content_temp->bindWidget("padding.horizontal.control", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig_->spacing.padding_y));
	padding_top_widget_ = content_temp->bindWidget("padding.top.control", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig_->spacing.padding_top));
	padding_right_widget_ = content_temp->bindWidget("padding.right.control", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig_->spacing.padding_right));
	padding_bottom_widget_ = content_temp->bindWidget("padding.bottom.control", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig_->spacing.padding_bottom));
	padding_left_widget_ = content_temp->bindWidget("padding.left.control", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig_->spacing.padding_left));

	space_horizontal_widget_ = content_temp->bindWidget("space.horizontal.control", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig_->spacing.space_y));
	space_vertical_widget_ = content_temp->bindWidget("space.vertical.control", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig_->spacing.space_x));

	checkbox_space_x_reverse_ = content_temp->bindWidget("space.vertical.reverse.controle", std::make_unique<Wt::WCheckBox>("reverse"));
	checkbox_space_y_reverse_ = content_temp->bindWidget("space.horizontal.reverse.controle", std::make_unique<Wt::WCheckBox>("reverse"));

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

	space_vertical_widget_->setCustomValueString("space-y-");
	space_horizontal_widget_->setCustomValueString("space-x-");


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

	space_vertical_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });
	space_horizontal_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });

	checkbox_space_x_reverse_->changed().connect(this, [=]() { styleChanged_.emit(); });
	checkbox_space_y_reverse_->changed().connect(this, [=]() { styleChanged_.emit(); });
};

std::string ElementSpacingWidget::getStyles()
{
	std::string elementClasses;

	if(padding_all_widget_->getValue().compare("none") != 0){ elementClasses += " " + padding_all_widget_->getValue(); }
	if(padding_vertical_widget_->getValue().compare("none") != 0){ elementClasses += " " + padding_vertical_widget_->getValue(); }
	if(padding_horizontal_widget_->getValue().compare("none") != 0){ elementClasses += " " + padding_horizontal_widget_->getValue(); }
	if(padding_top_widget_->getValue().compare("none") != 0){ elementClasses += " " + padding_top_widget_->getValue(); }
	if(padding_right_widget_->getValue().compare("none") != 0){ elementClasses += " " + padding_right_widget_->getValue(); }
	if(padding_bottom_widget_->getValue().compare("none") != 0){ elementClasses += " " + padding_bottom_widget_->getValue(); }
	if(padding_left_widget_->getValue().compare("none") != 0){ elementClasses += " " + padding_left_widget_->getValue(); }

	if(margin_all_widget_->getValue().compare("none") != 0){ elementClasses += " " + margin_all_widget_->getValue(); }
	if(margin_vertical_widget_->getValue().compare("none") != 0){ elementClasses += " " + margin_vertical_widget_->getValue(); }
	if(margin_horizontal_widget_->getValue().compare("none") != 0){ elementClasses += " " + margin_horizontal_widget_->getValue(); }
	if(margin_top_widget_->getValue().compare("none") != 0){ elementClasses += " " + margin_top_widget_->getValue(); }
	if(margin_right_widget_->getValue().compare("none") != 0){ elementClasses += " " + margin_right_widget_->getValue(); }
	if(margin_bottom_widget_->getValue().compare("none") != 0){ elementClasses += " " + margin_bottom_widget_->getValue(); }
	if(margin_left_widget_->getValue().compare("none") != 0){ elementClasses += " " + margin_left_widget_->getValue(); }


	if(space_vertical_widget_->getValue().compare("none") != 0){ elementClasses += " " + space_vertical_widget_->getValue(); }
	if(space_horizontal_widget_->getValue().compare("none") != 0){ elementClasses += " " + space_horizontal_widget_->getValue(); }
	if(checkbox_space_x_reverse_->isChecked()){ elementClasses += " space-x-reverse"; }
	if(checkbox_space_y_reverse_->isChecked()){ elementClasses += " space-y-reverse"; }
	// std::cout << "\n\n spacing classes : " << elementClasses << "\n\n";
	return elementClasses;

}

void ElementSpacingWidget::setClasses(SpacingData spacing)
{
	// resetStyles();
	// std::cout << "\nElementSpacingWidget::setStyleClasses \n";
	for(auto& padding_class : spacing.padding){
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
		if(space_class.find("space-x-") != std::string::npos){
			if(space_class.find("reverse") != std::string::npos){
				checkbox_space_x_reverse_->setChecked(true);
			}else {
				space_vertical_widget_->setValue(space_class);
			}
		}else if(space_class.find("space-y-") != std::string::npos){
			if(space_class.find("reverse") != std::string::npos){
				checkbox_space_y_reverse_->setChecked(true);
			}else {
				space_horizontal_widget_->setValue(space_class);
			}
		}
	}
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

	space_vertical_widget_->setValue();
	space_horizontal_widget_->setValue();
	
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

	space_vertical_widget_->setValue("space-x-4");
	space_horizontal_widget_->setValue("space-y-4");

	checkbox_space_x_reverse_->setChecked(true);
	checkbox_space_y_reverse_->setChecked(true);
}
