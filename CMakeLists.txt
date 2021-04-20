# 遍历项目根目录下所有的 .cpp 文件
file (GLOB_RECURSE files *.c *.h )
foreach (file ${files})
    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" exe ${file})
    add_executable (${exe} ${file})
    message (\ \ \ \ --\ src/${exe}.c\ will\ be\ compiled\ to\ bin/${exe})
endforeach ()