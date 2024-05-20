#pragma rsuse PathBuf = std::path::PathBuf
#pragma rsuse IoResultTup = std::io::Result<()>
#pragma rsuse IoResultTupIsOk = IoResultTup::is_ok
#pragma rsuse String = std::string::String
#pragma rsuse StringNew = String::new
#pragma rsuse StringPush = String::push
#pragma rsuse PathBufNew = PathBuf::new
#pragma rsuse PathBufPushStr = PathBuf::push::<&String>
#pragma rsuse CreateDir = std::fs::create_dir<&PathBuf>

#include <rust_deps/rust_deps.h>
#include <stdio.h>

int main() {
  PathBuf path_buf = PathBufNew();

  String str = StringNew();
  StringPush(&str, 'x');

  PathBufPushStr(&path_buf, &str);

  IoResultTup result = CreateDir(&path_buf);
  if (IoResultTupIsOk(&result)) {
    printf("Success!\n");
    return 0;
  } else {
    printf("Error creating directory!\n");
    return 1;
  }
}
