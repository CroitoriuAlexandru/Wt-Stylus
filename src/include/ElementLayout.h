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
	bool setPositionStart(std::string className);
	bool setPositionEnd(std::string className);
	bool setVisibility(std::string className);
	bool setZIndex(std::string className);


private:
	int getIndesOfStringInVector(std::string str, std::vector<StyleClass> vec);
	// SelectionGroupClassChanger *aspect_ratio_widget_;
	
	std::shared_ptr<Wt::WButtonGroup> aspect_ratio_group;
	std::shared_ptr<Wt::WButtonGroup> container_group;
	std::shared_ptr<Wt::WButtonGroup> columns_group;
	std::shared_ptr<Wt::WButtonGroup> break_after_group;
	std::shared_ptr<Wt::WButtonGroup> break_before_group;
	std::shared_ptr<Wt::WButtonGroup> break_inside_group;
	std::shared_ptr<Wt::WButtonGroup> box_decoration_break_group;
	std::shared_ptr<Wt::WButtonGroup> box_sizing_group;
	ComboBoxClassChanger* display_widget_;
	std::shared_ptr<Wt::WButtonGroup> floats_group;
	std::shared_ptr<Wt::WButtonGroup> clear_group;
	std::shared_ptr<Wt::WButtonGroup> isolation_group;
	std::shared_ptr<Wt::WButtonGroup> object_fit_group;
	std::shared_ptr<Wt::WButtonGroup> object_position_group;
	std::shared_ptr<Wt::WButtonGroup> overflow_group;
	std::shared_ptr<Wt::WButtonGroup> overflow_x_group;
	std::shared_ptr<Wt::WButtonGroup> overflow_y_group;
	std::shared_ptr<Wt::WButtonGroup> overscroll_behavior_group;
	std::shared_ptr<Wt::WButtonGroup> overscroll_behavior_x_group;
	std::shared_ptr<Wt::WButtonGroup> overscroll_behavior_y_group;
	std::shared_ptr<Wt::WButtonGroup> position_group;
	std::shared_ptr<Wt::WButtonGroup> position_inset_group;
	std::shared_ptr<Wt::WButtonGroup> position_inset_x_group;
	std::shared_ptr<Wt::WButtonGroup> position_inset_y_group;
	std::shared_ptr<Wt::WButtonGroup> position_top_group;
	std::shared_ptr<Wt::WButtonGroup> position_right_group;
	std::shared_ptr<Wt::WButtonGroup> position_bottom_group;
	std::shared_ptr<Wt::WButtonGroup> position_left_group;
	std::shared_ptr<Wt::WButtonGroup> visibility_group;
	std::shared_ptr<Wt::WButtonGroup> z_index_group;

	void setCustomTestValues();
	
	std::shared_ptr<Config> tailwindConfig_;
	
	Wt::Signal<std::string> styleChanged_;
};