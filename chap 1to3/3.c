#include <stdio.h>

int main () 
{
    int day;
    printf("enter day (1-7): ");
    scanf("%d", &day);

    switch (day)
    {
    case 1:printf("Monady");  
           break;
    case 2:printf("tuesday");
           break;
    case 3:printf("wenesday");
           break;
    case 4:printf("thursday");
           break;
    case 5:printf("friday");
           break;
    case 6:printf("saturaday");
           break;
    case 7:printf("sunday");
           break;
    
    default:printf("not a valid day");
        break;
    }
    return 0;

}