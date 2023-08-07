#include <string>
#include <vector>

namespace TailwindConfig {

    struct Propriety {
        Propriety(std::string className, std::string propriety, std::string description) : class_(className), propriety_(propriety), description_(description) {}
        std::string class_;
        std::string propriety_;
        std::string description_;
    };




    struct Tailwind_layout {
        struct Aspect_ratio {
            

            Propriety auto_{"aspect-auto", "aspect-ratio: auto;", ""};
            Propriety square_{"aspect-square", "aspect-ratio: 1 / 1;", ""};
            Propriety video_{"aspect-video", "aspect-ratio: 16 / 9;", ""};
            std::string description_ = "The aspect-ratio utility allows you to control the aspect ratio of an element. Use it to force an element to be a specific aspect ratio, regardless of its width and height.";
        };

        struct Container {
            Propriety container_{"container", "None = 	width: 100%;\n sm (640px) = max-width: 640px;\n md (768px) = max-width: 768px;\n lg (1024) = max-width 1024px;\n xl (1280px) = max-width: 1280px;\n 2xl (1536px) = max-width: 1536px;", ""};
            std::string description_ = "The container class sets the max-width of an element to match the min-width of the current breakpoint. This is useful if you prefer to design for a fixed set of screen sizes instead of trying to accommodate a fully fluid viewport. Note that unlike containers you might have used in other frameworks, Tailwinds container does not center itself automatically and does not have any built-in horizontal padding.";
        };

        struct Columns {
            std::vector<std::string> variants{"7xl", "6xl", "5xl", "4xl", "3xl", "2xl", "xl", "lg", "md", "sm", "xs", "auto", "12", "11", "10", "9", "8", "7", "6", "5", "4", "3", "2", "1"};
            std::string baseName = "columns";
            std::vector<Propriety> styleClasses_;
            std::string description_ = "The column-count utility specifies the number of columns an element should be divided into.";
            
            Columns(){
                for (auto variant : variants) 
                {
                    Propriety column{baseName + variant, "column-count: " + variant + ";", ""}; 
                    styleClasses_.push_back(column); 
                }
            }
        };

        struct Break_after {
            std::vector<std::string> variants{"auto", "avoid-page", "avoid", "all", "page", "left", "right", "column"};
            std::string baseName = "break-after";
            std::vector<Propriety> styleClasses_;
        };


        Aspect_ratio aspect_ratio_;
        Container container_;
        Columns columns_;
        Break_after break_after_;
    };

};