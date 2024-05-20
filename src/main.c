// #pragma vrinclude std::string::String::From<&str>::from as RustStringFromStrRef
// #pragma vrinclude std::string::String::len as RustStringLen
#pragma vrinclude std::string::String as RustString
#pragma vrinclude str::chars as RustStr_chars
#pragma vrinclude core::str::Chars<'static> as RustChars
#pragma vrinclude core::str::Chars<'static>::rev as RustChars_rev
#pragma vrinclude core::iter::Rev<core::str::Chars<'static>> as RustRevChars
#pragma vrinclude core::iter::Rev<core::str::Chars<'static>>::collect::<std::string::String> as RustRevChars_collectString
#pragma vrinclude std::string::String::as_str as RustString_as_str

#include <rust_deps/rust_deps.h>
#include <stdio.h>
#include <unistd.h>

int main() {
  VR_str_ref constant = RustStrFromCStr("bork");
  // RustString str = RustStringFromStrRef(constant);
  RustChars x = RustStr_chars(constant);
  RustRevChars reversed = RustChars_rev(x);
  RustString bork = RustRevChars_collectString(reversed);
  VR_str_ref bork_as_str = RustString_as_str(&bork);

  write(STDOUT_FILENO, RustStrToCStr(bork_as_str), RustStrLen(bork_as_str));

  printf("Success!\n");
  return 0;
}
