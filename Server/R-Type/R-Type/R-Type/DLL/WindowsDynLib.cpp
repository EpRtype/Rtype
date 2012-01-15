#ifdef WIN32
#include "WindowsDynLib.hpp"
#include <Windows.h>

std::wstring StringToWString(const std::string& s)
{
std::wstring temp(s.length(),L' ');
std::copy(s.begin(), s.end(), temp.begin());
return temp; 
}


std::string WStringToString(const std::wstring& s)
{
std::string temp(s.length(), ' ');
std::copy(s.begin(), s.end(), temp.begin());
return temp; 
}

WindowsDynLib::WindowsDynLib()
{}

WindowsDynLib::~WindowsDynLib()
{}

void* WindowsDynLib::openLib()
{
	return LoadLibrary(getlibName().c_str());
}

  void* WindowsDynLib::dlSymb()
  {
	return GetProcAddress(HandleOpen, SymbolName.c_str());
  }

 int WindowsDynLib::closeLib()
 {
	 return FreeLibrary(HandleOpen);
 }

  char* WindowsDynLib::errorLib()
  {
  return 0;
  }

  void WindowsDynLib::setlibName(std::string lib)
  {
	  libName = StringToWString(lib);
  }

  std::wstring WindowsDynLib::getlibName()
  {
	  return libName;
  }

  void WindowsDynLib::setSymbolName(std::string sym)
  {
	  SymbolName = sym.c_str();
  }

  std::string WindowsDynLib::getSymbolName()
  {
	  return SymbolName;
  }
  void WindowsDynLib::setHandleOpen(void* hdl)
  {
	  HandleOpen = (HINSTANCE)hdl;
  }
  void* WindowsDynLib::getHandleOpen()
  {
	  return HandleOpen;
  }

#endif
