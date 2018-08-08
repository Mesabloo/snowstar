# Snow*, a programming language based on the Assembly language's way of functioning.
---
> What is Snow* ?

Snow* is a programming language based on the Assembly language syntax, and also its way of functioning.

> How does it work ?

Snow*'s environment contains 3 segments: `mem` which is the basic memory holder, limited to 256 values; `temp` which is a special segment, holding until 32 values, but whose content changes on each `call`; `param` which is a [stack](https://en.wikipedia.org/wiki/Stack_(abstract_data_type)) containing values used in `sys`tem calls, for example, or which can be used in your own `call`s. <br>
Easy ways to manage them are `store`, `push`, `free` and `pop`. 

Example:
```
main: % Main entry point, absolutely needed

    store[mem, 41] 'Hello, World!'
    % In this case, we store the string 'Hello, World!' at the 41st index of the memory.

    free [mem, 41]
    % Now that we don't need it anymore, we can delete it

    push[param] 'Pushed into the params'
    % We can only push inside the params, because it is the only stack existing (and modifiable) in Snow*

    pop [param]
    % We may pop now, if we don't need them neither

    int 0
    % Don't forget this line, else your program will never stop
```

> Is there a way to learn the language ?

Yes, there is one. A website is hosted on github [here](https://mesabloo.github.io/snowstar-lang). You will find every information you need (docs, tutorials, examples) there. If you have any question/request, feel free to ask them to me. <br>
You will find me known as `Меѕаblоо#5674` on [Discord](https://www.discordapp.com) (please copy/paste, do not try to rewrite it).

> Just a free sample.

```
main: % Still needed

    rand[mem, 1] 0, 100
    % We generate a random number between 0 and 100, stored at mem#1

    repeat:
    % Repeat until the number is found

        push[param] 'Please input a number between 0 and 100:'
        % Tell the player to input something

        sys 1
        % System call: 1 = output

        pop [param]
        % Good habit to pop once everything has been used

        sys[temp, 1] 2
        % System call: 2 = input. We then store the value at temp#1

        stoi[temp, 1] [temp, 1]
        % We convert temp#1 into an integer because `sys 2` gives it us as a string. If the conversion fails (invalid input)

        cmp [mem, 1], [temp, 1]
        % We compare mem#1 and temp#1

        jwl lower
        % if mem#1 < temp#1 we go to lower:

        jwg greater
        % if mem#1 > temp#1 we got to greater:

        % else the number is the correct one

    push[param] 'You found the correct number !\n'
    % Let's tell the player he found the number

    sys 1
    % System call: 1 = output

    pop [param]
    % Good habit to pop once everything has been used

    free [temp, 1]
    free [mem, 1]
    % Just delete the data because we don't need them anymore
 
    int 0
    % Also still needed



greater:

    push[param] 'The number you are trying to guess is greater than the number you wrote.\n'
    % We push this long string inside the parameters, so that we can output it

    sys 1
    % System call: 1 = output values in parameters. Be aware it takes them in reverse order

    pop [param]
    % Better to remove the value from the parameters before doing anything else

    jmp repeat
    % We go to repeat: because the number has not been found



lower:

    push[param] 'The number you are trying to guess is lower than the number you wrote.\n'
    % We push this long string inside the parameters, so that we can output it

    sys 1
    % System call: 1 = output values in parameters. Be aware it takes them in reverse order

    pop [param]
    % Better to remove the value from the parameters before doing anything else

    jmp repeat
    % We go to repeat: because the number has not been found
```
The indentation is not necessary. You can get rid of it. It just makes it a bit more clear what "block" is what.

> No more questions ?

If you want to ask me some questions, you can ask them directly to me on [Discord](https://www.discordapp.com). I will asnwer them with no problem. <br>
If you want some features added, feel free to suggest them to me, or to someone who already talked to me before. <br><br>

## Languages used:
- C++ = VM/Compiler (`.cpp`)
- Snow* = examples/tests (`.sssc`)
- ColdWater = Snow* bytecode (`.cwsc`)
<br><br>

## Credits to:
- People who are helping me whenever I need help
- People who have faith in me
- People who are encouraging me programming/making this language