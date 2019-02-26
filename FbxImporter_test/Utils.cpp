#include "stdafx.h"
#include "Utils.h"


std::wstring getWorkingDir()
{
  HMODULE h;
  static TCHAR c;
  GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, &c, &h);

  wchar_t buffer[MAX_PATH];
  GetModuleFileName(h, buffer, MAX_PATH);
  std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
  return std::wstring(buffer).substr(0, pos);
}
