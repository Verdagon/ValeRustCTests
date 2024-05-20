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
#pragma vrinclude std::vec::Vec<&std::ffi::OsString>::as_slice as VecOsStringRefAsSlice
#pragma vrinclude subprocess::PopenConfig as RustPopenConfig
#pragma vrinclude subprocess::PopenConfig::default as RustPopenConfigDefault
#pragma vrinclude subprocess::Popen::create::<&std::ffi::OsString> as RustPopenCreate
#pragma vrinclude subprocess::Result<subprocess::Popen> as RustSubprocessPopenResult
#pragma vrinclude subprocess::Result<subprocess::Popen>::is_ok as RustSubprocessPopenResultIsOk
#pragma vrinclude subprocess::Result<subprocess::Popen>::unwrap as RustSubprocessPopenResultUnwrap
#pragma vrinclude subprocess::Popen as RustSubprocessPopen
#pragma vrinclude subprocess::Popen::wait as RustSubprocessPopenWait
#pragma vrinclude subprocess::Result<subprocess::ExitStatus> as RustSubprocessExitStatusResult
#pragma vrinclude subprocess::Result<subprocess::ExitStatus>::is_ok as RustSubprocessExitStatusResultIsOk

#include <rust_deps/rust_deps.h>
#include <stdio.h>

int main() {
  RustOsString program_name_osstring = RustOsStringNew();
  RustOsStringPushRefStr(&program_name_osstring, RustStrFromCStr("/bin/cat"));
  
  RustOsString arg1_osstring = RustOsStringNew();
  RustOsStringPushRefStr(&arg1_osstring, RustStrFromCStr("/Users/verdagon/hello.txt"));
  
  VecOsStringRef argv = VecOsStringRefNew();
  VecOsStringRefPush(&argv, &program_name_osstring);
  VecOsStringRefPush(&argv, &arg1_osstring);

  RustSubprocessPopenResult create_result =
      RustPopenCreate(
          VecOsStringRefAsSlice(&argv), RustPopenConfigDefault());

  if (!RustSubprocessPopenResultIsOk(&create_result)) {
    printf("Failed to open subprocess!\n");
    return 1;
  }
  RustSubprocessPopen process = RustSubprocessPopenResultUnwrap(create_result);

  RustSubprocessExitStatusResult wait_result =
      RustSubprocessPopenWait(&process);

  if (!RustSubprocessExitStatusResultIsOk(&wait_result)) {
    printf("Failed to wait on subprocess!\n");
    return 1;
  }

  printf("Success!\n");
  return 0;
}
