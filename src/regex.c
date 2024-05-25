// Seamless C->Rust example: using regex

// Import types. More advanced compilers with generics wouldn't need
// to specify these generic args in theory, it would basically be a
// vanilla java import.
#pragma rsuse Str = &str
#pragma rsuse String = std::string::String
#pragma rsuse Regex = regex::Regex
#pragma rsuse RegexResult = std::result::Result<Regex, regex::Error>
#pragma rsuse RegexCaptures = regex::Captures<'static>
#pragma rsuse OptionRegexCaptures = std::option::Option<RegexCaptures>
#pragma rsuse RegexMatch = regex::Match<'static>
#pragma rsuse OptionRegexMatch = std::option::Option<regex::Match<'static>>
// // Import methods. AFAICT more advanced compilers with generics won't
// // need any of these imports in theory.
#pragma rsuse Regex_new = Regex::new
#pragma rsuse Regex_captures = Regex::captures::<'static>
#pragma rsuse Regex_drop = Regex::drop
#pragma rsuse OptionRegexCaptures_drop = OptionRegexCaptures::drop
#pragma rsuse OptionRegexCaptures_is_none = OptionRegexCaptures::is_none
#pragma rsuse OptionRegexCaptures_unwrap = OptionRegexCaptures::unwrap
#pragma rsuse RegexResult_is_ok = RegexResult::is_ok
#pragma rsuse RegexResult_unwrap = RegexResult::unwrap
#pragma rsuse RegexResult_drop = RegexResult::drop
#pragma rsuse RegexCaptures_get = RegexCaptures::get
#pragma rsuse RegexCaptures_drop = RegexCaptures::drop
#pragma rsuse OptionRegexMatch_drop = OptionRegexMatch::drop
#pragma rsuse OptionRegexMatch_is_none = OptionRegexMatch::is_none
#pragma rsuse OptionRegexMatch_unwrap = OptionRegexMatch::unwrap
#pragma rsuse RegexMatch_as_str = RegexMatch::as_str
#pragma rsuse RegexMatch_drop = RegexMatch::drop
// Import the header generated by the Makefile invoking the tool
#include <rust_deps/rust_deps.h>

#include <stdio.h>
#include <unistd.h>

int main() {
  Str str = VR_StrFromCStr("hello my name is (.+) how are you");

  RegexResult regex_result = Regex_new(str);
  if (!RegexResult_is_ok(&regex_result)) {
    printf("Error making regex!\n");
    RegexResult_drop(regex_result);
    return 1;
  }
  Regex regex = RegexResult_unwrap(regex_result);

  OptionRegexCaptures maybe_captures = 
      Regex_captures(&regex, VR_StrFromCStr("hello my name is Valerian Vast how are you"));
  if (OptionRegexCaptures_is_none(&maybe_captures)) {
    printf("Not a match!\n");
    OptionRegexCaptures_drop(maybe_captures);
    Regex_drop(regex);
    return 1;
  }
  RegexCaptures captures = OptionRegexCaptures_unwrap(maybe_captures);

  OptionRegexMatch maybe_match = RegexCaptures_get(&captures, 1);
  if (OptionRegexMatch_is_none(&maybe_match)) {
    printf("No capture group!\n");
    OptionRegexMatch_drop(maybe_match);
    RegexCaptures_drop(captures);
    Regex_drop(regex);
    return 1;
  }
  RegexMatch match = OptionRegexMatch_unwrap(maybe_match);
  Str match_as_str = RegexMatch_as_str(&match);

  write(STDOUT_FILENO, VR_StrToCStr(match_as_str), VR_StrLen(match_as_str));
  printf("\nSuccess!\n");

  RegexMatch_drop(match);
  RegexCaptures_drop(captures);
  Regex_drop(regex);

  return 0;
}

// More notes:
// - rust_deps.h contains all the auto-generated bindings.
// - This is C, user needs to manage their memory. User shouldn't e.g.:
//   - Move `Str str` while Chars is alive.
//   - Forget to drop() the revString.
// - VR_StrFromCStr is a builtin that makes a Rust str from a char*.
// - VR_StrToCStr is a builtin that gets the char* back from Rust str.
// - VR_StrLen gets the length of a Rust str.