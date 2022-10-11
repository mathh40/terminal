// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#include "precomp.h"

#include "../inc/SizeAdjustment.h"

SizeAdjustment SizeAdjustment::FromString(const wchar_t* str)
{
    const auto firstChar = *str;
    const auto isRelative = firstChar == '+' || firstChar == '-';
    const auto referenceFrame = isRelative ? ReferenceFrame::Relative : ReferenceFrame::Absolute;

    auto& errnoRef = errno; // Nonzero cost, pay it once.
    errnoRef = 0;

    wchar_t* end;
    const auto amount = std::wcstof(str, &end);

    if (str == end || errnoRef == ERANGE)
    {
        return {};
    }

    auto unit = Unit::None;
    if (*end)
    {
        if (wcscmp(end, L"%") == 0)
        {
            unit = Unit::Percent;
        }
        else if (wcscmp(end, L"px") == 0)
        {
            unit = Unit::Pixel;
        }
        else if (wcscmp(end, L"pt") == 0)
        {
            unit = Unit::Point;
        }
        else
        {
            return {};
        }
    }

    return { amount, unit, referenceFrame };
}

float SizeAdjustment::AdjustValue(float value, float dpi) const noexcept
{
    if (!amount)
    {
        return value;
    }

    auto result = 0.0f;

    switch (unit)
    {
    case Unit::None:
        result = value * amount;
        break;
    case Unit::Percent:
        result = value * amount / 100.0f;
        break;
    case Unit::Pixel:
        result = amount / 96.0f * dpi;
        break;
    case Unit::Point:
        result = amount / 72.0f * dpi;
        break;
    }

    if (referenceFrame == ReferenceFrame::Relative)
    {
        result += value;
    }

    return result;
}
