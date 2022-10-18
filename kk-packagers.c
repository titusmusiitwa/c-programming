#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * main - program entry point
 * Return: Always 0 (success)
 */
struct EMPLOYEE_PAY
{
    char name[50];
    char position[32];
    int working_hours;
    float salary;
};

void fileRead(FILE *ifp, char *file);
void fileWrite(FILE *ofp, char *name);
void addEmployeeDetails(FILE *afp, char *file, struct EMPLOYEE_PAY emp, float dollar);
float getSalary(char *filename, int hours, char *position, float dollar);

int main(void)
{
    FILE *fp, *wpp;
    char file[] = "weekly_payload.txt";
    char week_id[20];
    char c;
    struct EMPLOYEE_PAY pay;
    float dollar;

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

    printf("\nEnter week identifier: ");
    scanf("%s", week_id);
    printf("Dollar value: ");
    scanf("%f", &dollar);
    printf("\nEnter employee details for the week\n-----------------------------------");
    strcat(week_id, ".txt");

    fp = fopen(file, "r");

    if ((wpp = fopen(week_id, "r")) == NULL)
    {
        fprintf(wpp, "Employee Payment details for week {{%s}}", week_id);
        fputs("\n------------------------------------------------\n", wpp);
        fclose(wpp);
    }
    else
    {
        wpp = fopen(week_id, "a");
    }

    addEmployeeDetails(wpp, file, pay, dollar);
    fileRead(wpp, week_id);

    printf("\n\nAdd other employee pay details? -- y/n: ");
    scanf(" %c", &c);

    if (c == 'y' || c == 'Y')
    {
        addEmployeeDetails(wpp, file, pay, dollar);
    }
    else
    {
        fclose(wpp);
        return (1);
    }

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

float getSalary(char *filename, int hours, char *position, float dollarValue)
{
    FILE *rfp;
    float payable;
    int l = strlen(position);
    int i, j;
    char c;
    char qstr[16], tmp[16], string[100], next1[5], next2[5];
    float h_rate, h_o_rate;

    if ((rfp = fopen(filename, "r")) == NULL)
    {
        printf("Error reading file!");
        return (-1);
    }

    if (hours < 40)
    {
        payable = 0.0;
    }
    else if (hours >= 40)
    {
        if (strstr(position, " "))
        {
            i = l - 1;
            j = 0;
            while (position[i] != ' ')
            {
                c = position[i];
                tmp[j] = c;
                j++;
                i--;
            }
            j = strlen(tmp) - 1;
            i = 0;
            while (j > -1)
            {
                qstr[i] = tmp[j];
                i++;
                j--;
            }
        }
        else
        {
            i = 0;
            while (i < l)
            {
                qstr[i] = position[i];
            }
        }

        while ((fscanf(rfp, "%s", string)) == 1)
        {
            if (strstr(string, qstr))
            {
                fscanf(rfp, "%s", next1);
                fscanf(rfp, "%s", next2);
            }
        }

        h_rate = atof(next1);
        h_o_rate = atof(next2);

        payable = dollarValue * (40 * h_rate + (hours - 40) * h_o_rate);
    }

    fclose(rfp);

    return payable;
}

void addEmployeeDetails(FILE *afp, char *file, struct EMPLOYEE_PAY emp, float dollar)
{
    char g;
    do
    {
        printf("\nEmployee name: ");
        scanf(" %[^\n]%*c", emp.name);
        printf("Position: ");
        scanf(" %[^\n]%*c", emp.position);
        printf("Working Hours: ");
        scanf("%d", &emp.working_hours);

        emp.salary = getSalary(file, emp.working_hours, emp.position, dollar);
        fprintf(afp, "%s\t\t%s\t\t%d\t%0.2f\n", emp.name, emp.position, emp.working_hours, emp.salary);

        printf("Add employee? -- y/n: ");
        scanf(" %c", &g);
    } while ((g == 'y' || g == 'Y'));
    fclose(afp);
}