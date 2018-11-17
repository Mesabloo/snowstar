import stdout;
import string;

i32 main() {
    str hw = "hello, world!";
    hw = string::capitalize(hw);
    % This transforms `hello, world!` into `Hello, World!` 
    print(hw);
    return 0;
}