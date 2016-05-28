#ifndef __LCC__
#define __LCC__
#endif

#include <stdio.h>
#include<stdlib.h>
#include <mysql.h>
#include<string>
#include<iostream>

using namespace std;

#define maxsize 1024

int login=0;
string Global_friendEmail;    //添加好友，互相添加，存全局变量
string Global_deleteRemark; //删除好友，互相删除
string Global_logID;          //删除日志，删除对应的评论、分享
//初始界面
void showHome();
//登录注册
void LoginOrRegist();
string Regist();
string LoginIn();
//主页
int HomeView();
//完善信息
int PerfectDate();
//完善基本信息
int PerfectPersonInfo();
string UpdatePersonInfo(string userIDstr);
string PerfectEmail(string userIDstr);
//完善个人经历
int PerfectExperience();
string PerfectEduExperience(string userIDstr);
string ChangeEduExperience(string userIDstr);
string PerfectWorkExperience(string userIDstr);
string ChangeWorkExperience(string userIDstr);
//分组管理  创建 修改 删除
int HandleGroup();
string CreateGroup(string userIDstr);
string ChangeGroup(string userIDstr);
string DeleteGroup(string userIDstr);
string ShowFriendInGroup(string userIDstr);
//好友添加到分组内
string AddFriendToGroup(string userIDstr);
//好友管理
int ManageGdFriend();
string SearchFriend();
string AddNewFriend(string userIDstr);
string AddNewFriendMutual(string userIDstr);
string DeleteFriend(string userIDstr);
string DeleteFriendMutual(string userIDstr);
//消息管理
int ManageNews();
string ShowNews(string userIDstr);
string SendNews(string userIDstr);
//日志管理
int ManageLog();
string ShowLog(string userIDstr);
string PublicLog(string userIDstr);
string ChangeLog(string userIDstr);
string DeleteLog(string userIDstr);
string DeleteReplyOfLog(string userIDstr);//日志删除，删除对应的回复
string DeleteShareOfLog(string userIDstr); //日志删除，删除对应的分享
//添加日志回复
int ManageReplyAndSharelog();
string AddComment(string userIDstr);
string ShowComment(string userIDstr);
//分享日志
string AddSharelog(string userIDstr);
string showSharLog(string userIDstr);

int main(int argc, char **argv)
{
    MYSQL mysql_conn; /* Connection handle */
    //
    showHome();
    LoginOrRegist();
    string userIDstr;
    string userEmail;
    MYSQL_RES *mysql_result;
    MYSQL_ROW mysql_row;
    if (mysql_init(&mysql_conn) != NULL)
    {
        if (mysql_real_connect(
                    &mysql_conn, "localhost", "root",
                    "mjy123456", "networking", MYSQL_PORT,
                    NULL, 0) != NULL)
            {
                if(login == 0)
                    {
                        system("cls");
                        const char *myquery = Regist().c_str();
                        mysql_query(&mysql_conn,"set names gbk");
                        mysql_query(&mysql_conn,myquery);

                        const char *myquery0 = LoginIn().c_str();
                        mysql_query(&mysql_conn,myquery0);
                        mysql_result = mysql_store_result(&mysql_conn);
                        //***********//判断不对*****
                        if(mysql_result!=0)
                            login = 1;   //登录成功
                        else login = 0;
                        int num_row = mysql_num_rows(mysql_result);
                        //int num_col = mysql_num_fields(mysql_result);
                        int f1;
                        for(f1=0; f1<num_row; f1++)
                        {
                            mysql_row = mysql_fetch_row(mysql_result);
                            userIDstr = mysql_row[0];
                            userEmail = mysql_row[1];
                            printf("\n");
                        }
                    }
                else
                    {
                        const char *myquery0 = LoginIn().c_str();
                        mysql_query(&mysql_conn,myquery0);
                        mysql_result = mysql_store_result(&mysql_conn);
                        if(mysql_result!=0)
                            login = 1;   //登录成功
                        else login =0 ;
                        int num_row = mysql_num_rows(mysql_result);
                        int f1;
                        for(f1=0; f1<num_row; f1++)
                        {
                            mysql_row = mysql_fetch_row(mysql_result);
                            userIDstr = mysql_row[0];
                            userEmail = mysql_row[1];
                            printf("\n");
                        }

                    }
                if(login==1)  //已登录
                {

                        system("cls");
                        while(int homenum = HomeView())
                       {
                           switch (homenum)
                           {
                           case 1://完善个人信息
                               {
                                   int datanum = PerfectDate();
                                   if(datanum == 1)  //完善基本信息
                                   {
                                       int personnum = PerfectPersonInfo();
                                       if(personnum == 1)  //基本信息修改
                                       {
                                           system("cls");
                                           const char *person_query = UpdatePersonInfo(userIDstr).c_str();
                                           mysql_query(&mysql_conn,person_query);
                                           mysql_result = mysql_store_result(&mysql_conn);
                                           if(mysql_result!=0) cout<<"\t修改成功"<<endl;
                                         }
                                       else if(personnum == 2) //添加更多邮箱
                                       {
                                           const char *email_query = PerfectEmail(userIDstr).c_str();
                                           mysql_query(&mysql_conn,email_query);
                                           mysql_result = mysql_store_result(&mysql_conn);
                                           if(mysql_result!=0) cout<<"\t添加成功"<<endl;
                                       }
                                       else

                                            system("cls");
                                            break;
                                   }
                                   else if(datanum == 2)  //完善个人经历
                                   {
                                       int expnum = PerfectExperience();
                                       if(expnum == 1)  //完善教育经历
                                       {
                                           system("cls");
                                           const char * edu_query = PerfectEduExperience(userIDstr).c_str();
                                           mysql_query(&mysql_conn,edu_query);
                                           mysql_result = mysql_store_result(&mysql_conn);
                                           if(mysql_result!=0) cout<<"\t添加成功"<<endl;
                                       }
                                       else if(expnum == 2) //修改教育经历
                                       {
                                           system("cls");
                                           const char * changedu_query = ChangeEduExperience(userIDstr).c_str();
                                           mysql_query(&mysql_conn,changedu_query);
                                           mysql_result = mysql_store_result(&mysql_conn);
                                           if(mysql_result!=0) cout<<"\t修改成功"<<endl;
                                       }
                                       else if(expnum == 3)  //完善工作经历
                                       {
                                           system("cls");
                                           const char * work_query = PerfectWorkExperience(userIDstr).c_str();
                                           mysql_query(&mysql_conn,work_query);
                                           mysql_result = mysql_store_result(&mysql_conn);
                                           if(mysql_result!=0) cout<<"\t添加成功"<<endl;
                                       }
                                       else if(expnum == 4) //修改工作经历
                                       {
                                           system("cls");
                                           const char * changework_query = ChangeWorkExperience(userIDstr).c_str();
                                           mysql_query(&mysql_conn,changework_query);
                                           mysql_result = mysql_store_result(&mysql_conn);
                                           if(mysql_result!=0) cout<<"\t修改成功"<<endl;
                                       }
                                       else
                                       {
                                           system("cls");
                                           break;
                                       }
                                                                                                               }
                                   else
                                    {
                                         system("cls");
                                         break;
                                    }
                                     break;

                               }
                           case 2://群组管理
                               {
                                   int groupnum = HandleGroup();
                                   if(groupnum == 1)//创建群组
                                   {
                                       system("cls");
                                       const char *creategroup_query = CreateGroup(userIDstr).c_str();
                                       mysql_query(&mysql_conn,creategroup_query);
                                       mysql_result = mysql_store_result(&mysql_conn);
                                       if(mysql_result!=0) cout<<"\t添加成功"<<endl;
                                   }
                                   else if(groupnum == 2) //修改群组
                                   {
                                       system("cls");
                                       const char * changeGroup_query = ChangeGroup(userIDstr).c_str();
                                       mysql_query(&mysql_conn,changeGroup_query);
                                       mysql_result = mysql_store_result(&mysql_conn);
                                       if(mysql_result!=0) cout<<"\t修改成功"<<endl;
                                   }
                                   else if(groupnum == 3)
                                   {
                                       system("cls");
                                       const char * delete_group_query = DeleteGroup(userIDstr).c_str();
                                       mysql_query(&mysql_conn,delete_group_query);
                                       mysql_result = mysql_store_result(&mysql_conn);
                                       if(mysql_result!=0) cout<<"\t删除成功"<<endl;
                                   }
                                   else if(groupnum == 4)
                                   {
                                       system("cls");
                                       const char * showFriendIngroup_query = ShowFriendInGroup(userIDstr).c_str();
                                       mysql_query(&mysql_conn,showFriendIngroup_query);
                                       mysql_result = mysql_store_result(&mysql_conn);
                                       int num_row = mysql_num_rows(mysql_result);
                                       cout<<endl;
                                       for(int i=0;i<num_row;i++)
                                       {
                                           mysql_row = mysql_fetch_row(mysql_result);
                                           if(i==0) printf("\t组名:%s\n\n",mysql_row[0]);
                                           printf("\t备注：%s\n",mysql_row[1]);
                                           printf("\t姓名:%s\n",mysql_row[2]);
                                           printf("\t邮箱:%s\n",mysql_row[3]);

                                       }
                                       if(mysql_result!=0) cout<<"\t"<<endl;
                                   }
                                   else
                                     {
                                         system("cls");
                                         break;
                                     }
                                 break;
                               }
                           case 3://好友管理
                               {
                                   int friendnum = ManageGdFriend();
                                   if(friendnum == 1) //查找好友
                                   {
                                        system("cls");
                                        const char *search_query = SearchFriend().c_str();
                                        mysql_query(&mysql_conn,search_query);
                                        mysql_result = mysql_store_result(&mysql_conn);
                                        int num_row = mysql_num_rows(mysql_result);
                                        int f1;
                                        printf("\n\t************************查找结果***********************\t\n");
                                        printf("\n");
                                        for(f1=0; f1<num_row; f1++)
                                        {
                                            mysql_row = mysql_fetch_row(mysql_result);
                                            printf("\t姓名：%s\n",mysql_row[0]);
                                            printf("\t邮箱: %s\n",mysql_row[1]);
                                            printf("\t性别：%s\n",mysql_row[2]);
                                            printf("\t生日：%s\n",mysql_row[3]);
                                            printf("\t住址：%s\n\n\n",mysql_row[4]);
                                        }
                                   }
                                   else if(friendnum == 2) //添加好友
                                   {
                                    system("cls");//添加到己方好友列表
                                    const char* addFriend_query = AddNewFriend(userIDstr).c_str();
                                    mysql_query(&mysql_conn,addFriend_query);
                                    mysql_result = mysql_store_result(&mysql_conn);
                                    if(mysql_result!=0) cout<<"\t添加成功"<<endl;
                                    //添加到对方列表
                                    const char* addFriendmutual_query = AddNewFriendMutual(userIDstr).c_str();
                                    mysql_query(&mysql_conn,addFriendmutual_query);
                                    mysql_result = mysql_store_result(&mysql_conn);
                                    if(mysql_result!=0) cout<<"\t添加成功"<<endl;
                                   }
                                   else if(friendnum == 3) //删除好友
                                   {
                                    system("cls");
                                    const char* deleteFriend_query = DeleteFriend(userIDstr).c_str();
                                    //cout<<deleteFriend_query<<endl;
                                    //const char* deleteFriendmutual_query = DeleteFriendMutual(userIDstr).c_str();
                                    //cout<<deleteFriendmutual_query<<endl;
                                    mysql_query(&mysql_conn,deleteFriend_query);
                                    //mysql_query(&mysql_conn,deleteFriendmutual_query);
                                    mysql_result = mysql_store_result(&mysql_conn);
                                    if(mysql_result!=0) cout<<"\t删除成功"<<endl;
                                   }
                                   else if(friendnum == 4)
                                   {
                                    system("cls");
                                    const char* addFriendToGroup_query = AddFriendToGroup(userIDstr).c_str();
                                    mysql_query(&mysql_conn,addFriendToGroup_query);
                                    mysql_result = mysql_store_result(&mysql_conn);
                                    if(mysql_result!=0) cout<<"\t添加成功"<<endl;
                                   }
                                   else
                                   {
                                      system("cls");
                                      break;
                                   }
                                    break;
                               }
                           case 4://消息管理
                            {
                                int newsnum = ManageNews();
                                if(newsnum == 1) //查看消息
                                {
                                    system("cls");
                                    const char* showNews_query = ShowNews(userIDstr).c_str();
                                    mysql_query(&mysql_conn,showNews_query);
                                    mysql_result = mysql_store_result(&mysql_conn);
                                    int num_row = mysql_num_rows(mysql_result);
                                    int f1;
                                    for(f1=0;f1<num_row;f1++)
                                    {
                                        mysql_row = mysql_fetch_row(mysql_result);
                                        printf("\t接收人ID：%s\n",mysql_row[3]);
                                        printf("\t发送人ID：%s\n",mysql_row[2]);
                                        printf("\t发送时间: %s\n",mysql_row[1]);
                                        printf("\t消息内容:%s\n\n\n",mysql_row[0]);
                                    }


                                }
                                else if(newsnum == 2) //发送消息
                                {
                                    system("cls");
                                    const char* sendNews_query = SendNews(userIDstr).c_str();
                                    mysql_query(&mysql_conn,sendNews_query);
                                    mysql_result = mysql_store_result(&mysql_conn);
                                    if(mysql_result!=0) cout<<"\t添加成功"<<endl;
                                }
                                else
                                    {
                                    system("cls");
                                     break;
                                     }
                                    break;

                            }
                           default: //日志管理
                            {
                                int lognum= ManageLog();
                                if(lognum == 1)
                                    {
                                    system("cls");
                                    const char* showlog_query = ShowLog(userIDstr).c_str();
                                    mysql_query(&mysql_conn,showlog_query);
                                    mysql_result = mysql_store_result(&mysql_conn);
                                    int num_row = mysql_num_rows(mysql_result);
                                    int f1;
                                    for(f1=0;f1<num_row;f1++)
                                    {
                                        mysql_row = mysql_fetch_row(mysql_result);
                                        printf("\t日志ID：%s\n",mysql_row[0]);
                                        printf("\t内容：%s\n",mysql_row[1]);
                                        printf("\t发表时间: %s\n",mysql_row[2]);
                                        printf("\t可回复:%s\n",mysql_row[3]);
                                        printf("\t可公开:%s\n",mysql_row[4]);
                                        printf("\n\n");
                                    }

                                    //评论及分享日志
                                    int num = ManageReplyAndSharelog();
                                    if(num == 1)  //评论日志
                                    {
                                        const char* add_comment_log_query = AddComment(userIDstr).c_str();
                                        mysql_query(&mysql_conn,add_comment_log_query);
                                        mysql_result = mysql_store_result(&mysql_conn);
                                    }
                                    else if(num == 2) //查看评论
                                    {
                                        system("cls");
                                        const char* show_comment_log_query = ShowComment(userIDstr).c_str();
                                        mysql_query(&mysql_conn,show_comment_log_query);
                                        mysql_result = mysql_store_result(&mysql_conn);
                                        int num_row = mysql_num_rows(mysql_result);
                                        int f1;
                                        for(f1=0;f1<num_row;f1++)
                                        {
                                            mysql_row = mysql_fetch_row(mysql_result);
                                            if(f1 == 0) printf("\t日志内容：%s\n\n",mysql_row[0]);
                                            printf("\t回复时间：%s\n",mysql_row[1]);
                                            printf("\t回复内容: %s\n",mysql_row[2]);

                                        }
                                    }
                                    else if(num == 3) //分享日志
                                    {
                                        const char* add_share_log_query = AddSharelog(userIDstr).c_str();
                                        mysql_query(&mysql_conn,add_share_log_query);
                                        mysql_result = mysql_store_result(&mysql_conn);
                                    }
                                    else if(num == 4)  //查看分享
                                    {
                                        system("cls");
                                       const char* show_share_log_query = showSharLog(userIDstr).c_str();
                                        mysql_query(&mysql_conn,show_share_log_query);
                                        mysql_result = mysql_store_result(&mysql_conn);
                                         int num_row = mysql_num_rows(mysql_result);
                                        int f1;
                                        for(f1=0;f1<num_row;f1++)
                                        {
                                            mysql_row = mysql_fetch_row(mysql_result);
                                            printf("\t日志内容：%s\n",mysql_row[0]);
                                            printf("\t修改时间：%s\n",mysql_row[1]);
                                            printf("\t分享时间: %s\n",mysql_row[2]);
                                            printf("\t分享内容: %s\n",mysql_row[3]);
                                            printf("\n\n");
                                        }
                                    }
                                    else
                                        break;
                                    }
                                else if(lognum == 2) //发表日志
                                    {
                                    system("cls");
                                    const char* sendLog_query = PublicLog(userIDstr).c_str();
                                    mysql_query(&mysql_conn,sendLog_query);
                                    mysql_result = mysql_store_result(&mysql_conn);
                                    if(mysql_result!=0) cout<<"\t添加成功"<<endl;
                                    }
                                else if(lognum == 3)
                                    {
                                        const char* changeLog_query = ChangeLog(userIDstr).c_str();
                                        //cout<<changeLog_query<<endl;
                                        mysql_query(&mysql_conn,changeLog_query);
                                        mysql_result = mysql_store_result(&mysql_conn);
                                        if(mysql_result!=0) cout<<"\t修改成功"<<endl;
                                    }
                                else if(lognum == 4)
                                    {
                                        string mysql_Query = DeleteLog(userIDstr);
                                        const char* deleteReplyOfLog_query = DeleteReplyOfLog(userIDstr).c_str();
                                        mysql_query(&mysql_conn,deleteReplyOfLog_query);
                                        mysql_result = mysql_store_result(&mysql_conn);
                                        const char* deleteShareOfLog_query = DeleteShareOfLog(userIDstr).c_str();
                                        mysql_query(&mysql_conn,deleteShareOfLog_query);
                                        mysql_result = mysql_store_result(&mysql_conn);

                                        const  static char* deleteLog_query = mysql_Query.c_str();
                                        //cout<<deleteLog_query<<endl;
                                        mysql_query(&mysql_conn,deleteLog_query);
                                        mysql_result = mysql_store_result(&mysql_conn);
                                        if(mysql_result!=0) cout<<"\t right delete!"<<endl;
                                    }
                               else
                                    {
                                        system("cls");
                                        break;
                                    }
                                }

                           }
                       }
                }
            }
        else
            printf("Connection fails.\n");
    }
    else
    {
        printf("Initialization fails.\n");
        return -1;
    }

    mysql_close(&mysql_conn);
    return 0;
}

void  showHome()
{
    printf("\t*****************************************\t\n\n");
    printf("\t*\t欢迎进入社交网络平台\t\t*\n\n");
    printf("\t*****************************************\t\n");
    printf("\n\n\n");
}

void LoginOrRegist()
{
    printf("\t*****************************************\t\n");
    printf("\t输入1 -> 登录 \t\t 输入0 -> 注册\t\n");
    cout<<"\t输入(1/0)：";
    scanf("\t%d",&login);
     printf("\n\n\n");
}

string Regist()
{
     printf("\t*******************注册******************\t\n");
     string query;
     string mainEmail,password,name,address,birthday,sex;
     printf("\t填写注册邮箱:");
     cin>>mainEmail;
     mainEmail = mainEmail+"','";
     printf("\t输入密码：");
     cin>>password;
     password = password+"','";
     printf("\t以下内容可选择为空（为空输入-1）\n");
     printf("\t输入姓名：");
     cin>>name;
     if(name == "-1")
        {
            name = "NULL";
            name = name+",";
       }
     else{
         name = name+"',";
     }
     printf("\t输入性别（男输入1，女输入0）：");
     cin>>sex;
     if(sex == "-1")
        {
            sex = "1,'";//默认为男
        }
    else{
        sex = sex +",'";
    }
     printf("\t输入地址：");
     cin>>address;
     if(address == "-1")
     {
         address = "NULL";
         address = address+"')";
     }
     else{
        address = address+"');";
     }
     printf("\t输入出生日期(例：2001.1.1)：");
     cin>>birthday;
     if(birthday == "-1")
        {
            birthday = "NULL";
            birthday = birthday + ",'";
        }
     else{
        birthday = birthday+"','";
     }
     query = "Insert into BasicInformation(mainEmail,password,name,sex,\
        birthday,address) values('";
    query = query +mainEmail+password+name+sex+birthday+address;
     printf("\n\n\n");
    return query;
}

string LoginIn()
{
     system("cls");
     printf("\t*******************登录******************\t\n");
     string query,mainEmail,password;
     printf("\t输入注册邮箱：");
     cin>>mainEmail;
     printf("\t输入密码：");
     cin>>password;
     query = "Select userID,mainEmail from BasicInformation where mainEmail = '" + mainEmail + \
            "' and password ='" + password +"';";
     printf("\n\n\n");
     return query;
}

int HomeView()
{
     //system("cls");
     int num;
     printf("\n\t***************************首页**************************\t\n");
     printf("\t1 完善个人信息  2 群组管理  3 好友管理  4 消息管理  5 日志管理\n");
     printf("\t输入对应编号进入对应功能页面:");
     cin>>num;
     while((num<1)||(num>5))
     {
         printf("\t编号输入错误，请重新输入：");
         cin>>num;
     }
     printf("\n\n\n");
     return num;
}
//**********************************************************
int PerfectDate()
{
    int num;
    printf("\n\t**********************完善个人信息*********************\t\n");
    printf("\t1 完善基本信息\t 2 完善个人经历\t 3 返回主页\n");
    printf("\t输入对应编号进入对应功能页面:");
     cin>>num;
     while((num<1)||(num>3))
     {
         printf("\t编号输入错误，请重新输入：");
         cin>>num;
     }
     printf("\n\n\n");
     return num;
}

int PerfectPersonInfo()
{
    int num;
    printf("\n\t**********************完善基本信息*********************\t\n");
    printf("\t1 完善基本信息\t 2 添加更多邮箱\t 3 返回主页\n");
    printf("\t输入对应编号进入对应功能页面:");
     cin>>num;
     while((num<1)||(num>3))
     {
         printf("\t编号输入错误，请重新输入：");
         cin>>num;
     }
     printf("\n\n\n");
     return num;
}

string UpdatePersonInfo(string userIDstr)
{
    printf("\n\t***********************修改信息**********************\t\n");
     string query,password,name,sex,address,birthday;
     query = "update BasicInformation SET password = '";
     printf("\t输入新密码：");
     cin>>password;
     query = query + password +"',name = '";
     printf("\t输入姓名：");
     cin>>name;
     query = query + name +"',sex =";
     printf("\t输入性别（男输入1，女输入0）：");
     cin>>sex;
     query = query + sex + ",address = '";
     printf("\t输入地址：");
     cin>>address;
     query = query + address +"',birthday = '";
     printf("\t输入出生日期(例：2001.1.1)：");
     cin>>birthday;
     query = query + birthday +"' where UserID = " + userIDstr +";";
     printf("\n\n\n");
    return query;
}

string PerfectEmail(string userIDstr)
{
    printf("\n\t***********************添加邮箱**********************\t\n");
    string email,query;
    printf("\t输入邮箱：");
    cin>>email;
    query = "Insert into useremail values("+userIDstr+",'"+email+"');";
     printf("\n\n\n");
    return query;
}

int PerfectExperience()
{
    int num;
    printf("\n\t**********************完善个人经历*********************\t\n");
    printf("\t1 添加教育经历  2 修改教育经历  3 添加工作经历  4 修改工作经历 5 返回主页\n");
    printf("\t输入对应编号进入对应功能页面:");
     cin>>num;
     while((num<1)||(num>5))
     {
         printf("\t编号输入错误，请重新输入：");
         cin>>num;
     }
      printf("\n\n\n");
     return num;
}

string PerfectEduExperience(string userIDstr)
{
    printf("\n\t**********************完善教育经历*********************\t\n");
    printf("\t以下内容可选择为空（为空输入-1）\n");
    string edulevel,BeginTime,EndTime,UnivName,degree,query;
    query = "Insert into EduExperience values("+userIDstr+",'";
    printf("\t输入教育等级：");
    cin>>edulevel;
    query = query + edulevel +"','";
    printf("\t输入开始时间（例2001.1.1）：");
    cin>>BeginTime;
    query = query + BeginTime + "','";
    printf("\t输入结束时间（例2001.1.1）：");
    cin>>EndTime;
    query = query + EndTime + "','";
     printf("\t输入学校名称：");
    cin>>UnivName;
    query = query + UnivName + "','";
     printf("\t输入学位：");
    cin>>degree;
    query = query + degree + "');";
     printf("\n\n\n");
    return query;

}

string ChangeEduExperience(string userIDstr)
{
    printf("\n\t**********************修改教育经历*********************\t\n");
    printf("\t以下内容可选择为空（为空输入-1）\n");
    string edulevel,BeginTime,EndTime,UnivName,degree,query;
    query = "Update  EduExperience set edulevel = '";
    printf("\t输入教育等级：");
    cin>>edulevel;
    query = query + edulevel +"',BeginTime = '";
    printf("\t输入开始时间（例2001.1.1）：");
    cin>>BeginTime;
    query = query + BeginTime + "',EndTime = '";
    printf("\t输入结束时间（例2001.1.1）：");
    cin>>EndTime;
    query = query + EndTime + "',UnivName = '";
     printf("\t输入学校名称：");
    cin>>UnivName;
    query = query + UnivName + "',degree = '";
     printf("\t输入学位：");
    cin>>degree;
    query = query + degree + "' where UserID ="+userIDstr+";";
     printf("\n\n\n");
    return query;
}

string PerfectWorkExperience(string userIDstr)
{
    printf("\n\t**********************完善工作经历*********************\t\n");
    printf("\t以下内容可选择为空（为空输入-1）\n");
    string query,workCompany,position,BeginTime,EndTime;
    query = "Insert into workexperience values("+userIDstr + ",'";
    printf("\t输入工作单位：");
    cin>>workCompany;
    query = query + workCompany +"','";
    printf("\t输入职位：");
    cin>>position;
    query = query + position +"','";
    printf("\t输入开始时间：");
    cin>>BeginTime;
    query = query + BeginTime +"','";
    printf("\t输入结束时间：");
    cin>>EndTime;
    query = query + EndTime +"');";
     printf("\n\n\n");
    return query;
}

string ChangeWorkExperience(string userIDstr)
{
    printf("\n\t**********************修改工作经历*********************\t\n");
    printf("\t以下内容可选择为空（为空输入-1）\n");
    string query,workCompany,position,BeginTime,EndTime;
    query = "update workexperience set workCompany = '";
    printf("\t输入工作单位：");
    cin>>workCompany;
    query = query + workCompany +"',position = '";
    printf("\t输入职位：");
    cin>>position;
    query = query + position +"',BeginTime ='";
    printf("\t输入开始时间：");
    cin>>BeginTime;
    query = query + BeginTime +"',EndTime='";
    printf("\t输入结束时间：");
    cin>>EndTime;
    query = query + EndTime +"' where UserID = "+userIDstr+";";
     printf("\n\n\n");
    return query;
}
//************************************************************
int HandleGroup()
{
    int num;
    printf("\n\t************************群组管理***********************\t\n");
    printf("\t 1 创建群组  2 修改群组  3 删除群组  4 查看群组内好友 5 返回首页\n");
    printf("\t输入对应编号进入对应功能页面:");
     cin>>num;
     while((num<1)||(num>5))
     {
         printf("\t编号输入错误，请重新输入：");
         cin>>num;
     }
     printf("\n\n\n");
     return num;
}

string CreateGroup(string userIDstr)
{
     printf("\n\t************************创建分组***********************\t\n");
     string query,GroupName;
     query = "Insert into FriendGroup(UserID,GroupName) values(" + userIDstr + ",'";
     printf("\t输入分组名称：");
     cin>>GroupName;
     query = query + GroupName +"');";
     printf("\n\n\n");
     return query;
}

string ChangeGroup(string userIDstr)
{
    printf("\n\t************************修改分组***********************\t\n");
    string query,Oldname,NewName;
    query = "Update FriendGroup set GroupName = '";
    printf("\t输入原分组名称:");
    cin>>Oldname;
    printf("\t输入其新的名称:");
    cin>>NewName;
    query = query + NewName +"' where UserID = " +userIDstr +" and GroupName = '"+Oldname+"';";
     printf("\n\n\n");
    return query;
}

string DeleteGroup(string userIDstr)
{
    printf("\n\t************************删除分组***********************\t\n");
    string query,GroupName;
    printf("\t输入要删除分组名称：");
    cin>>GroupName;
    query = "Delete from FriendGroup where UserID = "+userIDstr+" and GroupName = '"+GroupName+"';";
     printf("\n\n\n");
    return query;
}
string ShowFriendInGroup(string userIDstr)
{
    printf("\n\t************************组内好友***********************\t\n");
    string query,groupName;
    printf("\t输入查看好友分组:");
    cin>>groupName;
    query = "select groupname,remark,name,mainEmail from GoodFriend,BasicInformation where GoodFriend.UserID = " + userIDstr +" and groupname = '"+groupName+"' and GoodFriend.FriendID = BasicInformation.UserID;";
    return query;
}
//*****************************************************************

int ManageGdFriend()
{
   int num;
    printf("\n\t************************好友管理***********************\t\n");
    printf("\t 1 查找好友  2 添加好友  3 删除好友  4 组中添加好友  5 返回首页\n");
    printf("\t输入对应编号进入对应功能页面:");
     cin>>num;
     while((num<1)||(num>5))
     {
         printf("\t编号输入错误，请重新输入：");
         cin>>num;
     }
      printf("\n\n\n");
     return num;
}

string SearchFriend()
{
     printf("\n\t************************好友查找***********************\t\n");
     string query,FriendEmail;
     query = "Select name,mainEmail,sex,birthday,address from BasicInformation where mainEmail = '";
     printf("\t输入邮箱查找:");
     cin>>FriendEmail;
     query = query +FriendEmail+"';";
      printf("\n\n\n");
     return query;
}

string AddNewFriend(string userIDstr)
{
    printf("\n\t************************添加好友***********************\t\n");
    string query,FriendEmail,remark;
    query = "Insert into GoodFriend(UserID,FriendID,remark) values("+userIDstr+",(select userID from BasicInformation where mainEmail = '";
    printf("\t输入好友邮箱:");
    cin>>FriendEmail;
    Global_friendEmail = FriendEmail;  //存入全局变量，用于互相添加
    query = query +FriendEmail +"'),'";
    printf("\t输入备注：");
    cin>>remark;
    query = query +remark + "');";
     printf("\n\n\n");
    return query;
}
//对方好友列表中添加好友
string AddNewFriendMutual(string userIDstr)
{
    string query,FriendEmail,remark;
    query = "Insert into GoodFriend(UserID,FriendID) values((select userID from BasicInformation where mainEmail = '" + Global_friendEmail+"')," + userIDstr + ");";
    return query;
}
string DeleteFriend(string userIDstr)
{
    printf("\n\t************************删除好友***********************\t\n");
    string query,friendRemark;
    printf("\t输入好友备注:");
    cin>>friendRemark;
    Global_deleteRemark = friendRemark;
    query = "Delete from GoodFriend where UserID = " + userIDstr +" and remark = '"+friendRemark+"';";
     printf("\n\n\n");
    return query;
}
//对方好友列表中删除
string DeleteFriendMutual(string userIDstr)
{
    string query;
    query = "delete from goodfriend where FriendID = "+userIDstr + " and UserID in (select friendID from goodfriend where remark = '" + Global_deleteRemark + "');";
    return query;
}
string AddFriendToGroup(string userIDstr)
{
    printf("\n\t************************添加好友至分组***********************\t\n");
    string query,friendRemark,GroupName;
    printf("\t输入好友备注：");
    cin>>friendRemark;
    printf("\t输入分组名称:");
    cin>>GroupName;
    query = "Update goodfriend set groupName = '"+GroupName+"' where UserID = " +userIDstr +" and remark = '"+friendRemark+"';";
    return query;
}
//*****************************************************************
int ManageNews()
{
    int num;
    printf("\n\t************************消息管理***********************\t\n");
    printf("\t 1 查看消息 \t 2发送消息 \t 3 返回首页\n");
    printf("\t输入对应编号进入对应功能页面:");
     cin>>num;
     while((num<1)||(num>3))
     {
         printf("\t编号输入错误，请重新输入：");
         cin>>num;
     }
     printf("\n\n\n");
      return num;
}

string ShowNews(string userIDstr)
{
    printf("\n\t************************查看消息***********************\t\n");
    string query;
    query = "select * from News where SendpersonID = " + userIDstr +" or RecvpersonID = " +userIDstr+";";
     printf("\n\n\n");
     return query;
}

string SendNews(string userIDstr)
{
    printf("\n\t************************发送消息***********************\t\n");
    string query,RecvPerson,NewsContent;
    query = "Insert into News values('";
    printf("\t输入接收人邮箱:");
    cin>>RecvPerson;
    printf("\t输入发送内容：");
    cin>>NewsContent;
   // char * newContent = new char[maxsize];
    //gets(NewsContent);
    //NewsContent = newContent;
    query = query + NewsContent +"',CURTime()," + userIDstr+",";
    query = query+ "(select UserID from BasicInformation where mainEmail ='"+RecvPerson+"'));";
     printf("\n\n\n");
     return query;
}

//*****************************************************************
int ManageLog()
{
    system("cls");
    int num;
    printf("\n\t************************日志管理***********************\t\n");
    printf("\t 1 查看日志  2发表日志  3 修改日志  4 删除日志 5 返回首页 \n");
    printf("\t输入对应编号进入对应功能页面:");
    cin>>num;
     while((num<1)||(num>5))
     {
         printf("\t编号输入错误，请重新输入：");
         cin>>num;
     }
     printf("\n\n\n");
     return num;
}

string ShowLog(string userIDstr)
{
     printf("\n\t************************查看日志***********************\t\n");
     string query;
     query = "Select LogID,LogContent,ChangeTime,CanReply,CanPublic from Log where UserID = "+userIDstr+";";
      printf("\n\n\n");
      return query;
}

string PublicLog(string userIDstr)
{
    printf("\n\t************************发表日志***********************\t\n");
    string query,LogContent,CanReply,CanPublic,ChangeTime;
    query = "Insert into Log(UserID,LogContent,ChangeTime,CanReply,CanPublic) values(" + userIDstr + ",'";
    printf("\t输入日志内容：");
    cin>>LogContent;
    query = query +LogContent+"',CURTime(),";
    printf("\t是否可回复（是1/否0）：");
    cin>>CanReply;
     query = query +CanReply+",";
    printf("\t是否公开（是1/否0）：");
    cin>>CanPublic;
     query = query +CanPublic+");";
    printf("\n\n\n");
     return query;
}

string ChangeLog(string userIDstr)
{
    printf("\n\t************************修改日志***********************\t\n");
    string query,logID,LogContent,ChangeTime,CanReply,CanPublic;
    query = "update Log set LogContent = '";
    printf("\t输入修改日志的ID：");
    cin>>logID;
    printf("\t输入日志内容：");
    cin>>LogContent;
    query = query + LogContent+"',ChangeTime = CURTime(),CanPublic=";
    printf("\t是否公开（是1/否0）：");
    cin>>CanPublic;
    query = query +CanPublic + ",CanReply = ";
    printf("\t是否可回复（是1/否0）：");
    cin>>CanReply;
    query = query + CanReply +" where UserID = "+userIDstr+" and LogID = "+logID +";";
     printf("\n\n\n");
    return query;

}

string DeleteLog(string userIDstr)
{
    printf("\n\t*******************删除日志******************\t\n");
    string query,logID;
    printf("\t输入要删除日志的ID：");
    cin>>logID;
    Global_logID = logID;//保存全局变量，删除日志对应的回复
    query = "Delete from Log where UserID = "+userIDstr+" and logID = "+ logID + ";";
     printf("\n\n\n");
     return query;
}

string DeleteReplyOfLog(string userIDstr)
{
    string query;
    query = "delete from Reply where logID = " + Global_logID +" and ReplytopersonID = "+ userIDstr +";";
    return query;
}
string DeleteShareOfLog(string userIDstr)
{
    string query;
    query = "delete from share where logID = " +Global_logID +" and UserID = "+ userIDstr +";";
    return query;
}
//***********************************************************
int ManageReplyAndSharelog()
{
     int num;
    printf("\n\t************************日志评论与分享***********************\t\n");
    printf("\t 1 评论日志 2 查看评论 3 分享日志 4 查看分享日志  5 返回首页 \n");
    printf("\t输入对应编号进入对应功能页面:");
    cin>>num;
     while((num<1)||(num>5))
     {
         printf("\t编号输入错误，请重新输入：");
         cin>>num;
     }
     printf("\n\n\n");
     return num;
}
//添加评论
string AddComment(string userIDstr)
{
    printf("\n\t************************评论日志***********************\t\n");
    string query,replycontent,logID,replyToEmail;
    printf("\t输入被回复人邮箱：");
    cin>>replyToEmail;
    printf("\t输入回复日志ID：");
    cin>>logID;
    printf("\t输入回复内容：");
    cin>>replycontent;
    query = "insert into Reply(ReplytopersonID,BeRepliedID,LogID,replytime,replyContent) values("+userIDstr+",(select UserID from basicInformation where mainEmail = '" + replyToEmail+"'),"+logID+",CURTime(),'"+replycontent+"');";
    return query;
}

string ShowComment(string userIDstr)
{
     printf("\n\t************************查看评论***********************\t\n");
     string query,logID;
     printf("\t输入查看评论的日志的ID：");
     cin>>logID;
     query = "select LogContent,Replytime,ReplyContent from Log,Reply where Reply.LogID = log.LogID and reply.LogID = "+ logID+";";
     return query;
}


string AddSharelog(string userIDstr)
{
    printf("\n\t************************分享日志***********************\t\n");
    string query,logID,CommentContent;
    printf("\t输入分享日志的ID：");
    cin>>logID;
    printf("\t输入分享内容:");
    cin>>CommentContent;
    query = "insert into share(UserID,ShareTime,commentTime,commentContent,logID) values("+userIDstr+",CURTime(),CURTime(),'"+CommentContent+ "',"+logID+ ");";
    return query;
}
string showSharLog(string userIDstr)
{
    printf("\n\t************************查看分享***********************\t\n");
    string query;
    query = "select logContent,ChangeTime,ShareTime,CommentContent from share,log where share.logID = Log.logID and share.UserID = " + userIDstr +";";
    return query;
}





