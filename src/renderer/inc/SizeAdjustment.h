// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#pragma once

struct SizeAdjustment
{
    enum class Unit : uint8_t
    {
        None,
        Percent,
        Pixel,
        Point,
    };

    enum class ReferenceFrame : uint8_t
    {
        Relative,
        Absolute,
    };

    static SizeAdjustment FromString(const wchar_t* str);

    float AdjustValue(float value, float dpi) const noexcept;

    float amount = 0;
    Unit unit = Unit::None;
    ReferenceFrame referenceFrame = ReferenceFrame::Relative;
};
