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
      const std::wstring fbxFileName = L"Gates.fbx";

      auto fullFilePath = getWorkingDir() + L"\\..\\..\\rsrc\\" + fbxFileName;
      Logger::WriteMessage((L"Full file path: \'" + fullFilePath + L"\'").c_str());

      loadFromFile(fbxFileName);
    }

  };
}