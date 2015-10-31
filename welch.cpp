#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

#define SYMBOL 256

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
			std::cout << i + 1 << " " << word << '\n';
			break;
		}
	}
	
	return;
}

int main() {
//	char *alphabet = (char *) "TARAATATAAARAAA";
	char *alphabet = (char *) "wabba_wabba_wabba_wabba_woo_woo_woo";
	
	char *init_alpha = (char *) "_abow";
	
	std::vector<char*> dictionary;
	
//	for (int i=0; i<SYMBOL; i++) {
//		char *new_word = new char[2];
//		new_word[0] = (char) i;
//		new_word[1] = '\0';
//		
//		dictionary.push_back(new_word);
//	}
	
	for (int i=0; i<5; i++) {
		char *new_word = new char[2];
		new_word[0] = init_alpha[i];
		new_word[1] = '\0';
		
		dictionary.push_back(new_word);
	}
	
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
	
	return 0;
}
