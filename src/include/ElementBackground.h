#include <Wt/WTemplate.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WComboBox.h>
#include "ComboBoxes.h"
#include <Wt/WDialog.h>
#include <Wt/WPanel.h>
#include <Wt/WGroupBox.h>
#include <Wt/WButtonGroup.h>
#include <Wt/WRadioButton.h>

struct BackgroundData
{
	// bg-(fixed|local|scroll)
	std::string attachment = "none";
	// bg-clip-(border|padding|content|text)
	std::string clip = "none";
	std::string color_class = "none";
	// bg-origin-(border|padding|content)
	std::string origin = "none";
	// bg-(bottom|center|left|left-bottom|left-top|right|right-bottom|right-top|top)
	std::string position = "none";
	// bg-(repeat|no-repeat|repeat-x|repeat-y|repeat-round|repeat-space)
	std::string repeat = "none";
	// bg-(auto|cover|contain)
	std::string size = "none";
	// bg-gradient-(to-t|to-tr|to-r|to-br|to-b|to-bl|to-l|to-tl)
	std::string gradient = "none";

	std::string color_from = "none";
	std::string color_via = "none";
	std::string color_to = "none";

	std::string color_from_step = "none";
	std::string color_via_step = "none";
	std::string color_to_step = "none";

};


class ElementBackgroundWidget : public Wt::WPanel
{
public:
	ElementBackgroundWidget(std::shared_ptr<Config> tailwindConfig);
	// margin and padding at the moment


	void setClasses(BackgroundData bgData);
    Wt::Signal<std::string>& styleChanged() { return styleChanged_; };
	
	std::string getStyles();
	void resetStyles();

	bool setGradient(std::string className);
	bool setAttachment(std::string className);
	bool setClip(std::string className);
	bool setOrigin(std::string className);
	bool setPosition(std::string className);
	bool setRepeat(std::string className);
	bool setSize(std::string className);
private:
	int getIndesOfStringInVector(std::string str, std::vector<StyleClass> vec);
	std::shared_ptr<Wt::WButtonGroup> gradient_group;
	std::shared_ptr<Wt::WButtonGroup> attachment_group;
	std::shared_ptr<Wt::WButtonGroup> clip_group;
	std::shared_ptr<Wt::WButtonGroup> origin_group;
	std::shared_ptr<Wt::WButtonGroup> position_group;
	std::shared_ptr<Wt::WButtonGroup> repeat_group;
	std::shared_ptr<Wt::WButtonGroup> size_group;
	std::string gradient_class = "none";
	std::string attachment_class = "none";
	std::string clip_class = "none";
	std::string origin_class = "none";
	std::string position_class = "none";
	std::string repeat_class = "none";
	std::string size_class = "none";
	
	void setCustomTestValues();
	
	std::shared_ptr<Config> tailwindConfig_;
	
	Wt::Signal<std::string> styleChanged_;
};