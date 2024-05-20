#pragma vrinclude std::string::String::From<&str>::from as RustStringFromStrRef
#pragma vrinclude std::string::String::len as RustStringLen
#pragma vrinclude std::string::String as RustString

#include <rust_deps/rust_deps.h>
#include <stdio.h>

int main() {
  VR_str_ref constant = RustStrFromCStr("bork");
  RustString str = RustStringFromStrRef(constant);
  int len = RustStringLen(&str);
  printf("Length: %d\n", len);
  return 0;
}
