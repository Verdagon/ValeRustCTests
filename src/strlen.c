#pragma rsuse String = std::string::String
#pragma rsuse StringFromStr = String::From<&str>::from
#pragma rsuse StringLen = String::len
#include <rust_deps/rust_deps.h>
#include <stdio.h>

int main() {
  VR_str_ref constant = StrFromCStr("bork");
  String str = StringFromStrRef(constant);
  int len = StringLen(&str);
  printf("Length: %d\n", len);
  return 0;
}
