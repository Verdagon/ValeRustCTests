#pragma rsuse PathBuf = std::path::PathBuf
#pragma rsuse IoResultTup = std::io::Result<()>
#pragma rsuse IoResultTup_is_ok = IoResultTup::is_ok
#pragma rsuse IoResultTup_drop = IoResultTup::drop
#pragma rsuse String = std::string::String
#pragma rsuse String_new = String::new
#pragma rsuse String_drop = String::drop
#pragma rsuse String_push = String::push
#pragma rsuse PathBuf_new = PathBuf::new
#pragma rsuse PathBuf_pushStr = PathBuf::push::<&String>
#pragma rsuse PathBuf_drop = PathBuf::drop
#pragma rsuse create_dir = std::fs::create_dir<&PathBuf>
#include <rust_deps/rust_deps.h>

#include <stdio.h>

int main() {
  PathBuf path_buf = PathBuf_new();

  String str = String_new();
  String_push(&str, 'x');

  PathBuf_pushStr(&path_buf, &str);

  String_drop(str);

  IoResultTup result = create_dir(&path_buf);
  PathBuf_drop(path_buf);

  if (IoResultTup_is_ok(&result)) {
    printf("Success!\n");
    IoResultTup_drop(result);
    return 0;
  } else {
    printf("Error creating directory!\n");
    IoResultTup_drop(result);
    return 1;
  }
}
