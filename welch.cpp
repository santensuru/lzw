#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

#define SYMBOL 256

std::vector<int> token;

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
	
	char word[SYMBOL];
	memset(word, 0, SYMBOL);
	char character[2];
	character[1] = '\0';
	
	std::cout << alphabet << '\n';
	
	for (int i=0; i<strlen(alphabet) + 1; i++) {
		if (i < strlen(alphabet)) {
			character[0] = alphabet[i];
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
			
			if (i == strlen(alphabet))
				print_token(&dictionary, temp);
			
		}
	}
	
	print_dictionary(&dictionary);
	
	return;
}

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
	
	std::cout << '\n';
	
	decompress();
	
	return 0;
}
