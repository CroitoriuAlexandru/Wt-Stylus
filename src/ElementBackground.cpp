#include "include/ElementBackground.h"
#include <regex>
#include <string>

ElementBackgroundWidget::ElementBackgroundWidget(std::shared_ptr<Config> tailwindConfig)
	: tailwindConfig_(tailwindConfig),
	gradient_group(std::make_shared<Wt::WButtonGroup>()),
	gradient_step_group(std::make_shared<Wt::WButtonGroup>()),
	attachment_group(std::make_shared<Wt::WButtonGroup>()),
	clip_group(std::make_shared<Wt::WButtonGroup>()),
	origin_group(std::make_shared<Wt::WButtonGroup>()),
	position_group(std::make_shared<Wt::WButtonGroup>()),
	repeat_group(std::make_shared<Wt::WButtonGroup>()),
	size_group(std::make_shared<Wt::WButtonGroup>())
{

	setStyleClass("min-w-fit max-w-[300px] !border-x-0 !bg-neutral-700 !text-neutral-200 !border-neutral-900 px-1.5");
	setTitle("Backgrounds");
	titleBarWidget()->setStyleClass("flex items-center space-x-3 !border-b border-solid border-neutral-900");
	setCollapsible(true);
	
	
	auto resetBtn = titleBarWidget()->addWidget(std::make_unique<Wt::WText>());
	auto testBtn = titleBarWidget()->addWidget(std::make_unique<Wt::WText>());

	std::string iconStyles ="p-2 m-px bg-cover ";
	
	resetBtn->setStyleClass(iconStyles + "bg-[url(resources/icons/refresh.svg)] !ml-auto");
	testBtn->setStyleClass(iconStyles + "bg-[url(resources/icons/experimental-glass.svg)] !mr-2");

	resetBtn->clicked().connect([=](){ resetStyles(); styleChanged_.emit(); isCollapsed() ? expand() : collapse();});
	testBtn->clicked().connect([=](){ setCustomTestValues(); styleChanged_.emit(); isCollapsed() ? expand() : collapse(); });

	auto centralWidget = setCentralWidget(std::make_unique<Wt::WContainerWidget>());

	centralWidget->setStyleClass("flex flex-col w-full max-w-[300px]");

	// gradient image and colors
	// {
		auto gratient_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
		auto gradient_header = gratient_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
		auto gradient_body = gratient_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
		auto none_btns_wrapper = gradient_body->addWidget(std::make_unique<Wt::WContainerWidget>());
		auto directions_from_via_to_wrapper = gradient_body->addWidget(std::make_unique<Wt::WContainerWidget>());
		auto directions_wrapper = directions_from_via_to_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
		from_via_to_wrapper = directions_from_via_to_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());

		gradient_header->addWidget(std::make_unique<Wt::WText>("Gradient"))->setStyleClass("font-bold text-neutral-400");
		gradient_header->setStyleClass("flex");
		gradient_body->setStyleClass("flex");
		none_btns_wrapper->setStyleClass("flex");
		directions_from_via_to_wrapper->setStyleClass("flex flex-col");
		directions_wrapper->setStyleClass("flex");
		from_via_to_wrapper->setStyleClass("flex");
		for(int index = 0; index < tailwindConfig->backgrounds.background_image.styleClasses_.size(); ++index){
			// get the text after the last -
			std::string gradient_name = tailwindConfig->backgrounds.background_image.styleClasses_[index].className_;
			std::string gradient_direction = gradient_name.substr(gradient_name.find_last_of("-")+1);
			Wt::WRadioButton *btn;
			
			std::string tooltip_text;
			if(gradient_direction.compare("tl") == 0){
				tooltip_text = "To Top Left";
				btn = directions_wrapper->addWidget(std::make_unique<Wt::WRadioButton>(""));
				btn->setStyleClass("[&>span]:bg-[url(resources/icons/arrow-left-up.svg)]");
			}else if (gradient_direction.compare("tr") == 0){
				tooltip_text = "To Top Right";
				btn = directions_wrapper->addWidget(std::make_unique<Wt::WRadioButton>(""));
				btn->setStyleClass("[&>span]:bg-[url(resources/icons/arrow-right-up.svg)]");
			}else if (gradient_direction.compare("bl") == 0){
				tooltip_text = "To Bottom Left";
				btn = directions_wrapper->addWidget(std::make_unique<Wt::WRadioButton>(""));
				btn->setStyleClass("[&>span]:bg-[url(resources/icons/arrow-left-down.svg)]");
			}else if (gradient_direction.compare("br") == 0){
				tooltip_text = "To Bottom Right";
				btn = directions_wrapper->addWidget(std::make_unique<Wt::WRadioButton>(""));
				btn->setStyleClass("[&>span]:bg-[url(resources/icons/arrow-right-down.svg)]");
			}else if (gradient_direction.compare("t") == 0){
				tooltip_text = "To Top";
				btn = directions_wrapper->addWidget(std::make_unique<Wt::WRadioButton>(""));
				btn->setStyleClass("[&>span]:bg-[url(resources/icons/arrow-up.svg)]");
			}else if (gradient_direction.compare("b") == 0){
				tooltip_text = "To Bottom";
				btn = directions_wrapper->addWidget(std::make_unique<Wt::WRadioButton>(""));
				btn->setStyleClass("[&>span]:bg-[url(resources/icons/arrow-down.svg)]");
			}else if (gradient_direction.compare("l") == 0){
				tooltip_text = "To Left";
				btn = directions_wrapper->addWidget(std::make_unique<Wt::WRadioButton>(""));
				btn->setStyleClass("[&>span]:bg-[url(resources/icons/arrow-left.svg)]");
			}else if (gradient_direction.compare("r") == 0){
				tooltip_text = "To Right";
				btn = directions_wrapper->addWidget(std::make_unique<Wt::WRadioButton>(""));
				btn->setStyleClass("[&>span]:bg-[url(resources/icons/arrow-right.svg)]");
			}else if (gradient_name.compare("bg-none") == 0){
				tooltip_text = "No Background";
				btn = none_btns_wrapper->addWidget(std::make_unique<Wt::WRadioButton>(""));
				btn->setStyleClass("[&>span]:!p-0.5 mr-auto text-xs [&>span]:bg-neutral-900 [&>span]:hover:bg-neutral-800 text-white [&>input:checked_+_span]:bg-neutral-400 [&>span]:text-center [&>input:checked_+_span]:text-black");
				btn->setText("none");
			}else {
				tooltip_text = "No style class applied";
				btn = none_btns_wrapper->addWidget(std::make_unique<Wt::WRadioButton>(""));
				btn->addStyleClass("[&>span]:bg-[url(resources/icons/red-cross.svg)] ");
			}

			btn->addStyleClass("flex w-fit h-fit cursor-pointer m-px mx-0.5 p-px");
			btn->addStyleClass("[&>span]:bg-cover [&>input]:hidden [&>span]:p-2.5 [&>span]:m-px [&>span]:rounded-md");
			btn->addStyleClass("[&>span]:bg-neutral-500 [&>span]:hover:bg-neutral-400 [&>input:checked_+_span]:bg-neutral-400 ");
			btn->setToolTip(Wt::WString().tr("tooltip-styleClasses").arg(tooltip_text).arg(gradient_name), Wt::TextFormat::UnsafeXHTML);
			gradient_group->addButton(btn, index);
		}

		auto btn = from_via_to_wrapper->addWidget(std::make_unique<Wt::WRadioButton>("from color"));
		btn->setStyleClass("mx-auto flex w-fit h-fit cursor-pointer m-px mx-0.5 p-px");
		btn->addStyleClass("[&>input]:hidden [&>span]:p-3 [&>span]:m-px [&>span]:rounded-md");
		btn->addStyleClass("[&>span]:bg-neutral-500 [&>span]:hover:bg-neutral-400 [&>input:checked_+_span]:bg-neutral-400");
		btn->addStyleClass("[&>span]:!p-0.5 text-xs [&>span]:bg-neutral-900 [&>span]:hover:bg-neutral-800 text-white [&>input:checked_+_span]:bg-neutral-400 [&>span]:text-center [&>input:checked_+_span]:text-black");
		btn->setToolTip(Wt::WString().tr("tooltip-styleClasses").arg("From Color").arg("from"), Wt::TextFormat::UnsafeXHTML);
		gradient_step_group->addButton(btn, 0);

		btn = from_via_to_wrapper->addWidget(std::make_unique<Wt::WRadioButton>("via color"));
		btn->setStyleClass("mx-auto flex w-fit h-fit cursor-pointer m-px mx-0.5 p-px");
		btn->addStyleClass("[&>input]:hidden [&>span]:p-3 [&>span]:m-px [&>span]:rounded-md");
		btn->addStyleClass("[&>span]:bg-neutral-500 [&>span]:hover:bg-neutral-400 [&>input:checked_+_span]:bg-neutral-400");
		btn->addStyleClass("[&>span]:!p-0.5 text-xs [&>span]:bg-neutral-900 [&>span]:hover:bg-neutral-800 text-white [&>input:checked_+_span]:bg-neutral-400 [&>span]:text-center [&>input:checked_+_span]:text-black");
		btn->setToolTip(Wt::WString().tr("tooltip-styleClasses").arg("Via Color").arg("via"), Wt::TextFormat::UnsafeXHTML);
		gradient_step_group->addButton(btn, 1);

		btn = from_via_to_wrapper->addWidget(std::make_unique<Wt::WRadioButton>("to color"));
		btn->setStyleClass("mx-auto flex w-fit h-fit cursor-pointer m-px mx-0.5 p-px");
		btn->addStyleClass("[&>input]:hidden [&>span]:p-3 [&>span]:m-px [&>span]:rounded-md");
		btn->addStyleClass("[&>span]:bg-neutral-500 [&>span]:hover:bg-neutral-400 [&>input:checked_+_span]:bg-neutral-400");
		btn->addStyleClass("[&>span]:!p-0.5 text-xs [&>span]:bg-neutral-900 [&>span]:hover:bg-neutral-800 text-white [&>input:checked_+_span]:bg-neutral-400 [&>span]:text-center [&>input:checked_+_span]:text-black");
		btn->setToolTip(Wt::WString().tr("tooltip-styleClasses").arg("To Color").arg("to"), Wt::TextFormat::UnsafeXHTML);
		gradient_step_group->addButton(btn, 2);

		bg_color_widget = centralWidget->addWidget(std::make_unique<ColorSelecionWidget>(tailwindConfig->backgrounds.background_color, "Bg Color"));
		bg_color_from_widget = centralWidget->addWidget(std::make_unique<ColorSelecionWidget>(tailwindConfig->backgrounds.background_color_from, "From Color"));
		bg_color_via_widget = centralWidget->addWidget(std::make_unique<ColorSelecionWidget>(tailwindConfig->backgrounds.background_color_via, "Via Color"));
		bg_color_to_widget = centralWidget->addWidget(std::make_unique<ColorSelecionWidget>(tailwindConfig->backgrounds.background_color_to, "To Color"));
	// }

	// attachment
	// {
		auto attachment_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
		auto attachment_header = attachment_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
		auto attachment_body = attachment_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
		attachment_header->addWidget(std::make_unique<Wt::WText>("Background Attachment"))->setStyleClass("font-bold text-neutral-400");

		attachment_header->setStyleClass("flex");
		attachment_body->setStyleClass("flex");

		for(int index = 0; index < tailwindConfig->backgrounds.background_attachment.styleClasses_.size(); ++index){
			auto attachment_class = tailwindConfig->backgrounds.background_attachment.styleClasses_[index];
			Wt::WRadioButton *btn;
			if(attachment_class.className_.compare("none") == 0) {
				btn = attachment_body->addWidget(std::make_unique<Wt::WRadioButton>(""));
				btn->setStyleClass("[&>span]:bg-[url(resources/icons/red-cross.svg)] [&>span]:bg-cover [&>span]:p-3");
			}else {
				btn = attachment_body->addWidget(std::make_unique<Wt::WRadioButton>(attachment_class.className_));
				btn->setStyleClass("[&>span]:!p-0.5 mr-auto [&>span]:bg-neutral-900 [&>span]:hover:bg-neutral-800 text-white [&>input:checked_+_span]:bg-neutral-400 [&>span]:text-center [&>input:checked_+_span]:text-black");
			}
			btn->addStyleClass("flex w-fit h-fit cursor-pointer m-px mx-0.5 p-px");
			btn->addStyleClass("[&>input]:hidden [&>span]:m-px [&>span]:rounded-md");
			btn->addStyleClass("[&>span]:bg-neutral-500 [&>span]:hover:bg-neutral-400 [&>input:checked_+_span]:bg-neutral-400 ");
			btn->setToolTip(Wt::WString().tr("tooltip-styleClasses").arg(attachment_class.propriety_).arg(attachment_class.className_), Wt::TextFormat::UnsafeXHTML);
			attachment_group->addButton(btn, index);
		}
	// }

	gradient_step_group->button(0)->setChecked(true);
	// signals 
	gradient_step_group->checkedChanged().connect(this, [=](){
		switch(gradient_step_group->checkedId()){
			case 0:
				bg_color_from_widget->show();
				bg_color_via_widget->hide();
				bg_color_to_widget->hide();
				break;
			case 1:
				bg_color_from_widget->hide();
				bg_color_via_widget->show();
				bg_color_to_widget->hide();
				break;
			case 2:
				bg_color_from_widget->hide();
				bg_color_via_widget->hide();
				bg_color_to_widget->show();
				break;
		}
	});


	gradient_group->checkedChanged().connect(this, [=](){
		if(gradient_group->checkedId() > 1){
			from_via_to_wrapper->show();
			gradient_step_group->checkedChanged().emit(gradient_step_group->checkedButton());
		}else {
			bg_color_from_widget->hide();
			bg_color_via_widget->hide();
			bg_color_to_widget->hide();
			from_via_to_wrapper->hide();
		}
		styleChanged_.emit();
	});

	bg_color_widget->classChanged().connect([=](){ styleChanged_.emit(); });
	bg_color_from_widget->classChanged().connect([=](){ styleChanged_.emit(); });
	bg_color_via_widget->classChanged().connect([=](){ styleChanged_.emit(); });
	bg_color_to_widget->classChanged().connect([=](){ styleChanged_.emit(); });
	// attachment_group->checkedChanged().connect(this, [=](){ styleChanged_.emit(); });



	collapsed().connect(this, [=](){ 
		std::cout << "\n ------------------------ collapsed ------------------------" << std::endl;
	 });
	expanded().connect(this, [=](){
		std::cout << "\n ------------------------ expanded ------------------------" << std::endl;
	 });
};

std::string ElementBackgroundWidget::getStyles()
{
	std::string elementClasses;
	std::string gradient_name = tailwindConfig_->backgrounds.background_image.styleClasses_[gradient_group->checkedId()].className_;
	if(gradient_name.compare("none") != 0){elementClasses += gradient_name + " "; }
	if(bg_color_from_widget->getValue().compare("none") != 0){ elementClasses += bg_color_from_widget->getValue() + " "; }
	if(bg_color_via_widget->getValue().compare("none") != 0){ elementClasses += bg_color_via_widget->getValue() + " "; }
	if(bg_color_to_widget->getValue().compare("none") != 0){ elementClasses += bg_color_to_widget->getValue() + " "; }
	if(bg_color_widget->getValue().compare("none") != 0){ elementClasses += bg_color_widget->getValue() + " "; }
	// if(attachment_group->checkedId() != -1){ elementClasses += tailwindConfig_->backgrounds.background_attachment.styleClasses_[attachment_group->checkedId()].className_ + " "; }



	return elementClasses;
}

int ElementBackgroundWidget::getIndexOfStringInVector(std::string str, std::vector<StyleClass> vec){
	for(int index = 0; index < vec.size(); ++index){
		if(vec[index].className_.compare(str) == 0) return index;
	}
	return 0;
}

void ElementBackgroundWidget::setGradientColor(std::string className)
{
	// get id of the gradient
	int gradientIndex = getIndexOfStringInVector(className, tailwindConfig_->backgrounds.background_image.styleClasses_);
	if(gradientIndex == 0) return;
	expand();
	gradient_group->button(gradientIndex)->setChecked(true);
	gradient_group->checkedChanged().emit(gradient_group->checkedButton());
}

void ElementBackgroundWidget::setColor(std::string className)
{
	if(className.compare("none") == 0) return;
	expand();
	switch(className[0]){
		case 'b':
			bg_color_widget->setValue(className);
			break;
		case 'f':
			bg_color_from_widget->setValue(className);
			break;
		case 'v':
			bg_color_via_widget->setValue(className);
			break;
		case 't':
			bg_color_to_widget->setValue(className);
			break;
	}
}

void ElementBackgroundWidget::setClasses(BackgroundData bgData)
{
	bool activeClasses = false;
	resetStyles();

	setGradientColor(bgData.bg_image);
	setColor(bgData.bg_color);
	setColor(bgData.bg_color_from);
	setColor(bgData.bg_color_via);\
	setColor(bgData.bg_color_to);

	// if(bgData.bg_attachment.compare("none") != 0){ 
		// attachment_group->button(getIndexOfStringInVector(bgData.bg_attachment, tailwindConfig_->backgrounds.background_attachment.styleClasses_))->setChecked(true); activeClasses = true; 
		// }
	std::cout << "active classes:--------------------- " << activeClasses << std::endl;
	// if(activeClasses) expand();
	// else collapse();
}



void ElementBackgroundWidget::resetStyles()
{
	gradient_group->button(0)->setChecked(true);
	gradient_step_group->button(0)->setChecked(true);
	bg_color_widget->setValue("none");

	bg_color_from_widget->setValue("none");
	bg_color_via_widget->setValue("none");
	bg_color_to_widget->setValue("none");
	
	from_via_to_wrapper->hide();
	bg_color_from_widget->hide();
	bg_color_via_widget->hide();
	bg_color_to_widget->hide();

}

void ElementBackgroundWidget::setCustomTestValues()
{
	gradient_group->button(5)->setChecked(true);
	bg_color_widget->setValue("bg-neutral-400/60");
	// comboBox_attachment->setValue("bg-fixed");
	// comboBox_clip->setValue("bg-clip-border");
	// comboBox_origin->setValue("bg-origin-border");
	// comboBox_position->setValue("bg-center");
	// comboBox_repeat->setValue("bg-repeat");
	// comboBox_size->setValue("bg-auto");
}
