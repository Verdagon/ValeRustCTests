#pragma vrinclude std::path::PathBuf as RustPathBuf
#pragma vrinclude std::io::Result<()> as RustIoResultTup
#pragma vrinclude std::io::Result<()>::is_ok as RustIoResultTupIsOk
#pragma vrinclude std::string::String as RustString
#pragma vrinclude std::string::String::new as RustStringNew
#pragma vrinclude std::string::String::push as RustStringPush
#pragma vrinclude std::path::PathBuf::new as RustPathBufNew
#pragma vrinclude std::path::PathBuf::push::<&std::string::String> as RustPathBufPushStr
#pragma vrinclude std::fs::create_dir<&std::path::PathBuf> as RustCreateDir

#include <rust_deps/rust_deps.h>
#include <stdio.h>

int main() {
  RustPathBuf path_buf = RustPathBufNew();

  RustString str = RustStringNew();
  RustStringPush(&str, 'x');

  RustPathBufPushStr(&path_buf, &str);

  RustIoResultTup result = RustCreateDir(&path_buf);
  if (RustIoResultTupIsOk(&result)) {
    printf("Success!\n");
    return 0;
  } else {
    printf("Error creating directory!\n");
    return 1;
  }
}
