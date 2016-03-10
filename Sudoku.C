#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<ctype.h>


int sa[9][9];
int s[3][3][3][3];
int p[3][3][3][3][9];
int count = 0;
FILE *fp;
FILE *f1;

void table(void);
void input(void);
void ip_chk(void);
void pos_init(void);
void conv(void);
void conv_x(void);
void pos_ele(void);
void pos_ele_1(void);
int row_p(int, int, int, int, int);
int col_p(int, int, int, int, int);
int box_p(int, int, int, int, int);
int p_sum(int, int, int, int, int);
void output(void);
void save_file(void);
void load_file(void);


void main()
{

	int i, j, x, y, k;
	char c, str[2][20];
	clrscr();

	strcpy(str[0],"ENTER A NEW PUZZLE");
	strcpy(str[1],"LOAD A PUZZLE");
	i = 1;

	while(c!=13)
	{
		switch(c)
		{
			case 72:
				if(i>1)
					i--;
				else
					i = 2;

				break;

			case 80:
				if(i<2)
					i++;
				else
					i = 1;
				break;
		}

		for(k = 1; k < 3; k++)
		{
			if(k == i)
				textcolor(143);
			else
				textcolor(7);

			gotoxy(15,10+k*2);
			cprintf("%s",str[k-1]);
		}
		c = getch();
	}
	textcolor(7);
	clrscr();

	fp = fopen("LOG_1","w");
	f1 = fopen("log","w");
	if(i == 1)
	{
		printf("\nPress Esc When Done");
		table();
		input();
		conv();
		printf("\n\n\nPRESS 'S' TO SAVE THE PUZZLE TO A FILE");
		c = getch();
		if(c == 's' || c == 'S')
			save_file();
	}
	if(i == 2)
	{
		load_file();
		clrscr();
		conv();
		output();
		table();
		getch();
	}
	fprintf(fp,"\t\t....SUDOKU....\n\n");
	fprintf(fp,"INPUT VALUES");
	for(i = 0; i < 9; i++)
	{
		fprintf(fp,"\n");
		for(j = 0; j < 9; j++)
			fprintf(fp,"\t%d",sa[j][i]);
	}

	ip_chk();
	fprintf(fp,"ip verified\n");
 //	conv();
	fprintf(fp,"ARRAY conv s\n");
	pos_init();
	fprintf(fp,"POSSIBILITY ARRAY INIT\n");
	_setcursortype(_NOCURSOR);
//	clrscr();
	for(i = 0; i < 90; i++)
	{
		gotoxy(5,1);
//		printf("LOOP COUNT - %2d",i);
		fprintf(fp,"\n\nLOOP COUNT - %d\n\n",i);
		fprintf(f1,"\nloop count - %d \n\n",i);
		pos_ele();
		pos_init();
		if(count>2)
			i = 90;
		delay(20);
		output();

	}
//	printf("\no/p");
	output();
	getch();

	output();
	fclose(f1);
	fclose(fp);
	printf("\n\n\nPRESS ANY KEY TO CONTINUE......");
	getch();


	clrscr();
	printf("\n\n\n\n");
	printf("PROGRAMMED BY -\n\n");

	printf("\n\t ____________ \t   ______  \t   _______  \t _");
	printf("\n\t<____   _____> \t / ____  \\ \ \t  / ______\\ \t| |");
	printf("\n\t     | |    \t| /     \\ | \t | |        \t| |");
	printf("\n\t     | |     \t| |     | | \t | |______  \t| |");
	printf("\n\t  _  | |     \t| |     | | \t |  ______> \t| |");
	printf("\n\t | | | |      \t| |     | | \t | |        \t| |");
	printf("\n\t | \\_| |      \t| \\_____/ | \t | |______  \t| |_____");
	printf("\n\t  \\____/      \t \\_______/  \t  \\_______/ \t|_______|");
	printf("\n\n\n\n\n\nPRESS ANY KEY.....");

	getch();
	exit(1);

}



void table(void)
{
	int i,j;

	for(j = 0; j<=18; j++)
	{
		if(j==0)
		for(i=0; i<=36; i++)
		{
			gotoxy(i+20,3+j);
			if(i==0)
				printf("%c",201);
			else if(i==36)
				printf("%c",187);
			else if(i%12==0)
				printf("%c",203);
			else if(i%4==0)
				printf("%c",209);
			else
				printf("%c",205);
		}

		else if(j==18)
		for(i = 0; i<=36; i++)
		{
			gotoxy(i+20,j+3);

			if(i==0)
				printf("%c",200);
			else if(i == 36)
				printf("%c",188);
			else if(i%12==0)
				printf("%c",202);
			else if(i%4==0)
				printf("%c",207);
			else
				printf("%c",205);
		}
		else if(j%6==0)
		for(i = 0; i<= 36; i++)
		{
			gotoxy(i+20,j+3);
			if(i==0)
				printf("%c",204);
			else if(i==36)
				printf("%c",185);
			else if(i%12==0)
				printf("%c",206);
			else if(i%4==0)
				printf("%c",216);
			else
				printf("%c",205);
		}

		else if(j%2==0)
		for(i = 0; i<=36;i++)
		{
			gotoxy(20+i,j+3);
			if(i==0)
				printf("%c",199);
			else if(i==36)
				printf("%c",182);
			else if(i%12==0)
				printf("%c",215);
			else if(i%4==0)
				printf("%c",197);
			else
				printf("%c",196);
		}


		else
		for(i = 0; i<=36;i++)
		{
			gotoxy(20+i,j+3);
			if(i%12==0)
				printf("%c",186);
			else
				if(i%4 == 0)
				printf("%c",179);
		}

	}
}



void input(void)
{
	char c;
	int x = 22, y = 4;
	int i = 0, j = 0;
	int a,b;

//	gotoxy(50,0);
//	printf("Press Esc when Done");

	while(c != 27)
	{
		for(a = 0; a < 9; a++)
			for(b = 0; b < 9; b++)
			{
				gotoxy(a*4+22,b*2+4);
				if(sa[a][b])
					printf("%d",sa[a][b]);
				else
					printf(" ");
			}
		gotoxy(x,y);
		c = getch();
		if(isdigit(c))
		{
			 sa[i][j] = c - 48;
		}
		if(c-48 == 0)
			sa[i][j] = 0;
		else
		switch(c)
		{
			case 77:
				if(x<54)
				{
					x = x + 4;
					i++;
				}
				 gotoxy(x,y);
				 break;

			case 75:
				if(x > 22)
				{
					x = x - 4;
					i--;
				}
				gotoxy(x,y);
				break;

			case 72:
				if(y > 4)
				{
					y = y - 2;
					j--;
				}
				gotoxy(x,y);
				break;

			case 80:
				if(y < 20)
				{
					y = y + 2;
					j++;
				}
				gotoxy(x,y);
				break;
		}
	}
}
/*
void conv(void)
{

	int i, j;

	for(i = 0; i < 9; i++)
		for(j = 0; j < 9; j++)
			s[i%3][j%3][i/3][j/3] = sa[i][j];

	return;
}
 */


void conv(void)
{

	int i, j, a, b;
	int r, c;

	for(i = 0; i < 3; i++)
		for(a = 0; a < 3; a++)
			for(j = 0; j < 3; j++)
				for(b = 0; b < 3; b++)
				{
					c = i*3+a;
					r = j*3+b;
					s[i][j][a][b] = sa[r][c];
				}
	return;
}


void ip_chk(void)
{
	int i,j;
	int t;
	int b1, b2, i1, j1;
	int br, bc;
	int tr, tc;
	int t1, t2;
	fprintf(fp,"\n\tINPUT VERIFICATION\nERRORS:");
	for(i = 0; i < 9; i++)
		for(j = 0; j < 9; j++)
			for(t = 0; t < 9; t++)
			{
				if(t != j)
				{
					if(sa[i][j] && s[i][t] && sa[i][j] == sa[i][t])
						fprintf(fp,"\n\tERROR IN %d|%d n %d|%d",i,j,i,t);

				}
				if(t != i)
				{
					if(s[i][j] && sa[t][j] && sa[i][j] == sa[t][j])
						fprintf(fp,"\n\tERROR IN %d|%d n %d|%d",i,j,t,j);
				}
			}




	for(i = 0; i < 9; i++)
		for(j = 0; j < 9; j++)
		{
			for(t1 = (i-i%3); t1 < (i-i%3)+3; t1++)
				for(t2 = j-j%3; t2 < (j-j%3)+3; t2++)
				{
					if(i == t1 && j == t2)
						break;
					if(sa[i][j] && sa[t1][t2] && sa[i][j] == sa[t1][t2])
						fprintf(fp,"\n\tbERROR AT %d,%d n%d,%d",i,j,t1,t2);
				}
		}
}


void pos_init(void)
{
	int i, j, a, b, n;

	int x, y;
	fprintf(fp,"\nINITIALIZING ARRAY WITH POSSIBILITIES\n\n");
	for(i = 0; i < 3; i++)
		for(j = 0; j < 3; j++)
			for(a = 0; a < 3; a++)
				for(b = 0; b < 3; b++)
					for(n = 0; n < 9; n++)
					{
						if(s[i][j][a][b] != 0)
							p[i][j][a][b][n] = 0;
						else
							p[i][j][a][b][n] = 1;

					}
		pos_ele_1();

	for(x = 0; x < 3; x++)
		for(y = 0; y < 3; y++)
			for(a = 0; a < 3; a++)
				for(b = 0; b < 3; b++)
				{
					fprintf(fp," %d|%d --> %d|%d\n",x,y,a,b);
					for(n = 0; n < 9; n++)
						fprintf(fp," %d ",p[x][y][a][b][n]);
					fprintf(fp,"\n\n");
				}
	fprintf(fp,"\tEND OF INITIALIZATION");

	for(n = 0; n < 9; n++)
	{
		fprintf(f1,"\nPOSSIBILITY OF %d\n",n+1);
		for(x = 0; x < 3; x++)
			for(a = 0; a < 3; a++)
			{
				for(y = 0; y < 3; y++)
					for(b = 0; b < 3; b++)
						fprintf(f1,"\t%d",p[x][y][a][b][n]);
				fprintf(f1,"\n");
			}
	}




	for(i = 0; i < 9; i++)
	{
		fprintf(f1,"\n");
		for(j = 0; j < 9; j++)
			fprintf(f1,"\t%d",sa[j][i]);
	}

//  	getch();
//	pos_ele_1();


	for(i = 0; i < 9; i++)
	{
		fprintf(fp,"\n");
		for(j = 0; j < 9; j++)
			fprintf(fp,"\t%d",sa[j][i]);
	}
}


void pos_ele_1(void)
{
	int i, j, a, b, n;
	int x, y;

	for(i = 0; i < 3; i++)
		for(j = 0; j < 3; j++)
			for(a = 0; a < 3; a++)
				for(b = 0; b < 3; b++)
				{
					if(s[i][j][a][b])
					{
						n = s[i][j][a][b];

						for(x = 0; x < 3; x++)
							for(y = 0; y < 3; y++)
							{
								p[x][j][y][b][n-1] = 0;
								p[i][x][a][y][n-1] = 0;
								p[i][j][x][y][n-1] = 0;
							}
					}
				}
}



void pos_ele(void)
{
	int i, j, a, b;
	int n;
	int rp, cp, bp;
	int pdt;
	char x;
	int res = 0;



	for(i = 0; i < 3; i++)
		for(j = 0; j < 3; j++)
		{
//			printf("i = %d - j = %d",i,j);
			for(a = 0; a < 3; a++)
				for(b = 0; b < 3; b++)
				{
//					printf("\na=%d  -  b = %d\t",a,b);
					if(s[i][j][a][b] == 0)
					{
						for(n=1; n<=9; n++)
						{
							 rp = row_p(i, j, a, b, n);
							 cp = col_p(i, j, a, b, n);
							 bp = box_p(i, j, a, b, n);

  //							 printf("\nn-%d %d-%d- %d",n,rp,cp,bp);
							 pdt = rp * cp * bp;

							 if(kbhit())
							 {
								x = getche();
								if(x == 27)
								{
									count = 5;
									return;
								}
							 }
							 if(!pdt)
								p[i][j][a][b][n-1] = 0;
							 if(pdt)
							 {
								res =  p_sum(i, j, a, b, n);
								if(res)
									return;
							 }

    //							 printf("end of n=%d",n);
						}
					}
				}
		}

    count++;
}

int row_p(int i, int j, int a, int b, int n)
{
	int x, y;
	int r = 1;

	for(x = 0; x < 3; x++)
		for(y = 0; y < 3; y++)
		{
			if(x != i && y != a)
			{
				if(s[x][j][y][b] == n)
					r = 0;
			}
		}
	return(r);
}

int col_p(int i, int j, int a, int b, int n)
{
	int x, y;
	int r = 1;

	for(x = 0; x < 3; x++)
		for(y = 0; y < 3; y++)
		{
			if(x != j && y != b)
			{
				if(s[i][x][a][y] == n)
					r = 0;
			}
		}
	return(r);
}

int box_p(int i, int j, int a, int b, int n)
{
	int x, y;
	int r = 1;

	for(x = 0; x < 3; x++)
		for(y = 0; y < 3; y++)
		{
				if(s[i][j][x][y] == n)
					r = 0;
		}
	return(r);
}

int p_sum(int i, int j, int a, int b, int n)
{
	int t, o;
	int tt, x;
	int f = 0;

	int rp, cp, bp;


	fprintf(fp,"\np_sum of() i=%d j=%d a=%d b=%d n=%d",i,j,a,b,n);
	/* 	cell 	*/
//	gotoxy(50,1);
  //	printf("CELL");
	o = 0;
	for(t = 0; t < 9; t++)
		o = o + p[i][j][a][b][t];

	if(o == 1)
	{
		for(t = 0; t < 9; t++)
			if(p[i][j][a][b][t])
			{

				rp = row_p(i, j, a, b, t+1);
				cp = col_p(i, j, a, b, t+1);
				bp = box_p(i, j, a, b, t+1);
				s[i][j][a][b] = (t+1) * rp * cp * bp;
				if(s[i][j][a][b])
				{
					f = 1;
  //					output();
					p[i][j][a][b][t] = 0;
					t = 9;
					goto ele_t;
				}
			}
	}


	/*	box     */
    //	gotoxy(50,1);
    //	printf("BOX");

	o = 0;
	for(tt = 0; tt < 3; tt++)
		for(x = 0; x < 3; x++)
			o = o + p[i][j][tt][x][n-1];

	if(o == 1)
	{
		for(tt = 0; tt < 3; tt++)
			for(x = 0; x < 3; x++)
				if(p[i][j][tt][x][n-1])
				{

					rp = row_p(i, tt, a, x, n);
					cp = col_p(i, tt, a, x, n);
					bp = box_p(i, tt, a, x, n);
					s[i][j][tt][x] = n;
					if(s[i][j][tt][x])
					{
    //						output();
						for(t = 0; t<=9; t++)
							p[i][j][tt][x][t] = 0;
						tt = 3;
						x = 3;
						f = 4;
						goto ele_t;
					}
				}
	}


 //	printf("\tcell_s");
	/*	row	*/
//	gotoxy(50,1);
 //	printf("ROW");
	o = 0;
	for(tt = 0; tt < 3; tt++)
		for(x = 0; x < 3; x++)
			o = o + p[tt][j][x][b][n-1];

	if(o == 1)
	{
 //		for(tt = 0; tt < 3; tt++)
//			for(x = 0; x < 3; x++)
				if(p[i][j][a][b][n-1])
				{

					rp = row_p(i, j, a, b, n);
					cp = col_p(i, j, a, b, n);
					bp = box_p(i, j, a, b, n);
					s[i][j][a][b] = n * rp * cp * bp;
					if(s[i][j][a][b])
					{
						f = 2;
      //						output();
						p[i][j][a][b][n-1] = 0;
//					x = 3;
//					tt = 3;
						goto ele_t;
					}
				}
	}

//	printf("\trow_s");
	/*	column	*/

//	gotoxy(50,1);
 //	printf("COL");

	o = 0;

	for(tt = 0; tt < 3; tt++)
		for(x = 0; x < 3; x++)
			o = o + p[i][tt][a][x][n-1];

	if(o == 1)
	{
		for(tt = 0; tt < 3; tt++)
			for(x = 0; x < 3; x++)
				if(p[i][tt][a][x][n-1] == 1)
				{
					rp = row_p(i, tt, a, x, n-1);
					cp = col_p(i, tt, a, x, n-1);
					bp = box_p(i, tt, a, x, n-1);
					s[i][tt][a][x] = n;
					if(s[i][tt][a][x])
					{
						f = 3;
	//					output();
						p[i][tt][a][x][n-1] = 0;
						x = 3;
						tt = 3;
						goto ele_t;
					}
				}
	}

 //	printf("\tcol_s");

//	printf("\tbox_s");


	/*	       box	*/
/*	o = 0;

	for(t = 0; t < 3; t++)
		for(x = 0; x < 3; x++)
			o = o + p[i][j][t][x][n];

	if(o == 1)
     d
	{

		s[i][j][a][b] = n;
		f = 1;
   //		printf(".......%d.....",n);
		for(t = 0; t < 9; t++)
			p[i][j][a][b][t] = 0;
		for(t= 0; t < 3; t++)
			for(x = 0; x < 3; x++)
				p[i][j][t][x][n] = 0;
     //		getch();
		goto ele_t;
	}

  */


	ele_t:
		if(f)
		{
			for(t = 0; t < 9; t++)
				p[i][j][a][b][n] = 0;

			for(t = 0; t < 3; t++)
				for(x = 0; x < 3; x++)
					p[i][j][t][x][n-1] = 0;

			for(t = 0; t < 3; t++)
				for(x = 0;  x < 3; x++)
				{
					p[i][t][a][x][n-1] = 0;
					p[t][j][x][b][n-1] = 0;
				}

   /*			if(n == 9)
			{
				gotoxy(1,1);
				printf("%d",f);
			}
   */	                output();
			return(1);

		}
	return(0);

}
/*
void conv_x(void)
{
	int i, j, a, b;
	for(i = 0; i < 9; i++)
		for(j = 0; j < 9; j++)
			sa[i][j] = 0;

	for(i = 0; i < 3; i++)
		for(j = 0; j < 3; j++)
			for(a = 0; a < 3; a++)
				for(b = 0; b < 3; b++)
				sa[i+a*3][j+b*3] = s[i][j][a][b];
}
 */


void conv_x(void)
{
	int i, j, a, b, r, c;

	for(i = 0; i < 9; i++)
		for(j = 0; j < 9; j++)
			sa[i][j] = 0;

	for(i = 0; i < 3; i++)
		for(a = 0; a < 3; a++)
			for(j = 0; j < 3; j++)
				for(b = 0; b < 3; b++)
				{
					c = j*3+b;
					r = i*3+a;
					sa[r][c] = s[i][j][a][b];
				}

	return;
}

void output(void)
{
	int a, b;

//	clrscr();
 //	table();
	conv_x();


		for(a = 0; a < 9; a++)
			for(b = 0; b < 9; b++)
			{
				gotoxy(b*4+22,a*2+4);
				if(sa[a][b])
					printf("%d",sa[a][b]);
			}
}

void save_file(void)
{
	int i;
	FILE *fp;
	char ch[15];

	printf("\n\nenter a file name\t");
	scanf("%s",ch);

	fp = fopen(ch,"w");
	fwrite(sa, sizeof(sa),1,fp);

	printf("\nDATA WAS SUCCESSFULLY WRITTEN\n\n");
	fclose(fp);
	printf("\tPRESS ANY KEY TO CONTINUE");
	getch();
	clrscr();
	output();
	table();
	return;
}

void load_file(void)
{
	FILE *fp;
	char ch[15];
	printf("\n\nENTER THE NAME OF THE FILE TO LOAD\t");
	scanf("%s",ch);

	fp = fopen(ch,"r");

	if(fp == NULL)
	{
		printf("THRER WAS AN ERROR IN OPENING THE FILE....");
		printf("\nPRESS ANY KEY TO EXIT....");
		getch();
		getch();
		exit(1);
	}
	fread(sa, sizeof(sa),1,fp);
	fclose(fp);

	printf("\nSUDOKU PUZZLE WAS SUCCESSFULLY LOADED");
	printf("\n\tPERSS ANY KEY TO CONTINUE....");
	getch();
	return;
}
