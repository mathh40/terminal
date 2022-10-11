/*++
Copyright (c) Microsoft Corporation
Licensed under the MIT license.

Module Name:
- FontInfo.hpp

Abstract:
- This serves as the structure defining font information.

- FontInfoDesired - derived from FontInfoBase.  It also contains
  a desired size { X, Y }, to be supplied to the GDI's LOGFONT
  structure.  Unlike FontInfo, both desired X and Y can be zero.

Author(s):
- Michael Niksa (MiNiksa) 17-Nov-2015
--*/

#pragma once

#include "FontInfoBase.hpp"
#include "FontInfo.hpp"
#include "SizeAdjustment.h"

class FontInfoDesired : public FontInfoBase
{
public:
    FontInfoDesired(const std::wstring_view& faceName,
                    const unsigned char family,
                    const unsigned int weight,
                    const float fontSize,
                    const unsigned int uiCodePage) noexcept;
    FontInfoDesired(const FontInfo& fiFont) noexcept;

    bool operator==(const FontInfoDesired& other) = delete;

    void SetCellSizeAdjustments(const SizeAdjustment& adjustmentX, const SizeAdjustment& adjustmentY) noexcept;

    const SizeAdjustment& GetCellSizeAdjustmentX() const noexcept;
    const SizeAdjustment& GetCellSizeAdjustmentY() const noexcept;
    float GetFontSize() const noexcept;
    til::size GetEngineSize() const noexcept;
    bool IsDefaultRasterFont() const noexcept;

private:
    til::size _coordSizeDesired;
    float _fontSize;
    SizeAdjustment _adjustmentX;
    SizeAdjustment _adjustmentY;
};
