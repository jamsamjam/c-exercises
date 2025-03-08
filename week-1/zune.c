#include <stdio.h>

typedef enum {
    JANUARY = 1,
    FEBRUARY,
    MARCH,
    APRIL,
    MAY,
    JUNE,
    JULY,
    AUGUST,
    SEPTEMBER,
    OCTOBER,
    NOVEMBER,
    DECEMBER
} Month;

int IsLeapYear(int y)
{
    return (((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0));
}

int DaysForMonth(int year, Month month)
{
    int days = 31;

    switch (month) {
        case FEBRUARY:
            days = IsLeapYear(year) ? 29 : 28;
            break;
        case APRIL:
        case JUNE:
        case SEPTEMBER:
        case NOVEMBER:
            days = 30;
            break;
        default:
            break;
    }
    return days;
}

int main(void)
{    
    int year = 1979;
    Month month = DECEMBER;
    int day = 31;
    int days = 0;

    printf("Enter the number of days since 12/31/1979: ");
    scanf("%d", &days);

    // check if days >= 0 ?

    day += days;

    while (days >= (IsLeapYear(year) ? 366 : 365)) {
        day -= IsLeapYear(year) ? 366 : 365;
        year += 1;
    }

    while (days > DaysForMonth(year, month)) {
        days -= DaysForMonth(year, month);
        if (month == DECEMBER) {
            month = JANUARY;
            year++;
        } else {
            month++;
        }
    }

    printf("%02d/%02d/%d\n", day, month, year);
    
    return 0;
}