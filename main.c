#include <stdio.h>
#include <string.h>
#include <math.h>


typedef struct article_t{
    char name[31];
    int category;
    double price;
} article_t;

typedef struct articleheader_t{
    char artilcename[31];
    char category[31];
    char price[31];
    char vat[31];
} articleheader_t;

typedef struct records_t{
    article_t article;
} records_t;

double round_price(double wert){

    wert *= 20;
    wert = round(wert);
    wert /= 20;
    return wert;

}

void bubbleSort(struct records_t records[], int counter,int sort_type)
{
    records_t tmp;
    double number;
    double number1;

    if(sort_type == 0){

        for(int i = 0; i < counter;i++){
            for(int j = 0;j<counter -1;j++){

                number = records[j].article.price;
                number1 = records[j + 1].article.price;

                if(number > number1){
                    tmp = records[j];
                    records[j] = records[j + 1];
                    records[j + 1] = tmp;
                }
            }
        }
    }
    else{
        for(int i = 0; i < counter;i++){
            for(int j = 0;j<counter -1;j++){

                number = records[j].article.price;
                number1 = records[j + 1].article.price;

                if(number < number1){
                    tmp = records[j];
                    records[j] = records[j + 1];
                    records[j + 1] = tmp;
                }
            }
        }
    }
}


double calculate_new_price(int category, double price, char name[]){
    if(category == 15){
        price = price + 0.1;
    }
    else if(category == 11 && strstr(name,"Chips")){
        price = price + 0.2;
    }
    else if(category == 30){
        price = price + (price / 100 * 5);
    }
    else if(category == 100 || category == 20){
        price = price + (price / 100 * 10);
    }
    return price;
}

int main() {

    article_t article;
    articleheader_t articleheader;
    records_t records[100];

    int counter = 0;
    double newprice;
    FILE * myfile = NULL;
    FILE * mynewfile = NULL;

    myfile = fopen("Artikel.txt","r");
    mynewfile = fopen("NewArtikel.txt","w");

    /* read tableheader */
    fscanf(myfile,"%[^\t]\t%[^\t]\t%[^\n]\n",articleheader.artilcename,
           articleheader.category,articleheader.price);

    fprintf(mynewfile,"%s\t%s\t%s",articleheader.artilcename,articleheader.category,articleheader.price);

    /* read all article records and save them in array */
    do{

        fscanf(myfile,"%[^\t]\t%d\t%lf.2\n",article.name,&article.category,&article.price);
        article.price = round_price(calculate_new_price(article.category,article.price,article.name));
        records[counter].article = article;
        counter += 1;

    } while (!feof(myfile));

    /* sort the records */
    bubbleSort(records, counter,1);

    /* add records to new file */
    for(int i = 0; i < counter;i++){
        fprintf(mynewfile,"%s\t%d\t%.2lf",records[i].article.name,records[i].article.category,
                records[i].article.price);
    }
    fclose(myfile);
    fclose(mynewfile);
    return 0;
}
