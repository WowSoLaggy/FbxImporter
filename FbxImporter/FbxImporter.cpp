#include "stdafx.h"
#include "FbxImporter.h"

#include "BinaryReader.h"
#include "Element.h"
#include "Header.h"


namespace Fbx_NS
{
  namespace
  {
    // Fwd declaration
    Element readElement(BinaryReader& i_reader);

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
        property.compressedLength = dataTypeSizeInBytes * property.length;
        break;

      case PropertySerializationType::Array:
        i_reader.readValue(property.length);
        property.encoding = 0;
        property.compressedLength = dataTypeSizeInBytes * property.length;
        break;

      case PropertySerializationType::EncodedArray:
        i_reader.readValue(property.length);
        i_reader.readValue(property.encoding);
        i_reader.readValue(property.compressedLength);
        break;

      default:
        throw new std::runtime_error("Unexpected PropertySerializationType");
      }

      i_reader.readVector(property.data, property.compressedLength);

      return property;
    }

    void readChilds(BinaryReader& i_reader, Element& a_element)
    {
      static const int FooterLength = 13;

      while (i_reader.getOffset() + FooterLength < (int)a_element.endOffset)
      {
        auto element = readElement(i_reader);
        if (element.isZeroEntry())
          break;
        a_element.childs.push_back(std::move(element));
      }

      if (i_reader.getOffset() + FooterLength == (int)a_element.endOffset)
        i_reader.moveOffset(FooterLength);
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

      readChilds(i_reader, element);

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

    Element rootElement;
    rootElement.endOffset = reader.getSize();
    rootElement.propertiesCount = 0;
    rootElement.propertiesListLength = 0;
    rootElement.nameLength = 0;
    rootElement.name = "";

    readChilds(reader, rootElement);

    return rootElement;
  }

} // Fbx_NS
