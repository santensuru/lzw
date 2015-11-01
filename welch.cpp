#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

#define SYMBOL 64

std::vector<int> token;
int LENGTH = 0;

bool linear_search(std::vector<char*> *dictionary, char *word) {
	for (int i=0; i<(*dictionary).size(); i++) {
		if (strcmp((*dictionary).at(i), word) == 0) {
			return true;
		}
	}
	
	return false;
}

void print_token(std::vector<char*> *dictionary, char *word) {
	for (int i=0; i<(*dictionary).size(); i++) {
		if (strcmp((*dictionary).at(i), word) == 0) {
			std::cout << "(" << i + 1 << "," << word << ") ";
//			std::cout << i + 1 << " ";
			
			int new_token = i + 1;
			
			token.push_back(new_token);
			
			break;
		}
	}
	
	return;
}

void print_dictionary(std::vector<char*> *dictionary) {
	std::cout << "\n\n";
	
	for (int i=0; i<(*dictionary).size(); i++) {
		std::cout << "(" << i + 1 << "," << (*dictionary).at(i) << ") ";
	}
	
	std::cout << '\n';
	
	return;
}

void to_bit_array(std::vector<char> *bit_array, char *input) {
	for (int i=0; i<strlen(input); i++) {
		char temp = input[i];
		for (int j=0; j<8; j++) {
			if ((temp & 0x80) == 0x80) {
				(*bit_array).push_back(0x01);
			} else {
				(*bit_array).push_back(0x00);
			}
			temp <<= 1;
		}
	}
	
	return;
}

void to_base_64(char *ascii, unsigned char *base_64, int *length) {
	
//	std::cout << ascii << '\n';
	
//	for (int i=0; i<strlen(ascii); i++) {
//		std::cout << (int) ascii[i] << " ";
//	}
	
//	std::cout << '\n';
	
//	unsigned char *base_64 = new unsigned char[(int) (strlen(ascii) *8.0 /6 +0.5)];
	
	int l = 0;
	int k = 0;
	unsigned char temp_64 = 0x00;
	for (int i=0; i<*length; i++) {
		char temp = ascii[i];
		
		for (int j=0; j<8; j++) {
			if (k == 6) {
				base_64[l] = temp_64;
				std::cout << (int) base_64[l] << " ";
				l++;
				k=0;
				temp_64 = 0x00;
			}
			
			if ((temp & 0x80) == 0x80) {
				temp_64 ^= 0x01;
			}
			
			if (k < 5) {
				temp_64 <<= 1;
			}
			
			k++;
			
			temp <<= 1;
			
//			std::cout << i << " " << k << '\n';
		}
	}
	
	while (k < 5) {
		temp_64 <<= 1;
		k++;
	}
	base_64[l] = temp_64;
	
//	std::cout << " " << k << '\n';
	std::cout << (int) base_64[l] << " ";
	
	*length = ++l;
	
//	std::cout << l << " " << (int) (strlen(input) *8.0 /6 +0.5);
	
	return;
}

void to_ascii(unsigned char *base_64, char *ascii, int *length) {
	
	int l = 0;
	int k = 0;
	char temp_ascii = 0x00;
	for (int i=0; i<*length; i++) {
		unsigned char temp = base_64[i];
		
		for (int j=0; j<6; j++) {
			if (k == 8) {
				ascii[l] = temp_ascii;
				std::cout << (int) ascii[l] << " ";
				l++;
				k=0;
				temp_ascii = 0x00;
			}
			
			if ((temp & 0x80) == 0x80) {
				temp_ascii ^= 0x01;
			}
			
			if (k < 7) {
				temp_ascii <<= 1;
			}
			
			k++;
			
			temp <<= 1;
			
//			std::cout << i << " " << k << '\n';
		}
	}
	
	while (k < 7) {
		temp_ascii <<= 1;
		k++;
	}
	ascii[l] = temp_ascii;
	
//	std::cout << " " << k << '\n';
	std::cout << (int) ascii[l] << " ";
	
	*length = ++l;
	
//	std::cout << l << " " << (int) (strlen(input) *8.0 /6 +0.5);
	
	return;
}

/**
 * COMPRESS
 */

void compress() {
//	char *alphabet = (char *) "TARAATATAAARAAA";
	char *alphabet = (char *) "wabba_wabba_wabba_wabba_woo_woo_woo";
//	char *alphabet = (char *) "SAYA SUKA SAMA SITU SEBAB SITU SUKA SENYUM SAMA SAYA";
	
//	char *init_alpha = (char *) "_abow";
	
	std::vector<char*> dictionary;
	
	for (int i=0; i<SYMBOL; i++) {
		char *new_word = new char[2];
		new_word[0] = (char) i;
		new_word[1] = '\0';
		
		dictionary.push_back(new_word);
	}
	
//	for (int i=0; i<5; i++) {
//		char *new_word = new char[2];
//		new_word[0] = init_alpha[i];
//		new_word[1] = '\0';
//		
//		dictionary.push_back(new_word);
//	}
	
	unsigned char *out = new unsigned char[(int) (strlen(alphabet) *8.0 /6 +0.5)];
	int length = strlen(alphabet);
	to_base_64(alphabet, out, &length);
	LENGTH = length;
	std::cout << "\n\n";
	for (int i=0; i<length; i++) {
		std::cout << (int) out[i] << " ";
	}
	std::cout << "\n\n";
	
	char word[SYMBOL];
	memset(word, 0, SYMBOL);
	char character[2];
	character[1] = '\0';
	
	std::cout << alphabet << '\n';
	
	for (int i=0; i<length + 1; i++) {
		if (i < length) {
			character[0] = out[i];
		} else {
			character[0] = '\0';
		}
		
		char *temp = new char[strlen(word)];
		
		strcpy(temp, word);
		
		strcat(word, character);
		
		if (!linear_search(&dictionary, word)) {
			char *new_word = new char[strlen(word)];
			strcpy(new_word, word);
			
			print_token(&dictionary, temp);
			
			dictionary.push_back(new_word);
			strcpy(word, character);
			
		} else {
			
			if (i == length)
				print_token(&dictionary, temp);
			
		}
	}
	
	print_dictionary(&dictionary);
	
	return;
}

/**
 * DECOMPRESS
 */

void decompress() {
//	int token[] = { 5, 2, 3, 3, 2, 1, 6, 8, 10, 12, 9, 11, 7, 16, 5, 4, 4, 11, 21, 23, 4 };
	
//	char *init_alpha = (char *) "_abow";
	
	std::vector<char*> dictionary;
	
	for (int i=0; i<SYMBOL; i++) {
		char *new_word = new char[2];
		new_word[0] = (char) i;
		new_word[1] = '\0';
		
		dictionary.push_back(new_word);
	}
	
//	for (int i=0; i<5; i++) {
//		char *new_word = new char[2];
//		new_word[0] = init_alpha[i];
//		new_word[1] = '\0';
//		
//		dictionary.push_back(new_word);
//	}
	
	char word[SYMBOL];
	memset(word, 0, SYMBOL);
	char character[SYMBOL];
	memset(character, 0, SYMBOL);
	
//	for (int i=0; i<sizeof(token)/4; i++) {
	for (int i=0; i<token.size(); i++) {
		std::cout << token[i] << " ";
	}
	
	std::cout << '\n';
	
//	for (int i=0; i<sizeof(token)/4; i++) {
	for (int i=0; i<token.size(); i++) {
		strcpy(character, dictionary.at(token[i] - 1));
		
		char *temp = new char[strlen(word)];
		
		strcpy(temp, word);
		
		strcat(word, character);
		
		if (!linear_search(&dictionary, word)) {
			
			while (!linear_search(&dictionary, word)) {
				strcpy(temp, word);
				word[strlen(word) - 1] = '\0';
			}
			
			char *new_word = new char[strlen(word)];
			strcpy(new_word, temp);
			
			dictionary.push_back(new_word);
			strcpy(word, character);
			std::cout << character;
			
		} else {
			if (i == 0) {
				std::cout << character;
			}
			
		}
	}
	
	print_dictionary(&dictionary);
	
	return;
}

int main() {
	compress();
//	
	std::cout << '\n';
//	
	decompress();
	
//	char *alphabet = (char *) "wabba_wabba_wabba_wabba_woo_woo_woo";
//	char *out = new char[(int) (strlen(alphabet) *8.0 /6 +0.5)];
//	to_base_64(alphabet, out);
	
//	std::cout << alphabet << '\n';
	
//	for (int i=0; i<sizeof(out); i++) {
//		printf("%2x", out[i]);
//	}
	
	return 0;
}
