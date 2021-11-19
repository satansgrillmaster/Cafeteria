#include <stdio.h>
#include <string.h>
#include <math.h>


struct article_t{
    char name[31];
    int category;
    double price;
};

struct articleheader_t{
    char artilcename[31];
    char category[31];
    char price[31];
    char vat[31];
};

double round_price(double wert){

    wert *= 20;
    wert = round(wert);
    wert /= 20;
    return wert;

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
    printf("%.2lf",price);
    return price;
}

int main() {

    struct article_t article;
    struct articleheader_t articleheader;
    double newprice;
    FILE * myfile = NULL;
    FILE * mynewfile = NULL;

    myfile = fopen("Artikel.txt","r");
    mynewfile = fopen("NewArtikel.txt","w");
    // do while solange nicht endoffile !FEOF(pointer)

    fscanf(myfile,"%[^\t]\t%[^\t]\t%[^\t]\n",articleheader.artilcename,
           articleheader.category,articleheader.price);

    printf("%s, %s, %s, %s ",articleheader.artilcename,
           articleheader.category,articleheader.price, articleheader.vat);
    fprintf(mynewfile,"%s\t%s\t%s",articleheader.artilcename,articleheader.category,articleheader.price);

    do{

        fscanf(myfile,"%[^\t]\t%d\t%lf.2\n",article.name,&article.category,&article.price);
        newprice = round_price(calculate_new_price(article.category,article.price,article.name));
        fprintf(mynewfile,"%s\t%d\t%.2lf",article.name,article.category,newprice);

    } while (!feof(myfile));

    fclose(myfile);
    fclose(mynewfile);
    return 0;
}
