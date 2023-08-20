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
	
	StyleClassComboBox* 	comboBox_aspect_ratio_;
	Wt::WCheckBox* 				checkBox_container_;
	StyleClassComboBox* 	comboBox_columns_;
	StyleClassComboBox* 	comboBox_break_after_;
	StyleClassComboBox* 	comboBox_break_before_;
	StyleClassComboBox* 	comboBox_break_inside_;
	StyleClassComboBox* 	comboBox_box_decoration_break_;
	StyleClassComboBox* 	comboBox_box_sizing_;
	StyleClassComboBox* 	comboBox_display_;
	StyleClassComboBox* 	comboBox_floats_;
	StyleClassComboBox* 	comboBox_clear_;
	StyleClassComboBox* 	comboBox_isolation_;
	StyleClassComboBox* 	comboBox_object_fit_;
	StyleClassComboBox* 	comboBox_object_position_;
	StyleClassComboBox* 	comboBox_overflow_;
	StyleClassComboBox* 	comboBox_overflow_x_;
	StyleClassComboBox* 	comboBox_overflow_y_;
	StyleClassComboBox* 	comboBox_overscroll_behavior_;
	StyleClassComboBox* 	comboBox_overscroll_behavior_x_;
	StyleClassComboBox* 	comboBox_overscroll_behavior_y_;
	StyleClassComboBox* 	comboBox_position_;
	StyleClassComboBox* 	comboBox_inset_;
	StyleClassComboBox* 	comboBox_inset_x_;
	StyleClassComboBox* 	comboBox_inset_y_;
	StyleClassComboBox* 	comboBox_top_;
	StyleClassComboBox* 	comboBox_right_;
	StyleClassComboBox* 	comboBox_bottom_;
	StyleClassComboBox* 	comboBox_left_;
	StyleClassComboBox* 	comboBox_visibility_;
	StyleClassComboBox* 	comboBox_z_index_;

	Wt::Signal<> styleChanged_;
};