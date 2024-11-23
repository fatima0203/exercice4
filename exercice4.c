#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<semaphore.h>

int compteur =0;
int n;
sem_t sem1 ,sem2;


void *fthread1( void* arg)
{

    while(1)
    {
          sem_wait(&sem1);
           printf(" %d\n",compteur++ );
          if( compteur == n)
             for(int i=0 ;i<2*n ;i++)
                     sem_post(&sem2);


    }

        pthread_exit(NULL);

}

void *fthread2( void* arg)
{

    while(1)
    {
         sem_wait(&sem2);
         printf("%d\n",compteur--);

        if(compteur == (-n ) )
            for(int i=0 ;i<2*n ;i++)
                      sem_post(&sem1);


    }

        pthread_exit(NULL);

}


int main(int argc ,char const *argv[])
{

    if(argc <2)
    {
        perror("Nombre argument insuffissant");
        return 0;
    }
    n= atoi(argv[1]);

    pthread_t th1;
    pthread_t th2;
    int result;
    //initialisation des semaphores
     result = sem_init(&sem1 ,0,n);
     if(result == -1)
     {
         perror("Erreur d'initialisation de la sempahore");
         return 0;
     }

      result = sem_init(&sem2 ,0, 0);
     if(result == -1)
     {
         perror("Erreur d'initialisation de la sempahore");
         return 0;
     }



    int resultat1 ,resultat2;

      resultat1 = pthread_create( &th1 ,NULL ,fthread1 ,(void*) NULL);

      if(resultat1 == -1)
      {
          perror("erreur de creation du thread secondaire");
          return 0;
      }

      resultat2 = pthread_create( &th2 ,NULL ,fthread2,(void*) NULL);

      if(resultat2 == -1)
      {
          perror("erreur de creation du thread secondaire");
          return 0;
      }

        pthread_join(th1 ,NULL);
        pthread_join(th2 ,NULL);

        result = sem_destroy(&sem1);
        result = sem_destroy(&sem2);

    return 0;
}
