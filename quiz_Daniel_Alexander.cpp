#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

const int hashSize = 55;
int count = 1;

struct Product{
	char name[30];
	char cate[10];
	char brand[10];
	long long int stock;
	long long int price;
	char id[10];
	Product *next;
};

Product *hash[hashSize + 1];

Product *createNewProduct(char name[], char cate[], char brand[], long long int stock, long long int price, char id[]){
	Product *curr = (Product*)malloc(sizeof(Product));
	strcpy(curr->name, name);
	strcpy(curr->cate, cate);
	strcpy(curr->brand, brand);
	curr->stock = stock;
	curr->price = price;
	strcpy(curr->id, id);
	curr->next = NULL;
	return curr;
}

int hashFunction(char id[]){
	int total = id[3]*10 + id[4];
	return (total-1)%hashSize;
}

void insertHash(char name[], char cate[], char brand[], long long int stock, long long int price, char id[]){
	Product *insert = createNewProduct(name, cate, brand, stock, price, id);
	int key = hashFunction(id);
	if(hash[key] == NULL){
		hash[key] = insert;
	}
	else {
		Product *temp = hash[key];
		while(temp->next != NULL){
			temp = temp->next;
		}
		temp->next = insert;
	}
}

void printProduct(){
	for(int i=0; i<hashSize; i++){
		Product *temp = hash[i];
		if (hash[i] == NULL){
			return;
		}
		printf("===========================================================================\n");
			printf("| No |    ID   |  Product Name  |   Category  |  Brand  | Stock |  Price  |\n");
			printf("===========================================================================\n");
		while (temp != NULL){
			printf("| %2d | %7s | %14s | %11s | %7s | %5lld | %7lld |\n", i+1, temp->id, temp->name, temp->cate, temp->brand, temp->stock, temp->price);
			temp = temp->next;
		}
		printf("===========================================================================\n");
	}
}

int validateProductName(char name[]){
	int len = strlen(name);
	if(len >= 5 && len <= 24){
		return 1;
	}
	return 0;
}

int validateProductCate(char cate[]){
	if(strcmp(cate, "Shoes") == 0 || strcmp(cate, "Bag") == 0){
		return 1;
	}
	return 0;
}

int validateProductBrand(char brand[]){
	if(strcmp(brand, "Nike") == 0 || strcmp(brand, "Adidas") == 0){
		return 1;
	}
	return 0;
}

void insertProduct(){
	char name[30];
	char cate[10];
	char brand[10];
	long long int stock;
	long long int price;
	char id[10];
	do{
		printf("Input Product Name [5-24 characters]: ");
		scanf("%[^\n]", name); getchar();
	}while(!validateProductName(name));
	
	do{
		printf("Choose Category [Shoes | Bag] (case sensitive): ");
		scanf("%[^\n]", cate); getchar();
	}while(!validateProductCate(cate));
	
	do{
		printf("Choose Brand [Nike | Adidas] (case sensitive) : ");
		scanf("%[^\n]", brand); getchar();
	}while(!validateProductBrand(brand));
	
	do{
		printf("Input Stock [ 50 - 150 ] : ");
		scanf("%lld", &stock); getchar();
	}while(stock < 50 || stock > 150);
	
	do{
		printf("Input Price [ 200000 - 1000000 ] : ");
		scanf("%lld", &price); getchar();
	}while(price < 200000 || price > 1000000);
	
	id[0] = 'N';
	id[1] = 'K';
	id[2] = 'W';
	id[3] = count/10;
	id[4] = count%10;
	
	printf("Generated ID: %s\n", id);
	insertHash(name, cate, brand, stock, price, id);
}

void removeProduct(){
	char id[7];
	printProduct();
	if (hash[0] == NULL){
		printf("There is No Data!\n\n\n");
		printf("Press Enter to Continue...");
		getchar();
		return;
	}
	printf("Input ItemID to delete(case insensitive) : ");
	scanf("%[^\n]", id); getchar();
	
	int key = hashFunction(id);
	if(hash[key]==NULL){
		printf("Product not found...\n");
		return;
	}
	if(strcmpi(hash[key]->id, id) == 0){
		Product *temp = hash[key]->next;
		free(hash[key]);
		hash[key] = temp;
		printf("Product has been successfully removed!\n");
	}
	else{
		Product *temp = hash[key];
		while(temp->next != NULL){
			if(strcmpi(temp->id, id) == 0){
				Product *temp2 = temp->next;
				temp->next = temp2->next;
				free (temp2);
				printf("Product has been successfully removed!\n");
				return;
			}
			temp = temp->next;
		}
		printf("Product not found...\n");
	}
}

int main(){
	int menu = 0;
	do{
		printProduct();
		if (hash[0] == NULL){
			printf("There is No Data!\n\n\n");
		}
		printf("NAKEWAREHOUSE\n");
		printf("=============\n");
		printf("1. Insert New Product\n");
		printf("2. Delete Product\n");
		printf("3. Exit\n");
		printf(">> ");
		scanf("%d", &menu); getchar();
		
		if(menu == 1){
			insertProduct();
		}
		else if(menu == 2){
			removeProduct();
		}
		count++;
	}while(menu != 3);
	
	return 0;
}
