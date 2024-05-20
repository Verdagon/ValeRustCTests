#pragma rsuse OsString = std::ffi::OsString
#pragma rsuse OsStringNew = OsString::new
#pragma rsuse OsStringPushRefStr = OsString::push::<&str>
#pragma rsuse VecOsStringRef = std::vec::Vec<&OsString>
#pragma rsuse VecOsStringRefNew = VecOsStringRef::new
#pragma rsuse VecOsStringRefPush = VecOsStringRef::push
#pragma rsuse VecOsStringRefAsSlice = VecOsStringRef::as_slice
#pragma rsuse PopenConfig = subprocess::PopenConfig
#pragma rsuse PopenConfigDefault = PopenConfig::default
#pragma rsuse Popen = subprocess::Popen
#pragma rsuse PopenCreate = Popen::create::<&OsString>
#pragma rsuse PopenResult = subprocess::Result<Popen>
#pragma rsuse PopenResultIsOk = PopenResult::is_ok
#pragma rsuse PopenResultUnwrap = PopenResult::unwrap
#pragma rsuse PopenWait = Popen::wait
#pragma rsuse ExitStatusResult = subprocess::Result<subprocess::ExitStatus>
#pragma rsuse ExitStatusResultIsOk = ExitStatusResult::is_ok

#include <rust_deps/rust_deps.h>
#include <stdio.h>

int main() {
  OsString program_name_osstring = OsStringNew();
  OsStringPushRefStr(&program_name_osstring, VR_StrFromCStr("/bin/cat"));
  
  OsString arg1_osstring = OsStringNew();
  OsStringPushRefStr(&arg1_osstring, VR_StrFromCStr("/Users/verdagon/hello.txt"));
  
  VecOsStringRef argv = VecOsStringRefNew();
  VecOsStringRefPush(&argv, &program_name_osstring);
  VecOsStringRefPush(&argv, &arg1_osstring);

  PopenResult create_result =
      PopenCreate(
          VecOsStringRefAsSlice(&argv), PopenConfigDefault());

  if (!PopenResultIsOk(&create_result)) {
    printf("Failed to open subprocess!\n");
    return 1;
  }
  Popen process = PopenResultUnwrap(create_result);

  ExitStatusResult wait_result = PopenWait(&process);

  if (!ExitStatusResultIsOk(&wait_result)) {
    printf("Failed to wait on subprocess!\n");
    return 1;
  }

  printf("Success!\n");
  return 0;
}
