#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

//4.line  Boolean veri türü için dört makro içerir
//4. line ontains four macros for a Boolean data type
//5. line ise temel matematiksel islemleri gerçeklestirmek için tasarlanmis bir standart kütüphanedir
//5. line is a standard library designed to perform basic mathematical operations


const char matrix_bigram_strings[10][3] ={"th", "he", "in", "er", "an", "en", "ch", "de", "ei", "te"};
// in this line we made up a string array for the English words
// burada Ingilizce icin dizi olusturduk

const char matrix_trigram_strings[10][4]={"the", "and", "ing", "ent", "ion", "der", "sch", "ich", "nde", "die"};
// in this line we made up a string array for the German words
// burada Almanca icin dizi olusturduk

const char languages[2][8]={"English", "German"};

const float frequency_eng[20]={ 2.71, 2.33, 2.03, 1.78, 1.61, 1.13, 0.01, 0.01, 0.01, 0.01, 1.81, 0.73, 0.72, 0.42, 0.42, 0.01, 0.01, 0.01, 0.01, 0.01 };
//burada Ingilizce dilinin frekans degerleri verildi
//these are the frequencies for the English words

const float frequency_germ[20]={ 0.01, 0.89, 1.71, 3.90, 1.07, 3.61, 2.36, 2.31, 1.98, 1.98, 0.01, 0.01, 0.01, 0.01, 0.01, 1.04, 0.76, 0.75, 0.72, 0.62 };
//burada Almanca dilinin frekans deðerleri verildi
//these are the frequencies for the German words

float calculated_frequencies[20];
float distances [2]={0,0};

void filter_str(char text[]);
void calculate_frequencies_bi(char text[]);
void calculate_frequencies_tri(char text[]);
void calculate_distances();
void detect_lang();

int main(frequency_germ,frequency_eng)
{
	// gets ile bir text aliyoruz filtrelemeye basliyoruz
	// here we are getting an input with the command gets then we'll start filtering
    char text[1000];
    printf("Enter a text: ");
    gets(text);
    filter_str(text);
    calculate_frequencies_bi(text);
    calculate_frequencies_tri(text);
    calculate_distances();
    detect_lang();
    return 0;
}

void filter_str(char text[])
{
	/* basically in this function we are filtering the input from characters other then letters */
	// input'u harfler haric characterlerden temizliyoruz
	printf("Program is working...\n");
	printf("****************************************************************************************************\n");
    int i,b,a;
    a=strlen(text);
    for(b=0;b<a;b++)
    {
        text[b]=tolower(text[b]);
    }

    for(i=0;i<a;i++)
    {
        if((text[i]>='a'&&text[i]<='z'))
        {
            text[i]=text[i];
        }
        else
            text[i]=' ';
    }
    printf("\nCleared text\n");
    puts(text);
    printf("\n");

}
void calculate_frequencies_bi(char text[])
{
    int i,a,c;
    a=strlen(text);
    // strlen means string length
    // burada metnin içindeki bigramlari ariyoruz
    for (i=0;i<a;i++)
    {
        for (c=0;c<10;c++)
        {
            if(text[i]==matrix_bigram_strings[c][0])
            {
                if(text[i+1]==matrix_bigram_strings[c][1])
                    calculated_frequencies[c]+=1;
            }
        }

    }

}

void calculate_frequencies_tri(char text[])
{
// all the things done in this function are for calculating the frequencies
//burada metnin içindeki trigramlari ariyoruz
    int i,a,c;
    a=strlen(text);
    for(i=0;i<a;i++)
    {
        for(c=0;c<10;c++)
        {
            if(text[i]==matrix_trigram_strings[c][0])
            {
                if(text[i+1]==matrix_trigram_strings[c][1])
                {
                    if(text[i+2]==matrix_trigram_strings[c][2])
                    {
                        calculated_frequencies[c+10]+=1;
                    }
                }
            }

        }

    }
//burada ise bulmus oldugumuz bigram ve trigramlardan metnin bigram ve trigram frekanslarini elde ediyoruz
int x,y;
float counter1=0,counter2=0;
for(x=0;x<10;x++)
{
    counter1+=calculated_frequencies[x];
}
for(x=0;x<10;x++)
{
    calculated_frequencies[x]=calculated_frequencies[x]/(float)counter1;
}
for(y=10;y<20;y++)
{
    counter2+=calculated_frequencies[y];
}
for(y=10;y<20;y++)
{
    calculated_frequencies[y]=calculated_frequencies[y]/(float)counter1;
}
printf("\n****************************************************************************************************\n");
int p;
for(p=0;p<10;p++)
{
    printf("%.2f\t",calculated_frequencies[p]);
}
printf("\n----------------------------------------------------------------------------------------------------\n");
for(p=10;p<20;p++)
{
    printf("%.2f\t",calculated_frequencies[p]);
}

}
void calculate_distances()
{
//burada buldugumuz bütün frekanslari ingilizce ve almancanin frekanslarindan çikarip hepsini topluyoruz ve sonuçta hangi deger daha küçükse metnin o dilde yazildigini anliyoruz
//Here we subtracting all the frequencies we found from the English and German frequencies and adding them all together, then deciding if the text is in English or German
    float total=0.0;
printf("\n****************************************************************************************************\n");
    for(int i=0;i<20;i++)
    {
        total+=pow((calculated_frequencies[i]-frequency_eng[i]),2);
    }

    distances[0]=sqrt(total) ;
    printf("\nCalculated frequency for english\n");
    printf("%f\n",distances[0]);

    float total2=0.0;
    for(int i=0;i<20;i++)
    {
        total2+=pow((calculated_frequencies[i]-frequency_germ[i]),2);
    }

    distances[1]=sqrt(total2);
    printf("\nCalculated frequency for german\n");
    printf("%f\n",distances[1]);
}
void detect_lang()
{
	// in this function we are finally declaring whether the input is English or German and printing it on the console
	// burda input'un Ingilizce mi yoksa Almanca mi oldugunu hesaplatip ekrana yazdiriyoruz
    printf("\n****************************************************************************************************\n");
    if (distances[0]<distances[1])
        printf("Your text is in english");
    if (distances[1]<distances[0])
        printf("Your text is in german");

}

