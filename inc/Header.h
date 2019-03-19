#pragma once

#include <array>


namespace Fbx_NS
{
  struct Header
  {
    std::array<uint8_t, 21> magic;
    std::array<uint8_t, 2> reserved;
    uint32_t version;
  };

} // Fbx_NS
