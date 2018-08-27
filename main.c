#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#define NUMBER_OF_MENU 25
#define FOOD_FILE_PATH "./food.txt"
#define MAXLINE 200

struct food {
    int serial_number;
    char *name;
    char *address;
    char *menu[NUMBER_OF_MENU];
    int type;
};

char input;
void home_page();
int add();
int view(char *);
int getline(char line[], int max);
int num_of_rows(char *);
void casual(char *);


int main(int argc, char *argv[])
{
    while (1) {
        home_page();
        switch (input) {
        case '0':
            exit(0);
            break;
        case '1':
            add();
            break;
        case '2':
            view(FOOD_FILE_PATH);
            system("pause");
            break;
        case '3':
            casual(FOOD_FILE_PATH);
            break;
        dafault:
            printf("error input.");
            break;
        }     
    }
    return 0;
}



/*
HOME PAGE
*/
void home_page(void)
{
    system("cls");
    printf("-----------------吃啥------------------\n");
    printf("-            0:退出\n");
    printf("-            1:添加\n");
    printf("-            2:查看\n");
    printf("-            3:随便\n");
    printf("-            4:选一下\n");
    printf("-            5:推荐\n");
    printf("---------------------------------------\n");
    printf("请输入：");
    input = getchar();
    rewind(stdin);
}




/*
add
*/
int add()
{
    int i = 0;
    FILE * fp;
    int size;
    char flag = 'n';
    fp = fopen(FOOD_FILE_PATH, "a");
    char line[MAXLINE];
    do {
        size = getline(line, MAXLINE);
        if (size <= 0) {
            printf("error, input again\n");
            continue;
        }
        i = 0;
        while(line[i] != '\0' && line[i] != '\n') {
            printf("%c", line[i]);
            putc(line[i], fp);
            i++;
        }
        if (line[i] == '\n') {
            putc('\n', fp);
        }
        
        printf("add more(y/n)?");
        flag = getchar();
        rewind(stdin);
    } while (flag == 'y' || flag == 'Y');
    fclose(fp);
}

/*
getline
*/
int getline(char line[], int max)
{
    int i;
    char c;
    i = 0;
    rewind(stdin);
    printf("input the information：");
    c = getchar();
    //getchar();
    while (--max > 0 && (c != EOF) && c != '\n') {
        line[i++] = c;
        c = getchar();
    }
    if (c == '\n') {
        line[i++] = '\n';
    }
    line[i] = '\0';
    return i;
}

/*
view
*/
int view(char *filepath)
{
    int line = 0;
    FILE *fp;
    char c;
    fp = fopen(filepath, "r");
    while ((c = getc(fp)) != EOF) {
        putc(c, stdout);
    }
    fclose(fp);
}

/*
*casual
*/
void casual(char *filepath)
{
    int rows;
    int casual_num;
    int count = 0;
    char c;
    FILE *fp;
    fp = fopen(filepath, "r");
    srand(time(NULL));
    rows = num_of_rows(FOOD_FILE_PATH);
    casual_num = rand() % rows + 1;
    while (count != (casual_num -1) && (c = getc(fp)) != EOF) {
        if (c == '\n') {
            count++;
        }
    }
    c = getc(fp);
    while (c != EOF && c != '\n') {
        putc(c, stdout);
        c = getc(fp);
    }
    getchar();
    fclose(fp);
}


/*
返回文本行数
*/

int num_of_rows(char *filepath)
{
    int rows = 0;
    char c;
    char *fp;
    fp = fopen(filepath, "r");
    while ((c = getc(fp)) != EOF) {
        if (c == '\n') {
            rows++;
        }
    }
    fclose(fp);
    return rows;
}
