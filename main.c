#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

void filter_str(char str[],int n);
void calculate_frequencies_bi(char str[],int n,char bigram[][3],float x[]);
void calculate_frequencies_tri(char str[],int n,char trigram[][4],float y[]);
void calculate_distances(float calculated_frequencies[],float frequency_eng[],float frequency_germ[],float dist[]);
void detect_lang(float dist[],char languages[][8]);

int main()
{

    system("color 1A"); // Terminal ekranimizin siradan gorunmemesi icin renklendirme yaptik.

    char metin[50000]; //Kullanicinin daha kapsamli metinleri inceleyebilmesi icin dizimizi uzun tuttuk.
    float calculated_frequencies[20];
    const char matrix_bigram_strings[10][3] ={"th", "he", "in", "er", "an", "en", "ch", "de", "ei", "te"};
    const char matrix_trigram_strings[10][4]={"the", "and", "ing", "ent", "ion", "der", "sch", "ich", "nde", "die"};
    const float frequency_eng[20]={ 2.71, 2.33, 2.03, 1.78, 1.61, 1.13, 0.01, 0.01, 0.01, 0.01, 1.81, 0.73, 0.72, 0.42, 0.42, 0.01, 0.01, 0.01, 0.01, 0.01 };
    const float frequency_germ[20]={ 0.01, 0.89, 1.71, 3.90, 1.07, 3.61, 2.36, 2.31, 1.98, 1.98, 0.01, 0.01, 0.01, 0.01, 0.01, 1.04, 0.76, 0.75, 0.72, 0.62 };
    const char languages[2][8]={"english", "german"};
    float distances [2]={0,0};

    printf("Lutfen ALT+ENTER tuslarina basiniz.\n");
    Sleep(5000);
    printf("Dilini ogrenmek istediginiz metini giriniz: ");
    gets(metin); // Metni aldik.

    int metin_uzunluk=strlen(metin); //Metnin uzunlugunu fonksiyonlardaki dongulerde sinirlandirma yapabilmek icin olctuk.

    filter_str(metin,metin_uzunluk); //Metni bigram ve trigramlari arastiracak sekilde isledik. Arastirdigimiz bigram ve trigramlar kucuk harfle yazilmis oldugu icin harf donusumu yaptik. Harf harici karakterleri cikardik.

    calculate_frequencies_bi(metin,metin_uzunluk,matrix_bigram_strings,calculated_frequencies); //Metinde gecen bigramlarin frekansini bulduk.

    calculate_frequencies_tri(metin,metin_uzunluk,matrix_trigram_strings,calculated_frequencies); //Metinde gecen trigramlarin frekansini bulduk.

    calculate_distances(calculated_frequencies, frequency_eng,frequency_germ,distances); //Her bir dil icin frekanslarin oklid uzakligini hesapladik.

    system("cls"); //Aldigimiz metin kalabalik gozukmesin diye sayfayi temizledik.

    int secim; //Kullanicinin secimini gorebilmek icin degisken tanimladik.

    menu: // Menuyu tekrar kullanabilmek icin bir baslangic duragi olusturduk.

    //Kullanici dostu bir program yazmis olmak icin ve bilgilendirme yapabilmek icin bu menuyu hazirladik

    printf("\n\n\n\t\t\t\t\t\t**********************************************************************************************************\n\n\n");
    printf("\t\t\t\t\t\t Girdiginiz metnin hangi dille yazildigini ogrenmek istiyorsaniz 1'e basiniz\n\n");
    printf("\t\t\t\t\t\t Girdiginiz metinde gecen bigram ve trigramlarin frekanslarini gormek icin 2'ye basiniz\n\n");
    printf("\t\t\t\t\t\t Girdiginiz metnin Ingilizce ve Almanca diline olan hesapladigimiz uzakligini gormek icin 3'e basiniz\n\n");
    printf("\t\t\t\t\t\t Girdiginiz metnin isledigimiz halini gormek istiyorsaniz 4'e basiniz\n\n");
    printf("\t\t\t\t\t\t Cikis icin 5'e basiniz\n\n");
    printf("\n\n\n\t\t\t\t\t\t**********************************************************************************************************\n\n\n");

    printf("\t\t\t\t\t\tSeciminiz: ");
    scanf("%d",&secim);

        if(secim == 1){
            system("cls"); // Sade bir gorunum olusturmasi icin onceki metinleri temizledik.
            detect_lang(distances,languages); // Secime karsilik gelen degerde dili belirleyen fonksiyonun cagrilmasi islemidir.
        }
        else if(secim == 2){
            system("cls");  // Sade bir gorunum olusturmasi icin onceki metinleri temizledik.
            for(int i=0;i<20;i++){

                if(i>=0 && i<10)
                    printf("\n\t\t\t\t\t\tcalculated_frequencies[%d] frekans degeri = %f (bigram)",i,calculated_frequencies[i]);//Kullancinin girdigi metindeki bigramlarin frekans degerini gosterdik.
                else if(i>=10 && i<20)
                    printf("\n\t\t\t\t\t\tcalculated_frequencies[%d] frekans degeri = %f (trigram)",i,calculated_frequencies[i]);//Kullancinin girdigi metindeki trigramlarin frekans degerini gosterdik.
                else
                    break;
            }
        }
        else if(secim == 3){
            system("cls");// Sade bir gorunum olusturmasi icin onceki metinleri temizledik.
            printf("\n\n\t\t\t\t\t\tGirilen metnin Ingilizce ile uzakligi=%f\n",distances[0]);//Kullanicinin girdigi metnin Ingilizce diline olan oklid uzakligini gosterdik.
            printf("\t\t\t\t\t\tGirilen metnin Almanca ile uzakligi=%f\n\n",distances[1]);//Kullanicinin girdigi metnin Almanca diline olan oklid uzakligini gosterdik.
        }
        else if(secim == 4){
            system("cls");// Sade bir gorunum olusturmasi icin onceki metinleri temizledik.
            printf("Girdiginiz metnin isledigimiz hali;\n\n");
            puts(metin);//Kullanicinin girdigi metnin buyuk-kucuk harf donusumu yapilip harf harici karakterlerin metinden cikarilarak hazirlanmis hali.
            printf("\ndir\n");
        }
        else if(secim == 5){
            goto cikis;//Kullanicinin cikis yapabilmesi icin secim olusturduk.
        }
        else{
            system("cls");// Sade bir gorunum olusturmasi icin onceki metinleri temizledik.
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\tLutfen gecerli bir rakam giriniz!");// Secimde belirtilen rakamlardan farkli bir rakam girilmesi durumunda verdirdigimiz uyari.
            Sleep(3000);// Yaptigimiz uyarinin ekranda 3 saniye durmasini saglayan komut.
            system("cls");// Sade bir gorunum olusturmasi icin onceki metinleri temizledik.
        }

    goto menu; // Menuyu tekrar kullanabilmek icin olusturdugumuz baslangic duragina gonderen komut.

    cikis://Kullanici cikis secimi yaptiginda buraya yonlenir.

    return 0;
}

void filter_str(char str[],int n){ // str[] => metin[] , n => metnin islenmis halinin uzunlugu

    for(int i=0;i<n;i++){

        if(str[i]>=65 && str[i]<=90 || str[i]>=97 && str[i]<=122){ // Metindeki olan karakterlerden sadece harfleri sectik.
            str[i]=tolower(str[i]);//Metindeki buyuk harfleri kucuk harflerle degistirdik.
        }
        else{
            str[i]=32;//Harf harici karakterleri "space" karakterine atadik.
        }

    }

}

void calculate_frequencies_bi(char str[],int n,char bigram[][3],float x[]){// str[] => metin[] , n => metnin islenmis halinin uzunlugu, bigram[][3] => matrix_bigram_strings , x[] => calculated_frequencies


    int i,j,k;

    float th,he,in,er,an,en,ch,de,ei,te; //Sayac olusturduk.

    th=0;
    he=0;
    in=0;
    er=0;
    an=0;
    en=0;
    ch=0;
    de=0;
    ei=0;
    te=0;

    for(i=0;i<n;i++){ // Bigramlarin sayisini burada hesapladik.
    //Her bir karakter teker teker kontrol ediliyor.
        for(j=0;j<10;j++){

            for(k=0;k<2;k++){

               if (str[i]==bigram[j][k] && str[i+1]==bigram[j][k+1]){

                    if(bigram[j][k]=='t' && bigram[j][k+1]=='h')
                            th++;
                        else if(bigram[j][k]=='h' && bigram[j][k+1]=='e')
                            he++;
                        else if(bigram[j][k]=='i' && bigram[j][k+1]=='n')
                            in++;
                        else if(bigram[j][k]=='e' && bigram[j][k+1]=='r')
                            er++;
                        else if(bigram[j][k]=='a' && bigram[j][k+1]=='n')
                            an++;
                        else if(bigram[j][k]=='e' && bigram[j][k+1]=='n')
                            en++;
                        else if(bigram[j][k]=='c' && bigram[j][k+1]=='h')
                            ch++;
                        else if(bigram[j][k]=='d' && bigram[j][k+1]=='e')
                            de++;
                        else if(bigram[j][k]=='e' && bigram[j][k+1]=='i')
                            ei++;
                        else if(bigram[j][k]=='t' && bigram[j][k+1]=='e')
                            te++;
                        else
                            continue;
                    }
                    else
                        break;
            }
        }

    }

    //Bigramlarin frekanslarini hesapladik.
    x[0]=(th*2*100)/n;
    x[1]=(he*2*100)/n;
    x[2]=(in*2*100)/n;
    x[3]=(er*2*100)/n;
    x[4]=(an*2*100)/n;
    x[5]=(en*2*100)/n;
    x[6]=(ch*2*100)/n;
    x[7]=(de*2*100)/n;
    x[8]=(ei*2*100)/n;
    x[9]=(te*2*100)/n;

}

void calculate_frequencies_tri(char str[],int n,char trigram[][4],float y[]){   // str[] => metin[] , n => metnin islenmis halinin uzunlugu, trigram[][4] => matrix_trigram_strings , y[] => calculated_frequencies


    int i,j,k;
    float the,and,ing,ent,ion,der,sch,ich,nde,die;//Sayac olusturduk.

    the=0;
    and=0;
    ing=0;
    ent=0;
    ion=0;
    der=0;
    sch=0;
    ich=0;
    nde=0;
    die=0;

    for(i=0;i<n;i++){// Trigramlarin sayisini burada hesapladik.
    //Her bir karakter teker teker kontrol ediliyor.
        for(j=0;j<10;j++){

            for(k=0;k<3;k++){

                if (str[i]==trigram[j][k] && str[i+1]==trigram[j][k+1] && str[i+2]==trigram[j][k+2]){

                    if(trigram[j][k]=='t' && trigram[j][k+1]=='h' && trigram[j][k+2]=='e')
                        the++;
                    else if(trigram[j][k]=='a' && trigram[j][k+1]=='n' && trigram[j][k+2]=='d')
                        and++;
                    else if(trigram[j][k]=='i' && trigram[j][k+1]=='n' && trigram[j][k+2]=='g')
                        ing++;
                    else if(trigram[j][k]=='e' && trigram[j][k+1]=='n' && trigram[j][k+2]=='t')
                        ent++;
                    else if(trigram[j][k]=='i' && trigram[j][k+1]=='o' && trigram[j][k+2]=='n')
                        ion++;
                    else if(trigram[j][k]=='d' && trigram[j][k+1]=='e' && trigram[j][k+2]=='r')
                        der++;
                    else if(trigram[j][k]=='s' && trigram[j][k+1]=='c' && trigram[j][k+2]=='h')
                        sch++;
                    else if(trigram[j][k]=='i' && trigram[j][k+1]=='c' && trigram[j][k+2]=='h')
                        ich++;
                    else if(trigram[j][k]=='n' && trigram[j][k+1]=='d' && trigram[j][k+2]=='e')
                        nde++;
                    else if(trigram[j][k]=='d' && trigram[j][k+1]=='i' && trigram[j][k+2]=='e')
                        die++;
                    else
                        continue;
                    }
                else
                    break;
            }
        }

    }

    //Trigramlarin frekanslarini hesapladik.
    y[10]=(the*3*100)/n;
    y[11]=(and*3*100)/n;
    y[12]=(ing*3*100)/n;
    y[13]=(ent*3*100)/n;
    y[14]=(ion*3*100)/n;
    y[15]=(der*3*100)/n;
    y[16]=(sch*3*100)/n;
    y[17]=(ich*3*100)/n;
    y[18]=(nde*3*100)/n;
    y[19]=(die*3*100)/n;

}

void calculate_distances(float calculated_frequencies[],float frequency_eng[],float frequency_germ[],float dist[]){
//calculated_frequencies[] => Hesapladigimiz frekanslar , frequency_eng[],frequency_germ[] => verilen degerler , dist[] => distances [2]
    float engdeger=0; //Sayac
    float germdeger=0;//Sayac

    for(int i=0;i<20;i++){

        engdeger+=(pow(abs(calculated_frequencies[i]-frequency_eng[i]),2));//Oklid uzaklik hesaplama 1. adim

    }

    engdeger=sqrt(engdeger); // Oklid uzaklik hesaplama 2. adim

    for(int i=0;i<20;i++){

        germdeger+=(pow(abs(calculated_frequencies[i]-frequency_germ[i]),2));//Oklid uzaklik hesaplama 1. adim

    }

    germdeger=sqrt(germdeger); // Oklid uzaklik hesaplama 2. adim

    dist[0]=engdeger; //Bigram ve trigramlarimizin Inglýzce diline olan oklid uzakliginin 0. indise atanmasi.
    dist[1]=germdeger; //Bigram ve trigramlarimizin Almanca diline olan oklid uzakliginin 1. indise atanmasi.

}

void detect_lang(float dist[],char languages[][8]){ // Dilin belirlenmesi.
//dist[] => distance[2],  languages[][8] => verilen dizi
    if(dist[0]>dist[1])
        printf("\t\t\t\t\t\tGirilen metnin dili: %s\n",languages[1]);
        // Ingilizce diline olan uzakligin Almanca diline olan uzakliktan fazla olmasi durumunda Almanca dilinin secilmesi islemi.
    else if(dist[1]>dist[0])
        printf("\t\t\t\t\t\tGirilen metnin dili: %s\n",languages[0]);
        // Almanca diline olan uzakligin Ingýlýzce diline olan uzakliktan fazla olmasi durumunda Ingýlýzce dilinin secilmesi islemi.
    else
        printf("\t\t\t\t\t\tGirilen dil Ingilizce de Almanca da olabilir.\n");
        // Cok dusuk bir ihtimalle de olsa esitlik durumunda tercih belirtilmemesi islemi.
}
