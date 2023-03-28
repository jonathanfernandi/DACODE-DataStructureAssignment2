#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct Game {
	char name[31];
	char developer[21];
	char genre[11];
	int year;
	float price;
	int height;
	Game *left, *right;
} *game = NULL;

Game *newGame(char *name, char *developer, char *genre, int year, float price) {
	Game *addGame = (Game*)malloc(sizeof(Game));
	strcpy(addGame->name, name);
	strcpy(addGame->developer, developer);
	strcpy(addGame->genre, genre);
	addGame->year = year;
	addGame->price = price;
	addGame->height = 1;
	addGame->left = addGame->right = NULL;
	return addGame;
}

int getMax(int left, int right) {
	if(left > right) {
		return left;
	}
	return right;
}

int getHeight(Game *curr) {
	if(curr == NULL) {
		return 0;
	}
	return curr->height;
}

int getWeight(Game *curr) {
	if(curr == NULL) {
		return 0;
	}
	return (getHeight(curr->left) - getHeight(curr->right));
}

Game *rightRotate(Game *curr) {
	Game *tempLeft = curr->left;
	Game *tempRight = tempLeft->right;
	tempLeft->right = curr;
	curr->left = tempRight;
	curr->height = getMax(getHeight(curr->left), getHeight(curr->right)) + 1;
	tempLeft->height = getMax(getHeight(tempLeft->left), getHeight(tempLeft->right)) + 1;
	return tempLeft;
}

Game *leftRotate(Game *curr) {
	Game *tempRight = curr->right;
	Game *tempLeft = tempRight->left;
	tempRight->left = curr;
	curr->right = tempLeft;
	curr->height = getMax(getHeight(curr->left), getHeight(curr->right)) + 1;
	tempRight->height = getMax(getHeight(tempRight->left), getHeight(tempRight->right)) + 1;
	return tempRight;
}

Game *balanceTree(Game *curr) {
	curr->height = getMax(getHeight(curr->left), getHeight(curr->right)) + 1;
	int weight = getWeight(curr);
	
	if((weight > 1) && (getWeight(curr->left) >= 0)) {
		return rightRotate(curr);
	}
	if((weight > 1) && (getWeight(curr->left) < 0)) {
		curr->left = leftRotate(curr->left);
		return rightRotate(curr);
	}
	
	if((weight < -1) && (getWeight(curr->right) <= 0)) {
		return leftRotate(curr);
	}
	if((weight < -1) && (getWeight(curr->right) > 0)) {
		curr->right = rightRotate(curr->right);
		return leftRotate(curr);
	}
	
	return curr;
}

Game *insertGame(Game *curr, char *name, char *developer, char *genre, int year, float price) {
	if(!curr) {
		curr = newGame(name, developer, genre, year, price);
	} else if(strcmp(name, curr->name) < 0) {
		curr->left = insertGame(curr->left, name, developer, genre, year, price);
	} else if(strcmp(name, curr->name) > 0) {
		curr->right = insertGame(curr->right, name, developer, genre, year, price);
	} else {
		return curr;
	}
	
	return balanceTree(curr);
}

void insert() {
	system("cls");
	
	char name[31];
	while(1) {
		printf("Insert game name [between 3 to 30 characters] : ");
		scanf("%[^\n]", name); getchar();
		
		int len = strlen(name);
		if((len >= 3) && (len <= 30)) {
			break;
		}
	}
	
	char developer[21];
	while(1) {
		printf("Insert developer [ends with ' inc.' || between 6 to 20 characters] : ");
		scanf("%[^\n]", developer); getchar();
		
		int len = strlen(developer);
		if((len >= 6) && (len <= 20)) {
			if((developer[len - 5] == ' ') && (developer[len - 4] == 'i') && (developer[len - 3] == 'n') && (developer[len - 2] == 'c') && (developer[len - 1] == '.')) {
				break;
			}
		}
	}
	
	char genre[11];
	while(1) {
		printf("Insert game genre [RPG || FPS || Simulation] : ");
		scanf("%[^\n]", genre); getchar();
		
		if((strcmp(genre, "RPG") == 0) || (strcmp(genre, "FPS") == 0) || (strcmp(genre, "Simulation") == 0)) {
			break;
		}
	}
	
	int year;
	while(1) {
		printf("Insert release year [1980 - 2023] : ");
		scanf("%d", &year); getchar();
		
		if((year >= 1980) && (year <= 2023)) {
			break;
		}
	}
	
	float price;
	while(1) {
		printf("Insert price [2.00 - 1000.00] : ");
		scanf("%f", &price); getchar();
		
		if((price >= 2.00) && (price <= 1000.00)) {
			break;
		}
	}
	
	game = insertGame(game, name, developer, genre, year, price);
	
	system("cls");
	printf("Game added!\nPress enter to continue . . ."); getchar();
}

void preorder(Game *curr) {
	if(!curr) {
		return;
	}
	printf("| %-31s| %-21s| %-16s| %d  |%7.2f |\n", curr->name, curr->developer, curr->genre, curr->year, curr->price);
	preorder(curr->left);
	preorder(curr->right);
}

void inorder(Game *curr) {
	if(!curr) {
		return;
	}
	inorder(curr->left);
	printf("| %-31s| %-21s| %-16s| %d  |%7.2f |\n", curr->name, curr->developer, curr->genre, curr->year, curr->price);
	inorder(curr->right);
}

void postorder(Game *curr) {
	if(!curr) {
		return;
	}
	postorder(curr->left);
	postorder(curr->right);
	printf("| %-31s| %-21s| %-16s| %d  |%7.2f |\n", curr->name, curr->developer, curr->genre, curr->year, curr->price);
}

void view() {
	system("cls");
	
	if(!game) {
		printf("No data!\nPress enter to continue . . ."); getchar();
		return;
	}
	
	puts("View Menu\n============\n1. Preorder\n2. Inorder\n3. Postorder\n0. Back");
	
	int displayViewMode = 1;
	while(displayViewMode) {
		int option;
		printf(">> ");
		scanf("%d", &option); getchar();
		
		puts("============================================================================================\n| Name                           | Developer            | Genre           | Year  | Price  |\n============================================================================================");
		
		switch(option) {
			case 1: {
				preorder(game);
				displayViewMode = 0;
				break;
			}
			
			case 2: {
				inorder(game);
				displayViewMode = 0;
				break;
			}
			
			case 3: {
				postorder(game);
				displayViewMode = 0;
				break;
			}
			
			case 0: {
				return;
				break;
			}
		}
	}
	printf("============================================================================================\nPress enter to continue . . ."); getchar();
	return;
}

Game *predecessor(Game *curr) {
	if(!curr->left) {
        return curr;
    }
	
	Game *temp = curr->left;
	while(temp->right) {
		temp = temp->right;
	}
	return temp;
}

Game *search(Game *curr, char *name) {
	if(!curr) {
		return NULL;
	} else if(strcmp(name, curr->name) < 0) {
		return search(curr->left, name);
	} else if(strcmp(name, curr->name) > 0) {
		return search(curr->right, name);
	}
	return curr;
}

Game *removeGame(Game *curr, char *name) {
	if(!curr) {
		return curr;
	} else if(strcmp(name, curr->name) < 0) {
		curr->left = removeGame(curr->left, name);
	} else if(strcmp(name, curr->name) > 0) {
		curr->right = removeGame(curr->right, name);
	} else {
		if(!curr->right && !curr->left) {
			free(curr);
			curr = NULL;
			return NULL;
		} else if(!curr->left || !curr->right) {
			Game *temp;
			if(!curr->left) {
				temp = curr->right;
			} else {
				temp = curr->left;
			}
			free(curr);
			curr = NULL;
			return temp;
		} else {
			Game *temp = predecessor(curr->left);
			strcpy(curr->name, temp->name);
			strcpy(curr->developer, temp->developer);
			strcpy(curr->genre, temp->genre);
			curr->year = temp->year;
			curr->price = temp->price;
			curr->left = removeGame(curr->left, temp->name);
			return balanceTree(curr);
		}
	}
	return balanceTree(curr);
}

Game *removeAll(Game *curr) {
	if(!curr) {
        return NULL;
    }
    curr->left = removeAll(curr->left);
    curr->right = removeAll(curr->right);
    free(curr);
    return NULL;
}

void deleteGame() {
	system("cls");
	
	if(!game) {
		printf("No data!\nPress enter to continue . . ."); getchar();
		return;
	}
	
	puts("============================================================================================\n| Name                           | Developer            | Genre           | Year  | Price  |\n============================================================================================");
	inorder(game);
	printf("============================================================================================\nInsert game name [0 to back] : ");
	
	char name[31];
	scanf("%[^\n]", name); getchar();
	
	if(strcmp(name, "0") == 0) {
		return;
	} else {
		Game *find = search(game, name);
		if(!find) {
			printf("Game not found!\nPress enter to continue . . ."); getchar();
			return;
		}
		
		game = removeGame(game, name);
		printf("Game deleted!\nPress enter to continue . . ."); getchar();
	}
}

void deleteAll() {
	system("cls");
	
	while(1) {
		char removeCommand[2];
		printf("Are you sure? [case insensitive | Y/N] : ");
		scanf("%[^\n]", removeCommand); getchar();
		if(strcmpi(removeCommand, "Y") == 0) {
			game = removeAll(game);
			printf("Press enter to continue . . ."); getchar();
			return;
		} else if(strcmpi(removeCommand, "N") == 0) {
			printf("Press enter to continue . . ."); getchar();
			return;
		}
	}
}

void menu() {
	while(1) {
		system("cls");
		puts("GameBros\n===========\n1. Insert new game\n2. Delete game\n3. View all games\n4. Delete all\n5. Exit");
		
		int displayMenu = 1;
		while(displayMenu) {
			int option;
			printf(">> ");
			scanf("%d", &option); getchar();
			
			switch(option) {
				case 1: {
					insert();
					displayMenu--;
					break;
				}
				
				case 2: {
					deleteGame();
					displayMenu--;
					break;
				}
				
				case 3: {
					view();
					displayMenu--;
					break;
				}
				
				case 4: {
					deleteAll();
					displayMenu--;
					break;
				}
				
				case 5: {
					return;
				}
			}
		}
	}
}

int main() {
	game = insertGame(game, "Balorent", "Chaos inc.", "FPS", 2020, 2.00);
	game = insertGame(game, "Final Spritesy IX", "Round Enix inc.", "RPG", 2004, 5.25);
	game = insertGame(game, "Grand Auto III", "Popsun inc.", "RPG", 2000, 2.50);
	game = insertGame(game, "Phone of Duty", "Inactivision inc.", "FPS", 2016, 7.50);
	game = insertGame(game, "Suikodamn 2", "Komina inc.", "RPG", 1990, 2.50);
	game = insertGame(game, "The Simps 4", "eak inc.", "Simulation", 2014, 4.20);
	
	menu();
	
	system("cls");
	puts("Thank you! :D");
	
	return 0;
}
