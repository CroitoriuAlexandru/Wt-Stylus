#include "include/ElementLayout.h"
#include <regex>
#include <string>

ElementLayoutWidget::ElementLayoutWidget(std::shared_ptr<Config> tailwindConfig)
	: tailwindConfig_(tailwindConfig)
{

	setStyleClass("min-w-fit max-w-[300px] !border-x-0 text-center !bg-neutral-700 !text-neutral-200");
	setTitle("Transforms");
	titleBarWidget()->setStyleClass("flex items-center space-x-3 !border-b border-solid border-neutral-500");
	setCollapsible(true);
	content_temp = setCentralWidget(std::make_unique<Wt::WTemplate>(tr("stylus-layout-template")));

	auto resetBtn = titleBarWidget()->addWidget(std::make_unique<Wt::WText>());
	auto testBtn = titleBarWidget()->addWidget(std::make_unique<Wt::WText>());

	std::string buttons_styles ="p-2 m-px bg-cover hover:bg-neutral-900 rounded-md ";
	
	resetBtn->setStyleClass(buttons_styles + "bg-[url(resources/icons/refresh.svg)] !ml-auto");
	testBtn->setStyleClass(buttons_styles + "bg-[url(resources/icons/experimental-glass.svg)] !mr-2");

	resetBtn->clicked().connect([=](){ resetStyles(); styleChanged_.emit(); isCollapsed() ? expand() : collapse();});
	testBtn->clicked().connect([=](){ setCustomTestValues(); styleChanged_.emit(); isCollapsed() ? expand() : collapse(); });


	comboBox_aspect_ratio_ = content_temp->bindWidget("combobox-aspect-ratio", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig->layout.aspect_ratio));
	checkBox_container_ = content_temp->bindWidget("checkbox-container", std::make_unique<Wt::WCheckBox>("Container"));
	comboBox_columns_ = content_temp->bindWidget("combobox-columns", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig->layout.columns));
	comboBox_break_after_ = content_temp->bindWidget("combobox-break-after", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig->layout.break_after));
	comboBox_break_before_ = content_temp->bindWidget("combobox-break-before", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig->layout.break_before));
	comboBox_break_inside_ = content_temp->bindWidget("combobox-break-inside", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig->layout.break_inside));
	comboBox_box_decoration_break_ = content_temp->bindWidget("combobox-box-decoration-break", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig->layout.box_decoration_break));
	comboBox_box_sizing_ = content_temp->bindWidget("combobox-box-sizing", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig->layout.box_sizing));
	comboBox_display_ = content_temp->bindWidget("combobox-display", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig->layout.display));
	comboBox_floats_ = content_temp->bindWidget("combobox-floats", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig->layout.floats));
	comboBox_clear_ = content_temp->bindWidget("combobox-clear", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig->layout.clear));
	comboBox_isolation_ = content_temp->bindWidget("combobox-isolation", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig->layout.isolation));
	comboBox_object_fit_ = content_temp->bindWidget("combobox-object-fit", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig->layout.object_fit));
	comboBox_object_position_ = content_temp->bindWidget("combobox-object-position", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig->layout.object_position));
	comboBox_overflow_ = content_temp->bindWidget("combobox-overflow", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig->layout.overflow));
	comboBox_overflow_x_ = content_temp->bindWidget("combobox-overflow-x", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig->layout.overflow_x));
	comboBox_overflow_y_ = content_temp->bindWidget("combobox-overflow-y", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig->layout.overflow_y));
	comboBox_overscroll_behavior_ = content_temp->bindWidget("combobox-overscroll-behavior", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig->layout.overscroll_behavior));
	comboBox_overscroll_behavior_x_ = content_temp->bindWidget("combobox-overscroll-behavior-x", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig->layout.overscroll_behavior_x));
	comboBox_overscroll_behavior_y_ = content_temp->bindWidget("combobox-overscroll-behavior-y", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig->layout.overscroll_behavior_y));
	comboBox_position_ = content_temp->bindWidget("combobox-position", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig->layout.position));
	comboBox_inset_ = content_temp->bindWidget("combobox-inset", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig->layout.position_inset));
	comboBox_inset_x_ = content_temp->bindWidget("combobox-inset-x", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig->layout.position_inset_x));
	comboBox_inset_y_ = content_temp->bindWidget("combobox-inset-y", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig->layout.position_inset_y));
	comboBox_top_ = content_temp->bindWidget("combobox-top", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig->layout.position_top));
	comboBox_right_ = content_temp->bindWidget("combobox-right", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig->layout.position_right));
	comboBox_bottom_ = content_temp->bindWidget("combobox-bottom", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig->layout.position_bottom));
	comboBox_left_ = content_temp->bindWidget("combobox-left", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig->layout.position_left));
	comboBox_visibility_ = content_temp->bindWidget("combobox-visibility", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig->layout.visibility));
	comboBox_z_index_ = content_temp->bindWidget("combobox-z-index", std::make_unique<ComboBoxClassWithCustoms>(tailwindConfig->layout.z_index));


	comboBox_aspect_ratio_->setCustomValueString("aspect-ratio-");
	comboBox_columns_->setCustomValueString("columns-");
	comboBox_break_after_->setCustomValueString("break-after-");
	comboBox_break_before_->setCustomValueString("break-before-");
	comboBox_break_inside_->setCustomValueString("break-inside-");
	comboBox_box_decoration_break_->setCustomValueString("box-decoration-break-");
	comboBox_box_sizing_->setCustomValueString("box-sizing-");
	comboBox_display_->setCustomValueString("display-");
	comboBox_floats_->setCustomValueString("floats-");
	comboBox_clear_->setCustomValueString("clear-");
	comboBox_isolation_->setCustomValueString("isolation-");
	comboBox_object_fit_->setCustomValueString("object-fit-");
	comboBox_object_position_->setCustomValueString("object-position-");
	comboBox_overflow_->setCustomValueString("overflow-");
	comboBox_overflow_x_->setCustomValueString("overflow-x-");
	comboBox_overflow_y_->setCustomValueString("overflow-y-");
	comboBox_overscroll_behavior_->setCustomValueString("overscroll-behavior-");
	comboBox_overscroll_behavior_x_->setCustomValueString("overscroll-behavior-x-");
	comboBox_overscroll_behavior_y_->setCustomValueString("overscroll-behavior-y-");
	comboBox_position_->setCustomValueString("position-");
	comboBox_inset_->setCustomValueString("inset-");
	comboBox_inset_x_->setCustomValueString("inset-x-");
	comboBox_inset_y_->setCustomValueString("inset-y-");
	comboBox_top_->setCustomValueString("top-");
	comboBox_right_->setCustomValueString("right-");
	comboBox_bottom_->setCustomValueString("bottom-");
	comboBox_left_->setCustomValueString("left-");
	comboBox_visibility_->setCustomValueString("visibility-");
	comboBox_z_index_->setCustomValueString("z-");


	// deactivate custom checkbox
	comboBox_aspect_ratio_->setCondition("custom-checkbox", false);
	comboBox_columns_->setCondition("custom-checkbox", false);
	comboBox_break_after_->setCondition("custom-checkbox", false);
	comboBox_break_before_->setCondition("custom-checkbox", false);
	comboBox_break_inside_->setCondition("custom-checkbox", false);
	comboBox_box_decoration_break_->setCondition("custom-checkbox", false);
	comboBox_box_sizing_->setCondition("custom-checkbox", false);
	comboBox_display_->setCondition("custom-checkbox", false);
	comboBox_floats_->setCondition("custom-checkbox", false);
	comboBox_clear_->setCondition("custom-checkbox", false);
	comboBox_isolation_->setCondition("custom-checkbox", false);
	comboBox_object_fit_->setCondition("custom-checkbox", false);
	comboBox_object_position_->setCondition("custom-checkbox", false);
	comboBox_overflow_->setCondition("custom-checkbox", false);
	comboBox_overflow_x_->setCondition("custom-checkbox", false);
	comboBox_overflow_y_->setCondition("custom-checkbox", false);
	comboBox_overscroll_behavior_->setCondition("custom-checkbox", false);
	comboBox_overscroll_behavior_x_->setCondition("custom-checkbox", false);
	comboBox_overscroll_behavior_y_->setCondition("custom-checkbox", false);
	comboBox_position_->setCondition("custom-checkbox", false);
	comboBox_inset_->setCondition("custom-checkbox", false);
	comboBox_inset_x_->setCondition("custom-checkbox", false);
	comboBox_inset_y_->setCondition("custom-checkbox", false);
	comboBox_top_->setCondition("custom-checkbox", false);
	comboBox_right_->setCondition("custom-checkbox", false);
	comboBox_bottom_->setCondition("custom-checkbox", false);
	comboBox_left_->setCondition("custom-checkbox", false);
	comboBox_visibility_->setCondition("custom-checkbox", false);
	comboBox_z_index_->setCondition("custom-checkbox", false);

	// signals for default classes for tailwind
	comboBox_aspect_ratio_->classChanged().connect([=](){ styleChanged_.emit(); });
	checkBox_container_->checked().connect([=](){ styleChanged_.emit(); });
	comboBox_columns_->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_break_after_->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_break_before_->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_break_inside_->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_box_decoration_break_->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_box_sizing_->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_display_->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_floats_->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_clear_->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_isolation_->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_object_fit_->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_object_position_->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_overflow_->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_overflow_x_->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_overflow_y_->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_overscroll_behavior_->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_overscroll_behavior_x_->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_overscroll_behavior_y_->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_position_->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_inset_->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_inset_x_->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_inset_y_->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_top_->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_right_->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_bottom_->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_left_->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_visibility_->classChanged().connect([=](){ styleChanged_.emit(); });
	comboBox_z_index_->classChanged().connect([=](){ styleChanged_.emit(); });
};

std::string ElementLayoutWidget::getStyles()
{
	std::string elementClasses;

	if(comboBox_aspect_ratio_->getValue().compare("none") != 0){ elementClasses += comboBox_aspect_ratio_->getValue() + " "; }
	if(checkBox_container_->isChecked()){ elementClasses += "container "; }
	if(comboBox_columns_->getValue().compare("none") != 0){ elementClasses += comboBox_columns_->getValue() + " "; }
	if(comboBox_break_after_->getValue().compare("none") != 0){ elementClasses += comboBox_break_after_->getValue() + " "; }
	if(comboBox_break_before_->getValue().compare("none") != 0){ elementClasses += comboBox_break_before_->getValue() + " "; }
	if(comboBox_break_inside_->getValue().compare("none") != 0){ elementClasses += comboBox_break_inside_->getValue() + " "; }
	if(comboBox_box_decoration_break_->getValue().compare("none") != 0){ elementClasses += comboBox_box_decoration_break_->getValue() + " "; }
	if(comboBox_box_sizing_->getValue().compare("none") != 0){ elementClasses += comboBox_box_sizing_->getValue() + " "; }
	if(comboBox_display_->getValue().compare("none") != 0){ elementClasses += comboBox_display_->getValue() + " "; }
	if(comboBox_floats_->getValue().compare("none") != 0){ elementClasses += comboBox_floats_->getValue() + " "; }
	if(comboBox_clear_->getValue().compare("none") != 0){ elementClasses += comboBox_clear_->getValue() + " "; }
	if(comboBox_isolation_->getValue().compare("none") != 0){ elementClasses += comboBox_isolation_->getValue() + " "; }
	if(comboBox_object_fit_->getValue().compare("none") != 0){ elementClasses += comboBox_object_fit_->getValue() + " "; }
	if(comboBox_object_position_->getValue().compare("none") != 0){ elementClasses += comboBox_object_position_->getValue() + " "; }
	if(comboBox_overflow_->getValue().compare("none") != 0){ elementClasses += comboBox_overflow_->getValue() + " "; }
	if(comboBox_overflow_x_->getValue().compare("none") != 0){ elementClasses += comboBox_overflow_x_->getValue() + " "; }
	if(comboBox_overflow_y_->getValue().compare("none") != 0){ elementClasses += comboBox_overflow_y_->getValue() + " "; }
	if(comboBox_overscroll_behavior_->getValue().compare("none") != 0){ elementClasses += comboBox_overscroll_behavior_->getValue() + " "; }
	if(comboBox_overscroll_behavior_x_->getValue().compare("none") != 0){ elementClasses += comboBox_overscroll_behavior_x_->getValue() + " "; }
	if(comboBox_overscroll_behavior_y_->getValue().compare("none") != 0){ elementClasses += comboBox_overscroll_behavior_y_->getValue() + " "; }
	if(comboBox_position_->getValue().compare("none") != 0){ elementClasses += comboBox_position_->getValue() + " "; }
	if(comboBox_inset_->getValue().compare("none") != 0){ elementClasses += comboBox_inset_->getValue() + " "; }
	if(comboBox_inset_x_->getValue().compare("none") != 0){ elementClasses += comboBox_inset_x_->getValue() + " "; }
	if(comboBox_inset_y_->getValue().compare("none") != 0){ elementClasses += comboBox_inset_y_->getValue() + " "; }
	if(comboBox_top_->getValue().compare("none") != 0){ elementClasses += comboBox_top_->getValue() + " "; }
	if(comboBox_right_->getValue().compare("none") != 0){ elementClasses += comboBox_right_->getValue() + " "; }
	if(comboBox_bottom_->getValue().compare("none") != 0){ elementClasses += comboBox_bottom_->getValue() + " "; }
	if(comboBox_left_->getValue().compare("none") != 0){ elementClasses += comboBox_left_->getValue() + " "; }
	if(comboBox_visibility_->getValue().compare("none") != 0){ elementClasses += comboBox_visibility_->getValue() + " "; }
	if(comboBox_z_index_->getValue().compare("none") != 0){ elementClasses += comboBox_z_index_->getValue() + " "; }

	return elementClasses;
}

void ElementLayoutWidget::setClasses(LayoutData layoutData)
{
	resetStyles();

	if(layoutData.aspect_ratio.compare("none") != 0){ comboBox_aspect_ratio_->setValue(layoutData.aspect_ratio); }
	if(layoutData.container){ checkBox_container_->setChecked(true); }
	if(layoutData.columns.compare("none") != 0){ comboBox_columns_->setValue(layoutData.columns); }
	if(layoutData.break_after.compare("none") != 0){ comboBox_break_after_->setValue(layoutData.break_after); }
	if(layoutData.break_before.compare("none") != 0){ comboBox_break_before_->setValue(layoutData.break_before); }
	if(layoutData.break_inside.compare("none") != 0){ comboBox_break_inside_->setValue(layoutData.break_inside); }
	if(layoutData.box_decoration_break.compare("none") != 0){ comboBox_box_decoration_break_->setValue(layoutData.box_decoration_break); }
	if(layoutData.box_sizing.compare("none") != 0){ comboBox_box_sizing_->setValue(layoutData.box_sizing); }
	if(layoutData.display.compare("none") != 0){ comboBox_display_->setValue(layoutData.display); }
	if(layoutData.floats.compare("none") != 0){ comboBox_floats_->setValue(layoutData.floats); }
	if(layoutData.clear.compare("none") != 0){ comboBox_clear_->setValue(layoutData.clear); }
	if(layoutData.isolation.compare("none") != 0){ comboBox_isolation_->setValue(layoutData.isolation); }
	if(layoutData.object_fit.compare("none") != 0){ comboBox_object_fit_->setValue(layoutData.object_fit); }
	if(layoutData.object_position.compare("none") != 0){ comboBox_object_position_->setValue(layoutData.object_position); }
	for(auto& overflow_class : layoutData.overflow){
		if(overflow_class.find("overflow-") != std::string::npos){
			comboBox_overflow_->setValue(overflow_class);
		}else if(overflow_class.find("overflow-x-") != std::string::npos){
			comboBox_overflow_x_->setValue(overflow_class);
		}else if(overflow_class.find("overflow-y-") != std::string::npos){
			comboBox_overflow_y_->setValue(overflow_class);
		}
	}
	for(auto& overscroll_behavior_class : layoutData.overscroll_behavior){
		if(overscroll_behavior_class.find("overscroll-behavior-") != std::string::npos){
			comboBox_overscroll_behavior_->setValue(overscroll_behavior_class);
		}else if(overscroll_behavior_class.find("overscroll-behavior-x-") != std::string::npos){
			comboBox_overscroll_behavior_x_->setValue(overscroll_behavior_class);
		}else if(overscroll_behavior_class.find("overscroll-behavior-y-") != std::string::npos){
			comboBox_overscroll_behavior_y_->setValue(overscroll_behavior_class);
		}
	}
	if(layoutData.position.compare("none") != std::string::npos){ comboBox_position_->setValue(layoutData.position); }
	for(auto& inset_class : layoutData.inset){
		if(inset_class.find("inset-") != std::string::npos){
			comboBox_inset_->setValue(inset_class);
		}else if(inset_class.find("inset-x-") != std::string::npos){
			comboBox_inset_x_->setValue(inset_class);
		}else if(inset_class.find("inset-y-") != std::string::npos){
			comboBox_inset_y_->setValue(inset_class);
		}
	}
	for(auto& top_left_bottom_right_class : layoutData.top_left_bottom_right){
		if(top_left_bottom_right_class.find("top-") != std::string::npos){
			comboBox_top_->setValue(top_left_bottom_right_class);
		}else if(top_left_bottom_right_class.find("right-") != std::string::npos){
			comboBox_right_->setValue(top_left_bottom_right_class);
		}else if(top_left_bottom_right_class.find("bottom-") != std::string::npos){
			comboBox_bottom_->setValue(top_left_bottom_right_class);
		}else if(top_left_bottom_right_class.find("left-") != std::string::npos){
			comboBox_left_->setValue(top_left_bottom_right_class);
		}
	}
	if(layoutData.visibility.compare("none") != std::string::npos){ comboBox_visibility_->setValue(layoutData.visibility); }
	if(layoutData.z_index.compare("none") != std::string::npos){ comboBox_z_index_->setValue(layoutData.z_index); }

}

void ElementLayoutWidget::resetStyles()
{
	comboBox_aspect_ratio_->setValue("none");
	checkBox_container_->setChecked(false);
	comboBox_columns_->setValue("none");
	comboBox_break_after_->setValue("none");
	comboBox_break_before_->setValue("none");
	comboBox_break_inside_->setValue("none");
	comboBox_box_decoration_break_->setValue("none");
	comboBox_box_sizing_->setValue("none");
	comboBox_display_->setValue("none");
	comboBox_floats_->setValue("none");
	comboBox_clear_->setValue("none");
	comboBox_isolation_->setValue("none");
	comboBox_object_fit_->setValue("none");
	comboBox_object_position_->setValue("none");
	comboBox_overflow_->setValue("none");
	comboBox_overflow_x_->setValue("none");
	comboBox_overflow_y_->setValue("none");
	comboBox_overscroll_behavior_->setValue("none");
	comboBox_overscroll_behavior_x_->setValue("none");
	comboBox_overscroll_behavior_y_->setValue("none");
	comboBox_position_->setValue("none");
	comboBox_inset_->setValue("none");
	comboBox_inset_x_->setValue("none");
	comboBox_inset_y_->setValue("none");
	comboBox_top_->setValue("none");
	comboBox_right_->setValue("none");
	comboBox_bottom_->setValue("none");
	comboBox_left_->setValue("none");
	comboBox_visibility_->setValue("none");
	comboBox_z_index_->setValue("none");
}

void ElementLayoutWidget::setCustomTestValues()
{

	comboBox_aspect_ratio_->setValue("aspect-square");
	checkBox_container_->setChecked(true);
	comboBox_columns_->setValue("columns-2");
	comboBox_break_after_->setValue("break-after-avoid");
	comboBox_break_before_->setValue("break-before-avoid");
	comboBox_break_inside_->setValue("break-inside-avoid");
	comboBox_box_decoration_break_->setValue("box-decoration-clone");
	comboBox_box_sizing_->setValue("border-box");
	comboBox_display_->setValue("inline-block");
	comboBox_floats_->setValue("float-right");
	comboBox_clear_->setValue("clear-both");
	comboBox_isolation_->setValue("isolate");
	comboBox_object_fit_->setValue("object-contain");
	comboBox_object_position_->setValue("object-bottom");
	comboBox_overflow_->setValue("overflow-auto");
	comboBox_overflow_x_->setValue("overflow-x-scroll");
	comboBox_overflow_y_->setValue("overflow-y-scroll");
	comboBox_overscroll_behavior_->setValue("overscroll-contain");
	comboBox_overscroll_behavior_x_->setValue("overscroll-x-contain");
	comboBox_overscroll_behavior_y_->setValue("overscroll-y-contain");
	comboBox_position_->setValue("absolute");
	comboBox_inset_->setValue("inset-0");
	comboBox_inset_x_->setValue("inset-x-0");
	comboBox_inset_y_->setValue("inset-y-0");
	comboBox_top_->setValue("top-5");
	comboBox_right_->setValue("right-3");
	comboBox_bottom_->setValue("bottom-2");
	comboBox_left_->setValue("left-7");
	comboBox_visibility_->setValue("visible");
	comboBox_z_index_->setValue("z-10");

}
