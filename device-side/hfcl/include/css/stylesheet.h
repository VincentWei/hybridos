/*
** HFCL - HybridOS Foundation Class Library
**
** Copyright (C) 2018 Beijing FMSoft Technologies Co., Ltd.
**
** This file is part of HFCL.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef HFCL_CSS_STYLESHEET_H_
#define HFCL_CSS_STYLESHEET_H_

#include "../common/common.h"
#include "../common/stlalternative.h"

#define MAKE_PROPERTY_VALUE(id, type, keyword)  \
    ((DWORD32)(                                 \
        ((DWORD32)((keyword) & 0xFFFF)) |       \
        ((DWORD32)((type) & 0x000F) << 16) |    \
        ((DWORD32)((id) & 0x0FFF) << 20)        \
    ))

#define PROPERTY_VALUE2ID(value)        (((value) & 0xFFF00000) >> 20)
#define PROPERTY_VALUE2TYPE(value)      (((value) & 0x000F0000) >> 16)
#define PROPERTY_VALUE2KEYWORD(value)   ((value) & 0x0000FFFF)

namespace hfcl {

typedef enum _PropertyIds {
    PID_BACKGROUND_ATTACHMENT,
    PID_BACKGROUND_COLOR,
    PID_BACKGROUND_IMAGE,
    PID_BACKGROUND_POSITION_X,
    PID_BACKGROUND_POSITION_Y,
    PID_BACKGROUDN_REPEAT,
    PID_BORDER_TOP_COLOR,
    PID_BORDER_TOP_STYLE,
    PID_BORDER_TOP_WIDTH,
    PID_BORDER_RIGHT_COLOR,
    PID_BORDER_RIGHT_STYLE,
    PID_BORDER_RIGHT_WIDTH,
    PID_BORDER_BOTTOM_COLOR,
    PID_BORDER_BOTTOM_STYLE,
    PID_BORDER_BOTTOM_WIDTH,
    PID_BORDER_LEFT_COLOR,
    PID_BORDER_LEFT_STYLE,
    PID_BORDER_LEFT_WIDTH,
    PID_BORDER_COLLAPSE,
    PID_BORDER_SPACEING,
    PID_BOTTOM,
    PID_CLEAR,
    PID_CLIP,
    PID_CAPTION_SIDE,
    PID_COLOR,
    PID_CONTENT,
    PID_COUNTER_INCREMENT,
    PID_COUNTER_RESET,
    PID_CURSOR,
    PID_DIRECTION,
    PID_DISPLAY,

    PID_POSITION,

    PID_HEIGHT,

    PID_EMPTY_CELLS,

    PID_FLOAT,

    PID_FONT_FAMILY,
    PID_FONT_SIZE,
    PID_FONT_STYLE,
    PID_FONT_VARIANT,
    PID_FONT_WEIGHT,
    PID_FONT,

    PID_LEFT,

    PID_LETTER_SPACING,

    PID_LINE_HEIGHT,

    PID_LIST_STYLE_IMAGE,
    PID_LIST_STYLE_POSITION,
    PID_LIST_STYLE_TYPE,

    PID_MARGIN_LEFT,
    PID_MARGIN_TOP,
    PID_MARGIN_RIGHT,
    PID_MARGIN_BOTTOM,

    PID_MAX_HEIGHT,
    PID_MAX_WIDTH,

    PID_MIN_HEIGHT,
    PID_MIN_WIDHT,

    PID_ORPHANS,

    PID_OUTLINE_COLOR,
    PID_OUTLINE_STYLE,
    PID_OUTLINE_WIDTH,

    PID_OVERFLOW,

    PID_PADDING_LEFT,
    PID_PADDING_TOP,
    PID_PADDING_RIGHT,
    PID_PADDING_BOTTOM,

    PID_PAGE_BREAK_AFTER,
    PID_PAGE_BREAK_BEFORE,
    PID_PAGE_BREAK_INSIDE,

    PID_POSITION,

    PID_QUOTES,

    PID_RIGHT,

    PID_TABLE_LAYOUT,

    PID_TEXT_ALIGN,

    PID_TEXT_DECORATION,

    PID_TEXT_INDENT,

    PID_TEXT_TRANSFORM,

    PID_TOP,

    PID_UNICODE_BIDI,

    PID_VERTICAL_ALIGN,

    PID_VISIBILITY,

    PID_WHITE_SPACE,

    PID_WINDOWS,

    PID_WIDTH,

    PID_WORD_SPACING,

    PID_Z_INDEX,
} PropertyIds;

// The property value types
typedef enum _PropertyValueTypes {
    PVT_KEYWORD,
    PVT_INTEGER,
    PVT_NUMBER,
    PVT_PERCENTAGE,
    PVT_LENGTH,
    PVT_RGBA,
    PVT_URI,
    PVT_STRING,
} PropertyValueTypes;

// The property value keywords
typedef enum _PropertyValueKeywords {
    PVK_USE_DATA = 0,

    PVK_INITIAL,
    PVK_INHERIT,
    PVK_NONE,
    PVK_AUTO,
    PVK_TRANSPARENT,

    PVK_SCROLL,
    PVK_FIXED,

    PVK_LEFT,
    PVK_CENTER,
    PVK_RIGHT,
    PVK_TOP,
    PVK_MIDDLE,
    PVK_BOTTOM,

    PVK_REPEAT,
    PVK_REPEAT_X,
    PVK_REPEAT_Y,
    PVK_NO_REPEAT,

    PVK_BOTH,

    PVK_NORMAL,
    PVK_OPEN_QUOTE,
    PVK_CLOSE_QUOTE,
    PVK_OPEN_QUOTE,
    PVK_NO_CLOSE_QUOTE,

    PVK_CROSSHAIR,
    PVK_DEFAULT,
    PVK_POINTER,
    PVK_MOVE,
    PVK_E_RESIZE,
    PVK_NE_RESIZE,
    PVK_NW_RESIZE,
    PVK_N_RESIZE,
    PVK_SE_RESIZE,
    PVK_SW_RESIZE,
    PVK_S_RESIZE,
    PVK_W_RESIZE,
    PVK_TEXT,
    PVK_WAIT,
    PVK_HELP,
    PVK_PROGRESS,

    PVK_LTR,
    PVK_RTL,

    PVK_INLINE,
    PVK_BLOCK,
    PVK_LIST_ITEM,
    PVK_INLINE_BLOCK,
    PVK_TABLE,
    PVK_INLINE_TABLE,
    PVK_TABLE_ROW_GROUP,
    PVK_TABLE_HEADER_GROUP,
    PVK_TABLE_FOOTER_GROUP,
    PVK_TABLE_ROW,
    PVK_TABLE_COLUMN_GROUP,
    PVK_TABLE_COLUMN,
    PVK_TABLE_CELL,
    PVK_TABLE_CAPTION,

    PVK_SHOW,
    PVK_HIDE,

    PVK_XX_SMALL,
    PVK_X_SMALL,
    PVK_SMALL,
    PVK_MEDIUM,
    PVK_LARGE,
    PVK_X_LARGE,
    PVK_XX_LARGE,

    PVK_LARGER,
    PVK_SMALLER,

    PVK_NORMAL,
    PVK_ITALIC,
    PVK_OBLIQUE,

    PVK_SMALL_CAPS,

    PVK_BOLD,
    PVK_BOLDER,
    PVK_LIGHTER,
    PVK_100,
    PVK_200,
    PVK_300,
    PVK_400,
    PVK_500,
    PVK_600,
    PVK_700,
    PVK_800,
    PVK_900,

    PVK_CAPTION,
    PVK_ICON,
    PVK_MENU,
    PVK_MESSAGE_BOX,
    PVK_SMALL_CAPTION,
    PVK_STATUS_BAR,

    PVK_INSIDE,
    PVK_OUTSIDE,

    PVK_DISC,
    PVK_CIRCLE,
    PVK_SQUARE,
    PVK_DECIMAL,
    PVK_DECIMAL_LEADING_ZERO,
    PVK_LOWER_ROMAN,
    PVK_UPPER_ROMAN,
    PVK_LOWER_GREEK,
    PVK_LOWER_LATIN,
    PVK_UPPER_LATIN,
    PVK_ARMENIAN,
    PVK_GEORGIAN,
    PVK_LOWER_ALPHA,
    PVK_UPPER_ALPHA,

    PVK_HIDDEN,
    PVK_DOTTED,
    PVK_DASHED,
    PVK_SOLID,
    PVK_DOUBLE,
    PVK_GROOVE,
    PVK_RIDGE,
    PVK_INSET,
    PVK_OUTSET,

    PVK_THIN,
    PVK_MEDIUM,
    PVK_THICK,

    PVK_VISIBLE,
    PVK_HIDDEN,
    PVK_SCROLL,

    PVK_ALWAYS,
    PVK_AVOID,

    PVK_STATIC,
    PVK_RELATIVE,
    PVK_ABSOLUTE,
    PVK_FIXED,

    PVK_JUSTIFY,

    PVK_UNDERLINE,
    PVK_OVERLINE,
    PVK_LINE_THROUGH,
    PVK_BLINK,

    PVK_CAPITALIZE,
    PVK_UPPERCASE,
    PVK_LOWERCASE,

    PVK_NORMAL,
    PVK_EMBED,
    PVK_BIDI_OVERRIDE,

    PVK_BASELINE,
    PVK_SUB,
    PVK_SUPER,
    PVK_TOP,
    PVK_TEXT_TOP,
    PVK_MIDDLE,
    PVK_BOTTOM,
    PVK_TEXT_BOTTOM,

    PVK_VISIBLE,
    PVK_HIDDEN,
    PVK_COLLAPSE,

    PVK_PRE,
    PVK_NOWRAP,
    PVK_PRE_WRAP,
    PVK_PRE_LINE,
} PropertyValueKeywords;

// Property values
// color (COLOR)
#define PV_COLOR_TRANSPARENT    \
    MAKE_PROPERTY_VALUE(PID_COLOR, PVT_KEYWORD, PVK_TRANSPARENT)
#define PV_COLOR_RGBA           \
    MAKE_PROPERTY_VALUE(PID_COLOR, PVT_RGBA, PVK_USE_DATA)

// background-attachment (BACKGROUND_ATTACHMENT)
#define PV_BACKGROUND_ATTACHMENT_SCROLL     \
    MAKE_PROPERTY_VALUE(PID_BACKGROUND_ATTACHMENT, PVT_KEYWORD, PVK_SCROLL)
#define PV_BACKGROUND_ATTACHMENT_FIXED      \
    MAKE_PROPERTY_VALUE(PID_BACKGROUND_ATTACHMENT, PVT_KEYWORD, PVK_FIXED)
#define PV_BACKGROUND_ATTACHMENT_INHERIT    \
    MAKE_PROPERTY_VALUE(PID_BACKGROUND_ATTACHMENT, PVT_KEYWORD, PVK_INHERIT)

// background-color (BACKGROUND_COLOR)
#define PV_BACKGROUND_COLOR_COLOR       \
    MAKE_PROPERTY_VALUE(PID_BACKGROUND_COLOR, PVT_RGBA, PVK_USE_DATA)
#define PV_BACKGROUND_COLOR_TRANSPARENT \
    MAKE_PROPERTY_VALUE(PID_BACKGROUND_COLOR, PVT_KEYWORD, PVK_TRANSPARENT)
#define PV_BACKGROUND_COLOR_INHERIT     \
    MAKE_PROPERTY_VALUE(PID_BACKGROUND_COLOR, PVT_KEYWORD, PVK_INHERIT)

// background-image (BACKGROUND_IMAGE)
#define PV_BACKGROUND_IMAGE_URI     \
    MAKE_PROPERTY_VALUE(PID_BACKGROUND_IMAGE, PVT_URI, PVK_USE_DATA)
#define PV_BACKGROUND_IMAGE_NONE    \
    MAKE_PROPERTY_VALUE(PID_BACKGROUND_IMAGE, PVT_KEYWORD, PVK_NONE)
#define PV_BACKGROUND_IMAGE_INHERIT \
    MAKE_PROPERTY_VALUE(PID_BACKGROUND_IMAGE, PVT_KEYWORD, PVK_INHERIT)

// background-position (BACKGROUND_POSITION)
#define PV_BACKGROUND_POSITION_PERCENTAGE   \
    MAKE_PROPERTY_VALUE(PID_BACKGROUND_POSITION, PVT_PERCENTAGE, PVK_USE_DATA)
#define PV_BACKGROUND_POSITION_LENGTH       \
    MAKE_PROPERTY_VALUE(PID_BACKGROUND_POSITION, PVT_LENGTH, PVK_USE_DATA)
#define PV_BACKGROUND_POSITION_LEFT         \
    MAKE_PROPERTY_VALUE(PID_BACKGROUND_POSITION, PVT_KEYWORD, PVK_LEFT)
#define PV_BACKGROUND_POSITION_CENTER       \
    MAKE_PROPERTY_VALUE(PID_BACKGROUND_POSITION, PVT_KEYWORD, PVK_CENTER)
#define PV_BACKGROUND_POSITION_RIGHT        \
    MAKE_PROPERTY_VALUE(PID_BACKGROUND_POSITION, PVT_KEYWORD, PVK_RIGHT)

// background-repeat (BACKGROUND_REPEAT)
#define PV_BACKGROUND_REPEAT_REPEAT     \
    MAKE_PROPERTY_VALUE(PID_BACKGROUND_REPEAT_INHERIT, PVT_KEYWORD, PVK_REPEAT)
#define PV_BACKGROUND_REPEAT_REPEAT_X   \
    MAKE_PROPERTY_VALUE(PID_BACKGROUND_REPEAT_INHERIT, PVT_KEYWORD, PVK_REPEAT_X)
#define PV_BACKGROUND_REPEAT_REPEAT_Y   \
    MAKE_PROPERTY_VALUE(PID_BACKGROUND_REPEAT_INHERIT, PVT_KEYWORD, PVK_REPEAT_Y)
#define PV_BACKGROUND_REPEAT_NO_REPEAT  \
    MAKE_PROPERTY_VALUE(PID_BACKGROUND_REPEAT_INHERIT, PVT_KEYWORD, PVK_NO_REPEAT)
#define PV_BACKGROUND_REPEAT_INHERIT    \
    MAKE_PROPERTY_VALUE(PID_BACKGROUND_REPEAT_INHERIT, PVT_KEYWORD, PVK_INHERIT)

// border-collapse (BORDER_COLLAPSE)
#define PV_BORDER_COLLAPSE_COLLAPSE \
    MAKE_PROPERTY_VALUE(PID_BORDER_COLLAPSE, PVT_KEYWORD, PVK_COLLAPSE)
#define PV_BORDER_COLLAPSE_SEPARATE \
    MAKE_PROPERTY_VALUE(PID_BORDER_COLLAPSE, PVT_KEYWORD, PVK_SEPARATE)
#define PV_BORDER_COLLAPSE_INHERIT  \
    MAKE_PROPERTY_VALUE(PID_BORDER_COLLAPSE, PVT_KEYWORD, PVK_INHERIT)

// border-left-color (BORDER_LEFT_COLOR)
#define PV_BORDER_LEFT_COLOR_COLOR  \
    MAKE_PROPERTY_VALUE(PID_BORDER_LEFT_COLOR, PVT_RGBA, PVK_USE_DATA)
#define PV_BORDER_LEFT_COLOR_TRANSPARENT    \
    MAKE_PROPERTY_VALUE(PID_BORDER_TOP_TRANSPARENT, PVT_KEYWORD, PVK_TRANSPARENT)
#define PV_BORDER_LEFT_COLOR_INHERIT    \
    MAKE_PROPERTY_VALUE(PID_BORDER_TOP_INHERIT, PVT_KEYWORD, PVK_INHERIT)

// border-top-color (BORDER_TOP_COLOR)
#define PV_BORDER_TOP_COLOR_COLOR  \
    MAKE_PROPERTY_VALUE(PID_BORDER_TOP_COLOR, PVT_RGBA, PVK_USE_DATA)
#define PV_BORDER_TOP_COLOR_TRANSPARENT    \
    MAKE_PROPERTY_VALUE(PID_BORDER_TOP_TRANSPARENT, PVT_KEYWORD, PVK_TRANSPARENT)
#define PV_BORDER_TOP_COLOR_INHERIT    \
    MAKE_PROPERTY_VALUE(PID_BORDER_TOP_INHERIT, PVT_KEYWORD, PVK_INHERIT)

// border-right-color (BORDER_RIGHT_COLOR)
#define PV_BORDER_RIGHT_COLOR_COLOR  \
    MAKE_PROPERTY_VALUE(PID_BORDER_RIGHT_COLOR, PVT_RGBA, PVK_USE_DATA)
#define PV_BORDER_RIGHT_COLOR_TRANSPARENT    \
    MAKE_PROPERTY_VALUE(PID_BORDER_RIGHT_TRANSPARENT, PVT_KEYWORD, PVK_TRANSPARENT)
#define PV_BORDER_RIGHT_COLOR_INHERIT    \
    MAKE_PROPERTY_VALUE(PID_BORDER_RIGHT_INHERIT, PVT_KEYWORD, PVK_INHERIT)

// border-bottom-color (BORDER_BOTTOM_COLOR)
#define PV_BORDER_BOTTOM_COLOR_COLOR  \
    MAKE_PROPERTY_VALUE(PID_BORDER_BOTTOM_COLOR, PVT_RGBA, PVK_USE_DATA)
#define PV_BORDER_BOTTOM_COLOR_TRANSPARENT    \
    MAKE_PROPERTY_VALUE(PID_BORDER_BOTTOM_TRANSPARENT, PVT_KEYWORD, PVK_TRANSPARENT)
#define PV_BORDER_BOTTOM_COLOR_INHERIT    \
    MAKE_PROPERTY_VALUE(PID_BORDER_BOTTOM_INHERIT, PVT_KEYWORD, PVK_INHERIT)

// border-top-style (BORDER_TOP_STYLE)
#define PV_BORDER_TOP_STYLE_NONE    \
    MAKE_PROPERTY_VALUE(PID_BORDER_TOP_STYLE, PVT_KEYWORD, PVK_NONE)
#define PV_BORDER_TOP_STYLE_HIDDEN  \
    MAKE_PROPERTY_VALUE(PID_BORDER_TOP_STYLE, PVT_KEYWORD, PVK_HIDDEN)
#define PV_BORDER_TOP_STYLE_DOTTED  \
    MAKE_PROPERTY_VALUE(PID_BORDER_TOP_STYLE, PVT_KEYWORD, PVK_DOTTED)
#define PV_BORDER_TOP_STYLE_DASHED  \
    MAKE_PROPERTY_VALUE(PID_BORDER_TOP_STYLE, PVT_KEYWORD, PVK_DASHED)
#define PV_BORDER_TOP_STYLE_SOLID   \
    MAKE_PROPERTY_VALUE(PID_BORDER_TOP_STYLE, PVT_KEYWORD, PVK_SOLID)
#define PV_BORDER_TOP_STYLE_DOUBLE  \
    MAKE_PROPERTY_VALUE(PID_BORDER_TOP_STYLE, PVT_KEYWORD, PVK_DOUBLE)
#define PV_BORDER_TOP_STYLE_GROOVE  \
    MAKE_PROPERTY_VALUE(PID_BORDER_TOP_STYLE, PVT_KEYWORD, PVK_GROOVE)
#define PV_BORDER_TOP_STYLE_RIDGE   \
    MAKE_PROPERTY_VALUE(PID_BORDER_TOP_STYLE, PVT_KEYWORD, PVK_RIDGE)
#define PV_BORDER_TOP_STYLE_INSET   \
    MAKE_PROPERTY_VALUE(PID_BORDER_TOP_STYLE, PVT_KEYWORD, PVK_INSET)
#define PV_BORDER_TOP_STYLE_OUTSET  \
    MAKE_PROPERTY_VALUE(PID_BORDER_TOP_STYLE, PVT_KEYWORD, PVK_OUTSET)
#define PV_BORDER_TOP_STYLE_INHERIT \
    MAKE_PROPERTY_VALUE(PID_BORDER_TOP_STYLE, PVT_KEYWORD, PVK_INHERIT)

// border-top-width (BORDER_TOP_WIDTH)

    PID_BORDER_TOP_WIDTH,
    PID_BORDER_RIGHT_COLOR,
    PID_BORDER_RIGHT_STYLE,
    PID_BORDER_RIGHT_WIDTH,
    PID_BORDER_BOTTOM_COLOR,
    PID_BORDER_BOTTOM_STYLE,
    PID_BORDER_BOTTOM_WIDTH,
    PID_BORDER_LEFT_COLOR,
    PID_BORDER_LEFT_STYLE,
    PID_BORDER_LEFT_WIDTH,
    PID_BORDER_COLLAPSE,
    PID_BORDER_SPACEING,
    PID_BOTTOM,
    PV_ALIGN_LEFT
    PV_ALIGN_CENTER
    PV_ALIGN_RIGHT

    PV_VERTICAL_ALIGN_TOP,
    PV_VERTICAL_ALIGN_MIDDLE,
    PV_VERTICAL_ALIGN_BOTTOM,

    PV_CLEAR_INHERIT,
    PV_CLEAR_NONE,
    PV_CLEAR_LEFT,
    PV_CLEAR_RIGHT,
    PV_CLEAR_BOTH,

    PV_CLIP_INHERIT,
    PV_CLIP_AUTO,

    PV_CONTENT_NORMAL,
    PV_CONTENT_OPEN_QUOTE,
    PV_CONTENT_CLOSE_QUOTE,
    PV_CONTENT_NO_OPEN_QUOTE,
    PV_CONTENT_NO_CLOSE_QUOTE,

    PV_CURSOR_AUTO,
    PV_CURSOR_CROSSHAIR,
    PV_CURSOR_DEFAULT,
    PV_CURSOR_POINTER,
    PV_CURSOR_MOVE,
    PV_CURSOR_E_RESIZE,
    PV_CURSOR_NE_RESIZE,
    PV_CURSOR_NW_RESIZE,
    PV_CURSOR_N_RESIZE,
    PV_CURSOR_SE_RESIZE,
    PV_CURSOR_SW_RESIZE,
    PV_CURSOR_S_RESIZE,
    PV_CURSOR_W_RESIZE,
    PV_CURSOR_TEXT,
    PV_CURSOR_WAIT,
    PV_CURSOR_HELP,
    PV_CURSOR_PROGRESS,
    PV_CURSOR_INHERIT,
    PV_CURSOR_URI,

    PV_DIRECTION_LTR,
    PV_DIRECTION_RTL,
    PV_DIRECTION_INHERIT,

    PV_DISPLAY_INLINE,
    PV_DISPLAY_BLOCK,
    PV_DISPLAY_LIST_ITEM,
    PV_DISPLAY_INLINE_BLOCK,
    PV_DISPLAY_TABLE,
    PV_DISPLAY_INLINE_TABLE,
    PV_DISPLAY_TABLE_ROW_GROUP,
    PV_DISPLAY_TABLE_HEADER_GROUP,
    PV_DISPLAY_TABLE_FOOTER_GROUP,
    PV_DISPLAY_TABLE_ROW,
    PV_DISPLAY_TABLE_COLUMN_GROUP,
    PV_DISPLAY_TABLE_COLUMN,
    PV_DISPLAY_TABLE_CELL,
    PV_DISPLAY_TABLE_CAPTION,
    PV_DISPLAY_NONE,
    PV_DISPLAY_INHERIT,

    PV_EMPTY_CELLS_SHOW,
    PV_EMPTY_CELLS_HIDE,
    PV_EMPTY_CELLS_INHERIT,

    PV_FLOAT_LEFT,
    PV_FLOAT_RIGHT,
    PV_FLOAT_NONE,
    PV_FLOAT_INHERIT,

    PV_FONT_FAMILY_NAME,
    PV_FONT_FAMILY_INHERIT,

    PV_FONT_SIZE_ABSOLUTE_SIZE,
    PV_FONT_SIZE_RELATIVE_SIZE,
    PV_FONT_SIZE_LENGTH,
    PV_FONT_SIZE_PERCENTAGE,
    PV_FONT_SIZE_INHERIT,

    PV_FONT_STYLE_NORMAL,
    PV_FONT_STYLE_ITALIC,
    PV_FONT_STYLE_OBLIQUE,
    PV_FONT_STYLE_INHERIT,

    PV_FONT_VARIANT_NORMAL,
    PV_FONT_VARIANT_SMALL_CAPS,
    PV_FONT_VARIANT_INHERIT,

    PV_FONT_WEIGHT_NORMAL,
    PV_FONT_WEIGHT_BOLD,
    PV_FONT_WEIGHT_BOLDER,
    PV_FONT_WEIGHT_LIGHTER,
    PV_FONT_WEIGHT_100,
    PV_FONT_WEIGHT_200,
    PV_FONT_WEIGHT_300,
    PV_FONT_WEIGHT_400,
    PV_FONT_WEIGHT_500,
    PV_FONT_WEIGHT_600,
    PV_FONT_WEIGHT_700,
    PV_FONT_WEIGHT_800,
    PV_FONT_WEIGHT_900,
    PV_FONT_WEIGHT_INHERIT,

    PV_FONT_SYSTEM_FONT_CAPTION,
    PV_FONT_SYSTEM_FONT_ICON,
    PV_FONT_SYSTEM_FONT_MENU,
    PV_FONT_SYSTEM_FONT_MESSAGE_BOX,
    PV_FONT_SYSTEM_FONT_SMALL_CAPTION,
    PV_FONT_SYSTEM_FONT_STATUS_BAR,

    PV_HEIGHT_LENGTH        = PV_METRICS_LENGTH,
    PV_HEIGHT_PERCENTAGE    = PV_GENERIC_PERCENTAGE,
    PV_HEIGHT_AUTO          = PV_GENERIC_AUTO,
    PV_HEIGHT_INHERIT       = PV_GENERIC_INHERIT,

    PV_LEFT_LENGTH,
    PV_LEFT_PERCENTAGE,
    PV_LEFT_AUTO,
    PV_LEFT_INHERIT,

    PV_LETTER_SPACING_NORMAL,
    PV_LETTER_SPACING_LENGTH,
    PV_LETTER_SPACING_INHERIT,

    PV_LINE_HEIGHT_NORMAL,
    PV_LINE_HEIGHT_NUMBER,
    PV_LINE_HEIGHT_LENGTH,
    PV_LINE_HEIGHT_PERCENTAGE,
    PV_LINE_HEIGHT_INHERIT,

    PV_LIST_STYLE_IMAGE_URI,
    PV_LIST_STYLE_IMAGE_NONE,
    PV_LIST_STYLE_IMAGE_INHERIT,

    PV_LIST_STYLE_POSITION_INSIDE,
    PV_LIST_STYLE_POSITION_OUTSIDE,
    PV_LIST_STYLE_POSITION_INHERIT,

    PV_LIST_STYLE_TYPE_DISC,
    PV_LIST_STYLE_TYPE_CIRCLE,
    PV_LIST_STYLE_TYPE_SQUARE,
    PV_LIST_STYLE_TYPE_DECIMAL,
    PV_LIST_STYLE_TYPE_DECIMAL_LEADING_ZERO,
    PV_LIST_STYLE_TYPE_LOWER_ROMAN,
    PV_LIST_STYLE_TYPE_UPPER_ROMAN,
    PV_LIST_STYLE_TYPE_LOWER_GREEK,
    PV_LIST_STYLE_TYPE_LOWER_LATIN,
    PV_LIST_STYLE_TYPE_UPPER_LATIN,
    PV_LIST_STYLE_TYPE_ARMENIAN,
    PV_LIST_STYLE_TYPE_GEORGIAN,
    PV_LIST_STYLE_TYPE_LOWER_ALPHA,
    PV_LIST_STYLE_TYPE_UPPER_ALPHA,
    PV_LIST_STYLE_TYPE_NONE,
    PV_LIST_STYLE_TYPE_INHERIT,

    PV_MARGIN_AUTO,
    PV_MARGIN_LENGTH,
    PV_MARGIN_PERCENTAGE,
    PV_MARGIN_INHERIT,

    PV_MARGIN_LEFT_AUTO,
    PV_MARGIN_LEFT_LENGTH,
    PV_MARGIN_LEFT_PERCENTAGE,
    PV_MARGIN_LEFT_INHERIT,

    PV_MARGIN_TOP_AUTO,
    PV_MARGIN_TOP_LENGTH,
    PV_MARGIN_TOP_PERCENTAGE,
    PV_MARGIN_TOP_INHERIT,

    PV_MARGIN_RIGHT_AUTO,
    PV_MARGIN_RIGHT_LENGTH,
    PV_MARGIN_RIGHT_PERCENTAGE,
    PV_MARGIN_RIGHT_INHERIT,

    PV_MARGIN_BOTTOM_AUTO,
    PV_MARGIN_BOTTOM_LENGTH,
    PV_MARGIN_BOTTOM_PERCENTAGE,
    PV_MARGIN_BOTTOM_INHERIT,

    PV_MAX_HEIGHT_NONE,
    PV_MAX_HEIGHT_LENGTH,
    PV_MAX_HEIGHT_PERCENTAGE,
    PV_MAX_HEIGHT_INHERIT,

    PV_MAX_WIDTH_NONE,
    PV_MAX_WIDTH_LENGTH,
    PV_MAX_WIDTH_PERCENTAGE,
    PV_MAX_WIDTH_INHERIT,

    PV_MIN_HEIGHT_LENGTH,
    PV_MIN_HEIGHT_PERCENTAGE,
    PV_MIN_HEIGHT_INHERIT,

    PV_MIN_WIDHT_LENGTH,
    PV_MIN_WIDHT_PERCENTAGE,
    PV_MIN_WIDHT_INHERIT,

    PV_ORPHANS_INTEGER,
    PV_ORPHANS_INHERIT,

    PV_OUTLINE_COLOR_COLOR,
    PV_OUTLINE_COLOR_INVERT,
    PV_OUTLINE_COLOR_INHERIT,

    PV_OUTLINE_STYLE_NONE,
    PV_OUTLINE_STYLE_HIDDEN,
    PV_OUTLINE_STYLE_DOTTED,
    PV_OUTLINE_STYLE_DASHED,
    PV_OUTLINE_STYLE_SOLID,
    PV_OUTLINE_STYLE_DOUBLE,
    PV_OUTLINE_STYLE_GROOVE,
    PV_OUTLINE_STYLE_RIDGE,
    PV_OUTLINE_STYLE_INSET,
    PV_OUTLINE_STYLE_OUTSET,
    PV_OUTLINE_STYLE_INHERIT,

    PV_OUTLINE_WIDTH_THIN,
    PV_OUTLINE_WIDTH_MEDIUM,
    PV_OUTLINE_WIDTH_THICK,
    PV_OUTLINE_WIDTH_LENGTH,
    PV_OUTLINE_WIDTH_INHERIT,

    PV_OVERFLOW_VISIBLE,
    PV_OVERFLOW_HIDDEN,
    PV_OVERFLOW_SCROLL,
    PV_OVERFLOW_AUTO,
    PV_OVERFLOW_INHERIT,

    PV_PADDING_LENGTH,
    PV_PADDING_PERCENTAGE,
    PV_PADDING_INHERIT,

    PV_PADDING_LEFT_LENGTH,
    PV_PADDING_LEFT_PERCENTAGE,
    PV_PADDING_LEFT_INHERIT,

    PV_PADDING_TOP_LENGTH,
    PV_PADDING_TOP_PERCENTAGE,
    PV_PADDING_TOP_INHERIT,

    PV_PADDING_RIGHT_LENGTH,
    PV_PADDING_RIGHT_PERCENTAGE,
    PV_PADDING_RIGHT_INHERIT,

    PV_PADDING_BOTTOM_LENGTH,
    PV_PADDING_BOTTOM_PERCENTAGE,
    PV_PADDING_BOTTOM_INHERIT,

    PV_PAGE_BREAK_AFTER_AUTO,
    PV_PAGE_BREAK_AFTER_ALWAYS,
    PV_PAGE_BREAK_AFTER_AVOID,
    PV_PAGE_BREAK_AFTER_LEFT,
    PV_PAGE_BREAK_AFTER_RIGHT,
    PV_PAGE_BREAK_AFTER_INHERIT,

    PV_PAGE_BREAK_BEFORE_AUTO,
    PV_PAGE_BREAK_BEFORE_ALWAYS,
    PV_PAGE_BREAK_BEFORE_AVOID,
    PV_PAGE_BREAK_BEFORE_LEFT,
    PV_PAGE_BREAK_BEFORE_RIGHT,
    PV_PAGE_BREAK_BEFORE_INHERIT,

    PV_PAGE_BREAK_INSIDE_AVOID,
    PV_PAGE_BREAK_INSIDE_AUTO,
    PV_PAGE_BREAK_INSIDE_INHERIT,

    PV_POSITION_STATIC,
    PV_POSITION_RELATIVE,
    PV_POSITION_ABSOLUTE,
    PV_POSITION_FIXED,
    PV_POSITION_INHERIT     = PV_GENERIC_INHERIT,

    PV_QUOTES_STRING        = PV_GENERIC_STRING,
    PV_QUOTES_NONE          = PV_GENERIC_NONE,
    PV_QUOTES_INHERIT       = PV_GENERIC_INHERIT,

    PV_RIGHT_LENGTH         = PV_METRICS_LENGTH,
    PV_RIGHT_PERCENTAGE     = PV_GENERIC_PERCENTAGE,
    PV_RIGHT_AUTO           = PV_GENERIC_AUTO,
    PV_RIGHT_INHERIT        = PV_GENERIC_INHERIT,

    PV_TABLE_LAYOUT_AUTO,
    PV_TABLE_LAYOUT_FIXED,
    PV_TABLE_LAYOUT_INHERIT,

    PV_TEXT_ALIGN_LEFT,
    PV_TEXT_ALIGN_RIGHT,
    PV_TEXT_ALIGN_CENTER,
    PV_TEXT_ALIGN_JUSTIFY,
    PV_TEXT_ALIGN_INHERIT       = PV_GENERIC_INHERIT,

    PV_TEXT_DECORATION_NONE,
    PV_TEXT_DECORATION_UNDERLINE,
    PV_TEXT_DECORATION_OVERLINE,
    PV_TEXT_DECORATION_LINE_THROUGH,
    PV_TEXT_DECORATION_BLINK,
    PV_TEXT_DECORATION_INHERIT  = PV_GENERIC_INHERIT,

    PV_TEXT_INDENT_LENGTH,
    PV_TEXT_INDENT_PERCENTAGE,
    PV_TEXT_INDENT_INHERIT,

    PV_TEXT_TRANSFORM_CAPITALIZE,
    PV_TEXT_TRANSFORM_UPPERCASE,
    PV_TEXT_TRANSFORM_LOWERCASE,
    PV_TEXT_TRANSFORM_NONE          = PV_GENERIC_NONE,
    PV_TEXT_TRANSFORM_INHERIT       = PV_GENERIC_INHERIT,

    PV_TOP_LENGTH       = PV_GENERIC_INHERIT,
    PV_TOP_PERCENTAGE   = PV_GENERIC_PERCENTAGE,
    PV_TOP_AUTO         = PV_GENERIC_AUTO,
    PV_TOP_INHERIT      = PV_GENERIC_INHERIT,

    PV_UNICODE_BIDI_NORMAL,
    PV_UNICODE_BIDI_EMBED,
    PV_UNICODE_BIDI_BIDI_OVERRIDE,
    PV_UNICODE_BIDI_INHERIT        = PV_GENERIC_INHERIT,

    PV_VERTICAL_ALIGN_BASELINE,
    PV_VERTICAL_ALIGN_SUB,
    PV_VERTICAL_ALIGN_SUPER,
    PV_VERTICAL_ALIGN_TOP,
    PV_VERTICAL_ALIGN_TEXT_TOP,
    PV_VERTICAL_ALIGN_MIDDLE,
    PV_VERTICAL_ALIGN_BOTTOM,
    PV_VERTICAL_ALIGN_TEXT_BOTTOM,
    PV_VERTICAL_ALIGN_PERCENTAGE   = PV_GENERIC_PERCENTAGE,
    PV_VERTICAL_ALIGN_LENGTH       = PV_METRICS_LENGTH,
    PV_VERTICAL_ALIGN_INHERIT      = PV_GENERIC_INHERIT,

    PV_VISIBILITY_VISIBLE,
    PV_VISIBILITY_HIDDEN,
    PV_VISIBILITY_COLLAPSE,
    PV_VISIBILITY_INHERIT   = PV_GENERIC_INHERIT,

    PV_WHITE_SPACE_NORMAL,
    PV_WHITE_SPACE_PRE,
    PV_WHITE_SPACE_NOWRAP,
    PV_WHITE_SPACE_PRE_WRAP,
    PV_WHITE_SPACE_PRE_LINE,
    PV_WHITE_SPACE_INHERIT  = PV_GENERIC_INHERIT,

    PV_WINDOWS_INTEGER      = PV_GENERIC_INTEGER,
    PV_WINDOWS_INHERIT      = PV_GENERIC_INHERIT,

    PV_WIDTH_LENGTH         = PV_METRICS_LENGTH,
    PV_WIDTH_PERCENTAGE     = PV_GENERIC_PERCENTAGE,
    PV_WIDTH_AUTO           = PV_GENERIC_AUTO,
    PV_WIDTH_INHERIT        = PV_GENERIC_INHERIT,

    PV_WORD_SPACING_NORMAL,
    PV_WORD_SPACING_LENGTH  = PV_METRICS_LENGTH,
    PV_WORD_SPACING_INHERIT = PV_GENERIC_INHERIT,

    PV_Z_INDEX_AUTO         = PV_GENERIC_AUTO,
    PV_Z_INDEX_INTEGER      = PV_GENERIC_INTEGER,
    PV_Z_INDEX_INHERIT      = PV_GENERIC_INHERIT,

class PropertyValue {
public:
    Property ();
    Property (PropertyValues value, HTData data = 0);
    ~Property () {};

    PropertyValues getValue () const { return m_value; }
    PropertyValueDataTypes getDataType () const { return m_data; }
    HTData getData () const { return m_data; }
    HTReal getDataAsNumber () const { return (HTReal)m_data; }
    HTReal getDataAsInteger () const { return (int)m_data; }
    const char* getDataAsCString () const { return (const char*)m_data; }

#if 0
    HTReal getComputed () const { return m_computed; }
    void setComputed (HTReal computed) { m_computed = computed; }

    string& getComputedString () const { return m_computed_string; }
    void setComputedString (const string& new_str) {
        m_computed_string = new_str;
    }

    HTReal getUsed () const { return m_used; }
    void setUsed (HTReal used) { m_used = used; }

    string& getUsedString () const { return m_used_str; }
    void setUsedString (const string& new_str) {
        m_used_str = new_str;
    }

    HTReal getActual () const { return m_actual; }
    void setActual (HTReal actual) { m_actual = actual; }
#endif

private:
    PropertyValues m_value;
    HTData m_data;

#if 0
    HTReal m_computed;
    HTReal m_used;
    HTReal m_actual;

    // for URI and other content
    string m_computed_string;
    string m_used_string;
    string m_actual_string;
#endif
};

class PropertyValueComputed : public PropertyValue {
}

class StyleSheet {
public:
    StyleSheet () : m_id (0) {}
    StyleSheet (int id) : m_id (id) {}
    ~StyleSheet () {}

    bool setDisplay (PropertyValues value) {
        return setProperty (PID_DISPLAY, value);
    }

    bool setPosition (PropertyValues value) {
        return setProperty (PID_POSITION, value);
    }

    bool setMarginLeft (PropertyValues value, HTReal addData = 0.0f) {
        return setProperty (PID_MARGIN_LEFT, value, (HTData)addData);
    }

    bool setMarginTop (PropertyValues value, HTReal addData = 0.0f) {
        return setProperty (PID_MARGIN_TOP, value, (HTData)addData);
    }

    bool setMarginRight (PropertyValues value, HTReal addData = 0.0f) {
        return setProperty (PID_MARGIN_RIGHT, value, (HTData)addData);
    }

    bool setMarginBottom (PropertyValues value, HTReal addData = 0.0f) {
        return setProperty (PID_MARGIN_BOTTOM, value, (HTData)addData);
    }

    bool setMargin (HTReal left = 0.0f, HTReal top = 0.0f,
                HTReal right = 0.0f, HTReal bottom = 0.0f) {
        bool ret1 = setProperty (PID_MARGIN_LEFT, PV_MARGIN_LENGTH, left);
        bool ret2 = setProperty (PID_MARGIN_TOP, PV_MARGIN_LENGTH, top);
        bool ret3 = setProperty (PID_MARGIN_RIGHT, PV_MARGIN_LENGTH, right);
        bool ret4 = setProperty (PID_MARGIN_BOTTOM, PV_MARGIN_LENGTH, bottom);

        return (ret1 && ret2 && ret3 && ret4);
    }

protected:
    bool setProperty (PropertyIds id, PropertyValues value, HTData addData = 0);

private:
    MAPCLASSKEY(PropertyIds, PropertyValue, PropertyValueMap);
    PAIR(PropertyIds, PropertyValue, PropertyValuePair);

    int m_id;
    PropertyValueMap m_map;
}

namespace css {

} // namespace css

} // namespace hfcl

#endif /* HFCL_CSS_STYLESHEET_H_ */
