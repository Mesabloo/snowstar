#!/bin/bash

java -jar ext/antlr/antlr-4.7.1-complete.jar SnowStarLexer.g4 -Dlanguage=Cpp -no-listener -visitor -o lib/antlr

java -jar ext/antlr/antlr-4.7.1-complete.jar SnowStarParser.g4 -Dlanguage=Cpp -no-listener -visitor -o lib/antlr
