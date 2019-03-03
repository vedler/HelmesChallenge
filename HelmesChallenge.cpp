#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <chrono>
#include <locale>
#include <codecvt>
#include <string>
#include <cstdio>
#include <cwchar>
using namespace std;

#define CHARMAP_SIZE 55
#define CHARMAP_SIZEOF_SIZE 220

// We presume that the usage of special characters are to be considered in finding the anagrams based on this answer:
//  * When the input is multi-word, then its expected to match a multi-word anagram (the basis being that the input
//       contains space, the output should also contain space).
// ... and equally as much the definition of the exercise itself:
//  * The result should be an executable application, that finds all anagrams for provided word from a provided
//       dictionary as fast as possible.
// ... meaning that if the input word includes for example a dash ('-'), the anagram must contain one as well

// Another presumption is about the case sensitivity:
//  * Text case sensitivity - shall one put attention on that? No.
// ... by this we presume that no text manipulation in terms of capitalization and so on should be handled, 
//		i.e. the case of "Harju" not returning "urjah" as an anagram is correct behaviour, as no case insenitive searches are needed

const int get_char_index(const wchar_t& ch) {

	// Squeeze everything out for performance
	// ... yes this is not maintainable code, but thats not in the requirements :D
	switch (ch) {
		case L' ': return 0;
		default: 
		case L'!': return 1;
		case L'\'': return 2;
		case L'-': return 3;
		case L'A': return 4;
		case L'B': return 5;
		case L'C': return 6;
		case L'D': return 7;
		case L'E': return 8;
		case L'G': return 9;
		case L'H': return 10;
		case L'I': return 11;
		case L'J': return 12;
		case L'K': return 13;
		case L'N': return 14;
		case L'P': return 15;
		case L'R': return 16;
		case L'S': return 17;
		case L'T': return 18;
		case L'U': return 19;
		case L'V': return 20;
		case L'a': return 21;
		case L'b': return 22;
		case L'c': return 23;
		case L'd': return 24;
		case L'e': return 25;
		case L'f': return 26;
		case L'g': return 27;
		case L'h': return 28;
		case L'i': return 29;
		case L'j': return 30;
		case L'k': return 31;
		case L'l': return 32;
		case L'm': return 33;
		case L'n': return 34;
		case L'o': return 35;
		case L'p': return 36;
		case L'q': return 37;
		case L'r': return 38;
		case L's': return 39;
		case L't': return 40;
		case L'u': return 41;
		case L'v': return 42;
		case L'w': return 43;
		case L'x': return 44;
		case L'y': return 45;
		case L'z': return 46;
		case L'ä': return 47;
		case L'é': return 48;
		case L'õ': return 49;
		case L'ö': return 50;
		case L'ü': return 51;
		case L'Š': return 52;
		case L'š': return 53;
		case L'ž': return 54;
	}
}

void build_char_counter(int (&chars)[CHARMAP_SIZE], const wstring& inp) {
	memset(chars, 0, sizeof(chars));  // 55 * 4 = 220
	for (const wchar_t& c : inp) {
		++chars[get_char_index(c)];
	}
}

bool are_chars_equal(const int (&a)[CHARMAP_SIZE], const int(&b)[CHARMAP_SIZE])
{
	for (int i = 0; i < CHARMAP_SIZE; i++)
	{
		if (a[i] != b[i])
		{
			return false;
		}
	}
	return true;
}

// https://stackoverflow.com/a/25142564
std::wstring s2ws(const std::string& s) {
    std::string curLocale = setlocale(LC_ALL, ""); 
    const char* _Source = s.c_str();
    size_t _Dsize = mbstowcs(NULL, _Source, 0) + 1;
    wchar_t *_Dest = new wchar_t[_Dsize];
    wmemset(_Dest, 0, _Dsize);
    mbstowcs(_Dest,_Source,_Dsize);
    std::wstring result = _Dest;
    delete []_Dest;
    setlocale(LC_ALL, curLocale.c_str());
    return result;
}

int main(int argc, char *argv[]) {
	auto start = chrono::steady_clock::now();
	setlocale(LC_ALL, "");
	std::locale::global (std::locale ("et_EE.UTF-8"));

	string fpath = argv[1];
	string n_inp = argv[2];
	wstring inp = s2ws(n_inp);
	auto inp_len = inp.length();
	int inp_chars[CHARMAP_SIZE] = {0};
	// Build input character list
	build_char_counter(inp_chars, inp);

	vector<wstring> result;
	int compare_chars[CHARMAP_SIZE] = {0};

	wifstream file(fpath);
	locale loc("et_EE.UTF-8");
	file.imbue(loc);

	if (file.is_open()) {
		wstring line;
		while (getline(file, line)) {
			if (inp_len != line.length()) {
				continue;
			}
			build_char_counter(compare_chars, line);

			if (are_chars_equal(inp_chars, compare_chars)) {
				if (line != inp) {
					result.push_back(line);
				}
			}
		}
		
		file.close();
	}

	auto end = chrono::steady_clock::now();
	cout << chrono::duration <double, micro>(end - start).count();
	for (const auto& elem : result) {
		printf(",%ls", elem.c_str());
		
	}
	wcout << endl;
	return 0;
}



