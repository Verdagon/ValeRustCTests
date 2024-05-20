#pragma rsuse Str = &str
#pragma rsuse Str_chars = str::chars
#pragma rsuse String = std::string::String
#pragma rsuse String_as_str = String::as_str
#pragma rsuse Chars = core::str::Chars<'static>
#pragma rsuse Chars_rev = Chars::rev
#pragma rsuse RevChars = core::iter::Rev<Chars>
#pragma rsuse RevChars_collectString = RevChars::collect::<String>

#include <rust_deps/rust_deps.h>
#include <stdio.h>
#include <unistd.h>

int main() {
  Str constant = VR_StrFromCStr("bork");
  Chars x = Str_chars(constant);
  RevChars reversed = Chars_rev(x);
  String bork = RevChars_collectString(reversed);
  Str bork_as_str = String_as_str(&bork);

  write(STDOUT_FILENO, VR_StrToCStr(bork_as_str), VR_StrLen(bork_as_str));

  printf("Success!\n");
  return 0;
}
