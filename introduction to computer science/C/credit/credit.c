#include<stdio.h>
#include<cs50.h>
#include<math.h>

int length (long int number);
bool check (long int card);


int main(void)
{
    long int card_num;

    card_num = get_long("enter your debit/credit card number\n");
    printf("check if starting with 4 %f\n", card_num/pow(10,15));

    int c13=card_num/pow(10,13), c12=card_num/pow(10,12),c15=card_num/pow(10,15), c14=card_num/pow(10,14);

    if (check(card_num))
    {
        printf("INVALID\n");
    }
    else if (length(card_num)==15 && (c13==34 || c13==37) )
    {
        printf("AMEX\n");

    }
    else if (((length(card_num)==13 && (c12==4)) || ((length(card_num)==16) && (c15==4))))
    {
        printf("VISA\n");
    }
    else if (length(card_num)==16 && (c14 == 51 || c14 == 52 || c14 == 53 || c14 == 54 || c14 == 55))
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID\n");
    }


}


// gets legnth of number
int length (long int number)
{
    int count=0;
    while (number/10 != 0)
    {
// not sure why count not increasing during first loop or division not occuring-store in number
        number/=10;
        count++;
        printf("%li and count is %i\n",number,count);

    }

    if (count>0)
    {
        count++;
    }
    else
    {
        count=0;
    }
    printf("length is %i \n",count);
    return count;
}

// card number  is validated with 0 as valid
bool check (long int card)
{
    int add=0, power=0, total=0,counter=1;
    while (card!=0)
    {
        printf("counter %i\n",counter);
        if (counter%2!=0)
        {

         add+=card%10;
         printf("add%i\n",add);
        }
        else
        {
            if (length(2*(card%10))>1)
            {
                int dummy = 2*(card%10);
                dummy = dummy%10 + dummy/10;
                power+=dummy;
            }
            else
            {
                power+=2*(card%10);
            }
         printf("power%i\n",power);
        }
    counter++;
    card/=10;
    printf("card %li",card);
    }
    total=add+power;
    printf("total is %i\n",total);
    return total%10;

}