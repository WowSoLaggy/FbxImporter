#include "stdafx.h"
#include "CppUnitTest.h"

#include "Utils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace FbxImporterTest_NS
{
  TEST_CLASS(FbxImporterTester)
  {
  public:

    TEST_METHOD(SimpleLoad)
    {
      const std::wstring fbxFileName = L"Character.fbx";

      auto fullFilePath = getWorkingDir() + L"\\..\\..\\rsrc\\" + fbxFileName;
      Logger::WriteMessage((L"Full file path: \'" + fullFilePath + L"\'").c_str());

      try
      {
        auto rootElement = Fbx_NS::loadFromFile(fullFilePath);
      }
      catch (std::exception& exc)
      {
        std::string string{ exc.what() };
        std::wstring wstring{ string.cbegin(), string.cend() };
        Assert::Fail(wstring.c_str());
      }
      catch (...)
      {
        Assert::Fail(L"Unhandled exception");
      }
    }

  };
}