#pragma once


class BinaryReader
{
public:
  BinaryReader(const std::wstring& i_fileName)
    : d_stream(i_fileName, std::ios::binary)
    , d_offset(0)
  {
    d_stream.seekg(0, std::ios::end);
    d_size = (int)d_stream.tellg();
    d_stream.seekg(0, std::ios::beg);
  }

  bool isOpen() const { return d_stream.is_open(); }
  int getOffset() const { return d_offset; }
  int getSize() const { return d_size; }

  void moveOffset(int i_offset)
  {
    d_stream.seekg(i_offset, std::ios::cur);
    d_offset += i_offset;
  }

  template<size_t SIZE>
  void readArray(std::array<uint8_t, SIZE>& o_dest)
  {
    d_stream.read((char*)o_dest.data(), SIZE);
    d_offset += SIZE;
  }

  void readVector(std::vector<uint8_t>& o_dest, int i_length)
  {
    if (o_dest.size() != i_length)
      o_dest.resize(i_length);
    d_stream.read((char*)o_dest.data(), i_length);
    d_offset += i_length;
  }

  void readString(std::string& o_dest, int i_length)
  {
    std::vector<char> tempVector(i_length);
    d_stream.read(tempVector.data(), i_length);
    o_dest = std::string(tempVector.cbegin(), tempVector.cend());
    d_offset += i_length;
  }

  template<typename T>
  void readValue(T& o_dest)
  {
    int length = sizeof(T);
    d_stream.read((char*)(&o_dest), length);
    d_offset += length;
  }

private:
  std::ifstream d_stream;
  int d_offset;
  int d_size;
};
