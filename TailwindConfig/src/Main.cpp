#include <iostream>
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

int main() {
    Config config = Config();

    // Layout
    // std::cout << config.layout.AspectRatioData() << std::endl;
    // std::cout << config.layout.ContainerData() << std::endl;
    // std::cout << config.layout.ColumnsData() << std::endl;
    // std::cout << config.layout.BreakAfterData() << std::endl;
    // std::cout << config.layout.BreakBeforeData() << std::endl;
    // std::cout << config.layout.BreakInsideData() << std::endl;
    // std::cout << config.layout.BoxDecorationBreakData() << std::endl;
    // std::cout << config.layout.BoxSizingData() << std::endl;
    // std::cout << config.layout.DisplayData() << std::endl;
    // std::cout << config.layout.FloatsData() << std::endl;
    // std::cout << config.layout.ClearData() << std::endl;
    // std::cout << config.layout.IsolationData() << std::endl;
    // std::cout << config.layout.ObjectFitData() << std::endl;
    // std::cout << config.layout.ObjectPositionData() << std::endl;
    // std::cout << config.layout.OverflowData() << std::endl;
    // std::cout << config.layout.OverscrollBehaviorData() << std::endl;
    // std::cout << config.layout.PositionData() << std::endl;
    // std::cout << config.layout.PositionSidesData() << std::endl;
    // std::cout << config.layout.VisibilityData() << std::endl;
    // std::cout << config.layout.ZIndexData() << std::endl;

    // Flexbox
    // std::cout << config.flexbox.BasisData() << std::endl;
    // std::cout << config.flexbox.DirectionData() << std::endl;
    // std::cout << config.flexbox.WrapData() << std::endl;
    // std::cout << config.flexbox.FlexData() << std::endl;
    // std::cout << config.flexbox.GrowData() << std::endl;
    // std::cout << config.flexbox.ShrinkData() << std::endl;
    // std::cout << config.flexbox.OrderData() << std::endl;
    // std::cout << config.flexbox.PlaceData() << std::endl;
    // std::cout << config.flexbox.JustifyData() << std::endl;
    // std::cout << config.flexbox.AlignData() << std::endl;

    // Grid
    // std::cout << config.grid.OrderData() << std::endl;
    // std::cout << config.grid.GridTemplateData() << std::endl;
    // std::cout << config.grid.GridColsData() << std::endl;
    // std::cout << config.grid.GridRowsData() << std::endl;
    // std::cout << config.grid.GridAutoData() << std::endl;
    // std::cout << config.grid.GapData() << std::endl;

    // Spacing
    // std::cout << config.spacing.MarginData() << std::endl;
    // std::cout << config.spacing.PaddingData() << std::endl;

    // Sizing
    // std::cout << config.sizing.WidthData() << std::endl;
    // std::cout << config.sizing.HeightData() << std::endl;
    // std::cout << config.sizing.MaxHeightData() << std::endl;
    // std::cout << config.sizing.MinWidthData() << std::endl;
    // std::cout << config.sizing.MinHeightData() << std::endl;
    // std::cout << config.sizing.MaxWidthData() << std::endl;

    // Typography
    // std::cout << config.typography.FontFamilyData() << std::endl;
    // std::cout << config.typography.FontSizeData() << std::endl;
    // std::cout << config.typography.FontSmoothingData() << std::endl;
    // std::cout << config.typography.FontStyleData() << std::endl;
    // std::cout << config.typography.FontWeightData() << std::endl;
    // std::cout << config.typography.FontVariantNumericData() << std::endl;
    // std::cout << config.typography.LetterSpacingData() << std::endl;
    // std::cout << config.typography.LineClampData() << std::endl;
    // std::cout << config.typography.LineHeightData() << std::endl;
    // std::cout << config.typography.ListStyleImageData() << std::endl;
    // std::cout << config.typography.ListStylePositionData() << std::endl;
    // std::cout << config.typography.ListStyleTypeData() << std::endl;
    // std::cout << config.typography.TextAlignData() << std::endl;
    // std::cout << config.typography.TextDecorationData() << std::endl;
    // std::cout << config.typography.TextDecorationStyleData() << std::endl;
    // std::cout << config.typography.TextDecorationThiknessData() << std::endl;
    // std::cout << config.typography.TextUnderlineOffsetData() << std::endl;
    // std::cout << config.typography.TextTransformData() << std::endl;
    // std::cout << config.typography.TextOverflowData() << std::endl;
    // std::cout << config.typography.TextIndentData() << std::endl;
    // std::cout << config.typography.VerticalAlignData() << std::endl;
    // std::cout << config.typography.WhitespaceData() << std::endl;
    // std::cout << config.typography.WordBreakData() << std::endl;
    // std::cout << config.typography.HyphensData() << std::endl;
    // std::cout << config.typography.ContentData() << std::endl;

    // backgrounds
    // std::cout << config.backgrounds.backgroundAttachmentData() << std::endl;
    // std::cout << config.backgrounds.backgroundClipData() << std::endl;
    // std::cout << config.backgrounds.backgroundColorData() << std::endl;
    // std::cout << config.backgrounds.backgroundOriginData() << std::endl;
    // std::cout << config.backgrounds.backgroundPositionData() << std::endl;
    // std::cout << config.backgrounds.backgroundRepeatData() << std::endl;
    // std::cout << config.backgrounds.backgroundSizeData() << std::endl;
    // std::cout << config.backgrounds.backgroundImageData() << std::endl;
    // std::cout << config.backgrounds.gradientStopsData() << std::endl;

    // Borders
    // std::cout << config.borders.BorderRadiusData() << std::endl;
    // std::cout << config.borders.BorderWidthData() << std::endl;
    // std::cout << config.borders.BorderStyleData() << std::endl;
    // std::cout << config.borders.DivideData() << std::endl;
    // std::cout << config.borders.OutlineData() << std::endl;
    // std::cout << config.borders.RingData() << std::endl;

    // Effects
    // std::cout << config.effects.boxShadowData() << std::endl;
    // std::cout << config.effects.boxShadowColorData() << std::endl;
    // std::cout << config.effects.opacityData() << std::endl;
    // std::cout << config.effects.mixBlendModeData() << std::endl;

    // Filters
    // std::cout << config.filters.BlurData() << std::endl;
    // std::cout << config.filters.BrightnessData() << std::endl;
    // std::cout << config.filters.ContrastData() << std::endl;
    // std::cout << config.filters.DropShadowData() << std::endl;
    // std::cout << config.filters.GrayscaleData() << std::endl;
    // std::cout << config.filters.HueRotateData() << std::endl;
    // std::cout << config.filters.InvertData() << std::endl;
    // std::cout << config.filters.SaturateData() << std::endl;
    // std::cout << config.filters.SepiaData() << std::endl;
    // std::cout << config.filters.BackdropBlurData() << std::endl;
    // std::cout << config.filters.BackdropBrightnessData() << std::endl;
    // std::cout << config.filters.BackdropContrastData() << std::endl;
    // std::cout << config.filters.BackdropGrayscaleData() << std::endl;
    // std::cout << config.filters.BackdropHueRotateData() << std::endl;
    // std::cout << config.filters.BackdropInvertData() << std::endl;
    // std::cout << config.filters.BackdropOpacityData() << std::endl;
    // std::cout << config.filters.BackdropSaturateData() << std::endl;
    // std::cout << config.filters.BackdropSepiaData() << std::endl;

    // Tables
    // std::cout << config.tables.BorderCollapseData() << std::endl;
    // std::cout << config.tables.TableLayoutData() << std::endl;
    // std::cout << config.tables.CaptionSideData() << std::endl;
    // std::cout << config.tables.BorderSpacingData() << std::endl;

    // Transitions and Animations
    // std::cout << config.transitions_and_animation.TransitionPropertyData() << std::endl;
    // std::cout << config.transitions_and_animation.TransitionDurationData() << std::endl;
    // std::cout << config.transitions_and_animation.TransitionTimingFunctionData() << std::endl;
    // std::cout << config.transitions_and_animation.TransitionDelayData() << std::endl;
    // std::cout << config.transitions_and_animation.AnimationData() << std::endl;

    // Transform
    std::cout << config.transforms.scaleData() << std::endl;
    std::cout << config.transforms.rotateData() << std::endl;
    std::cout << config.transforms.translateData() << std::endl;
    std::cout << config.transforms.skewData() << std::endl;
    std::cout << config.transforms.transformOriginData() << std::endl;

    // Interactivity
    // std::cout << config.interactivity.appearanceData() << std::endl;
    // std::cout << config.interactivity.cursorData() << std::endl;
    // std::cout << config.interactivity.pointerEventsData() << std::endl;
    // std::cout << config.interactivity.resizeData() << std::endl;
    // std::cout << config.interactivity.scrollBehaviorData() << std::endl;
    // std::cout << config.interactivity.scrollMarginData() << std::endl;
    // std::cout << config.interactivity.scrollPaddingData() << std::endl;
    // std::cout << config.interactivity.scrollSnapAlignData() << std::endl;
    // std::cout << config.interactivity.scrollSnapStopData() << std::endl;
    // std::cout << config.interactivity.scrollSnapTypeData() << std::endl;
    // std::cout << config.interactivity.touchActionData() << std::endl;
    // std::cout << config.interactivity.userSelectData() << std::endl;
    // std::cout << config.interactivity.willChangeData() << std::endl;

    // Svg
    // std::cout << config.svg.strokeWidthData() << std::endl;

    // Accessibility
    // std::cout << config.accessibility.screenReadersData() << std::endl;
    
    
return 0;
}
