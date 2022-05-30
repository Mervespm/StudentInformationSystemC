#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Class_t
{
	char code[10];
	char name[50];
	int credit;
	int quota;
	int counter;
	int *idList;
	struct Class_t *next;

}Class;

typedef struct Student_t
{
	int id;
	char name[20];
	char surname[20];
	int numOfClass;
	int numOfCredit;
	struct Student_t *next;
	struct Student_t *prev;
}Student;


Class *getClass(char *code, char *name, int credit, int quota);
Class * searchClass(Class **head, char *code);
void addClass(Class **head,char *code, char *name, int credit, int quota);
void deleteClasses(Class **head,char *code);



Student * getStudent(int id, char *name, char *surname, int numOfCredit, int numOfClass);
Student * searchStudent(Student **head , int id);
void addStudent(Student **head,int id, char *name, char *surname, int numOfCredit, int numOfClass);
void deleteStudent(Student** head, int id);

void RecordFileEnrollment(char *code, int id, char *date, int *counter);
void dropOut(char *givenCode, int givenId);
void ClosedClass(char *givenCode);

int EnrollinCourse(Student **headOfStudent,Class **headOfClass, char *courseId, int studentId, char *date, int *counter,int MAX_CLASS,int MAX_CREDIT);
int deleteEnrollment(Student **headOfStudent,Class **headOfClass ,char *courseId, int studentId);

void printStudentSchedule(Class **headOfClass,int studentId);
void printGivenClass(char *code , Class **headOfClass);

void saveStudents( char *filename, Student **head);
void saveClasses( char *filename, Class **head);

int main()
{
	Class *headOfClass = NULL;
	Student *headOfStudent = NULL;
	int counter = 10000;
	int choice = 1;
	int studentId, numOfCredit, numOfClass;
	char sName[20], sSurname[20];
	char cCode[10], cName[50], date[10];
	int cQuato, cCredit;
	int control = 0;
	int MAX_CLASS,MAX_CREDIT;

	//Delete past content in Record
	fclose(fopen("OgrenciDersKayit.txt", "w"));
	fclose(fopen("ogrenciler.txt", "w"));
	fclose(fopen("dersler.txt", "w"));

	printf("\nMenuye gecmeden once lutfen MAX_CREDIT ve MAX_CLASS bilgilerini giriniz:\n");
	scanf("%d", &MAX_CREDIT);scanf("%d", &MAX_CLASS);
	
	addStudent(&headOfStudent, 22011002, "Fatma", "Bulut", 6, 2);
	addStudent(&headOfStudent, 22011001, "Merve", "Karabulut", 4, 1);
	addStudent(&headOfStudent, 22011003, "Volkan", "Kilic", 0, 0);
	addStudent(&headOfStudent, 22011011, "Emrecan", "Ozturk", 0, 0);
	addStudent(&headOfStudent, 22011004, "Hande", "Tekin", 0, 0);
	addStudent(&headOfStudent, 22011009, "Fatih", "Yurt", 0, 0);

	addClass(&headOfClass, "BLM1032", "Devre Teorisi", 6, 180);
	addClass(&headOfClass, "ITB3360", "Sanat Tarihi", 3, 70);
	addClass(&headOfClass, "BLM1022", "Sayisal Analiz", 3, 80);
	addClass(&headOfClass, "MDB1031", "Ileri Ingizce 1", 3, 35);
	addClass(&headOfClass, "MAT1072", "Matematik 2", 4, 120);
	addClass(&headOfClass, "MAT1071", "Matematik 1", 4, 120);
	addClass(&headOfClass, "BLM3021", "Algoritma Analizi", 3, 60);
	addClass(&headOfClass, "BLM2051", "Seminer", 0, 90);

	EnrollinCourse(&headOfStudent, &headOfClass, "BLM1032", 22011001,"15.10.2020",&counter,MAX_CLASS,MAX_CREDIT);
	EnrollinCourse(&headOfStudent, &headOfClass, "BLM2051", 22011001,"16.11.2019",&counter,MAX_CLASS,MAX_CREDIT);
	EnrollinCourse(&headOfStudent, &headOfClass, "BLM1032", 22011009,"15.10.2021",&counter,MAX_CLASS,MAX_CREDIT);
	EnrollinCourse(&headOfStudent, &headOfClass, "BLM1022", 22011009,"27.12.2020",&counter,MAX_CLASS,MAX_CREDIT);
	EnrollinCourse(&headOfStudent, &headOfClass, "MAT1072", 22011009,"15.10.2019",&counter,MAX_CLASS,MAX_CREDIT);
	EnrollinCourse(&headOfStudent, &headOfClass, "BLM1032", 22011004,"29.09.2020",&counter,MAX_CLASS,MAX_CREDIT);
	EnrollinCourse(&headOfStudent, &headOfClass, "ITB3360", 22011004,"15.10.2020",&counter,MAX_CLASS,MAX_CREDIT);
	EnrollinCourse(&headOfStudent, &headOfClass, "ITB3360", 22011011,"07.10.2022",&counter,MAX_CLASS,MAX_CREDIT);
	EnrollinCourse(&headOfStudent, &headOfClass, "MAT1072", 22011003,"15.10.2020",&counter,MAX_CLASS,MAX_CREDIT);
	EnrollinCourse(&headOfStudent, &headOfClass, "MAT1072", 22011002,"15.10.2020",&counter,MAX_CLASS,MAX_CREDIT);
	EnrollinCourse(&headOfStudent, &headOfClass, "MAT1071", 22011002,"19.08.2021",&counter,MAX_CLASS,MAX_CREDIT);
	EnrollinCourse(&headOfStudent, &headOfClass, "BLM3021", 22011002,"15.03.2020",&counter,MAX_CLASS,MAX_CREDIT);

	printGivenClass("MAT1072", &headOfClass);

	deleteClasses(&headOfClass, "MAT1072");
	
	deleteEnrollment(&headOfStudent,&headOfClass,"ITB3360",22011011);
	
	

	do
	{
		printf("\n\n---------------MENU-------------\n\n");
		printf("OGRENCI OLUSTURMAK ICIN 1'E BASINIZ\n");
		printf("OGRENCI SILMAK ICIN 2'YE BASINIZ\n");
		printf("DERS OLUSTURMAK ICIN 3'E BASINIZ\n");
		printf("DERS SILMEK ICIN 4'E BASINIZ\n");
		printf("DERS ALMAK ICIN 5'E BASINIZ\n");
		printf("DERS BIRAKMAK ICIN 6'YA BASINIZ\n");
		printf("DERS PROGRAMI OLUSTURMAK ICIN 7'YE BASINIZ\n");
		printf("DERSI ALAN OGRENCILERI LISTELEMEK ICIN 8'E BASINIZ\n");
		printf("CIKMAK ICIN 0'A BASINIZ\n");
		scanf("%d", &choice);

		switch(choice)
		{
			case 1:
				printf("\nSirayla ogrenci no, ad, soyad, aldigi kredi ve ders bilgilerini giriniz:\n");
				scanf("%d", &studentId); scanf("%s", sName);
				scanf("%s", sSurname); scanf("%d", &numOfCredit); scanf("%d", &numOfClass);
				addStudent(&headOfStudent,studentId,sName, sSurname,numOfCredit, numOfClass);
			break;

			case 2:
				printf("\nOgrenci no giriniz:\n");
				scanf("%d", &studentId);
				deleteStudent(&headOfStudent, studentId);
			break;

			case 3:
				printf("\nSirayla ders kodu, adi, kredi ve kota bilgilerini giriniz:\n");
				scanf("%s", cCode); scanf("%s", cName);
				scanf("%d", &cCredit); scanf("%d", &cQuato);
				addClass(&headOfClass, cCode, cName, cCredit, cQuato);
			break;

			case 4:
				printf("\nDers kodunu giriniz:\n");
				scanf("%s", cCode); 
				deleteClasses(&headOfClass, cCode);
			break;

			case 5:

				printf("\nDers kodunu, ogrenci noyu ve tarihi giriniz:\n");
				scanf("%s", cCode);  scanf("%d", &studentId); scanf("%s", date);
				EnrollinCourse(&headOfStudent,&headOfClass, cCode, studentId,date,&counter,MAX_CLASS,MAX_CREDIT);
				
			break;

			case 6:

				printf("\nDers kodunu, ogrenci noyu  giriniz:\n");
				scanf("%s", cCode);  scanf("%d", &studentId);
				deleteEnrollment(&headOfStudent,&headOfClass, cCode, studentId);
			break;

			case 7:
				printf("\nOgreni noyu giriniz:\n");
				scanf("%d", &studentId);
				printStudentSchedule(&headOfClass,studentId);	
			break;

			case 8:
				printf("\nDers kodunu giriniz:\n");
				scanf("%s", cCode );
				printGivenClass(cCode,&headOfClass);	
			break;

		}

	}while(choice != 0);
	
	
	saveClasses("dersler.txt", &headOfClass);
	saveStudents("ogrenciler.txt", &headOfStudent);	

	return 0;
}


//Sinif yapisindan degerlerdean bir pointer olusturur.
Class *getClass(char *code, char *name, int credit, int quota)
{
	Class *c;
	c = (Class*)malloc(sizeof(Class));
	strcpy(c->code, code);
	strcpy(c->name, name);
	c->credit = credit;
	c->quota = quota;
	c->counter = 0;
	c->idList = (int*)malloc(1*sizeof(int));
	c->next = NULL;
	return c;
}


//Ogrenci yapisindan degerlerdean bir pointer olusturur.
Student * getStudent(int id, char *name, char *surname, int numOfCredit, int numOfClass)
{ 
	Student *s;
	s = (Student*)malloc(sizeof(Student));
	s->id = id;
	strcpy(s->name, name);
	strcpy(s->surname, surname);
	s->numOfClass = numOfClass;
	s->numOfCredit = numOfCredit;
	s->next = NULL;
	s->prev = NULL;
	return s;
}

//Ders koduna gore arama yapar.
Class * searchClass(Class **head, char *code)
{
    Class* tmp;
    tmp = *head; 
    while (tmp != NULL)
    {
        if (strcmp(tmp->code,code) == 0)
        {
            return tmp;
        }
        tmp = tmp->next;
    }

    return NULL;
}

//Ders koduna gore sirali sekilde ekleme yapar.
void addClass(Class **head,char *code, char *name, int credit, int quota)
{
    Class *tmp;
    Class *newClass;
	newClass = getClass(code, name, credit, quota);

	if(searchClass(head, code) != NULL)
	{
		printf("\n%s kodlu ders bulunmakta. ", code);
		return;
	}

	else
	{
		if (*head == NULL || strcmp((*head)->code , newClass->code) > 0)
	    {
	        newClass->next = *head;
	        *head = newClass;
	    }
	    else 
	    {
	        tmp = *head;

	        while (tmp->next != NULL && strcmp(tmp->next->code , newClass->code) < 0)
	         {
	            tmp = tmp->next;
	        }
	        newClass->next = tmp->next;
	        tmp->next = newClass;
	    }
	    printf("%s kodlu ders eklendi\n", code);

	}
    
    
}

//Ders siler.
void deleteClasses(Class **head,char *code)
{
	Class *tmp,*prev = NULL;
	tmp = *head;

	if(tmp != NULL && strcmp(tmp->code,code) == 0)
	{
		*head = tmp->next;
		free(tmp);
		return;	
	}
	else
	{
		while (tmp != NULL && strcmp(tmp->code,code) != 0)
		{
       		prev = tmp;
        	tmp = tmp->next;
    	}
 
    	if (tmp == NULL)
    	{
    		printf("\n%s kodlu ders bulunmamaktadir.", code);
        	return;
    	}

    	printf("%s kodlu ders silindi", code);
    	prev->next = tmp->next;
 		ClosedClass(code);
    	free(tmp);		
	}
}

//Ogrenci arar ve pointerini dondurur.
Student * searchStudent(Student **head , int id)
{
 
    Student *temp = *head;
    int pos = 0;

    while (temp->id != id && temp->next != NULL) {
 
       
        pos++;
        temp = temp->next;
    }
    if (temp->id != id)
    {
        return NULL;
    }

    return temp;
}

//Ogrenci numarasina gore sirali ekler.
void addStudent(Student **head,int id, char *name, char *surname, int numOfCredit, int numOfClass)
{

    Student *tmp;
 	Student *newStudent;
	newStudent = getStudent(id, name, surname, numOfCredit, numOfClass);	
    
    if (*head== NULL)
    {
        *head = newStudent;
    }
 
    else if ((*head)->id > newStudent->id) 
    {
        newStudent->next = *head;
        newStudent->next->prev = newStudent;
        *head = newStudent;
    }
 
    else 
    {
        tmp = *head;
   
        while (tmp->next != NULL && tmp->next->id < newStudent->id)
        {
            tmp = tmp->next;
        }  
 
        newStudent->next = tmp->next;
   
        if (tmp->next != NULL)
        {
            newStudent->next->prev = newStudent;
        }
 		
        tmp->next = newStudent;
        newStudent->prev = tmp;
        
    }
    printf("%d nolu ogrenci eklendi.\n", id);
}


//Ogrenci siler.
void deleteStudent(Student** head, int id)
{
	Student *current, *pre_node, *last;
	current = (Student*)malloc(sizeof(Student));
    
    if (*head == NULL )
    {
    	printf("\nOgrenci listesi bos\n");
        return;
    }

    else if ((*head)->id == id) 
	{
        if((*head)->next != NULL)
        {
         	(*head)-> next-> prev = NULL;
         	(*head) = (*head)-> next;
         	return;
         }
        else
         {
         	head = NULL;
         	printf("\nOgrenci listesi bosaldi\n");
         	return;
      	}

    }
    else if((*head)->id != id && (*head)->next == NULL)
    {
      	printf("\n%d nolu ogrenci bulunamadi\n", id);
	    return;
	}
 
    current = (*head);
   
   	while(current->next != NULL && current->id != id) {
      	pre_node = current;
      	current = current->next;
   	}        

   if(current->id == id)
   {
     	pre_node->next = pre_node->next->next;
            
      	if(pre_node->next != NULL) 
      	{          
         	pre_node->next->prev = pre_node;
	      } 
	    else
      	{
       	  	last = pre_node;
     	}

      	free(current);
      	printf("%d nolu ogrenci silindi", id);
   } 
   else
   {
      	printf("\n%d nolu ogrenci bulunamadi\n", id);
   }
}

//Dosyada kapandi bilgisini gunceller.
void ClosedClass(char *givenCode)
{
	int id, counter, i = 0;
	int count = 0;
	char code[15];
	char date[15], stm[20];
	FILE *ptr;
	ptr = fopen("OgrenciDersKayit.txt","r+");
	
	if(ptr == NULL)
	{
		printf("Error...\n");
		exit(1);
	}
	i = 0;
	
	while(fscanf(ptr,"%d,%[^,],%d,%[^,],%s\n",&counter,code,&id,date,stm) != EOF)
	{
		

		if(strcmp(code, givenCode) == 0 )
		{
			
			fseek(ptr, i + strlen(code) + strlen(date) + 17, SEEK_SET);
			fputs("kapandi", ptr);
			
		}
		
		i += (strlen(code) + strlen(date) + 18 + strlen(stm));
		
	}
	
	fclose(ptr);

}

//Kayitli bilgisini dosyaya yazar.
void RecordFileEnrollment(char *code, int id, char *date, int *counter)
{
	FILE *ptr;
	ptr = fopen("OgrenciDersKayit.txt","a");
	(*counter) ++;
	if(ptr == NULL)
	{
		printf("Error...\n");
		exit(1);
	}
	
	fprintf(ptr,"%d,%s,%d,%s,%s\n",*counter,code,id, date,"kayitli");
	fclose(ptr);
}


//Birakti bilgisini ders kayit dosyasina yazar.
void dropOut(char *givenCode, int givenId)
{
	int id, counter, i = 0;
	int count = 0;
	char code[15], date[15], stm[15];
	FILE *ptr;
	ptr = fopen("OgrenciDersKayit.txt","r+");
	
	if(ptr == NULL)
	{
		printf("Error...\n");
		exit(1);
	}
	
	while(fscanf(ptr,"%d,%[^,],%d,%[^,],%s\n",&counter,code,&id,date,stm) != EOF)
	{

		if(strcmp(code, givenCode) == 0 && id == givenId)
		{
			
			fseek(ptr,i + strlen(code) + strlen(date) + 17, SEEK_SET);
			fputs("birakti", ptr);
		}
		i += (strlen(code) + strlen(date) + 18 + strlen(stm));
		
	}
	
	fclose(ptr);
}


//Derste tutulan ogrenci no listesine ekleme yapar ve RecordFileEnrollment fonsiyonunu cagiriir.
int EnrollinCourse(Student **headOfStudent,Class **headOfClass, char *courseId, int studentId, char *date, int *counter,int MAX_CLASS,int MAX_CREDIT)
{
	int i;
	Class *classTmp;
	Student *studentTmp;
	studentTmp = searchStudent(headOfStudent, studentId);

	if(studentTmp == NULL)
	{
		printf("\n%d nolu ogrenci bulunmamaktadir. \n", studentId);
		return 0;
	}
	if(searchClass(headOfClass, courseId) == NULL)
	{
		printf("\n%s kodlu ders bulunmamaktadir\n", courseId);
		return 0;
	}
	classTmp = *headOfClass;

	while(classTmp != NULL && strcmp(classTmp->code,courseId) != 0)
	{
		
		classTmp = classTmp->next;

	}
	
	if(classTmp != NULL)
	{	
		if(classTmp->quota <= classTmp-> counter)
		{
			printf("\nKota dolmustur...\n");
			return 0;
		}
		else if((studentTmp->numOfCredit + classTmp->credit) > MAX_CREDIT)
		{
			
			printf("\n%d nolu kredi limitini asmaktadir.\n",studentTmp->id);
			return 0;		
		}	
		
		else if(studentTmp->numOfClass + 1 > MAX_CLASS)
		{
			
			printf("\n%d nolu ders limitini asmaktadir.\n",studentTmp->id);
			return 0;	
		}
		else
		{
			classTmp->idList = (int*)realloc((classTmp->idList),sizeof(int));
			i = 0;

			while(i <= classTmp->counter)
			{
				if(*(classTmp->idList + i) > studentId )
				{
					int tmp = *(classTmp->idList + i);
					*(classTmp->idList + i)= studentId;
					studentId = tmp;	
				}

				i++;
			}
			
			classTmp->counter ++;
			studentTmp->numOfCredit = studentTmp->numOfCredit + classTmp->credit;
			studentTmp->numOfClass++;
			*(classTmp->idList + classTmp->counter) = studentId;
			printf("\n%s kodlu derse %d nolu ogrenci eklenmistir.\n", classTmp->code,studentTmp->id );
			RecordFileEnrollment(classTmp->code, studentTmp->id , date, counter);
			return 1;

		}
	}
	return 0;	
}

//Ogrenci listesinden numarayi siler ve DropOut fonksiyonunu cagirir.
int deleteEnrollment(Student **headOfStudent,Class **headOfClass ,char *courseId, int studentId)
{
	int i;
	Class *classTmp;
	Student *studentTmp;
	studentTmp = searchStudent(headOfStudent, studentId);

	if(studentTmp == NULL )
	{
		printf("\n%d nolu ogrenci bulunmamaktadir.\n", studentId);
		return 0;
	}

	if( searchClass(headOfClass, courseId) == NULL)
	{
		printf("\n%s kodlu ders bulunmamaktadir.\n", courseId);
		return 0;
	}

	classTmp = *headOfClass;

	while(classTmp != NULL && strcmp(classTmp->code,courseId) != 0)
	{
		
		classTmp = classTmp->next;

	}
	if(classTmp != NULL)
	{	
		i = 0;

		while(i <= classTmp->counter && *(classTmp->idList + i) != studentId )
		{
			i++;
		}
		if( i <= classTmp->counter )
		{
			
			int* temp = malloc((classTmp->counter - 1) * sizeof(int)); 
		    memmove(temp, classTmp->idList,(i+1)*sizeof(int));
		    memmove(temp+i,(classTmp->idList)+(i+1),(classTmp->counter  - i)*sizeof(int));
		    free ((classTmp->idList));
		    classTmp->idList = temp;
		    classTmp->counter -- ;
		    studentTmp -> numOfCredit -= classTmp->credit;
		    studentTmp -> numOfClass --;
		    dropOut(classTmp->code, studentId);
		    printf("\n%s kodlu dersten %d nolu ogrenci silindi\n",courseId, studentId ); 
		    return 1;
		}
		
	}
	return 0;
	
}


//Verilen koddaki dersi alan ogrencileri dosyaya yazar.
void printGivenClass(char *code , Class **headOfClass)
{
	Class *tmp;
	FILE *ptr;
	int i;

	tmp = searchClass(headOfClass, code);
	if(tmp == NULL)
	{
		printf("%s kodlu ders bulunmamaktadir", code);
		return;
	}

	char filename[15] = "1234567.txt";
	strncpy(filename, code , 7);
	
	ptr = fopen(filename, "w");

	for (i = 1; i <= tmp->counter ; i++)
	{
		fprintf(ptr,"%d\n",*(tmp->idList + i));

	}

	printf("%s kodlu dersi alan ogrenciler yazdirilmistir", code);
	fclose(ptr);
}

//Girilen numaradaki ogrencinin aldigi derleri soyaya yazar.
void printStudentSchedule(Class **headOfClass,int studentId)
{
	int i;
	FILE *ptr;
	char filename[26] = "12345678_DERSPROGRAMI.txt";
	char tmp[10];
	sprintf(tmp, "%d", studentId);
	strncpy(filename, tmp, 8);

	ptr = fopen(filename, "w+");

	Class *classTmp = *headOfClass;

	while(classTmp != NULL )
	{
		for (i = 1; i <= classTmp->counter ; i++)
		{
			if(*(classTmp->idList + i) == studentId)
			{
				
				fprintf(ptr, "%s\n", classTmp->code);
			}
			
		}

		classTmp = classTmp->next;
		
	}
	fclose(ptr);
	printf("\n%d nolu ogrencinin ders programi yazdirilmistir.\n", studentId);	
	
	
}

//Listelere gore son kayitlari ders dosyasina kaydeder.
void saveClasses( char *filename, Class **head)
{
	int i=0,count =0;
	FILE *ptr;
	ptr = fopen(filename,"w");
	Class *tmp;
	if(ptr == NULL)
	{
		printf("Error...\n");
		exit(1);
	}
	tmp = *head;
	while(tmp != NULL)
	{
		fprintf(ptr,"%s,%s,%d,%d\n",tmp->code,tmp->name,tmp->credit,tmp->quota);
		tmp = tmp->next;
	}

	fclose(ptr);
}

//Listedeki son guncellemeleri dosyaya kaydeder.
void saveStudents( char *filename, Student **head)
{
	FILE *ptr;
	ptr = fopen(filename,"w");
	Student *tmp;
	if(ptr == NULL)
	{
		printf("Error...\n");
		exit(1);
	}
	tmp = *head;
	while(tmp != NULL)
	{
		fprintf(ptr,"%d,%s,%s,%d,%d\n",tmp->id,tmp->name,tmp->surname,
				tmp->numOfCredit,tmp->numOfClass);
		tmp= tmp->next;
	}

	fclose(ptr);
}



//Dosya eger dolu ise okuma ve listeye ekleme islemi yapar.
void readClass(char *filename, Class **headOfClass)
{
	char code[10], name[50];
	int credit, quota;
	FILE * Fptr;

	Fptr = fopen(filename,"r");
	
	if(Fptr == 0)
	{
		printf("Error...\n");
		exit(0) ;
	}

	while(fscanf(Fptr, "%[^,],%[^,],%d,%d\n",code,name,&credit,&quota) != EOF)
	{
		addClass(headOfClass, code, name, credit, quota);
	}
	
    
	fclose(Fptr);
}


//Dosya eger dolu ise okuma ve listeye ekleme islemi yapar.
void readStudent(char *filename,Student **headOfStudent)
{
	char name[20], surname[20];
	int id, numOfCredit, numOfClass;
	
	FILE * Fptr;

	Fptr = fopen(filename,"r");
	
	if(Fptr == 0)
	{
		printf("Error...\n");
		exit(0) ;
	}

	while(fscanf(Fptr, "%d,%[^,],%[^,],%d, %d\n",&id,name,surname,&numOfCredit,&numOfClass ) != EOF)
	{
		addStudent(headOfStudent,id,name, surname, numOfCredit, numOfClass);
	}
	
  
	fclose(Fptr);
}






