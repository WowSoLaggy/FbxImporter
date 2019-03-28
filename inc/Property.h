#pragma once

#include <unordered_map>


enum class PropertyType
{
  Bool, BoolArray,

  Short,
  Int, IntArray,
  Long, LongArray,

  Float, FloatArray,
  Double, DoubleArray,

  String,
  Raw,
};

const std::unordered_map<uint8_t, PropertyType> PropertyTypeCodeToTypeMap
{
  { 'C', PropertyType::Bool },{ 'b', PropertyType::BoolArray },

  { 'Y', PropertyType::Short },
  { 'I', PropertyType::Int },{ 'i', PropertyType::IntArray },
  { 'L', PropertyType::Long },{ 'l', PropertyType::LongArray },

  { 'F', PropertyType::Float },{ 'f', PropertyType::FloatArray },
  { 'D', PropertyType::Double },{ 'd', PropertyType::DoubleArray },

  { 'S', PropertyType::String },
  { 'R', PropertyType::Raw },
};

const std::unordered_map<PropertyType, int> PropertyTypeToTypeSizeMap
{
  { PropertyType::Bool,   1 },{ PropertyType::BoolArray,    1 },

{ PropertyType::Short,  2 },
{ PropertyType::Int,    4 },{ PropertyType::IntArray,     4 },
{ PropertyType::Long,   8 },{ PropertyType::LongArray,    8 },

{ PropertyType::Float,  4 },{ PropertyType::FloatArray,   4 },
{ PropertyType::Double, 8 },{ PropertyType::DoubleArray,  8 },

{ PropertyType::String, 1 },
{ PropertyType::Raw,    1 },
};

enum class PropertySerializationType
{
  Value,        // Just a value
  Array,        // Length, then array of values
  EncodedArray, // Length, encoding flag, compressed length, then array
};

const std::unordered_map<PropertyType, PropertySerializationType>
PropertyTypeToSerializationTypeMap
{
  { PropertyType::Bool,         PropertySerializationType::Value },
{ PropertyType::BoolArray,    PropertySerializationType::EncodedArray },

{ PropertyType::Short,        PropertySerializationType::Value },
{ PropertyType::Int,          PropertySerializationType::Value },
{ PropertyType::IntArray,     PropertySerializationType::EncodedArray },
{ PropertyType::Long,         PropertySerializationType::Value },
{ PropertyType::LongArray,    PropertySerializationType::EncodedArray },

{ PropertyType::Float,        PropertySerializationType::Value },
{ PropertyType::FloatArray,   PropertySerializationType::EncodedArray },
{ PropertyType::Double,       PropertySerializationType::Value },
{ PropertyType::DoubleArray,  PropertySerializationType::EncodedArray },

{ PropertyType::String,       PropertySerializationType::Array },
{ PropertyType::Raw,          PropertySerializationType::Array },
};

struct Property
{
  PropertyType type;
  uint32_t length;
  uint32_t encoding;
  uint32_t compressedLength;
  std::vector<uint8_t> data;
};
