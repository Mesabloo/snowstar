# <img src="https://mesabloo.github.io/snowstar-lang/icons/snowstar_64x64.png" type="image/png" height="64" widht="64" style="vertical-align:middle"/> <b>Snow*, 4th generation</b>

## <u>What is Snow* ?</u>

Snow* is a programming language which knew several generations:

- The first one called [RainDrop](https://mesabloo.github.io/snowstar-lang/about.html#raindrop) was an Object-Oriented programming language.<br>
It really never took off in the first place, being always a theoritical project more than anything else.

- The second one was called [#*](https://mesabloo.github.io/snowstar-lang/about.html#sharpstar) (SharpStar)<br>
It was an ASM-like language with some inconsistences (registers holding only up to one value).<br>
It was the real first programming language made here from nothing. The VM was slow, the compiler inefficient.

- The third generation was the first called [Snow*](https://mesabloo.github.io/snowstar-lang/about.html#snowstar1).<br>
It was still an ASM-like, but more developped than the previous one. It contained more instructions, the VM was faster, the compiler more efficient.

- The fourth generation, [Snow*](https://mesabloo.github.io/snowstar-lang/about.html#snowstar2), an Object-Oriented programming language.<br>
This generation is built with ANTLR and LLVM (later) to offer power and native compilation.

## <u>Behind Snow*, a developer, Mesabloo.</u>

I've been working on Snow* from the second generation until now since the beginning of June 2018. I wanted to create my own programming language since the beginning of October/November of 2017. ([RainDrop](https://mesabloo.github.io/snowstar-lang/about.html#raindrop) came to life around this time) Because I never really understood how they work, and because I wanted to compile RainDrop into ASM (the Assembly Language), it didn't go far enough to actually be considered a good "experience" (just a basic Lexer + a simple compiling process until the AST generation, where I got stuck).<br>
After this, I switched from Java to C++ and completely changed the syntax of the language, creating my first "ASM-like" language.<br>
And now, I changed it again, and I'm ready to go for it.

## <u>What about a free sample ?</u>

Samples can be found [here](https://mesabloo.github.io/snowstar-lang/about.html#sample-snowstar2) but I will post here a simple `Hello, World!` program made in Snow* 4th gen:

<pre>
.:
    Declaration of the main method. The parameters of it are unrequired, you may write it without.

    @param `argc` is of type int8 ;
    @param `argv` is of type list&lt;string&gt; ;
    @return int32
:.

§ So that we can use `print()`.
import stdio;

int32 main(int8 argc, list&lt;string&gt; argv) {
    print("Hello, World!")
    § We print "Hello, World!" in the console.
    return 0
    § We return from the function, with an int32 value.
}

.:
    This sample is not yet compilable.
    Don't try to compile it, you'll get many errors.
:.
</pre>

## <u>Special thanks to</u>
People from many Discord servers helping me when I need help. Links to them will be put down below.
- __NaN - Not a Name__ : a francophone programming related Discord server, very nice and helpful:<br>
[![Discord bagde](https://img.shields.io/badge/Discord-Join%20us!-blue.svg)](https://discord.gg/zcWp9sC)
- __The Programmer's Hangout__ : a nice community about programming with many developers from all around the world:<br> [![Discord bagde](https://img.shields.io/badge/Discord-Join%20us!-blue.svg)](https://discord.gg/programming)
- __Atelier - Création d'un langage de programmation__ : a francophone Discord server about the creation of programming languages, with some languages creator such as me.<br> [![Discord bagde](https://img.shields.io/badge/Discord-Join%20us!-blue.svg)](https://discord.gg/8VhspcJ)
- Some other servers where people helped me mentally by being here for me whenever I needed some comfort.
- My friends who put some hope in my project.
- All the people who starred this repository so far. It's really pleasant.

## <u>Software used with their licenses</u>
- [__ANTLR4__](https://github.com/antlr/antlr4), released under BSD-3 clause license, Copyright (c) 2012-2017 The ANTLR Project. All rights reserved
- [__termcolor__](https://github.com/ikalnytskyi/termcolor), released under BSD license, Copyright (c) 2013 Ihor Kalnytskyi
- [__LLVM__](https://github.com/llvm-mirror/llvm), released under Open Source license, Copyright (c) 2003-2018 University of Illinois at Urbana-Champaign.
All rights reserved.
- [__Tiny Process Library__](https://gitlab.com/eidheim/tiny-process-library), released under the MIT License, Copyright (c) 2015-2018 Ole Christian Eidheim