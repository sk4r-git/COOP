#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define xstr(s) str(s)
#define str(s) #s


class Exam{
  private:
    size_t sA, sB, sC;
  public:
    char * topic;
    size_t score;
    virtual void updateAbs(){
      score = sA + sB + sC;
    }
    virtual float getWeight(){
      float res = (sA*5 + sB*3 + sC*2) / 10;
      return res;
    }
};

class SimpleString{
  char * buffer;
  size_t len;
  virtual size_t useless(){
    return len;
  }
  virtual void set(char *s){
    strncpy(buffer, s, len);
  }
};



class Music{
    public:
        Music(){
            printf("what size is your music?\n");
            scanf("%d", &length);
            content = new char[length+1];
            getchar();
            printf("what is the content of your music ?\n");
            fgets(content, length+1, stdin);
            getchar();
        }
        Music(int l, char * c) : length(l), content(c){}

        virtual void listen(){
            printf("%s\n", this->content);
        }

        virtual void change(){

        }

        virtual ~Music(){
            delete content;
        }
    private:
        int length;
        char * content;
};

class Shelf{
    public:
        Shelf(){
        }

        virtual void add(){
            int which;
            printf("where do you want to place your music?\n");
            scanf("%d", &which);
            while (which > 20 or which < 0){
                printf("you can't have music here.\n");
                printf("Please choose another place between 0 and 20");
                scanf("%d", &which);
            }

            musics[which] = new Music();
            return;
        }

        virtual void change(){
            int which;
            printf("which music you want to change?\n");
            scanf("%d", &which);
            while (which > 20 or which < 0){
                printf("you can't have music here.\n");
                printf("Please choose another place between 0 and 20");
                scanf("%d", &which);
            }

            musics[which]->change();
            return;
        }

        virtual void listen(){
            int which;
            printf("which music want you to listen?\n");
            scanf("%d", &which);
            while (which > 20 or which < 0){
                printf("you can't have music here.\n");
                printf("Please choose another place between 0 and 20");
                scanf("%d", &which);
            }
            musics[which]->listen();
        }

        virtual void del(){
            int which;
            printf("which one you want to delete?\n");
            scanf("%d", &which);
            while (which > 20 or which < 0){
                printf("you can't have music here.\n");
                printf("Please choose another place between 0 and 20");
                scanf("%d", &which);
            }
            delete musics[which];
            return;
        }

        virtual void del_all(){
            for (int i =0; i < 21; i++){
                if (musics[i] != 0x00){
                    delete musics[i];
                }
            }
        }
    private:
        Music * musics[20];
};

// class Listen{
//     int num;
//     virtual void get_num(){
//         printf("what music do you want to listen?");
//         for (int i = 0; i < music_count; i++){
//             printf("%d, ", i);
//         }
//         printf("%d if you want listen them all.\n", 0);
//         scanf("%d", &num);
//     }

// };


int main() {
    
    int choice;
    Shelf * shelf = new Shelf();
    setvbuf(stdin, 0, 2, 0);
    setvbuf(stdout, 0, 2, 0);
    printf("Let's write or listen some musics\n");


    while (1) {

        printf("=========================================\n");
        printf("1. Write a new music\n");
        printf("2. Change the content of a music\n");
        printf("3. Listen music\n");
        printf("4. Delete a music\n");
        printf("5. Exit\n");
        printf("=========================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        switch(choice){
            case 1:
                shelf->add();
                break;
            case 2:
                shelf->change();
                break;
            case 3:
                shelf->listen();
                break;
            case 4:
                shelf->del();
                break;
            case 5:
                shelf->del_all();
                break;
            default:
                exit(0);
        };



    }

    return 0;

}

