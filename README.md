# HelmesChallenge
Submission for the Helmes coding challenge by Kristjan Vedler


## Compilation flags
Code was compiled with the following G++ command:

`g++ -Ofast -frename-registers -funroll-loops -fprofile-use -fopenmp -D_GLIBCXX_PARALLEL -m64 -finput-charset=UTF8 -std=c++11 HelmesChallenge.cpp -o bin/anagramApp`

## Other prerequisites
Funnily enough, looking back at it I should've probably used Java instead, so I would've been on time (performance vs coding time). Forgot that file encoding is a nightmare in cross-platform C++. Algorithm outline in Python took an hour, writing it into C++ after not having touched the language for a long while: 6h.

And with that being said, the only prerequisite would be for the **lemma file to be in UTF-8 encoding**, instead of ANSI/cp1257.
