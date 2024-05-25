#pragma rsuse Str = &str
#pragma rsuse String = std::string::String
#pragma rsuse String_fromStr = String::From<&str>::from
#pragma rsuse String_len = String::len
#pragma rsuse String_drop = String::drop
#include <rust_deps/rust_deps.h>
#include <stdio.h>

int main() {
  Str b = VR_StrFromCStr("bork");
  String s = String_fromStr(b);
  int len = String_len(&s);
  printf("Length: %d\n", len);
  String_drop(s);
  return 0;
}
