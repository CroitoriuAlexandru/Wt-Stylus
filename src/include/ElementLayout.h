#include <Wt/WTemplate.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WComboBox.h>
#include "ComboBoxes.h"
#include <Wt/WDialog.h>
#include <Wt/WPanel.h>

struct LayoutData
{
	std::string aspect_ratio = "none";
	bool container = false;
	std::string columns = "none";
	std::string break_after = "none";
	std::string break_before = "none";
	std::string break_inside = "none";
	std::string box_decoration_break = "none";
	std::string box_sizing = "none";
	std::string display = "none";
	std::string floats = "none";
	std::string clear = "none";
	std::string isolation = "none";
	std::string object_fit = "none";
	std::string object_position = "none";
	std::vector<std::string> overflow = {};
	std::vector<std::string> overscroll_behavior = {};
	std::string position = "none";
	std::vector<std::string> inset = {};
	std::vector<std::string> top_left_bottom_right = {};
	std::string visibility = "none";
	std::string z_index = "none";
};


class ElementLayoutWidget : public Wt::WPanel
{
public:
	ElementLayoutWidget(std::shared_ptr<Config> tailwindConfig);
	// margin and padding at the moment


	void setClasses(LayoutData layoutData);
    Wt::Signal<>& styleChanged() { return styleChanged_; };
	std::string getStyles();
	void resetStyles();
private:
	void setCustomTestValues();
	
	Wt::WTemplate* 				content_temp;
	std::shared_ptr<Config> 	tailwindConfig_;
	
	ComboBoxClassWithCustoms* 	comboBox_aspect_ratio_;
	Wt::WCheckBox* 				checkBox_container_;
	ComboBoxClassWithCustoms* 	comboBox_columns_;
	ComboBoxClassWithCustoms* 	comboBox_break_after_;
	ComboBoxClassWithCustoms* 	comboBox_break_before_;
	ComboBoxClassWithCustoms* 	comboBox_break_inside_;
	ComboBoxClassWithCustoms* 	comboBox_box_decoration_break_;
	ComboBoxClassWithCustoms* 	comboBox_box_sizing_;
	ComboBoxClassWithCustoms* 	comboBox_display_;
	ComboBoxClassWithCustoms* 	comboBox_floats_;
	ComboBoxClassWithCustoms* 	comboBox_clear_;
	ComboBoxClassWithCustoms* 	comboBox_isolation_;
	ComboBoxClassWithCustoms* 	comboBox_object_fit_;
	ComboBoxClassWithCustoms* 	comboBox_object_position_;
	ComboBoxClassWithCustoms* 	comboBox_overflow_;
	ComboBoxClassWithCustoms* 	comboBox_overflow_x_;
	ComboBoxClassWithCustoms* 	comboBox_overflow_y_;
	ComboBoxClassWithCustoms* 	comboBox_overscroll_behavior_;
	ComboBoxClassWithCustoms* 	comboBox_overscroll_behavior_x_;
	ComboBoxClassWithCustoms* 	comboBox_overscroll_behavior_y_;
	ComboBoxClassWithCustoms* 	comboBox_position_;
	ComboBoxClassWithCustoms* 	comboBox_inset_;
	ComboBoxClassWithCustoms* 	comboBox_inset_x_;
	ComboBoxClassWithCustoms* 	comboBox_inset_y_;
	ComboBoxClassWithCustoms* 	comboBox_top_;
	ComboBoxClassWithCustoms* 	comboBox_right_;
	ComboBoxClassWithCustoms* 	comboBox_bottom_;
	ComboBoxClassWithCustoms* 	comboBox_left_;
	ComboBoxClassWithCustoms* 	comboBox_visibility_;
	ComboBoxClassWithCustoms* 	comboBox_z_index_;

	Wt::Signal<> styleChanged_;
};