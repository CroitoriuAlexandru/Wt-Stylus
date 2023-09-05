#include <Wt/WTemplate.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WComboBox.h>

#include "ComboBoxClassChanger.h"
#include "SelectionGroupClassChanger.h"

#include <Wt/WDialog.h>
#include <Wt/WPanel.h>
#include <Wt/WGroupBox.h>
#include <Wt/WButtonGroup.h>
#include <Wt/WRadioButton.h>

struct LayoutData
{
	std::string aspect_ratio = "none";
	std::string container = "none";
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

	std::vector<std::string> overflow;
	std::vector<std::string> overscroll_behavior;
	
	std::string position = "none";
	std::vector<std::string> position_inset;
	std::vector<std::string> position_sides;

	std::string visibility = "none";
	std::string z_index = "none";
};


class ElementLayoutWidget : public Wt::WPanel
{
public:
	ElementLayoutWidget(std::shared_ptr<Config> tailwindConfig);

	void setClasses(LayoutData layoutData);
    Wt::Signal<std::string>& styleChanged() { return styleChanged_; };
	
	std::string getStyles();
	void resetStyles();

	bool setAspectRatio(std::string className);
	bool setContainer(std::string className);
	bool setColumns(std::string className);
	bool setBreakAfter(std::string className);
	bool setBreakBefore(std::string className);
	bool setBreakInside(std::string className);
	bool setBoxDecorationBreak(std::string className);
	bool setBoxSizing(std::string className);
	bool setDisplay(std::string className);
	bool setFloats(std::string className);
	bool setClear(std::string className);
	bool setIsolation(std::string className);
	bool setObjectFit(std::string className);
	bool setObjectPosition(std::string className);
	bool setOverflow(std::string className);
	bool setOverflowX(std::string className);
	bool setOverflowY(std::string className);
	bool setOverscrollBehavior(std::string className);
	bool setOverscrollBehaviorX(std::string className);
	bool setOverscrollBehaviorY(std::string className);
	bool setPosition(std::string className);
	bool setPositionInset(std::string className);
	bool setPositionInsetX(std::string className);
	bool setPositionInsetY(std::string className);
	bool setPositionTop(std::string className);
	bool setPositionRight(std::string className);
	bool setPositionBottom(std::string className);
	bool setPositionLeft(std::string className);
	bool setVisibility(std::string className);
	bool setZIndex(std::string className);

	// its punlic because of the flex and grid witch needs to change depending on the display value
	ComboBoxClassChanger* display_widget_;
private:

	int getIndesOfStringInVector(std::string str, std::vector<StyleClass> vec);
	ComboBoxClassChanger *aspect_ratio_widget_;
	SelectionGroupClassChanger *container_widget_;
	ComboBoxClassChanger *columns_widget_;
	ComboBoxClassChanger *break_after_widget_;
	ComboBoxClassChanger *break_before_widget_;
	ComboBoxClassChanger *break_inside_widget_;
	ComboBoxClassChanger *box_decoration_break_widget_;
	SelectionGroupClassChanger *box_sizing_widget_;
	SelectionGroupClassChanger *floats_widget_;
	SelectionGroupClassChanger *clear_widget_;
	SelectionGroupClassChanger *isolation_widget_;
	ComboBoxClassChanger *object_fit_widget_;
	ComboBoxClassChanger *object_position_widget_;
	ComboBoxClassChanger *overflow_widget_;
	ComboBoxClassChanger *overflow_x_widget_;
	ComboBoxClassChanger *overflow_y_widget_;
	ComboBoxClassChanger *overscroll_behavior_widget_;
	ComboBoxClassChanger *overscroll_behavior_x_widget_;
	ComboBoxClassChanger *overscroll_behavior_y_widget_;
	ComboBoxClassChanger *position_widget_;
	ComboBoxClassChanger *position_inset_widget_;
	ComboBoxClassChanger *position_inset_x_widget_;
	ComboBoxClassChanger *position_inset_y_widget_;
	ComboBoxClassChanger *position_top_widget_;
	ComboBoxClassChanger *position_right_widget_;
	ComboBoxClassChanger *position_bottom_widget_;
	ComboBoxClassChanger *position_left_widget_;
	ComboBoxClassChanger *visibility_widget_;
	ComboBoxClassChanger *z_index_widget_;

	std::string aspect_ratio_class = "none";
	std::string container_class = "none";
	std::string columns_class = "none";
	std::string break_after_class = "none";
	std::string break_before_class = "none";
	std::string break_inside_class = "none";
	std::string box_decoration_break_class = "none";
	std::string box_sizing_class = "none";
	std::string display_class = "none";
	std::string floats_class = "none";
	std::string clear_class = "none";
	std::string isolation_class = "none";
	std::string object_fit_class = "none";
	std::string object_position_class = "none";
	std::string overflow_class = "none";
	std::string overflow_x_class = "none";
	std::string overflow_y_class = "none";
	std::string overscroll_behavior_class = "none";
	std::string overscroll_behavior_x_class = "none";
	std::string overscroll_behavior_y_class = "none";
	std::string position_class = "none";
	std::string position_inset_class = "none";
	std::string position_inset_x_class = "none";
	std::string position_inset_y_class = "none";
	std::string position_top_class = "none";
	std::string position_right_class = "none";
	std::string position_bottom_class = "none";
	std::string position_left_class = "none";
	std::string visibility_class = "none";
	std::string z_index_class = "none";



	void setCustomTestValues();
	
	std::shared_ptr<Config> tailwindConfig_;
	
	Wt::Signal<std::string> styleChanged_;
};