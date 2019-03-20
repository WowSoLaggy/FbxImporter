#include "stdafx.h"
#include "FbxImporter.h"

#include "BinaryReader.h"
#include "Element.h"
#include "Header.h"


namespace Fbx_NS
{
  namespace
  {
    Property readProperty(BinaryReader& i_reader)
    {
      uint8_t typeCode;
      i_reader.readValue(typeCode);

      Property property;
      property.type = PropertyTypeCodeToTypeMap.at(typeCode);

      int dataTypeSizeInBytes = PropertyTypeToTypeSizeMap.at(property.type);
      PropertySerializationType serializationType =
        PropertyTypeToSerializationTypeMap.at(property.type);

      switch (serializationType)
      {
      case PropertySerializationType::Value:
        property.length = 1;
        property.encoding = 0;
        property.compressedLength = property.length;
        break;

      case PropertySerializationType::Array:
        i_reader.readValue(property.length);
        property.encoding = 0;
        property.compressedLength = property.length;
        break;

      case PropertySerializationType::EncodedArray:
        i_reader.readValue(property.length);
        i_reader.readValue(property.encoding);
        i_reader.readValue(property.compressedLength);
        break;

      default:
        throw new std::runtime_error("Unexpected PropertySerializationType");
      }

      i_reader.readVector(property.data, dataTypeSizeInBytes * property.compressedLength);

      return property;
    }

    Element readElement(BinaryReader& i_reader)
    {
      Element element;
      i_reader.readValue(element.endOffset);
      i_reader.readValue(element.propertiesCount);
      i_reader.readValue(element.propertiesListLength);
      i_reader.readValue(element.nameLength);
      i_reader.readString(element.name, element.nameLength);

      element.properties.reserve(element.propertiesCount);
      for (int propertyIdx = 0; propertyIdx < (int)element.propertiesCount; ++propertyIdx)
        element.properties.push_back(std::move(readProperty(i_reader)));

      static const int FooterLength = 13;

      while (i_reader.getOffset() + FooterLength < (int)element.endOffset)
        element.childs.push_back(std::move(readElement(i_reader)));

      if (i_reader.getOffset() + FooterLength == (int)element.endOffset)
        i_reader.moveOffset(FooterLength);

      return element;
    }

  } // anonymous NS


  Element loadFromFile(const std::wstring& i_fileName)
  {
    BinaryReader reader(i_fileName);
    if (!reader.isOpen())
      throw new std::runtime_error("File not found");

    Header header;
    reader.readArray(header.magic);
    reader.readArray(header.reserved);
    reader.readValue(header.version);

    return readElement(reader);
  }

} // Fbx_NS
