#include <stdio.h>

/**
 * main - program entry point
 * Return: Always 0 (success)
 */
#define MAX_BUFF_SIZE = 1032;

void fileWrite(FILE *ofp, char *name);

int main(void)
{
    FILE *fp;
    char file[] = "weekly_payload.txt";
    char c;

    if ((fp = fopen(file, "r")) == NULL)
    {
        fprintf(stderr, "Can't open file! File doesn't exist or lacks right permissions.\n");
        printf("Create a new file? -- y/n: ");
        scanf("%c", &c);

        if (c == 'y' || c == 'Y')
        {
            fp = fopen(file, "a+");
            fputs("CATEGORY_ID\t\tPOSITION\t\tHOURLY_RATE\t\tHOURLY_RATE_OVERTIME", fp);
            fputs("\n----------------------------------------------------------------------------------------------\n", fp);
            fclose(fp);
            fileWrite(fp, file);
        }
        else
        {
            return (1);
        }
    }

    return (0);
}

void fileWrite(FILE *ofp, char *name)
{
    char l;
    if ((ofp = fopen(name, "r")) == NULL)
    {
        ofp = fopen(name, "a+");
    }

    l = fgetc(ofp);
    while (l != EOF)
    {
        printf("%c", l);
        l = fgetc(ofp);
    }

    fputs("sdfdjksdf", ofp);

    while ((l = fgetc(stdin)))
    {
        if ((l == 27))
            break;
        fputc(l, ofp);
    }
    fclose(ofp);
}