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
  };

} // Fbx_NS
