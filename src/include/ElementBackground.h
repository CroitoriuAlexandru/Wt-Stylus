#include <Wt/WTemplate.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WComboBox.h>
#include "ComboBoxes.h"
#include <Wt/WDialog.h>
#include <Wt/WPanel.h>


struct BackgroundData
{
	// bg-(fixed|local|scroll)
	std::string bg_attachment = "none";
	// bg-clip-(border|padding|content|text)
	std::string bg_clip = "none";
	std::string bg_color = "none";
	// bg-origin-(border|padding|content)
	std::string bg_origin = "none";
	// bg-(bottom|center|left|left-bottom|left-top|right|right-bottom|right-top|top)
	std::string bg_position = "none";
	// bg-(repeat|no-repeat|repeat-x|repeat-y|repeat-round|repeat-space)
	std::string bg_repeat = "none";
	// bg-(auto|cover|contain)
	std::string bg_size = "none";
	// bg-gradient-(to-t|to-tr|to-r|to-br|to-b|to-bl|to-l|to-tl)
	std::string bg_image = "none";

	std::string bg_color_from = "none";
	std::string bg_color_via = "none";
	std::string bg_color_to = "none";

	std::string bg_color_from_step = "none";
	std::string bg_color_via_step = "none";
	std::string bg_color_to_step = "none";

};


class ElementBackgroundWidget : public Wt::WPanel
{
public:
	ElementBackgroundWidget(std::shared_ptr<Config> tailwindConfig);
	// margin and padding at the moment


	void setClasses(BackgroundData bgData);
    Wt::Signal<>& styleChanged() { return styleChanged_; };
	std::string getStyles();
	void resetStyles();
	
	ColorSelecionWidget *bg_color_widget;
	ColorSelecionWidget *bg_color_from_widget;
	ColorSelecionWidget *bg_color_via_widget;
	ColorSelecionWidget *bg_color_to_widget;

	std::shared_ptr<Wt::WButtonGroup> gradient_group;
	std::shared_ptr<Wt::WButtonGroup> gradient_step_group;

	std::shared_ptr<Wt::WButtonGroup> attachment_group;
	std::shared_ptr<Wt::WButtonGroup> clip_group;
	std::shared_ptr<Wt::WButtonGroup> origin_group;
	std::shared_ptr<Wt::WButtonGroup> position_group;
	std::shared_ptr<Wt::WButtonGroup> repeat_group;
	std::shared_ptr<Wt::WButtonGroup> size_group;

	// this is where the radio buttons for chosing from via to collors. its saved because it needs to be hidden when not needed
	Wt::WContainerWidget *from_via_to_wrapper;
	int getIndexOfStringInVector(std::string str, std::vector<StyleClass> vec);
	void setCustomTestValues();
	
	std::shared_ptr<Config> tailwindConfig_;
	
	Wt::Signal<> styleChanged_;

	// bg custom regexp
	std::regex regex_custom_color =  std::regex("bg-\\[[\\S]*\\]");
	// bg-(inherit|current|transparent|black|white)
	std::regex regex_def_classes = std::regex("(bg|from|via|to)-(inherit|current|transparent|black|white)");
	// bg-((slate|gray|zinc|neutral|stone|red|orange|amber|yellow|lime|green|emerald|teal|cyan|sky|blue|indigo|violet|purple|fuchsia|pink|rose)-(950|900|800|700|600|500|400|300|200|150|100|50)\/((100|95|90|85|80|75|70|65|60|55|50|45|40|35|30|25|20|15|10|5|0)|\[[\S]*\])[ ]((from|via|to)-(0|5|10|15|20|25|30|35|40|45|50|55|60|65|70|75|80|85|90|95|100)%)?)
	std::regex regex_color_classes = std::regex("(bg|from|via|to)-((slate|gray|zinc|neutral|stone|red|orange|amber|yellow|lime|green|emerald|teal|cyan|sky|blue|indigo|violet|purple|fuchsia|pink|rose)-(950|900|800|700|600|500|400|300|200|150|100|50)\\/((100|95|90|85|80|75|70|65|60|55|50|45|40|35|30|25|20|15|10|5|0)|\\[[\\S]*\\]))");
};