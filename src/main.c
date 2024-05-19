// #pragma vrinclude std::string::String::From<&str>::from as RustStringFromStrRef
// #pragma vrinclude std::string::String::len as RustStringLen
// #pragma vrinclude std::string::String as RustString
#pragma vrinclude std::ffi::OsString as RustOsString
// #pragma vrinclude std::ffi::OsString::From<&str>::from as RustOsStringFrom
#pragma vrinclude std::ffi::OsString::new as RustOsStringNew
#pragma vrinclude std::ffi::OsString::push::<&str> as RustOsStringPushRefStr
#pragma vrinclude std::vec::Vec<&std::ffi::OsString> as VecOsStringRef
#pragma vrinclude std::vec::Vec<&std::ffi::OsString>::new as VecOsStringRefNew
#pragma vrinclude std::vec::Vec<&std::ffi::OsString>::push as VecOsStringRefPush
// #pragma vrinclude subprocess::PopenConfig as RustPopenConfig
// #pragma vrinclude subprocess::PopenConfig::default as RustPopenConfigDefault
// #pragma vrinclude subprocess::Popen::create as RustPopenCreate
// #pragma vrinclude subprocess::Result<Popen> as RustSubprocessPopenResult
// #pragma vrinclude subprocess::Result<Popen>::is_ok as RustSubprocessPopenResultIsOk

#include <rust_deps/rust_deps.h>
#include <stdio.h>

int main() {
  // RustString str = RustStringFromStrRef(constant);
  // int len = RustStringLen(&str);
  // printf("Length: %d\n", len);
  // return 0;


  RustOsString program_name_osstring = RustOsStringNew();
  RustOsStringPushRefStr(&program_name_osstring, RustStrFromCStr("/bin/cat"));
  // RustOsString program_name_osstring = RustOsStringFrom(RustStrFromCStr("/bin/cat"));
  
  // const char* arg1_cstr = ;
  // OsString_extern arg1_osstring;
  // OsString_new_extern((const int8_t*)arg1_cstr, strlen(arg1_cstr), &arg1_osstring);
  RustOsString arg1_osstring = RustOsStringNew();
  RustOsStringPushRefStr(&arg1_osstring, RustStrFromCStr("/Users/verdagon/hello.txt"));
  
  VecOsStringRef argv = VecOsStringRefNew();
  VecOsStringRefPush(&argv, &program_name_osstring);
  VecOsStringRefPush(&argv, &arg1_osstring);

  // RustPopenConfig popen_config = RustPopenConfigDefault();

  // Result_Popen_PopenError_extern result;
  // Popen_create_extern(&argv, &popen_config, &result);

  // bool is_ok = Result_Popen_PopenError_is_ok_extern(&result);

  // if (!is_ok) {
  //   return 1;
  // }
  return 0;
}
