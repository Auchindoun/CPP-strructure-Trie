#include <iostream>
using namespace std;

const int size_of_alphabet = 26;

struct TrieNode
{
	struct TrieNode *children[size_of_alphabet]; //дети(: заготовки под буквы
	bool is_end_of_word; //метка конца слова
};

struct TrieNode *AddNode() //добавление узла
{
	struct TrieNode *pnode = new TrieNode;

	pnode->is_end_of_word = false;

	for (int i = 0; i < size_of_alphabet; i++)
		pnode->children[i] = NULL;

	return pnode;
}


void InsertWord(struct TrieNode *root, string key) //создаём из узлов слово
{
	struct TrieNode *crawl = root;

	for (int i = 0; i < key.length(); i++)
	{
		int index = key[i] - 'a'; //ASCII приколы (удобная индексация для каждой буквы алфавита)
		if ((crawl->children[index]) == NULL)
		{
			crawl->children[index] = AddNode();
		}
		
		crawl = crawl->children[index]; //идём дальше
	}
	
	crawl->is_end_of_word = true; //чтобы в them не найти the и т.п.
}


bool SearchWord(struct TrieNode *root, string key) //проверяем наличие слова
{
	struct TrieNode *crawl = root;

	for (int i = 0; i < key.length(); i++)
	{
		int index = key[i] - 'a';
		if ((crawl->children[index]) == NULL)
		{
			return false;
		}
		crawl = crawl->children[index];
	}

	return (crawl->is_end_of_word);
}

bool DeleteWord(struct TrieNode *root, string key) //удаляем слово
{
	struct TrieNode *crawl = root;

	for (int i = 0; i < key.length(); i++)
	{
		int index = key[i] - 'a';
		if ((crawl->children[index]) == NULL)
		{
			return false; //слова для удаления нет
		}
		crawl = crawl->children[index];
	}
    
    if (crawl->is_end_of_word == true)
    {
        crawl->is_end_of_word = false;
        return true;
    }
    else
    {
        return false; //слова для удаления нет
    }
}



int main()
{

	string keys[] = {"them", "infinite", "eclipse", "has", "begun"};

	struct TrieNode *root = AddNode();
	int n = sizeof(keys)/sizeof(keys[0]);

	for (int i = 0; i < n; i++)
	{
		InsertWord(root, keys[i]);
	}
	
	SearchWord(root, "the") ? cout << "Yes, the word |the| in the trie\n" : cout << "No, the word |the| not in the trie\n";
	SearchWord(root, "eclipse") ? cout << "Yes, the word |eclipse| in the trie\n" : cout << "No, the word |eclipse| not in the trie\n";
	DeleteWord(root, "eclips") ? cout << "Deleted word |eclips|\n" : cout << "No word |eclips| in trie\n";
	DeleteWord(root, "eclipse") ? cout << "Deleted word |eclipse|\n" : cout << "No word |eclipse| in trie\n";
	SearchWord(root, "eclipse") ? cout << "Yes, the word |eclipse| in the trie\n" : cout << "No, the word |eclipse| not in the trie\n";
	SearchWord(root, "cake") ? cout << "Yes, the word |cake| in the trie\n" : cout << "No, the word |cake| not in the trie\n";
	SearchWord(root, "life") ? cout << "Yes, the word |life| in the trie\n" : cout << "No, the word |life| not in the trie\n";
	return 0;
}