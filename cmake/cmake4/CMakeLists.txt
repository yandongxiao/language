cmake_minimum_required(VERSION 2.8)
set(var "ABC")

macro(Moo arg)
    message("arg = ${arg}")
    set(arg "abc")
    message("# After change the value of arg.")
    message("arg = ${arg}")
endmacro()

message("=== Call macro ===")
Moo(var)

function(Foo arg)
    message("arg = ${arg}")
    set(arg "abc")
    message("# After change the value of arg.")
    message("arg = ${arg}")
endfunction()

message("=== Call function ===")
Foo(${var})
