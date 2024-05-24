#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>


using namespace std;

void free_pop(){
  asm ("pop %rdx");
  asm ("pop %rdi");
  asm ("call *%rdx");
  asm ("ret");
}


/*ceci est juste un objet avec 2 virtual fonctions,
le but est dappeler la main loop en faisant croire quelle
va executer les actions pour ces deux eleves mais en vrai elle
va le faire pour dautres objets*/
class Student{
  public:
    virtual void incCourseCount(){
    };
    virtual void decCourseCount(){
    };
};


/*ici donc la main loop qui va executer la deuxieme fonction de 
la vtable de chaque object qu'on lui fera passer pour des students*/
class Course{
  public:
    Student ** students;
    size_t nStudents;
    virtual void rmCourse(){
      for (size_t i = 0; i < nStudents; i++){
        students[i]->decCourseCount();
      }
      delete students;
      return;
    }
};

/*on va donc creer ces deux classes: Exam et SimpleString
afin pendant l'exploitation de donner ces objects a la main loop
qui va executer les 2 emes fonctions associées et produire 
une ecriture arbitraire qqpart in the memoire*/
class Exam{
  private:
    size_t sA, sB, sC;
  public:
    char * topic;
    size_t score;
    size_t score2;
    virtual void updateAbs(){
      score = sA + sB;
      score2 = sA +sC;
    }
    virtual float getWeight(){
      float res = (sA*5 + sB*3 + sC*2) / 10;
      return res;
    }
};

class SimpleString{
  public:
  long * buffer;
  size_t len;
  long * freeptr;
  virtual size_t useless(){
    return len;
  }
  virtual void set(char *s){
    freeptr = (long*) puts;
    *buffer = (long)freeptr;
  }
};

class GuiButton{
  public:
    long id;
    int (*callbackClick)(long) = 0;
    virtual void registerClick(){
      int a = 0;
    }
    virtual void click(){
        callbackClick(id);
    }
};


/*en partant du principe qu'on a tout bien fait mdr*/
void print_heap(){
  FILE * proc = fopen("/proc/self/maps", "r");
  char line[200];
  int no_heap = 0;
  while (true){
    memset(line, 0, 200);
    line[0] = '0';
    line[1] = 'x';
    fgets(line+2, 200, proc);
    if (strstr(line, "[heap]") != 0){
      break;
    }
    if (strstr(line, "[vdso]") != 0){
      no_heap = 1;
      break;
    }
  }
  if (no_heap == 1){
    printf("there is no heap now\n");
    return;
  }
  int from = 0;
  char * t = strchr(line, '-');
    *t = '\n';
  from = strtoll(line, NULL, 16);
  int *to   = (int*)sbrk(0);
  printf("heap from %p  to  %p\n", from, to);
  return;
}



int main(){
  /*le bof pour recuperer la main sur rip
  puis notre payload*/
//   int  *pop_ptr = (int*)&free_pop;
//   printf("free pop = %p\n", pop_ptr);
//   char bof[8];
char * our_payload = (char *)malloc(0x1000);

  /*creation et use des structures pour generer les vtables*/
  Student ** studentscouple = (Student **)malloc(sizeof(Student *));
  *studentscouple = new Student;
  *(studentscouple+1) = new Student;
  Course * randomCourse = new Course;
  randomCourse->students = studentscouple;
  randomCourse->nStudents = 2;
  Exam * randomExam = new Exam;
  SimpleString * randomString = new SimpleString;
  GuiButton * randombuton = new GuiButton;
  randomString->useless();
  randomExam->getWeight();
  randombuton->registerClick();

  Course * exploit_Course = new Course;
  printf("lets write your own Course at %p knwoing that the code is startng at %p "
      "class we will call the main loop after\n", exploit_Course, &main);


  fgets((char*)randomCourse, 0x1000, stdin);

  exploit_Course->rmCourse();

  return 0;
  
}