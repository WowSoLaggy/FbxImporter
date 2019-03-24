#pragma once

#include "Property.h"

#include <string>
#include <vector>

namespace Fbx_NS
{
  struct Element
  {
    uint32_t endOffset;
    uint32_t propertiesCount;
    uint32_t propertiesListLength;
    uint8_t nameLength;
    std::string name;
    std::vector<Property> properties;
    std::vector<Element> childs;

    bool isZeroEntry() const
    {
      return
        endOffset == 0 &&
        propertiesCount == 0 &&
        propertiesListLength == 0 &&
        nameLength == 0;
    }
  };

} // Fbx_NS
