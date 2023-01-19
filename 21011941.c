#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Yazar
{
    int yazarID;
    char yazarAd[30];
    char yazarSoyad[30];
    struct Yazar *next;
} Yazar;
typedef struct Ogrenci
{
    char ogrID[9];
    char ad[30];
    char soyad[30];
    int puan;
    struct Ogrenci *next;
    struct Ogrenci *prev;
} Ogrenci;
typedef struct KitapOrnek
{
    char EtiketNo[20];
    char Durum[8];
    struct KitapOrnek *next;
} KitapOrnek;
typedef struct Kitap
{
    char kitapAdi[30];
    char ISBN[14];
    int adet;
    struct Kitap *next;
    struct KitapOrnek *head;
} Kitap;
typedef struct KitapYazar
{
    char ISBN[14];
    int YazarID;
} KitapYazar;
typedef struct Tarih
{
    unsigned gun : 5;
    unsigned ay : 4;
    unsigned yil : 12;
} Tarih;
typedef struct KitapOdunc
{
    char EtiketNo[20];
    char ogrID[9];
    unsigned islemTipi : 1;
    struct Tarih islemTarihi;
} KitapOdunc;

typedef struct Funcptr
{
    void (*add)(void *);
    void (*print)(void *);
    void *(*search)(void *, void *, void *, int);
    void (*del)(void *, void *, int);
    void (*edit)(void *);
} Funcptr;
//
void loadFromFile(void *head, void (*funcptr)(void *, char *), char *fileName);
int printMenu(char *name, void *head, void *headADR, Funcptr *funcptr, void *iliski, void *otherhead, int iN);

int KOload(KitapOdunc **kodizi);
void KOeslestir(KitapOdunc *kodizi, Ogrenci *ohead, Kitap *khead, int koN);
void KOceza(KitapOdunc *kodizi, Ogrenci *ogrenci, int i, Ogrenci *ogrhead);
int KOislemi(KitapOdunc *kodizi, Ogrenci *ogrenci, Kitap *kitap, int koN, void (*funptr)(KitapOrnek **, Kitap *, Ogrenci *), char *islem, unsigned a);
void kitabalma(KitapOrnek **ornek, Kitap *kitap, Ogrenci *ogrenci);
void kitabverme(KitapOrnek **ornek, Kitap *kitap, Ogrenci *ogrenci);
void updateKO(KitapOdunc *kodizi, int N);

int kitapYazarOlustur(KitapYazar **kdizi);
void KYdelyazar(KitapYazar *kydizi, int ID, int iN);
void updateKY(KitapYazar *kydizi, int iN);

//==========================================

// Kitap ===========================
void listRaf(Kitap *kitap);
void listTE(KitapOdunc *kodizi, int N);

int KYeslestir(KitapYazar **kydizi, int iN, Yazar *yhead, Kitap *khead);
void KYguncelle(KitapYazar *kydizi, int iN, Yazar *yhead, Kitap *khead);

void loadKitapa(void *head, char *Line);
void updateKitap(Kitap *head);

void KitapAdd(void *head);
void KitapPrint(void *head);
void *kitapSearch(void *head, void *, void *, int);
void kitapDel(void *head, void *iliski, int iN);
void kitapEdit(void *head);
void kitapfreeMem(Kitap **head);

void KitapOrnekOlustur(Kitap *kitap, void (*funptr)(KitapOrnek *));
void printKitapOrnek(KitapOrnek *head);
void kitapOrnekFree(KitapOrnek *head);
void loadKitapOrnek(void *head, char *Line);
//==================================

// Ogr ===========================
void listKO(Ogrenci *ogrenci, Kitap *kitap);
void listCezali(Ogrenci *tmp);
int ogrIDcomp(char *entered, Ogrenci *tmp);
Ogrenci *ogrSer(char *entered, Ogrenci *tmp, int (*funcptr)(char *, Ogrenci *));
void loadOgr(void *head, char *Line);
void updateOgr(Ogrenci *head);
void OgrPrint(void *head);
void OgrAdd(void *head);
void *OgrSearch(void *head, void *, void *, int);
void OgrDel(void *head, void *iliski, int);
void OgrEdit(void *head);
void OgrfreeMem(Ogrenci **head);
//==================================

// Yazar ===========================
void loadYazara(void *head, char *Line);
void updateYazar(Yazar *head);

void YazPrint(void *head);
void YazAdd(void *head);
void *YazSearch(void *head, void *, void *, int);
void YazDel(void *head, void *iliski, int);
void YazEdit(void *head);
void YazarfreeMem(Yazar **head);
//==================================

int main()
{
    int a = 1, koN, kiN, i;
    Yazar *yazarhead = NULL;
    Ogrenci *ogrenci = NULL;
    Kitap *kitap = NULL;
    KitapYazar *kydizi;
    KitapOdunc *kodizi;

    Funcptr yazarfuncptr = {YazAdd, YazPrint, YazSearch, YazDel, YazEdit};
    Funcptr ogrencifuncptr = {OgrAdd, OgrPrint, OgrSearch, OgrDel, OgrEdit};
    Funcptr kitapfunptr = {KitapAdd, KitapPrint, kitapSearch, kitapDel, kitapEdit};

    koN = KOload(&kodizi);
    kiN = kitapYazarOlustur(&kydizi);

    loadFromFile(&yazarhead, loadYazara, "Yazarlar.csv");
    loadFromFile(&ogrenci, loadOgr, "Ogrenciler.csv");
    loadFromFile(&kitap, loadKitapa, "Kitaplar.csv");
    loadFromFile(&kitap, loadKitapOrnek, "KitapOdunc.csv");

    updateKitap(kitap);

    KOeslestir(kodizi, ogrenci, kitap, koN);
    while (a != 0)
    {
        printf("| 0> to Exit\n");
        printf("| 1> Yazar islemleri \n");
        printf("| 2> Ogrenci islemleri \n");
        printf("| 3> Kitap islemleri \n");
        printf("| 4> Kitap Odunc Alma\n");
        printf("| 5> Kitap Odunc Verme\n");
        printf("| 6> Clear Screen\n");

        scanf("%d", &a);
        fflush(stdin);
        switch (a)
        {
        case 1:
            while (printMenu("Yazar", yazarhead, &yazarhead, &yazarfuncptr, kydizi, kitap, kiN))
                ;
            break;
        case 2:
            printf("| 0> Kitap Teslim etmeyen ogrinciler listesi\n");
            printf("| 1> cezali ogrinciler listesi\n");
            printf("| 2> Ogrenci islemleri\n");
            scanf("%d", &i);
            if (i == 0)
                listKO(ogrenci, kitap);
            if (i == 1)
                listCezali(ogrenci);
            if (i == 2)
                while (printMenu("Ogrenci", ogrenci, &ogrenci, &ogrencifuncptr, kodizi, ogrenci, koN))
                    ;
            break;
        case 3:
            printf("| 0> Raftaki kitaplar listesi\n");
            printf("| 1> Zamaninda teslim edilmeyen kitaplar listesi\n");
            printf("| 2> Kitap-Yazar eslestir\n");
            printf("| 3> Kitap Yazarini guncelle\n");
            printf("| 4> kitap islemleri\n");
            scanf("%d", &i);
            if (i == 0)
                listRaf(kitap);
            if (i == 1)
                listTE(kodizi, koN);
            if (i == 2)
                kiN = KYeslestir(&kydizi, kiN, yazarhead, kitap);
            if (i == 3)
                KYguncelle(kydizi, kiN, yazarhead, kitap);
            else if (i == 4)
                while (printMenu("Kitap", kitap, &kitap, &kitapfunptr, kydizi, yazarhead, kiN))
                    ;
            break;
        case 4:
            koN += KOislemi(kodizi, ogrenci, kitap, koN, kitabalma, "Alma", 0);
            if ((koN + 1) % 10 == 0)
                kodizi = (KitapOdunc *)realloc(kodizi, sizeof(KitapOdunc) * (koN + 11));
            break;
        case 5:
            koN += KOislemi(kodizi, ogrenci, kitap, koN, kitabverme, "verme", 1);
            if ((koN + 1) % 10 == 0)
                kodizi = (KitapOdunc *)realloc(kodizi, sizeof(KitapOdunc) * (koN + 11));
            break;
        case 6:
            system("cls");
            break;
        }
    }
    YazarfreeMem(&yazarhead);
    OgrfreeMem(&ogrenci);
    kitapfreeMem(&kitap);
    free(kydizi);
    free(kodizi);
    return 0;
}

void loadFromFile(void *head, void (*funcptr)(void *, char *), char *fileName)
{
    FILE *fptr;
    char Line[200];
    if ((fptr = fopen(fileName, "r")) == NULL)
    {
        printf("Error opening %s", fileName);
        return;
    }
    while (fgets(Line, 199, fptr) != NULL)
    {
        funcptr(head, Line);
    }
    fclose(fptr);
}
int printMenu(char *name, void *head, void *headADR, Funcptr *funcptr, void *iliski, void *otehrhead, int iN)
{
    int a = 1;
    fflush(stdin);
    printf("| 0> to go back\n");
    printf("| 1> %s eklemek icin \n", name);
    printf("| 2> %s listlelmek icin \n", name);
    printf("| 3> %s aramak icin \n", name);
    printf("| 4> %s Silmek icin \n", name);
    printf("| 5> %s guncellemek icin \n\n", name);
    scanf("%d", &a);
    fflush(stdin);
    switch (a)
    {
    case 1:
        funcptr->add(headADR);
        break;
    case 2:
        funcptr->print(head);
        break;
    case 3:
        funcptr->search(head, iliski, otehrhead, iN);
        break;
    case 4:
        funcptr->del(headADR, iliski, iN);
        break;
    case 5:
        funcptr->edit(headADR);
        break;
    default:
        break;
    }
    return a;
    system("cls");
}

void listRaf(Kitap *kitap)
{
    KitapOrnek *ornek;
    while (kitap != NULL)
    {
        ornek = kitap->head;
        while (ornek != NULL)
        {
            if (!strncmp(ornek->Durum, "Rafta", 5))
            {
                printf("%s %s\n", kitap->kitapAdi, ornek->EtiketNo);
            }
            ornek = ornek->next;
        }
        kitap = kitap->next;
    }
}
void listTE(KitapOdunc *kodizi, int N)
{
    int i = N - 1, j;

    while (i > 0)
    {
        if (kodizi[i].islemTipi)
        {
            j = i - 1;
            while (j >= 0 && strcmp(kodizi[i].EtiketNo, kodizi[j].EtiketNo))
                j--;
            if (j < 0)
                printf("! %s kitabi ne zaman alindigi belli degil\n", kodizi[i].EtiketNo);
            else
            {
                if ((kodizi[i].islemTarihi.gun - kodizi[j].islemTarihi.gun > 15) ||
                    (kodizi[i].islemTarihi.ay - kodizi[j].islemTarihi.ay) || (kodizi[i].islemTarihi.yil - kodizi[i].islemTarihi.yil))
                {
                    printf("%s \n", kodizi[i].EtiketNo);
                }
            }
        }
        i--;
    }
}

void listKO(Ogrenci *ogrenci, Kitap *kitap)
{
    Ogrenci *tmp;
    KitapOrnek *ornek;
    while (kitap != NULL)
    {
        ornek = kitap->head;
        while (ornek != NULL)
        {
            if (strncmp(ornek->Durum, "Rafta", 5))
            {
                tmp = ogrSer(ornek->Durum, ogrenci, ogrIDcomp);
                if (tmp != NULL)
                {
                    printf("ID: %s => %s-%s || Grade: %d\n", tmp->ogrID, tmp->ad, tmp->soyad, tmp->puan);
                }
            }
            ornek = ornek->next;
        }
        kitap = kitap->next;
    }
}
void listCezali(Ogrenci *tmp)
{
    while (tmp != NULL)
    {
        if (tmp->puan < 0)
            printf("ID: %s => %s-%s || Grade: %d\n", tmp->ogrID, tmp->ad, tmp->soyad, tmp->puan);
        tmp = tmp->next;
    }
}

int KOload(KitapOdunc **kodizi)
{
    unsigned i = 0, d, m, y, a;
    int N = 10;
    KitapOdunc *tmp = (KitapOdunc *)malloc(sizeof(KitapOdunc) * N);
    FILE *fptr;
    char Line[100];
    if ((fptr = fopen("KitapOdunc.csv", "r")) == NULL)
    {
        printf("Error opening KitapYazar");
        return 0;
    }
    while (fgets(Line, 99, fptr) != NULL)
    {
        sscanf(Line, "%[^,],%[^,],%u,%u.%u.%u\n", tmp[i].EtiketNo, tmp[i].ogrID, &a,
               &d, &m, &y);
        tmp[i].islemTipi = a;
        tmp[i].islemTarihi.gun = d;
        tmp[i].islemTarihi.ay = m;
        tmp[i].islemTarihi.yil = y;
        i++;
        if (i == N - 1)
        {
            N += 10;
            tmp = (KitapOdunc *)realloc(tmp, sizeof(KitapOdunc) * N);
        }
    }
    (*kodizi) = tmp;
    fclose(fptr);
    return i;
}
void updateKO(KitapOdunc *kodizi, int N)
{
    FILE *fp = fopen("KitapOdunc.csv", "w+");
    int i = 0;
    while (i < N - 1)
    {
        fprintf(fp, "%s,%s,%u,%u.%u.%u\n", kodizi[i].EtiketNo, kodizi[i].ogrID, kodizi[i].islemTipi,
                kodizi[i].islemTarihi.gun, kodizi[i].islemTarihi.ay, kodizi[i].islemTarihi.yil);
        i++;
    }
    fprintf(fp, "%s,%s,%u,%u.%u.%u", kodizi[i].EtiketNo, kodizi[i].ogrID, kodizi[i].islemTipi, kodizi[i].islemTarihi.gun, kodizi[i].islemTarihi.ay, kodizi[i].islemTarihi.yil);

    fclose(fp);
}
void ornekRaftaBasla(KitapOrnek *ornek)
{
    strcpy(ornek->Durum, "Rafta");
}
void askUserKitapOrenek(KitapOrnek *ornek)
{
    char ID[9];
    printf("Kitap Rafta ise 1 giriniz \nDegilese Alan ogrenci idsiniz giriniz : \n");
    scanf("%s", ID);
    if (!strcmp(ID, "1"))
        strcpy(ornek->Durum, "Rafta");
    else
        strcpy(ornek->Durum, ID);
}

int KOislemi(KitapOdunc *kodizi, Ogrenci *ogrenci, Kitap *kitap, int koN, void (*funptr)(KitapOrnek **, Kitap *, Ogrenci *), char *islem, unsigned a)
{
    unsigned d, m, y;
    Kitap *head = kitap;
    Ogrenci *ogrhead = ogrenci;
    KitapOrnek *ornek;
    printf("Hangi ogrenci kitab %s istiyor \n", islem);
    ogrenci = OgrSearch(ogrenci, NULL, NULL, 0);
    if (ogrenci == NULL)
        return 0;
    printf("%s hangi kitabi %s istiyor \n", ogrenci->ad, islem);
    kitap = kitapSearch(kitap, NULL, NULL, 0);
    if (kitap == NULL)
        kitap = head;
    else if (kitap->next == NULL)
        return 0;
    else
        kitap = kitap->next;
    ornek = kitap->head;
    funptr(&ornek, kitap, ogrenci);
    if (ornek == NULL)
        return 0;

    strcpy(kodizi[koN].EtiketNo, ornek->EtiketNo);
    strcpy(kodizi[koN].ogrID, ogrenci->ogrID);
    kodizi[koN].islemTipi = a;
    printf("Tarihi giriniz :gun.ay.yil :\n");
    scanf("%u.%u.%u", &d, &m, &y);
    kodizi[koN].islemTarihi.gun = d;
    kodizi[koN].islemTarihi.ay = m;
    kodizi[koN].islemTarihi.yil = y;
    if (a)
        KOceza(kodizi, ogrenci, koN, ogrhead);
    updateKO(kodizi, koN + 1);
    return 1;
}
void kitabalma(KitapOrnek **ornek, Kitap *kitap, Ogrenci *ogrenci)
{
    KitapOrnek *orn = (*ornek);
    if (ogrenci->puan < 0)
    {
        printf("ogrenci puani yetmez !\n");
        (*ornek) = NULL;
        return;
    }
    while (orn != NULL && strncmp(orn->Durum, "Rafta", 5))
        orn = orn->next;
    if (orn == NULL)
        printf("%s tum nushalari alinmis \n", kitap->kitapAdi);
    else
        strcpy(orn->Durum, ogrenci->ogrID);
    (*ornek) = orn;
}
void kitabverme(KitapOrnek **ornek, Kitap *kitap, Ogrenci *ogrenci)
{
    KitapOrnek *orn = (*ornek);
    while (orn != NULL && strcmp(orn->Durum, ogrenci->ogrID))
        orn = orn->next;
    if (orn == NULL)
        printf("%s isimli ogrenci %s isimli kitabi onceden almamistir \n", ogrenci->ad, kitap->kitapAdi);
    else
    {
        strcpy(orn->Durum, "Rafta");
    }
    (*ornek) = orn;
}

void KOeslestir(KitapOdunc *kodizi, Ogrenci *ohead, Kitap *khead, int koN)
{
    int i = 0, a = 1;
    Ogrenci *tmp;
    Kitap *ktmp;
    KitapOrnek *orhead;
    while (i < koN)
    {
        ktmp = khead;
        while (ktmp != NULL && strncmp(kodizi[i].EtiketNo, ktmp->ISBN, 13))
            ktmp = ktmp->next;

        if (ktmp == NULL)
            printf("|| UYARI || %s ISBN kitap kayitli degildir\n", kodizi[i].EtiketNo);

        else
        {
            tmp = ohead;
            while (tmp != NULL && strncmp(kodizi[i].ogrID, tmp->ogrID, 8))
                tmp = tmp->next;

            if (tmp == NULL)
                printf("|| UYARI || %s IDli ogrenci kayitli degildir\n", kodizi[i].ogrID);
            else
            {
                a = kodizi[i].islemTipi;
                orhead = ktmp->head;
                while (orhead != NULL && strcmp(kodizi[i].EtiketNo, orhead->EtiketNo))
                    orhead = orhead->next;
                if (orhead != NULL)
                {
                    if (a)
                        ornekRaftaBasla(orhead);
                    else
                        strcpy(orhead->Durum, tmp->ogrID);
                }
            }
        }
        i++;
    }
}
void KOceza(KitapOdunc *kodizi, Ogrenci *ogrenci, int i, Ogrenci *ogrhead)
{
    KitapOdunc ko = kodizi[i];
    int g = 0;
    int cezali;
    i--;
    while (i >= 0 && strcmp(kodizi[i].EtiketNo, ko.EtiketNo))
        i--;

    if (i < 0)
    {
        printf("|| Uyrai || %s kitabin alma islemi gorulmuyor \n", ko.EtiketNo);
        return;
    }
    g = (ko.islemTarihi.ay - kodizi[i].islemTarihi.ay) * 30 - kodizi[i].islemTarihi.gun;
    cezali = (ko.islemTarihi.gun + g > 15) || (ko.islemTarihi.yil - kodizi[i].islemTarihi.yil);

    if (cezali)
    {
        ogrenci->puan = ogrenci->puan - 10;
        printf("|| Uyrai || %s gec verme nedeni ile -10 puan caza verimistir\n", ogrenci->ad);
        updateOgr(ogrhead);
    }
}

int kitapYazarOlustur(KitapYazar **kdizi)
{
    int i = 0;
    int N = 10;
    KitapYazar *kydizi = (KitapYazar *)malloc(sizeof(KitapYazar) * N);
    FILE *fptr;
    char Line[100];
    if ((fptr = fopen("KitapYazar.csv", "r")) == NULL)
    {
        printf("Error opening KitapYazar");
        return 0;
    }
    while (fgets(Line, 99, fptr) != NULL)
    {
        sscanf(Line, "%[^,],%d\n", kydizi[i].ISBN, &(kydizi[i].YazarID));
        i++;
        if (i == N - 1)
        {
            N += 10;
            kydizi = (KitapYazar *)realloc(kydizi, sizeof(KitapYazar) * N);
        }
    }
    (*kdizi) = kydizi;
    fclose(fptr);
    return i;
}
void printKitapYazar(KitapYazar *kydizi, int iN)
{
    int i = 0;
    KitapYazar *dizi = kydizi;
    while (i < iN)
    {

        printf("%s,%d\n", kydizi[i].ISBN, kydizi[i].YazarID);
        i++;
    }
}
void KYdelyazar(KitapYazar *kydizi, int ID, int iN)
{
    int i = 0;
    while (i < iN)
    {
        if (kydizi[i].YazarID == ID)
        {
            kydizi[i].YazarID = -1;
        }
        i++;
    }
    updateKY(kydizi, iN);
}
int KYeslestir(KitapYazar **kydizi, int iN, Yazar *yhead, Kitap *khead)
{
    KitapYazar *dizi = (*kydizi);
    Kitap *kitap;
    Yazar *yazar;
    printf("Hangi kitabi henagi yazara eslestirilecek :\n");
    yazar = YazSearch(yhead, dizi, NULL, iN);
    if (yazar == NULL)
        yazar = yhead;
    else if (yazar->next == NULL)
        return iN;
    else
        yazar = yazar->next;

    kitap = kitapSearch(khead, dizi, yhead, iN);
    if (kitap == NULL)
        kitap = khead;
    else if (kitap->next == NULL)
        return iN;
    else
        kitap = kitap->next;

    strcpy(dizi[iN].ISBN, kitap->ISBN);
    dizi[iN].YazarID = yazar->yazarID;
    iN++;
    if (iN % 10 == 0)
    {
        (*kydizi) = (KitapYazar *)realloc((*kydizi), sizeof(KitapYazar) * iN);
    }
    updateKY((*kydizi), iN);
    return iN;
}
void KYguncelle(KitapYazar *kydizi, int iN, Yazar *yhead, Kitap *khead)
{
    KitapYazar *dizi = kydizi;
    Kitap *kitap;
    Yazar *yazar;
    int i = 0, f;
    printf("Hangi kitabin yazari guncellencek :\n");
    kitap = kitapSearch(khead, dizi, yhead, iN);
    if (kitap == NULL)
        kitap = khead;
    else if (kitap->next == NULL)
        return;
    else
        kitap = kitap->next;

    while (i < iN)
    {
        if (!strcmp(dizi[i].ISBN, kitap->ISBN))
        {
            if (dizi[i].YazarID >= 0)
                printf("%d id'li Yazarini guncellemek icin 1 giriniz\n", dizi[i].YazarID);
            if (dizi[i].YazarID == -1)
                printf("Bu kitabin bir yazari silinmistir onu guncellemek icin 1\n");
            printf("devametmek icin 0\n");
            scanf("%d", &f);
            if (f == 1)
            {
                yazar = YazSearch(yhead, NULL, NULL, 0);
                if (yazar == NULL)
                    yazar = yhead;
                else if (yazar->next == NULL)
                    return;
                else
                    yazar = yazar->next;
                dizi[i].YazarID = yazar->yazarID;
            }
        }
        i++;
    }
    updateKY(kydizi, iN);
}
void updateKY(KitapYazar *kydizi, int iN)
{
    int i = 1;
    FILE *fp = fopen("KitapYazar.csv", "w");
    if (iN > 0)
        ;
    fprintf(fp, "%s,%d", kydizi[0].ISBN, kydizi[0].YazarID);
    while (i < iN)
    {
        fprintf(fp, "\n%s,%d", kydizi[i].ISBN, kydizi[i].YazarID);
        i++;
    }
    fclose(fp);
}

void yazarIDsearch(int id, void *yhead)
{
    Yazar *head = yhead;
    while (head->yazarID != id)
        head = head->next;
    printf("ID:%d | %s-%s\n", id, head->yazarAd, head->yazarSoyad);
}

int countRaf(KitapOrnek *ornek)
{
    int i = 0;
    while (ornek != NULL)
    {
        if (!strncmp(ornek->Durum, "Rafta", 5))
            i++;
        ornek = ornek->next;
    }
    return i;
}
Kitap *kitapIDcomp(char *entered, Kitap *tmp, char *kitapAD, Kitap *head)
{
    int va1, va2;
    if (tmp == NULL)
    {
        if (strcmp(head->kitapAdi, kitapAD) != 0 || ((atoi(entered) - atoi(head->ISBN)) < 0))
            return NULL;
        if (strcmp(head->kitapAdi, kitapAD) == 0)
            return head;
        tmp = head;
    }
    va1 = atoi(entered);
    while (tmp->next != NULL && strcmp(tmp->next->kitapAdi, kitapAD) == 0)
    {
        va2 = atoi(tmp->next->ISBN);
        if ((va1 - va2) < 0)
            return tmp;
        tmp = tmp->next;
    }
    return tmp;
}
Kitap *KitapAdcomp(char *entered, Kitap *tmp)
{
    if (strcmp(entered, tmp->kitapAdi) <= 0)
        return NULL;

    while (tmp->next != NULL)
    {
        if (strcmp(entered, tmp->next->kitapAdi) <= 0)
            return tmp;
        tmp = tmp->next;
    }
    return tmp;
}
void addSorted(Kitap *tmp2, Kitap **Head, Kitap *tmp)
{
    if (tmp2 == NULL)
    {
        tmp->next = NULL;
        (*Head) = tmp;
        return;
    }
    tmp2 = KitapAdcomp(tmp->kitapAdi, (*Head));
    tmp2 = kitapIDcomp(tmp->ISBN, tmp2, tmp->kitapAdi, (*Head));
    if (tmp2 == NULL)
    {
        tmp->next = (*Head);
        (*Head) = tmp;
        return;
    }
    if (tmp2->next != NULL)
        tmp->next = tmp2->next;
    else
        tmp->next = NULL;
    tmp2->next = tmp;
}
void KitapAdd(void *head)
{
    Kitap *tmp = (Kitap *)malloc(sizeof(Kitap));
    Kitap **Head = head;
    Kitap *tmp2 = (*Head);
    printf("Kitap adini giriniz: ");
    fflush(stdin);
    scanf("%[^\n]", tmp->kitapAdi);
    printf("Kitap ISBN Numarasini giriniz:");
    fflush(stdin);
    scanf("%s", tmp->ISBN);
    printf("Kitap adet bilgisini giriniz:");
    scanf("%d", &(tmp->adet));
    KitapOrnekOlustur(tmp, ornekRaftaBasla);
    addSorted(tmp2, Head, tmp);
    updateKitap((*Head));
}
void KitapPrint(void *head)
{
    Kitap *tmp = head;
    while (tmp != NULL)
    {
        printf("ISBN: %s => %s-%d \n", tmp->ISBN, tmp->kitapAdi, tmp->adet);
        tmp = tmp->next;
    }
}
void *kitapSearch(void *head, void *iliski, void *otherHead, int iN)
{
    char kitapAdi[30];
    int i = 0;
    Kitap *tmp = head;
    Kitap *tmp2;
    KitapYazar *kydizi = iliski;
    printf("Kitap Adini giriniz\n");
    fflush(stdin);
    scanf("%[^\n]", kitapAdi);
    tmp = KitapAdcomp(kitapAdi, tmp);
    if (tmp == NULL)
    {
        tmp2 = NULL;
        tmp = head;
    }
    else if (tmp->next == NULL)
    {
        printf("There is no one with this name !\n");
        return tmp;
    }
    else
    {
        tmp2 = tmp;
        tmp = tmp->next;
    }

    printf("ISBN:%s | %s-%d\n", tmp->ISBN, tmp->kitapAdi, tmp->adet);
    if (iN)
    {
        printf("Yazarlari :\n");
        while (i < iN)
        {
            if (!strcmp(kydizi[i].ISBN, tmp->ISBN) && kydizi[i].YazarID >= 0)
                yazarIDsearch(kydizi[i].YazarID, otherHead);
            i++;
        }
        printf("\n");
    }
    printKitapOrnek((tmp->head));
    return tmp2;
}
void kitapDel(void *head, void *iliski, int iN)
{
    Kitap **Head = head;
    Kitap *tmp = kitapSearch((*Head), iliski, NULL, 0);
    Kitap *tmp2;
    if (tmp == NULL)
    {
        tmp = (*Head);
        if (countRaf(tmp->head) > 0)
        {
            printf("Alinin kitap var o nedenle bu kitabi silemezsininz\n");
            return;
        }
        *Head = (*Head)->next;
    }
    else if (tmp->next != NULL)
    {
        tmp2 = tmp->next;
        if (countRaf(tmp->head) > 0)
        {
            printf("Alinin kitap var o nedenle bu kitabi silemezsininz\n");
            return;
        }
        tmp->next = tmp2->next;
        tmp = tmp2;
    }
    kitapOrnekFree(tmp->head);
    free(tmp);
    updateKitap((*Head));
}
void kitapEdit(void *head)
{
    Kitap **Head = head;
    Kitap *tmp = kitapSearch((*Head), NULL, NULL, 0);
    Kitap *tmp2;
    if (tmp == NULL)
    {
        tmp = (*Head);
        *Head = (*Head)->next;
    }
    else if (tmp->next != NULL)
    {
        tmp2 = tmp->next;
        tmp->next = tmp2->next;
        tmp = tmp2;
    }
    else
        return;
    printf("Kitap Yeni adini giriniz: ");
    fflush(stdin);
    scanf("%[^\n]", tmp->kitapAdi);
    fflush(stdin);
    addSorted((*Head), Head, tmp);
    updateKitap((*Head));
}

void KitapOrnekOlustur(Kitap *kitap, void (*funptr)(KitapOrnek *))
{
    KitapOrnek *prev;
    KitapOrnek *ornek;
    char EtkNO[20];
    int i;
    for (i = 1; i <= kitap->adet; i++)
    {
        ornek = (KitapOrnek *)malloc(sizeof(KitapOrnek));
        if (i == 1)
            kitap->head = ornek;
        else
            prev->next = ornek;
        sprintf(EtkNO, "%s_%d", kitap->ISBN, i);
        strcpy(ornek->EtiketNo, EtkNO);

        funptr(ornek);
        prev = ornek;
    }
    ornek->next = NULL;
}
void printKitapOrnek(KitapOrnek *head)
{
    while (head != NULL)
    {
        printf("%s - %s \n", head->EtiketNo, head->Durum);
        head = head->next;
    }
}
void kitapOrnekFree(KitapOrnek *head)
{
    KitapOrnek *tmp;
    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

void loadKitapOrnek(void *head, char *Line)
{
    Kitap **Head = head;
    Kitap *tmp = (*Head);
    KitapOrnek *ohead;
    char Etk[20];
    char ID[9];
    int g, a, y;
    int aktif;
    sscanf(Line, "%[^,],%[^,],%d,%d.%d.%d\n", Etk, ID, &(aktif), &(g), &(a), &(y));
    if (aktif)
    {
        while (tmp != NULL && strncmp(Etk, tmp->ISBN, 13) != 0)
            tmp = tmp->next;
        if (tmp != NULL)
        {
            ohead = tmp->head;
            while (strcmp(Etk, ohead->EtiketNo))
                ohead = ohead->next;
            strcpy(ohead->Durum, ID);
        }
    }
}

void loadKitapa(void *head, char *Line)
{
    Kitap *tmp = (Kitap *)malloc(sizeof(Kitap));
    Kitap **Head = head;
    Kitap *tmp2 = (*Head);
    sscanf(Line, "%[^,],%[^,],%d\n", tmp->kitapAdi, tmp->ISBN, &(tmp->adet));
    KitapOrnekOlustur(tmp, ornekRaftaBasla);
    addSorted(tmp2, Head, tmp);
}
void updateKitap(Kitap *head)
{
    FILE *fptr;
    Kitap *tmp = head;
    fptr = fopen("Kitaplar.csv", "w+");
    while (tmp != NULL)
    {
        fprintf(fptr, "%s,%s,%d", tmp->kitapAdi, tmp->ISBN, tmp->adet);
        tmp = tmp->next;
        if (tmp != NULL)
            fputs("\n", fptr);
    }
    fclose(fptr);
}
void kitapfreeMem(Kitap **head)
{
    Kitap *tmp = *head;
    Kitap *prev;
    if (*head == NULL)
        return;
    while (tmp->next != NULL)
    {
        prev = tmp;
        tmp = tmp->next;
        kitapOrnekFree(prev->head);
        free(prev);
    }
    free(tmp);
    (*head) = NULL;
}

int ogrAdcomp(char *entered, Ogrenci *tmp)
{
    return strcmp(entered, tmp->ad);
}
int ogrSoyadcomp(char *entered, Ogrenci *tmp)
{
    return strcmp(entered, tmp->soyad);
}
int ogrIDcomp(char *entered, Ogrenci *tmp)
{
    return strcmp(entered, tmp->ogrID);
}
Ogrenci *ogrSer(char *entered, Ogrenci *tmp, int (*funcptr)(char *, Ogrenci *))
{
    while (tmp != NULL && funcptr(entered, tmp))
    {
        tmp = tmp->next;
    }
    return tmp;
}
void OgrPrint(void *head)
{
    Ogrenci *tmp = head;
    while (tmp != NULL)
    {
        printf("ID: %s => %s-%s || Grade: %d\n", tmp->ogrID, tmp->ad, tmp->soyad, tmp->puan);
        tmp = tmp->next;
    }
    /*while (tmp->prev != NULL)
    {
        tmp = tmp->prev;
        printf("%s %s %s %d\n",tmp->ogrID,tmp->ad,tmp->soyad,tmp->puan);
    } */
}
void OgrAdd(void *head)
{ // ogrenci id
    FILE *fptr;
    Ogrenci **tmp2 = head;
    Ogrenci *tmp = (Ogrenci *)malloc(sizeof(Ogrenci));
    fptr = fopen("Ogrenciler.csv", "a+");
    printf("Enter student name: ");
    scanf("%s", tmp->ad);
    printf("Enter student surname: ");
    scanf("%s", tmp->soyad);
    do
    {
        printf("Enter student ID: ");
        scanf("%s", tmp->ogrID);
    } while (ogrSer(tmp->ogrID, (*tmp2), ogrIDcomp) != NULL);

    tmp->puan = 100;

    if (*tmp2 != NULL)
    {
        (*tmp2)->prev = tmp;
        fputs("\n", fptr);
    }
    tmp->next = *tmp2;
    tmp->prev = NULL;
    *tmp2 = tmp;

    fprintf(fptr, "%s,%s,%s,%d", tmp->ogrID, tmp->ad, tmp->soyad, tmp->puan);

    fclose(fptr);
}
void *OgrSearch(void *head, void *iliski, void *otherHead, int iN)
{
    char entered[30];
    char *strings[3] = {"Name", "Surname", "ID"};
    int (*Fptr[3])(char *, Ogrenci *) = {ogrAdcomp, ogrSoyadcomp, ogrIDcomp};
    Ogrenci *tmp = head;
    KitapOdunc *dizi = iliski;
    int x, i = 0;

    printf("0 > Search Name\n");
    printf("1 > Search Surname\n");
    printf("2 > Search ID\n");
    scanf("%d", &x);
    printf("Enter Student %s\n", strings[x]);
    scanf("%s", entered);
    tmp = ogrSer(entered, tmp, Fptr[x]);

    if (tmp == NULL)
    {
        printf("There is no one with this Info !\n");
        return NULL;
    }
    printf("ID: %s => %s-%s || Grade: %d\n", tmp->ogrID, tmp->ad, tmp->soyad, tmp->puan);
    if (iN)
    {
        while (i < iN)
        {
            if (!strcmp(tmp->ogrID, dizi[i].ogrID))
            {
                printf("%s,%s,%u,%u.%u.%u\n", dizi[i].EtiketNo, dizi[i].ogrID, dizi[i].islemTipi,
                       dizi[i].islemTarihi.gun, dizi[i].islemTarihi.ay, dizi[i].islemTarihi.yil);
            }
            i++;
        }
    }
    return tmp;
}
void OgrDel(void *head, void *iliski, int iN)
{
    Ogrenci **Head = head;
    Ogrenci *tmp = OgrSearch((*Head), iliski, NULL, 0);
    if (tmp == NULL)
        return;
    if (tmp == (*Head))
    {
        if (tmp->next != NULL)
            (*Head) = tmp->next;
        else
            (*Head) = NULL;
        free(tmp);
        updateOgr((*Head));
        return;
    }
    if (tmp != NULL)
    {

        if (tmp->next != NULL)
            tmp->next->prev = tmp->prev;
        tmp->prev->next = tmp->next;
        free(tmp);
        updateOgr((*Head));
    }
}
void OgrEdit(void *head)
{
    Ogrenci **Head = head;
    Ogrenci *tmp = OgrSearch((*Head), NULL, NULL, 0);
    if (tmp != NULL)
    {
        printf("Enter student name: ");
        scanf("%s", tmp->ad);
        printf("Enter student surname: ");
        scanf("%s", tmp->soyad);
        printf("Enter student ID: ");
        scanf("%s", tmp->ogrID);
        printf("Enter Student grad:");
        scanf("%d", &tmp->puan);
    }
    updateOgr((*Head));
}
void OgrfreeMem(Ogrenci **head)
{
    Ogrenci *tmp = *head;
    if (*head == NULL)
        return;
    while (tmp->next != NULL)
    {
        tmp = tmp->next;
        free(tmp->prev);
    }
    free(tmp);
    (*head) = NULL;
}
void loadOgr(void *head, char *Line)
{
    Ogrenci **Head = head;
    Ogrenci *tmp = (Ogrenci *)malloc(sizeof(Ogrenci));
    sscanf(Line, "%[^,],%[^,],%[^,],%d\n", tmp->ogrID, tmp->ad, tmp->soyad, &(tmp->puan));

    if (*Head != NULL)
    {
        (*Head)->prev = tmp;
    }
    tmp->next = *Head;
    tmp->prev = NULL;
    *Head = tmp;
}
void updateOgr(Ogrenci *head)
{
    FILE *fptr;
    Ogrenci *tmp = head;
    fptr = fopen("Ogrenciler.csv", "w+");

    while (tmp != NULL)
    {
        fprintf(fptr, "%s,%s,%s,%d", tmp->ogrID, tmp->ad, tmp->soyad, tmp->puan);
        tmp = tmp->next;
        if (tmp != NULL)
            fputs("\n", fptr);
    }
    fclose(fptr);
}

void updateYazar(Yazar *head)
{
    FILE *fptr;
    Yazar *tmp = head;
    fptr = fopen("Yazarlar.csv", "w+");
    while (tmp != NULL)
    {
        fprintf(fptr, "%d,%s,%s", tmp->yazarID, tmp->yazarAd, tmp->yazarSoyad);
        tmp = tmp->next;
        if (tmp != NULL)
            fputs("\n", fptr);
    }
    fclose(fptr);
}
void YazarfreeMem(Yazar **head)
{
    Yazar *tmp = *head;
    Yazar *prev;
    if (*head == NULL)
        return;
    while (tmp->next != NULL)
    {
        prev = tmp;
        tmp = tmp->next;
        free(prev);
    }
    free(tmp);
    (*head) = NULL;
}
void loadYazara(void *head, char *Line)
{
    Yazar **Head = head;
    Yazar *tmp = (Yazar *)malloc(sizeof(Yazar));
    Yazar *tmp2 = (*Head);
    sscanf(Line, "%d,%[^,],%[^\n ]", &(tmp->yazarID), tmp->yazarAd, tmp->yazarSoyad);

    tmp->next = NULL;
    if (tmp2 == NULL)
    {
        (*Head) = tmp;
        return;
    }
    while (tmp2->next != NULL)
    {
        tmp2 = tmp2->next;
    }
    tmp2->next = tmp;
}
void YazPrint(void *head)
{
    Yazar *tmp = head;
    while (tmp != NULL)
    {
        printf("ID: %d => %s - %s \n", tmp->yazarID, tmp->yazarAd, tmp->yazarSoyad);
        tmp = tmp->next;
    }
}
void guncelle(Yazar *yazar)
{
    char yazarAd[30];
    char yazarSoyad[30];
    printf("%d %s %s Yazarin yeni bilgilerini giriniz\n", yazar->yazarID, yazar->yazarAd, yazar->yazarSoyad);
    printf("Yazar adini giriniz: ");
    scanf("%s", yazarAd);
    printf("Yazar soyadinin giriniz: ");
    scanf("%s", yazarSoyad);
    strcpy(yazar->yazarAd, yazarAd);
    strcpy(yazar->yazarSoyad, yazarSoyad);
}
void YazEdit(void *head)
{
    Yazar **Head = head;
    Yazar *tmp = YazSearch((*Head), NULL, NULL, 0);
    if (tmp == NULL)
    {
        guncelle((*Head));
    }
    else if (tmp->next != NULL)
    {
        guncelle(tmp->next);
    }
    updateYazar((*Head));
}
void YazDel(void *head, void *iliski, int iN)
{
    Yazar **Head = head;
    Yazar *tmp = YazSearch((*Head), NULL, NULL, 0);
    Yazar *tmp2;
    KitapYazar *ilisk = iliski;
    if (tmp == NULL)
    {
        tmp = *Head;
        *Head = (*Head)->next;
        KYdelyazar(ilisk, tmp->yazarID, iN);
        free(tmp);
    }
    else if (tmp->next != NULL)
    {
        tmp2 = tmp->next;
        tmp->next = tmp2->next;
        KYdelyazar(ilisk, tmp2->yazarID, iN);
        free(tmp2);
    }
    updateYazar((*Head));
}
void *YazSearch(void *head, void *iliski, void *otherHead, int iN)
{
    char yazarAd[30];
    Yazar *tmp = head;
    Yazar *prev = NULL;
    int i = 0;
    KitapYazar *kydizi = iliski;
    Kitap *khead = otherHead;
    Kitap *ktmp;
    printf("Yazarin adini giriniz\n");
    scanf("%s", yazarAd);
    while (tmp != NULL && strcmp(yazarAd, tmp->yazarAd))
    {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL)
    {
        printf("There is no one with this name !\n");
        return prev;
    }
    printf("\nYazar :%d %s %s\n", tmp->yazarID, tmp->yazarAd, tmp->yazarSoyad);
    if (iN)
    {
        printf("\nKitaplari :\n");
        while (i < iN)
        {
            if (kydizi[i].YazarID == tmp->yazarID)
            {
                ktmp = khead;
                while (ktmp != NULL && strcmp(ktmp->ISBN, kydizi[i].ISBN))
                    ktmp = ktmp->next;
                if (ktmp != NULL)
                {
                    printf("%s |  %s\n", ktmp->ISBN, ktmp->kitapAdi);
                    printKitapOrnek(ktmp->head);
                    printf("\n");
                }
            }
            i++;
        }
    }
    return prev;
}
void YazAdd(void *head)
{ // prev dondurur
    FILE *fptr;
    Yazar *tmp = (Yazar *)malloc(sizeof(Yazar));
    Yazar **Head = head;
    Yazar *tmp2 = (*Head);
    printf("Yazar adini giriniz: ");
    scanf("%s", tmp->yazarAd);
    printf("Yazar soyadinin giriniz: ");
    scanf("%s", tmp->yazarSoyad);
    tmp->next = NULL;

    if (tmp2 == NULL)
    {
        tmp->yazarID = 1;
        (*Head) = tmp;
        return;
    }

    while (tmp2->next != NULL)
    {
        tmp2 = tmp2->next;
    }
    tmp->yazarID = tmp2->yazarID + 1;

    tmp2->next = tmp;
    fptr = fopen("Yazarlar.csv", "a+");
    if (*Head != NULL)
        fputs("\n", fptr);
    fprintf(fptr, "%d,%s,%s", tmp->yazarID, tmp->yazarAd, tmp->yazarSoyad);
    fclose(fptr);
}