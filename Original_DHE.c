#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<time.h>


// Power function to return value of a ^ b mod P
long long int power(long long int a, long long int b, long long int P)
{
    if (b == 1)
        return a;
    else
    {
        double cpy=pow(a, b);
        long long int x = (long long int)(cpy)%P;
        //printf("<><>%lld %f\n",x,cpy);
        return x;
    }
}


int main()
{
    float time_spent = 0.0;

    //DHE Key Exchange Part

    long long int P, G, a, b, x, y, ka, kb;
    clock_t begin = clock();

    printf("***CONFIDENTIAL - Diffie Hellman Key Exchange***\n");
    // Both the persons will be agreed upon the public keys G and P
    printf("\nEnter the value of P which is agreed upon by the SENDER and RECEIVER - ");
    // A prime number P is taken
    scanf("%lld",&P);

    //P =17;
    printf("The value of P : %lld\n", P);

    // A primitve root for P, G is taken
    printf("\nEnter the value of G which is agreed upon by the SENDER and RECEIVER - ");
    scanf("%lld",&G);

    //G =4;
    printf("The value of G : %lld\n\n", G);

    // Sender will choose the private key a
    printf("***SENDER***\n\nEnter SENDER's private key - ");
    scanf("%lld",&a);

    //a = 3; // a is the chosen private key
    printf("The private key 'ka' for SENDER : %lld\n", a);
    x = power(G, a, P); // gets the generated key

    // Bob will choose the private key b
    printf("\n***RECEIVER***\n\nEnter RECEIVER's private key - ");
    scanf("%lld",&b);

    //b = 6; // b is the chosen private key
    printf("The private key 'kb' for RECEIVER : %lld\n\n", b);
    y = power(G, b, P); // gets the generated key

    // Generating the secret key after the exchange of keys
    ka = power(y, a, P); // Secret key for Sender
    kb = power(x, b, P); // Secret key for receiver

    printf("***SENDER***\n\n");
    printf("SENDER's Shared Secret key : %lld\n\n", ka);

    printf("***RECEIVER***\n\n");
    printf("RECEIVER's Shared Secret key : %lld\n", kb);

    printf("\n***KEY EXCHANGE SUCCESSFUL***\n");

    clock_t end = clock();

    time_spent += (float)(end - begin)/CLOCKS_PER_SEC;
    printf("Time elapsed is %f seconds", time_spent);
    return 0;
}
