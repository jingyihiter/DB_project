#ifndef __LCC__
#define __LCC__
#endif

#include <stdio.h>
#include <mysql.h>
#include <string.h>

int main(int argc, char *argv[])
{
    MYSQL mysql_conn; /* Connection handle */
    char my_query[1000];
    MYSQL_RES *mysql_result;
    MYSQL_ROW mysql_row;
    int f1,f2,num_row,num_col;
    int i,num,k;
    int j=0;
    char *Parameters[100];
    if (mysql_init(&mysql_conn) != NULL)
    {
        if (mysql_real_connect(
                    &mysql_conn, "localhost", "root",
                    "mjy123456", "company", MYSQL_PORT,
                    NULL, 0) != NULL)
        {
            //解析输入命令
            if(strcmp(argv[1],"company_query")!=0)
            {
                //printf("%s\n",argv[1]);
                printf("命令名输入错误！");
                return 0;
            }
            for(i=2;i<argc;i++)
            {
              if(strcmp(argv[i],"-q")==0)
              {
                  num = atoi(argv[i+1]);
                  //printf("查询序号 num = %d\n",num);
                  i++;
                  if(num < 1 || num>9)
                    {
                        printf("查询序号不存在");
                        return 0;
                    }
              }
              if(strcmp(argv[i],"-p")==0)
              {
                  //printf("参数列表：\n");
                  for(k=i+1;k<argc;k++)
                  {
                      Parameters[j]=argv[k];
                      //printf("%d %s\n",j,Parameters[j]);
                      j++;
                  }
                  break;
              }
            }
            switch(num)
            {
            case 1:
                {
                    char *pno;
                    pno = Parameters[0];
                    char *p0 = "select ESSN from WORKS_ON where PNO = '";
                    char *p01 = "'";
                    strcpy(my_query,p0);
                    strcat(my_query,pno);
                    strcat(my_query,p01);
                    break;
                }
            case 2:
                {
                    char *pname=Parameters[0];
                    char *p1 = "Select ENAME \
                    from employee,works_on,project \
                    where employee.ESSN = works_on.ESSN and project.PNO=works_on.PNO and project.PNAME ='";
                    char *p12 = "'";
                    strcpy(my_query,p1);
                    strcat(my_query,pname);
                    strcat(my_query,p12);
                    break;
                }
            case 3:
                {
                    char *dname=Parameters[0];
                    //gets(dname);
                    char *p2 = "Select ENAME,ADDRESS \
                    from employee,department                  \
                    where employee.DNO = department.DNO and department.DNAME ='";
                    char *p22 ="'";
                    strcpy(my_query,p2);
                    strcat(my_query,dname);
                    strcat(my_query,p22);
                    free(dname);
                    break;
                }
            case 4:
               {
                    char *dname=Parameters[0];
                    char *salary=Parameters[1];
                    char *p30 = "Select ENAME,ADDRESS from employee,department where employee.DNO = department.DNO and department.DNAME ='";
                    char *p301 = "'";
                    strcpy(my_query,p30);
                    strcat(my_query,dname);
                    strcat(my_query,p301);
                    char *p31 = " and employee.SALARY < ";
                    strcat(my_query,p31);
                    strcat(my_query,salary);
                    break;
               }
            case 5:
                {
                    char *pno=Parameters[0];
                    //gets(pno);
                    char *p4 = "Select ENAME from employee,works_on where employee.ESSN=works_on.ESSN and works_on.PNO !='";
                    char *p41 = "'";
                    strcpy(my_query,p4);
                    strcat(my_query,pno);
                    strcat(my_query,p41);
                    free(pno);
                    break;
                }
            case 6:
              {
                    char *ename=Parameters[0];
                    char *p5 = "Select ENAME,DNAME from employee,department where employee.DNO = department.DNO and employee.superssn in (Select ESSN from employee where ENAME = '";
                    char *p52 = "'";
                    strcpy(my_query,p5);
                    char *p51 = ")";
                    strcat(my_query,ename);
                    strcat(my_query,p52);
                    strcat(my_query,p51);
                    break;
               }
            case 7:
              {
                    char *pno1 = Parameters[0];
                    char *pno2 = Parameters[1];
                    char *p60 = "Select ESSN from employee where ESSN in (Select ESSN from works_on where PNO ='";
                    char *p61 = ") and ESSN in (Select ESSN from works_on where PNO ='";
                    char *p62 = ")";
                    char *p63 = "'";
                    strcpy(my_query,p60);
                    strcat(my_query,pno1);
                    strcat(my_query,p63);
                    strcat(my_query,p61);
                    strcat(my_query,pno2);
                    strcat(my_query,p63);
                    strcat(my_query,p62);
                    break;
               }
            case 8:
              {
                    char *salary=Parameters[0];
                    char *p7 ="Select DNAME from department where DNO in \
                    (Select DNO from employee  \
                    group by DNO  having avg(SALARY) < ";
                    char *p71 = ")";
                    strcpy(my_query,p7);
                    strcat(my_query,salary);
                    strcat(my_query,p71);
                    break;
               }
            default:
                {
                    char *n=Parameters[0];
                    char *hour =Parameters[1];
                    char *p8 = "Select ENAME from employee 	where ESSN in \
                    (Select ESSN from works_on \
                    group by ESSN having count(DNO)>=";
                    char *p81 = " and sum(HOURS)<=";
                    char *p82 = ")";
                    strcpy(my_query,p8);
                    strcat(my_query,n);
                    strcat(my_query,p81);
                    strcat(my_query,hour);
                    strcat(my_query,p82);
                    break;
               }

            }

            //数据库query
            mysql_query(&mysql_conn,"set names gbk");
            mysql_query(
                &mysql_conn,my_query);
            mysql_result = mysql_store_result(&mysql_conn);
            num_row = mysql_num_rows(mysql_result);
            num_col = mysql_num_fields(mysql_result);
            for(f1=0; f1<num_row; f1++)
            {
                mysql_row = mysql_fetch_row(mysql_result);
                for(f2=0; f2<num_col; f2++)
                {
                    printf("%s \t",mysql_row[f2]);
                }
                printf("\n");
            }
        }
        else
            printf("Query fails\n");

        /* Free the result to release the heap memory*/

    }
    else
    {
        int i = mysql_errno(&mysql_conn);
        const char *s = mysql_errno(&mysql_conn);
        printf("Connection fails(ERROR %d): %s\n",i,s);
    }
    mysql_free_result(mysql_result);
    //free(my_query);
    mysql_close(&mysql_conn);
    return 0;
}
