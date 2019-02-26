#include "stdafx.h"
#include "FbxImporter.h"


bool loadFromFile(const std::wstring& i_fileName)
{
  std::ifstream inputStream(i_fileName, std::ios::binary);
  if (!inputStream.is_open())
    return false;

  return true;
}
