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
    char subsPT[63];
    long long int subsCT[63];
    char ch='a';
    long long int i;

    /********************************************************************************************/

    //substituiton ciphertext array
    char alphabets[63]={'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',' '};
    long long int prime[63]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307};



    //plaintext alphabets initialising array
    for(i=0;i<63;i++)
    {
        subsPT[i]=alphabets[i];
    }
    //ciphertext alphabets initialising array
    for(i=0;i<63;i++)
    {
        subsCT[i]=prime[i];
    }
    /********************************************************************************************/

    //DHE Key Exchange Part


    long long int P, G, a, b, x, y, ka, kb;
    float time_spent = 0.0;
    clock_t begin = clock();
    printf("***CONFIDENTIAL - Diffie Hellman Key Exchange***\n");
    // Both the persons will be agreed upon the public keys G and P
    printf("\nEnter the value of P which is agreed upon by the SENDER and RECEIVER - ");
    // A prime number P is taken
    scanf("%lld",&P);
    //P = 23;
    printf("The value of P : %lld\n", P);

    // A primitve root for P, G is taken
    printf("\nEnter the value of G which is agreed upon by the SENDER and RECEIVER - ");
    scanf("%lld",&G);
    //G = 9;
    printf("The value of G : %lld\n\n", G);

    // Sender will choose the private key a
    printf("***SENDER***\n\nEnter SENDER's private key - ");
    scanf("%lld",&a);
    //a = 4; // a is the chosen private key
    printf("The private key 'ka' for SENDER : %lld\n", a);
    x = power(G, a, P); // gets the generated key

    // Bob will choose the private key b
    printf("\n***RECEIVER***\n\nEnter RECEIVER's private key - ");
    scanf("%lld",&b);
    //b = 3; // b is the chosen private key
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

    printf("Enter any key to continue to message transmission page !!");
    getch();
    system("cls");

    /********************************************************************************************/

    //ENCRYPTION
    char msg[100];
    long long int msglen,j,k;
    char alpha;
    long long int encryptedmsg[100];

    printf("***SENDER SIDE***\n");
    printf("\nEnter the message to be transmitted - ");
    fflush(stdin);
    gets(msg);
    //printf("<>DONE<>");
    printf("Message from the SENDER -  %s\n",msg);    msglen=strlen(msg);
    //printf("\nMessage length - %d\n",msglen);
    printf("\n***ENCRYPTION AT SENDER SIDE***\n");
    printf("\nSENDER's Shared Key : %lld",ka);
    k=0;
    while(k<msglen)
    {
        alpha=msg[k];
        for(i=0;i<63;i++)
        {
            if(subsPT[i]==alpha)
            {
                printf("%d",i);
                encryptedmsg[k]=subsCT[i];
                k++;
                break;
            }
        }
    }

    printf("\nSENDER's Message Encrypted As :");
    for(i=0;i<msglen;i++)
    {
        printf("\n%c\t",msg[i]);
        printf("%lld\t",encryptedmsg[i]);
    }

    //Formula used on the key
    for(i=0;i<msglen;i++)
    {
        encryptedmsg[i]=encryptedmsg[i]*ka+ka*ka;
    }

    printf("\n\n***TRANSMITTED MESSAGE VISIBLE TO MIDDLEMAN/ATTACKER OVER THE NETWORK***\n");
    printf("\nMessage transmitted as : ");

    for(i=0;i<msglen;i++)
    {
        printf("%lld ",encryptedmsg[i]);
    }


/********************************************************************************************/

    //DECRYPTION
    long long int decryptedmsg[100],copydecryptedmsg[100];
    char receivedmsg[100];
    long long int num;


    for(i=0;i<msglen;i++)
    {
        decryptedmsg[i]=encryptedmsg[i];
        copydecryptedmsg[i]=encryptedmsg[i];
    }

    //undoing the computation on the key
    for(i=0;i<msglen;i++)
    {
        decryptedmsg[i]=(decryptedmsg[i]-(kb*kb))/kb;
    }

    k=0;
    while(k<msglen)
    {
        num=decryptedmsg[k];
        for(i=0;i<63;i++)
        {
            if(subsCT[i]==num)
            {
                receivedmsg[k]=subsPT[i];
                k++;
                break;
            }
        }
    }

    printf("\n\n***DECRYPTION AT RECEIVER SIDE***\n");
    printf("\nRECEIVER's Shared Key - %lld",kb);

    printf("\nRECEIVER's Decrypts Message As :");
    for(i=0;i<msglen;i++)
    {
        printf("\n%lld\t",copydecryptedmsg[i]);
        printf("%c\t",receivedmsg[i]);
    }

    printf("\n\n***RECEIVER SIDE***\n");
    printf("\nMessage Received by RECEIVER : ");
    for(i=0;i<msglen;i++)
    {
        printf("%c",receivedmsg[i]);
    }
    printf("\n\n***TRANSMISSION SUCCESSFUL***\n");

    clock_t end = clock();

    time_spent += (float)(end - begin)/CLOCKS_PER_SEC;
    printf("Time elapsed is %f seconds", time_spent);
    return 0;
}
