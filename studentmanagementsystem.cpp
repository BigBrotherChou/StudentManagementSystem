#include<stdio.h> 
#include<stdlib.h>
#include<string.h>

//����ѧ����Ϣ�Ľṹ�� 
typedef struct Student{
	char Id[10];//ѧ�� 
	char Name[10];//���� 
	double Score1;//����1 
	double Score2;//����2 
	double Score3;//����3 
	double AverageScore;//ƽ���� 
	struct Student* link;
}Student;

//���嵥����ı�ͷ 
typedef struct
{
	struct Student *head;
}SingleList;

//�������� 
 void menu();
 void Init(SingleList *L);
 void HeadInsert(SingleList *L);
 void PrintList(SingleList *L);
 void Destory(SingleList *L);
 void InsertIntoFile(SingleList *L);
 void PrintMenu();
 int Search(SingleList *L,char *str); 
 int main(); 
//��ʼ��������
void Init(SingleList* L){
	L->head = NULL;
}
//��ͷ���� ���������� 
void HeadInsert(SingleList *L) {
	FILE* fp = fopen("database.txt", "r");
	Student* p;
	if (!fp) {
		printf("�ļ�������");
		exit(1);
	}
	p = (Student*)malloc(sizeof(Student));
	fscanf(fp, "%s %s %lf %lf %lf %lf ", p->Id, p->Name, &p->Score1, &p->Score2, &p->Score3, &p->AverageScore);
	p->link = L->head;
	L->head = p;

	while (!feof(fp))
	{
		p = (Student*)malloc(sizeof(Student));
		fscanf(fp, "%s %s %lf %lf %lf %lf ", p->Id, p->Name, &p->Score1, &p->Score2, &p->Score3, &p->AverageScore);
		p->link = L->head;
		L->head = p;
	}
	fclose(fp);
}
//������������е����� 
void swap(Student *p,Student *q){
	Student *temp;
	temp=(Student*)malloc(sizeof(Student));
	
	strcpy(temp->Id,p->Id);
	strcpy(temp->Name,p->Name);
	temp->Score1=p->Score1;
	temp->Score2=p->Score2;
	temp->Score3=p->Score3;
	temp->AverageScore=p->AverageScore;
	
	strcpy(p->Id,q->Id);
	strcpy(p->Name,q->Name);
	p->Score1=q->Score1;
	p->Score2=q->Score2;
	p->Score3=q->Score3;
	p->AverageScore=q->AverageScore;
	
	strcpy(q->Id,temp->Id);
	strcpy(q->Name,temp->Name);
	q->Score1=temp->Score1;
	q->Score2=temp->Score2;
	q->Score3=temp->Score3;
	q->AverageScore=temp->AverageScore;	
	
	free(temp);
}
//���ٵ�������֤�ڴ�Ľ���
void Destory(SingleList* L){
	Student *p;
	p=L->head;
	while(p->link)
	{
		free(p);
		p=p->link;
	}
 } 
//��ӡ��������
void PrintList(SingleList* L) {
	Student* p=(Student *)malloc(sizeof(Student));
	int count = 1;
	p=L->head;
	printf("���\tѧ��\t����\t����һ\t������\t������\tƽ����\t\n");
	while (p->link)
	{		
		printf("%d\t%s\t%s\t%3.2lf\t%3.2lf\t%3.2lf\t%3.2lf\t\n",count++, p->Id, p->Name, p->Score1, p->Score2, p->Score3, p->AverageScore);
		p = p->link;
	}
	printf("%d\t%s\t%s\t%3.2lf\t%3.2lf\t%3.2lf\t%3.2lf\t\n",count++, p->Id, p->Name, p->Score1, p->Score2, p->Score3, p->AverageScore);
	printf("--------------------��Ϣ��ʾ����-----------------------\n\n\n");
}
//����ѧ�� 0��ʾ���д�ѧ�� 1��ʾû�д�ѧ�ſ������ 
int Search(SingleList *L,char *str) {
	Student *p;
	p=L->head;
	while(p->link)
	{
		if(!strcmp(p->Id,str))
		{
			return 0;
		}
		p=p->link;
	}
	return 1;
}
//���ѧ����Ϣ
void add1() {
	SingleList L;
	Student student;
	printf("������ѧ��\n");
	scanf("%s[^\n]",student.Id);
	getchar();
	printf("����������\n");
	scanf("%s[^\n]", student.Name);
	getchar();
	printf("������ɼ�1\n");
	scanf("%lf[^\n]", &student.Score1);
	getchar();
	printf("������ɼ�2\n");
	scanf("%lf[^\n]", &student.Score2);
	getchar();
	printf("������ɼ�3\n");
	scanf("%lf[^\n]", &student.Score3);
	getchar();
	student.AverageScore = (student.Score1 + student.Score2 + student.Score3) / 3;
	Init(&L);
	HeadInsert(&L);
	if(Search(&L,student.Id))
	{
		FILE* fp;
		if (fp = fopen("database.txt", "a+"))
		{
			fprintf(fp,"%s %s %.2lf %.2lf %.2lf %.2lf \n",student.Id,student.Name,student.Score1,student.Score2,student.Score3,student.AverageScore);
			fclose(fp);		
		}
		else
		{
			printf("�ļ��򿪴���");
		}
	}
	else
	{
		printf("ѧ���Ѿ����ڣ����ʧ��");
	}
}
//�������е��������뵽�ļ�
void InsertIntoFile(SingleList *L){
	FILE *fp;
	Student *p;
	p=L->head;
	if(!p)
	{
		return;
	}
	fp=fopen("database.txt","w");
	if(fp)
	{
		while(p->link)
		{
			fprintf(fp,"%s %s %.2lf %.2lf %.2lf %.2lf \n",p->Id,p->Name,p->Score1,p->Score2,p->Score3,p->AverageScore);
			p=p->link;
		}
	}
	Destory(L);
} 
//����������Ϣ���
void add(char *id,char *name,char* score1_s,char* score2_s,char* score3_s) {
	double score1=atof(score1_s);
	double score2=atof(score2_s);
	double score3=atof(score3_s);
	FILE* fp;
	if (fp = fopen("database.txt", "a+"))
	{
		fprintf(fp, "\n%s %s %.2lf %.2lf %.2lf %.2lf",id,name,score1,score2,score3,(score1+score2+score3)/3);
	}
	else
	{
		printf("�ļ��򿪴���");
	}
	fclose(fp);
}
//��ʾ��ǰ��¼ 
void list(){
	Student *p;
	SingleList L;
	Init(&L);
	HeadInsert(&L);
	p=L.head;
	printf("--------��ǰ��¼----------\n");
	printf("ѧ��\t����\t����һ\t������\t������\tƽ����\t\n");
	printf("%s\t%s\t%3.2lf\t%3.2lf\t%3.2lf\t%3.2lf\t\n",p->Id, p->Name, p->Score1, p->Score2, p->Score3, p->AverageScore);
	Destory(&L);
}
//չʾ������Ϣ
void list_a(){
	SingleList L;
	Init(&L);
	HeadInsert(&L);
	PrintList(&L);
	Destory(&L);
}
//��ʾָ��ѧ�ŵ���Ϣ 
void list_x(char *x){
	
	Student *p;
	SingleList L;
	Init(&L);
	HeadInsert(&L);
	p=L.head;

	do{
		if(strcmp(p->Id,x)==0)
		{
			printf("ѧ��\t����\t����һ\t������\t������\tƽ����\t\n");
			printf("%s\t%s\t%3.2lf\t%3.2lf\t%3.2lf\t%3.2lf\t\n",p->Id, p->Name, p->Score1, p->Score2, p->Score3, p->AverageScore);
			break;
		}
		p=p->link;
	}	while(p!=NULL);
	Destory(&L);
}
//��ʾָ��������ѧ�� 
void list_n(char *n){
	Student *p;
	SingleList L;
	Init(&L);
	HeadInsert(&L);
	p=L.head;
	printf("ѧ��\t����\t����һ\t������\t������\tƽ����\t\n");
	do{
		if(strcmp(p->Name,n)==0)
		{			
			printf("%s\t%s\t%3.2lf\t%3.2lf\t%3.2lf\t%3.2lf\t\n",p->Id, p->Name, p->Score1, p->Score2, p->Score3, p->AverageScore);
		}
		p=p->link;
	}	while(p!=NULL);
	Destory(&L);
}
//ͨ������һ���� 
void sort_s1(){
	const double EPS = 1e-6;
	SingleList L;
	Student *p,*q;
	Init(&L);
	HeadInsert(&L);
	p=L.head;
	while(p->link)
	{
		q=p->link;
		while(q->link)
		{
			q=q->link;
			if(q->Score1<p->Score1+EPS)
			{
				swap(p,q);
		 	} 	 	
		}
		p=p->link;		
	}
	PrintList(&L);	
	Destory(&L);
}
//ͨ������������ 
void sort_s2(){
	const double EPS = 1e-6;
	SingleList L;
	Student *p,*q;
	Init(&L);
	HeadInsert(&L);
	p=L.head;
	while(p->link)
	{
		q=p->link;
		while(q->link)
		{
			q=q->link;
			if(q->Score2<p->Score2+EPS)
			{
				swap(p,q);
		 	} 
		}
		p=p->link;		
	}
	PrintList(&L);
	Destory(&L);	
}
//ͨ������������ 
void sort_s3(){
	const double EPS = 1e-6;
	SingleList L;
	Student *p,*q;
	Init(&L);
	HeadInsert(&L);
	p=L.head;
	while(p->link)
	{
		q=p->link;
		while(q->link)
		{
			q=q->link;
			if(q->Score3<p->Score3+EPS)
			{
				swap(p,q);
		 	} 
		}
		p=p->link;		
	}
	PrintList(&L);
	Destory(&L);	
}
//ͨ��ƽ��������
void sort(){
	const double EPS = 1e-6;
	SingleList L;
	Student *p,*q;
	Init(&L);
	HeadInsert(&L);
	p=L.head;
	while(p->link)
	{
		q=p->link;
		while(q->link)
		{
			q=q->link;
			if(q->AverageScore<p->AverageScore+EPS)
			{
				swap(p,q);
		 	} 		 	
		}
		p=p->link;		
	}
	PrintList(&L);
	Destory(&L);
}
//ͨ��ѧ������
void sort_x(){
	SingleList L;
	Student *p,*q;
	Init(&L);
	HeadInsert(&L);
	p=L.head;
	while(p->link)
	{
		q=p->link;
		while(q->link)
		{
			q=q->link;
			if(strcmp(p->Id,q->Id)>0)
			{
				swap(p,q);
		 	} 		 	
		}
		p=p->link;		
	}
	PrintList(&L);
	Destory(&L);
}
//ͨ����������
void sort_n(){
	SingleList L;
	Student *p,*q;
	Init(&L);
	HeadInsert(&L);
	p=L.head;
	while(p->link)
	{
		q=p->link;
		while(q->link)
		{
			q=q->link;
			if(strcmp(p->Name,q->Name)>0)
			{
				swap(p,q);
		 	} 		 	
		}
		p=p->link;		
	}
	PrintList(&L);
	Destory(&L);
 } 
//ɾ������ѧ����Ϣ
void rem_a(){
	FILE* fp;
	char ch;
	printf("�Ƿ�ɾ�����м�¼����y/n��");
	scanf("%c",&ch);
	getchar();
	//scanf("%c",&chose);
	if(ch==121) 
	{
  		fp = fopen("database.txt","w");  
 		if(fp==NULL)
 		{
 			printf("��¼ɾ��ʧ��\n");
  		}
  		else
  		{
  			printf("��¼ɾ���ɹ�\n");
	  	}
		fclose(fp);
		return;
	}
	else
	{
		printf("��ɾ��\n");
		fclose(fp);
	}

}
//ɾ��ָ��ѧ�ŵ���Ϣ
void rem_x(char *id){
	SingleList L;
	Student *p;
	Init(&L);
	HeadInsert(&L);
	p=L.head; 
	while(p->link)
	{
		if(strcmp(p->Id,id)==0)
		{
			Student *q=(Student*)malloc(sizeof(Student));
			q=p->link;
			if(!(p->link))
			{
				p=NULL;
				InsertIntoFile(&L);
				printf("ɾ���ɹ�");
			}
			else
			{
				swap(p,q);
				p->link=q->link;
				free(q);
				InsertIntoFile(&L);
				printf("ɾ���ɹ�");
			}
			return;
		}
		p=p->link; 
	}
	printf("û���ҵ���ѧ��\n");
 }
//ɾ����ǰ��¼
void rem(){
	SingleList L;
	Student *p,*q;
	Init(&L);
	HeadInsert(&L);
	p=L.head;
	printf("��ǰ��¼%s %s %.3lf %.3lf %.3lf %.3lf\n",p->Id,p->Name,p->Score1,p->Score2,p->Score3,p->AverageScore);
	q=p->link;
	L.head=q;
	free(p);
	InsertIntoFile(&L);
	printf("ɾ����ǰ��¼�ɹ�\n");
 }
 //�޸ĵ�ǰ��¼
void edit()
{
 	char *id;
	char *name;
	double score1;
	double score2;
	double score3;
 	SingleList L;
 	double averageScore;
	Student *p,*q;
	Init(&L);
	HeadInsert(&L);
	p=L.head;
	printf("��ǰ��¼%s %s %.3lf %.3lf %.3lf %.3lf\n",p->Id,p->Name,p->Score1,p->Score2,p->Score3,p->AverageScore);
	printf("------------------------------\n");
	printf("�������¼:");
	scanf("%s %s %lf %lf %lf",id,name,&score1,&score2,&score3);
	if(Search(&L,id)==1)
	{
		strcpy(p->Id,id);
		strcpy(p->Name,name);
		p->Score1=score1;
		p->Score2=score2;
		p->Score3=score3;
		p->AverageScore=(score1+score2+score3)/3;
		InsertIntoFile(&L);
	}else
	{
		printf("ѧ���Ѵ��� �޸�ʧ��\n"); 
	}
  }
// edit a���޸ĵ�ǰ��¼������
void edit_a(char *id,char *name,char* score1_s,char* score2_s,char* score3_s)
{
 	SingleList L;
	Student *p,*q;
	double score1=atof(score1_s);
	double score2=atof(score2_s);
	double score3=atof(score3_s);
	Init(&L);
	HeadInsert(&L);
	p=L.head;
	printf("��ǰ��¼%s %s %.3lf %.3lf %.3lf %.3lf\n",p->Id,p->Name,p->Score1,p->Score2,p->Score3,p->AverageScore);
	printf("------------------------------\n");
	if(Search(&L,id)==1)
	{
		strcpy(p->Id,id);
		strcpy(p->Name,name);
		p->Score1=score1;
		p->Score2=score2;
		p->Score3=score3;
		p->AverageScore=(score1+score2+score3)/3;
		InsertIntoFile(&L);
		printf("------------�޸ĳɹ�---------\n");
	}else
	{
		printf("ѧ���Ѵ��� �޸�ʧ��\n");
	}
}
//ֻ�޸ĵ�ǰ��¼ѧ�ţ���Ҫ����������ѧ�Ŵ������жϣ� 
void edit_x(char *id)
{
 	SingleList L;
	Student *p,*q;
	Init(&L);
	HeadInsert(&L);
	p=L.head;
	printf("��ǰ��¼%s %s %.3lf %.3lf %.3lf %.3lf\n",p->Id,p->Name,p->Score1,p->Score2,p->Score3,p->AverageScore);
	printf("------------------------------\n");
	if(Search(&L,id)==1)
	{
		strcpy(p->Id,id);
		InsertIntoFile(&L);
		printf("------------�޸ĳɹ�---------\n");
	}else
	{
		printf("ѧ���Ѵ��� �޸�ʧ��\n");
	}
}
//ֻ�޸ĵ�ǰ��¼����
void edit_n(char *name)
{
 	SingleList L;
	Student *p,*q;
	Init(&L);
	HeadInsert(&L);
	p=L.head;
	printf("��ǰ��¼%s %s %.3lf %.3lf %.3lf %.3lf\n",p->Id,p->Name,p->Score1,p->Score2,p->Score3,p->AverageScore);
	printf("------------------------------\n");
	strcpy(p->Name,name);
	InsertIntoFile(&L);
	printf("------------�޸ĳɹ�---------\n");
}
//ֻ�޸ĵ�ǰ��¼���� 1
void edit_s1(char *score1_s)
{
 	SingleList L;
	Student *p,*q;
	double score1=atof(score1_s);
	Init(&L);
	HeadInsert(&L);
	p=L.head;
	printf("��ǰ��¼%s %s %.3lf %.3lf %.3lf %.3lf\n",p->Id,p->Name,p->Score1,p->Score2,p->Score3,p->AverageScore);
	printf("------------------------------\n");
	p->Score1=score1;
	p->AverageScore=(p->Score2+score1+p->Score3)/3;
	InsertIntoFile(&L);
	printf("------------�޸ĳɹ�---------\n");
}
//ֻ�޸ĵ�ǰ��¼���� 2
void edit_s2(char* score2_s)
{
 	SingleList L;
	Student *p,*q;
	double score2=atof(score2_s);
	Init(&L);
	HeadInsert(&L);
	p=L.head;
	printf("��ǰ��¼%s %s %.3lf %.3lf %.3lf %.3lf\n",p->Id,p->Name,p->Score1,p->Score2,p->Score3,p->AverageScore);
	printf("------------------------------\n");
	p->Score2=score2;
	p->AverageScore=(p->Score1+score2+p->Score3)/3;
	InsertIntoFile(&L);
	printf("------------�޸ĳɹ�---------\n");
}
//ֻ�޸ĵ�ǰ��¼���� 3
void edit_s3(char* score3_s)
{
 	SingleList L;
	Student *p,*q;
	double score3=atof(score3_s);
	Init(&L);
	HeadInsert(&L);
	p=L.head;
	printf("��ǰ��¼%s %s %.3lf %.3lf %.3lf %.3lf\n",p->Id,p->Name,p->Score1,p->Score2,p->Score3,p->AverageScore);
	printf("------------------------------\n");
	p->Score3=score3;
	p->AverageScore=(p->Score1+score3+p->Score2)/3;
	InsertIntoFile(&L);
	printf("------------�޸ĳɹ�---------\n");
}
//set n�����õ�ǰ��¼����ʾ
void set(char* index_s){
	SingleList L;
	Student *p,*q;
	int index=atoi(index_s);
	Init(&L);
	HeadInsert(&L);
	p=L.head;
	q=L.head; 
	for(int i=0;i<=index;i++)
	{
		p=p->link;
		if(p==NULL)
		{
			printf("��Ų��ڷ�Χ\n");
			return ;
		}
	}
	printf("��ǰ��¼%s %s %.3lf %.3lf %.3lf %.3lf\n",p->Id,p->Name,p->Score1,p->Score2,p->Score3,p->AverageScore);
	printf("------------------------------\n");
	swap(p,q);
	InsertIntoFile(&L);
} 
//��ӡ�˵�����
void PrintMenu(){
	printf("���˵���\n");
 	printf("--------------\n");
 	printf("1����ʾѧ����¼��list��\n");
 	printf("2������ѧ����¼(add)\n");
 	printf("3��ɾ��ѧ����¼(rem)\n");
 	printf("4. �޸�ѧ����¼(edit)\n");
 	printf("5. ���õ�ǰ��¼(set)\n");
 	printf("6. ����ѧ����¼(sort)\n");
 	printf("7. ����(help)\n");
 	printf("8. �˳�(quit)\n");
 }
 //��ӡ���� 
void help(char *oder)
{
 	char list[]="list";
 	char add[]="add";
 	char rem[]="rem";
 	char edit[]="edit";
 	char sort[]="sort";
 	char set[]="set";
 	if(strcmp(oder,list)==0)
 	{
 		printf("list---------------��ʾ��ǰ��¼\n");
 		printf("list a-------------��ʾ���м�¼\n");
 		printf(" list x ѧ��ֵ------��ʾ��Ӧ��ѧ�š���¼\n");
 		printf("list n ����ֵ------��ʾ������Ӧ����������¼\n");
 		printf("------------------------------\n\n\n");
 		return;
	}else if(strcmp(oder,add)==0)
 	{
 		printf("add----------------------------------��������һ���¼�¼\n");
 		printf("add a ѧ�� ���� ����1 ����2 ����3----��������һ���¼�¼�����٣�\n");
 		printf("------------------------------\n\n\n");
 		return;
	}else if(strcmp(oder,rem)==0)
 	{
 		printf("rem----------------ɾ����ǰ��¼\n");
 		printf("rem a--------------ɾ�����м�¼\n");
 		printf("rem x ѧ��ֵ-------ɾ��ָ����ѧ�š���¼\n");
 		printf("------------------------------\n\n\n");
 		return; 
	} else if(strcmp(oder,edit)==0)
 	{
 		printf("edit---------------���µ�ǰ��¼������\n");
 		printf("edit x  ѧ��ֵ-----���µ�ǰ��¼ѧ��ֵ\n");
 		printf("edit n  ����ֵ-----���µ�ǰ��¼����ֵ\n");
 		printf("edit s1 ����1ֵ----���µ�ǰ��¼����1ֵ\n");
 		printf("edit s2 ����2ֵ----���µ�ǰ��¼����2ֵ\n");
 		printf("edit s3 ����3ֵ----���µ�ǰ��¼����3ֵ\n");
 		printf("edit a ѧ�� ���� ����1 ����2 ����3----���µ�ǰ��¼��������٣�\n");
 		printf("------------------------------\n\n\n");
 		return;
	}else if(strcmp(oder,sort)==0)
 	{
 		printf("sort---------------ʹ�á�ƽ���ɼ�����������\n");
 		printf("sort x-------------ʹ�á�ѧ�š���������\n");
 		printf("sort n-------------ʹ�á���������������\n");
 		printf("sort s1------------ʹ�á�����1����������\n");
 		printf("sort s2------------ʹ�á�����2����������\n");
 		printf("sort s3------------ʹ�á�����3����������\n");
 		printf("------------------------------\n\n\n");
 		return;
	}else if(strcmp(oder,set)==0)
 	{
 		printf("set n�����õ�ǰ��¼����ʾ�� \n");
 		printf("------------------------------\n\n\n");
 		return; 
	}else
	{
		printf("û�� %s ����\n",oder);
		printf("------------------------------\n\n\n");
		return;
	 } 
  } 
//����ѡ�� 
void menu(){
 	char oder[100];
 	char *result;
 	PrintMenu();
 	gets(oder);//��gets()����scanf �������ַ��� �м��пո� 
 	result=strtok(oder," ");//����strtok()�����ָ���������� 
 	if(strcmp(result,"rem")==0)
	 {
		result=strtok(NULL," ");
		if(result==NULL)
		{
			rem();
			return ;
		}
		if(strcmp(result,"a")==0)
		{
			rem_a();
			return ;
		}else if(strcmp(result,"x")==0)
		{
			result=strtok(NULL," ");
			rem_x(result);
			return ;
		}
	}
 	if(strcmp(result,"quit")==0)
	 {
 		exit(1);
	}
	if(strcmp(result,"help")==0)
	{
		result=strtok(NULL," ");
		help(result);
		return ;
	}
	if(strcmp(result,"list")==0)
	{
		result=strtok(NULL," ");
		if(result==NULL){
			list();
			return ;
		}else if(strcmp(result,"a")==0)
		{
			list_a();
			return ;
		}else if(strcmp(result,"x")==0)
		{
			result=strtok(NULL," ");
			list_x(result);
			return ;
		}else if(strcmp(result,"n")==0)
		{
			result=strtok(NULL," ");
			list_n(result);
			return ;
		}else
		{
			printf("�������\n");
			return ;
		}
	}
	if(strcmp(result,"sort")==0)
	{
		result=strtok(NULL," ");
		if(result==NULL){
			sort();
			return ;
		 } 
		else if(strcmp(result,"x")==0) {
			sort_x();
			return ;
		}
		else if(strcmp(result,"n")==0){
			sort_n();
			return ;
		}
		else if(strcmp(result,"s1")==0){
			sort_s1();
			return ;
		}
		else if(strcmp(result,"s2")==0){
			sort_s2();
			return ;
		}
		else if(strcmp(result,"s3")==0)
		{
			sort_s3();
			return ;
		}
		else
		{
			printf("�������\n");
			return ;
		}
	}
	if(strcmp(result,"add")==0)
	{
		result=strtok(NULL," ");
		if(result==NULL)
		{
			add1();
			return ;
		}else
		{
			char* name=result;
			char* id=strtok(NULL," ");
			char* s1=strtok(NULL," ");
			char* s2=strtok(NULL," ");
			char* s3=strtok(NULL," ");
			add(name,id,s1,s2,s3);
			return;
		}
	}
	if(strcmp(result,"set")==0)
	{
		result=strtok(NULL," ");
		set(result);
		return;
	} 
	if(strcmp(result,"edit")==0)
	{
		result=strtok(NULL," ");
		if(result==NULL)
		{
			edit();
			return;
		}
		else if(strcmp(result,"a")==0)
		{
			char *id,*name,*s1,*s2,*s3; 
			id=strtok(NULL," ");
			name=strtok(NULL," ");
			s1=strtok(NULL," ");
			s2=strtok(NULL," ");
			s3=strtok(NULL," ");
			edit_a(id,name,s1,s2,s3);
			return;
		}
		else if(strcmp(result,"x")==0)
		{
			char *id=strtok(NULL," ");	
			edit_x(id);
			return;
		}
		else if(strcmp(result,"n")==0)
		{
			char *name=strtok(NULL," ");
			edit_n(name);
			return;
		}
		else if(strcmp(result,"s1")==0)
		{
			char *s1=strtok(NULL," ");
			edit_s1(s1);
			return;
		}
		else if(strcmp(result,"s2")==0)
		{
			char *s2=strtok(NULL," ");
			edit_s2(s2);
			return;
		}
		else if(strcmp(result,"s3")==0)
		{
			char *s3=strtok(NULL," ");
			edit_s3(s3);
			return;
		}
	}
 }  
int main()
{
	while(1)
	{
		menu();
	}
	return 0;
}

