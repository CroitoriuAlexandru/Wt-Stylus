// #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
// #include "include/DocTest.h"

#include <iostream>
#include <fstream>

#include "include/Config.h"
#include "include/Layout.h"
#include "include/Borders.h"
#include "include/Backgrounds.h"
#include "include/Effects.h"
#include "include/Flexbox.h"
#include "include/Grid.h"
#include "include/Interactivity.h"
#include "include/Spacing.h"
#include "include/Sizing.h"
#include "include/Tables.h"
#include "include/Transforms.h"
#include "include/TransitionsAndAnimation.h"
#include "include/Typography.h"

using namespace Tailwind;

std::string getConfigData(Config &config)
{
    std::string data = "";
    // Layout
    data += config.layout.aspectRatioData();
    data += config.layout.containerData();
    data += config.layout.columnsData();
    data += config.layout.breakAfterData();
    data += config.layout.breakBeforeData();
    data += config.layout.breakInsideData();
    data += config.layout.boxDecorationBreakData();
    data += config.layout.boxSizingData();
    data += config.layout.displayData();
    data += config.layout.floatsData();
    data += config.layout.clearData();
    data += config.layout.isolationData();
    data += config.layout.objectFitData();
    data += config.layout.objectPositionData();
    data += config.layout.overflowData();
    data += config.layout.overscrollBehaviorData();
    data += config.layout.positionData();
    data += config.layout.positionSidesData();
    data += config.layout.visibilityData();
    data += config.layout.zIndexData();
    // Flexbox
    data += config.flexbox.basisData();
    data += config.flexbox.directionData();
    data += config.flexbox.wrapData();
    data += config.flexbox.flexData();
    data += config.flexbox.growData();
    data += config.flexbox.shrinkData();
    data += config.flexbox.orderData();
    data += config.flexbox.justifyData();
    data += config.flexbox.alignData();
    // Grid
    data += config.grid.orderData();
    data += config.grid.gridTemplateData();
    data += config.grid.gridColsData();
    data += config.grid.gridRowsData();
    data += config.grid.gridAutoData();
    data += config.grid.gapData();
    data += config.grid.placeData();
    // Spacing
    data += config.spacing.marginData();
    data += config.spacing.paddingData();
    data += config.spacing.spaceData();
    // Sizing
    data += config.sizing.widthData();
    data += config.sizing.heightData();
    data += config.sizing.maxHeightData();
    data += config.sizing.minWidthData();
    data += config.sizing.minHeightData();
    data += config.sizing.maxWidthData();
    // Typography
    data += config.typography.fontFamilyData();
    data += config.typography.fontSizeData();
    data += config.typography.fontSmoothingData();
    data += config.typography.fontStyleData();
    data += config.typography.fontWeightData();
    data += config.typography.fontVariantNumericData();
    data += config.typography.letterSpacingData();
    data += config.typography.lineClampData();
    data += config.typography.lineHeightData();
    data += config.typography.listStyleImageData();
    data += config.typography.listStylePositionData();
    data += config.typography.listStyleTypeData();
    data += config.typography.textAlignData();
    data += config.typography.textDecorationData();
    data += config.typography.textDecorationStyleData();
    data += config.typography.textDecorationThiknessData();
    data += config.typography.textUnderlineOffsetData();
    data += config.typography.textTransformData();
    data += config.typography.textOverflowData();
    data += config.typography.textIndentData();
    data += config.typography.verticalAlignData();
    data += config.typography.whitespaceData();
    data += config.typography.wordBreakData();
    data += config.typography.hyphensData();
    data += config.typography.contentData();
    // backgrounds
    data += config.backgrounds.backgroundAttachmentData();
    data += config.backgrounds.backgroundClipData();
    data += config.backgrounds.backgroundColorData();
    data += config.backgrounds.backgroundOriginData();
    data += config.backgrounds.backgroundPositionData();
    data += config.backgrounds.backgroundRepeatData();
    data += config.backgrounds.backgroundSizeData();
    data += config.backgrounds.backgroundImageData();
    data += config.backgrounds.gradientStopsData();
    // Borders
    data += config.borders.borderRadiusData();
    data += config.borders.borderWidthData();
    data += config.borders.borderStyleData();
    data += config.borders.divideData();
    data += config.borders.outlineData();
    data += config.borders.ringData();
    // Effects
    data += config.effects.boxShadowData();
    // data += config.effects.boxShadowColorData();
    data += config.effects.opacityData();
    data += config.effects.mixBlendModeData();
    // Filters
    data += config.filters.blurData();
    data += config.filters.brightnessData();
    data += config.filters.contrastData();
    data += config.filters.dropShadowData();
    data += config.filters.grayscaleData();
    data += config.filters.hueRotateData();
    data += config.filters.invertData();
    data += config.filters.saturateData();
    data += config.filters.sepiaData();
    data += config.filters.backdropBlurData();
    data += config.filters.backdropBrightnessData();
    data += config.filters.backdropContrastData();
    data += config.filters.backdropGrayscaleData();
    data += config.filters.backdropHueRotateData();
    data += config.filters.backdropInvertData();
    data += config.filters.backdropOpacityData();
    data += config.filters.backdropSaturateData();
    data += config.filters.backdropSepiaData();

    // Tables
    data += config.tables.borderCollapseData();
    data += config.tables.borderSpacingData();
    data += config.tables.tableLayoutData();
    data += config.tables.captionSideData();

    // Transitions & Animation
    data += config.transitions_and_animation.transitionPropertyData();
    data += config.transitions_and_animation.transitionDurationData();
    data += config.transitions_and_animation.transitionTimingFunctionData();
    data += config.transitions_and_animation.transitionDelayData();
    data += config.transitions_and_animation.animationData();

    // Transform
    data += config.transforms.scaleData();
    data += config.transforms.rotateData();
    data += config.transforms.skewData();
    data += config.transforms.translateData();

    // Interactivity
    data += config.interactivity.appearanceData();
    data += config.interactivity.cursorData();
    data += config.interactivity.pointerEventsData();
    data += config.interactivity.resizeData();
    data += config.interactivity.scrollBehaviorData();
    data += config.interactivity.scrollMarginData();
    data += config.interactivity.scrollPaddingData();
    data += config.interactivity.scrollSnapAlignData();
    data += config.interactivity.scrollSnapStopData();
    data += config.interactivity.scrollSnapTypeData();
    data += config.interactivity.touchActionData();
    data += config.interactivity.userSelectData();
    data += config.interactivity.willChangeData();
    
    // Svg
    data += config.svg.strokeWidthData();

    // Accesibility
    data += config.accessibility.screenReadersData();

    return data;
}

std::vector<std::string> findAndRemoveMatches(boost::regex regex, std::string& str) {
    boost::regex_iterator<std::string::iterator> it(str.begin(), str.end(), regex);
    boost::regex_iterator<std::string::iterator> end;
    std::string result = "";

    std::vector<std::string> matches;

    size_t lastPos = 0;
    while (it != end) {
        result += str.substr(lastPos, it->position() - lastPos);
        matches.push_back(it->str()); // Store deleted value in vector
        lastPos = it->position() + it->length();
        ++it;
    }
    // remove padding classes from classes string
    str = result + str.substr(lastPos, str.length() - lastPos);
    return matches;
}

void removeNone(std::vector<StyleClass>& vec){
    for(int i = 0; i < vec.size(); i++){
        if(vec[i].className_.compare("none") == 0){
            vec.erase(vec.begin() + i);
            break;
        }
    }
}


int main() {
    std::ofstream output_file("tailwindClasses.txt", std::ios::trunc);
    Config config = Config();
    std::string configData = getConfigData(config);



    // Accesibility
    findAndRemoveMatches(config.accessibility.screen_readers_regex, configData);

    // Svg
    findAndRemoveMatches(config.svg.stroke_width_regex, configData);
    // stroke 
    // fill

    // Interactivity
    findAndRemoveMatches(config.interactivity.will_change_regex, configData);
    findAndRemoveMatches(config.interactivity.user_select_regex, configData);
    findAndRemoveMatches(config.interactivity.touch_action_regex, configData);
    findAndRemoveMatches(config.interactivity.scroll_snap_type_regex, configData);
    findAndRemoveMatches(config.interactivity.scroll_snap_proximity_regex, configData);
    findAndRemoveMatches(config.interactivity.scroll_snap_mandatory_regex, configData);
    findAndRemoveMatches(config.interactivity.scroll_snap_stop_regex, configData);
    findAndRemoveMatches(config.interactivity.scroll_snap_align_regex, configData);
    findAndRemoveMatches(config.interactivity.scroll_padding_regex, configData);
    findAndRemoveMatches(config.interactivity.scroll_margin_regex, configData);
    findAndRemoveMatches(config.interactivity.scroll_behavior_regex, configData);
    findAndRemoveMatches(config.interactivity.resize_regex, configData);
    findAndRemoveMatches(config.interactivity.pointer_events_regex, configData);
    // carret collor
    findAndRemoveMatches(config.interactivity.cursor_regex, configData);
    findAndRemoveMatches(config.interactivity.appearance_regex, configData);
    // accent color

    // Transform
    findAndRemoveMatches(config.transforms.origin_regex, configData);
    findAndRemoveMatches(config.transforms.skew_regex, configData);
    findAndRemoveMatches(config.transforms.translate_regex, configData);
    findAndRemoveMatches(config.transforms.rotate_regex, configData);
    findAndRemoveMatches(config.transforms.scale_regex, configData);

    // transitions & animation
    findAndRemoveMatches(config.transitions_and_animation.animation_regex, configData);
    findAndRemoveMatches(config.transitions_and_animation.transition_delay_regex, configData);
    findAndRemoveMatches(config.transitions_and_animation.transition_timing_function_regex, configData);
    findAndRemoveMatches(config.transitions_and_animation.transition_duration_regex, configData);
    findAndRemoveMatches(config.transitions_and_animation.transition_property_regex, configData);

    // Tables
    findAndRemoveMatches(config.tables.caption_side_regex, configData);
    findAndRemoveMatches(config.tables.table_layout_regex, configData);
    findAndRemoveMatches(config.tables.border_spacing_regex, configData);
    findAndRemoveMatches(config.tables.border_spacing_y_regex, configData);
    findAndRemoveMatches(config.tables.border_spacing_x_regex, configData);
    findAndRemoveMatches(config.tables.border_collapse_regex, configData);

    // Filters
    findAndRemoveMatches(config.filters.backdrop_sepia_regex, configData);
    findAndRemoveMatches(config.filters.backdrop_saturate_regex, configData);
    findAndRemoveMatches(config.filters.backdrop_opacity_regex, configData);
    findAndRemoveMatches(config.filters.backdrop_invert_regex, configData);
    findAndRemoveMatches(config.filters.backdrop_hue_rotate_regex, configData);
    findAndRemoveMatches(config.filters.backdrop_grayscale_regex, configData);
    findAndRemoveMatches(config.filters.backdrop_contrast_regex, configData);
    findAndRemoveMatches(config.filters.backdrop_brightness_regex, configData);
    findAndRemoveMatches(config.filters.backdrop_blur_regex, configData);
    findAndRemoveMatches(config.filters.sepia_regex, configData);
    findAndRemoveMatches(config.filters.saturate_regex, configData);
    findAndRemoveMatches(config.filters.invert_regex, configData);
    findAndRemoveMatches(config.filters.hue_rotate_regex, configData);
    findAndRemoveMatches(config.filters.grayscale_regex, configData);
    findAndRemoveMatches(config.filters.drop_shadow_regex, configData);
    findAndRemoveMatches(config.filters.contrast_regex, configData);
    findAndRemoveMatches(config.filters.brightness_regex, configData);
    findAndRemoveMatches(config.filters.blur_regex, configData);

    // Effects
    findAndRemoveMatches(config.effects.bg_blend_mode_regex, configData);
    findAndRemoveMatches(config.effects.mix_blend_mode_regex, configData);
    findAndRemoveMatches(config.effects.opacity_regex, configData);
    // findAndRemoveMatches(config.effects.box_shadow_color_regex, configData);
    findAndRemoveMatches(config.effects.box_shadow_regex, configData);

    // Borders
    findAndRemoveMatches(config.borders.ring_offset_width_regex, configData);
    findAndRemoveMatches(config.borders.ring_width_regex, configData);
    findAndRemoveMatches(config.borders.outline_offset_regex, configData);
    findAndRemoveMatches(config.borders.outline_style_regex, configData);
    findAndRemoveMatches(config.borders.outline_width_regex, configData);
    findAndRemoveMatches(config.borders.divide_style_regex, configData);
    findAndRemoveMatches(config.borders.divide_width_regex, configData);
    findAndRemoveMatches(config.borders.border_width_regex, configData);
    findAndRemoveMatches(config.borders.border_style_regex, configData);
    findAndRemoveMatches(config.borders.border_radius_regex, configData);

    // Backgrounds
    findAndRemoveMatches(config.backgrounds.background_color_to_step, configData);
    findAndRemoveMatches(config.backgrounds.background_color_via_step, configData);
    findAndRemoveMatches(config.backgrounds.background_color_from_step, configData);

    findAndRemoveMatches(config.backgrounds.background_color_regex, configData);
    findAndRemoveMatches(config.backgrounds.background_color_to_regex, configData);
    findAndRemoveMatches(config.backgrounds.background_color_via_regex, configData);
    findAndRemoveMatches(config.backgrounds.background_color_from_regex, configData);

    findAndRemoveMatches(config.backgrounds.background_image_regex, configData);
    findAndRemoveMatches(config.backgrounds.background_size_regex, configData);
    findAndRemoveMatches(config.backgrounds.background_repeat_regex, configData);
    findAndRemoveMatches(config.backgrounds.background_position_regex, configData);
    findAndRemoveMatches(config.backgrounds.background_origin_regex, configData);
    findAndRemoveMatches(config.backgrounds.background_clip_regex, configData);
    findAndRemoveMatches(config.backgrounds.background_attachment_regex, configData);

    // Typography
    findAndRemoveMatches(config.typography.content_regex, configData);
    findAndRemoveMatches(config.typography.hyphens_regex, configData);
    findAndRemoveMatches(config.typography.word_break_regex, configData);
    findAndRemoveMatches(config.typography.whitespace_regex, configData);
    findAndRemoveMatches(config.typography.vertical_align_regex, configData);
    findAndRemoveMatches(config.typography.text_indent_regex, configData);
    findAndRemoveMatches(config.typography.text_overflow_regex, configData);
    findAndRemoveMatches(config.typography.text_transform_regex, configData);
    findAndRemoveMatches(config.typography.text_underline_offset_regex, configData);
    findAndRemoveMatches(config.typography.text_decoration_thikness_regex, configData);
    findAndRemoveMatches(config.typography.text_decoration_style_regex, configData);
    findAndRemoveMatches(config.typography.text_decoration_regex, configData);
    findAndRemoveMatches(config.typography.text_align_regex, configData);
    findAndRemoveMatches(config.typography.line_style_type_regex, configData);
    findAndRemoveMatches(config.typography.line_style_position_regex, configData);
    findAndRemoveMatches(config.typography.line_style_image_regex, configData);
    findAndRemoveMatches(config.typography.line_height_regex, configData);
    findAndRemoveMatches(config.typography.line_clamp_regex, configData);
    findAndRemoveMatches(config.typography.letter_spacing_regex, configData);
    findAndRemoveMatches(config.typography.font_variant_numeric_regex, configData);
    findAndRemoveMatches(config.typography.font_weight_regex, configData);
    findAndRemoveMatches(config.typography.font_style_regex, configData);
    findAndRemoveMatches(config.typography.font_smoothing_regex, configData);
    findAndRemoveMatches(config.typography.font_size_regex, configData);
    findAndRemoveMatches(config.typography.font_family_regex, configData);

    // Sizing
    findAndRemoveMatches(config.sizing.width_regex, configData);
    findAndRemoveMatches(config.sizing.height_regex, configData);
    findAndRemoveMatches(config.sizing.max_height_regex, configData);
    findAndRemoveMatches(config.sizing.max_width_regex, configData);
    findAndRemoveMatches(config.sizing.min_width_regex, configData);
    findAndRemoveMatches(config.sizing.min_height_regex, configData);

    // Spacing
    findAndRemoveMatches(config.spacing.padding_regex, configData);
    findAndRemoveMatches(config.spacing.margin_regex, configData);
    findAndRemoveMatches(config.spacing.space_regex, configData);

    // Flex
    findAndRemoveMatches(config.flexbox.align_self_regex, configData);
    findAndRemoveMatches(config.flexbox.align_items_regex, configData);
    findAndRemoveMatches(config.flexbox.align_content_regex, configData);
    findAndRemoveMatches(config.flexbox.justify_self_regex, configData);
    findAndRemoveMatches(config.flexbox.justify_items_regex, configData);
    findAndRemoveMatches(config.flexbox.justify_content_regex, configData);
    findAndRemoveMatches(config.flexbox.shrink_regex, configData);
    findAndRemoveMatches(config.flexbox.grow_regex, configData);
    findAndRemoveMatches(config.flexbox.flex_regex, configData);
    findAndRemoveMatches(config.flexbox.wrap_regex, configData);
    findAndRemoveMatches(config.flexbox.direction_regex, configData);
    findAndRemoveMatches(config.flexbox.basis_regex, configData);
    findAndRemoveMatches(config.flexbox.order_regex, configData);

    // Grid
    findAndRemoveMatches(config.grid.place_content_regex, configData);
    findAndRemoveMatches(config.grid.place_items_regex, configData);
    findAndRemoveMatches(config.grid.place_self_regex, configData);
    findAndRemoveMatches(config.grid.gap_regex, configData);
    findAndRemoveMatches(config.grid.grid_auto_rows_regex, configData);
    findAndRemoveMatches(config.grid.grid_auto_columns_regex, configData);
    findAndRemoveMatches(config.grid.grid_auto_flow_regex, configData);
    findAndRemoveMatches(config.grid.grid_rows_end_regex, configData);
    findAndRemoveMatches(config.grid.grid_rows_span_regex, configData);
    findAndRemoveMatches(config.grid.grid_rows_start_regex, configData);
    findAndRemoveMatches(config.grid.grid_template_rows_regex, configData);
    findAndRemoveMatches(config.grid.grid_cols_end_regex, configData);
    findAndRemoveMatches(config.grid.grid_cols_span_regex, configData);
    findAndRemoveMatches(config.grid.grid_cols_start_regex, configData);
    findAndRemoveMatches(config.grid.grid_template_columns_regex, configData);
    findAndRemoveMatches(config.grid.order_regex, configData);

    // Layout
    findAndRemoveMatches(config.layout.z_index_regex, configData);
    findAndRemoveMatches(config.layout.visibility_regex, configData);
    findAndRemoveMatches(config.layout.position_sides_regex, configData);
    findAndRemoveMatches(config.layout.position_inset_regex, configData);
    findAndRemoveMatches(config.layout.position_regex, configData);
    findAndRemoveMatches(config.layout.overscroll_behavior_regex, configData);
    findAndRemoveMatches(config.layout.overflow_regex, configData);
    findAndRemoveMatches(config.layout.object_position_regex, configData);
    findAndRemoveMatches(config.layout.object_fit_regex, configData);
    findAndRemoveMatches(config.layout.isolation_regex, configData);
    findAndRemoveMatches(config.layout.clear_regex, configData);
    findAndRemoveMatches(config.layout.floats_regex, configData);
    findAndRemoveMatches(config.layout.display_regex, configData);
    findAndRemoveMatches(config.layout.box_sizing_regex, configData);
    findAndRemoveMatches(config.layout.box_decoration_break_regex, configData);
    findAndRemoveMatches(config.layout.break_inside_regex, configData);
    findAndRemoveMatches(config.layout.break_before_regex, configData);
    findAndRemoveMatches(config.layout.break_after_regex, configData);
    findAndRemoveMatches(config.layout.columns_regex, configData);
    findAndRemoveMatches(config.layout.container_regex, configData);
    findAndRemoveMatches(config.layout.aspect_ratio_regex, configData);


    // std::cout << config.backgrounds.backgroundColorData();

    // auto sizing_search_data = config.backgrounds.search_data();
    // for(auto data : sizing_search_data){
    //     std::cout << "\n <" << data << ">";
    // }

    std::cout << configData << std::endl;
    if(output_file.is_open()){
        output_file << configData;
        output_file.close();
    }
    else{
        std::cout << "Unable to open file" << std::endl;
    }
    return 0;
}




// TEST_CASE("Accesibility") {
//     // Accesibility
//     auto matches = findAndRemoveMatches(config.accessibility.screen_readers_regex, configData);
//     // remove the first element of the vector because it is none
//     auto screen_readers = config.accessibility.screen_readers.styleClasses_;
//     removeNone(screen_readers);
//     screen_readers.push_back(StyleClass("blank", ""));
//     for(int i = 0; i < matches.size(); i++){
//         std::cout << screen_readers[screen_readers.size()-1].className_ << std::endl;
//         CHECK(matches[i] == screen_readers[i].className_);
//     }
// }

// TEST_CASE("Layout") {
//     auto matches = findAndRemoveMatches(config.layout.aspect_ratio_regex, configData);
//     // remove the first element of the vector because it is none
//     auto aspect_ratio = config.layout.aspect_ratio.styleClasses_;
//     removeNone(aspect_ratio);
//     for(int i = 0; i < matches.size()+1; i++){
//         CHECK(matches[i] == aspect_ratio[i].className_);
//     }
// }



