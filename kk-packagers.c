#include <stdio.h>

/**
 * main - program entry point
 * Return: Always 0 (success)
 */
struct EMPLOYEE_PAY
{
    char name[50];
    char position[20];
    int working_hours;
};

void fileRead(FILE *ifp, char *file);
void fileWrite(FILE *ofp, char *name);

int main(void)
{
    FILE *fp;
    char file[] = "weekly_payload.txt";
    /*char week_id[10];*/
    char c;

    if ((fp = fopen(file, "r")) == NULL)
    {
        fprintf(stderr, "Can't open file! File doesn't exist or lacks right permissions.\n");
        printf("Create a new file? -- y/n: ");
        scanf("%c", &c);

        if (c == 'y' || c == 'Y')
        {
            fp = fopen(file, "a+");
            fputs("CATEGORY_ID\tPOSITION\t\t\tHOURLY_RATE\tHOURLY_RATE_OVERTIME", fp);
            fputs("\n----------------------------------------------------------------------------------------------\n", fp);
            fclose(fp);
            fileWrite(fp, file);
        }
        else
        {
            return (1);
        }
    }

    fileRead(fp, file);
    printf("\n\nDo you wish to add new record(s)? -- y/n: ");
    scanf("%c", &c);

    if (c == 'y' || c == 'Y')
    {
        fp = fopen(file, "a+");
        fileWrite(fp, file);
    }

    /*
    printf("\nEnter week identifier: ");
    scanf("%s", week_id);

    printf("\nEmployee Pay details for week %s", week_id);
    */

    return (0);
}

void fileRead(FILE *ifp, char *file)
{
    char m;

    if ((ifp = fopen(file, "r")) == NULL)
    {
        printf("Error: Something went wrong! Check your file.");
        return;
    }

    m = fgetc(ifp);
    while (m != EOF)
    {
        printf("%c", m);
        m = fgetc(ifp);
    }
    fclose(ifp);
}

void fileWrite(FILE *ofp, char *name)
{
    char l;

    fileRead(ofp, name);
    printf("\n");
    fopen(name, "a");

    while ((l = fgetc(stdin)))
    {
        if ((l == 27))
            break;
        fputc(l, ofp);
    }

    fclose(ofp);
}
