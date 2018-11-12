import io;
import string;

int32 main() {
    string str = "hello, world!";
    % `"hello, world"` returns an `array<char>` 
    print(string::to_char_array(str));
    % We cannot print a "user-defined" `dtype` (in this case `string`)
    return 0;
}