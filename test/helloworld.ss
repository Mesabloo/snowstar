import stdout;
import string;

i32() main = () => {
    @mut str hw = "hello, world!";
    hw = string::capitalize(hw);
    % This transforms `hello, world!` into `Hello, World!` 
    print(hw);
    return (i32)(+0);
};