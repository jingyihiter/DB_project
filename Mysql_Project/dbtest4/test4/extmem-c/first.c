
#include <stdlib.h>
#include <stdio.h>
#include "extmem.h"
#include<time.h>
#define MAX 1000
typedef struct TempArray
 {
     int c;
     int d;
     int blk;
 }TempArray;
int temp_count=0,tempflag=0;
int Random(int low,int high);                            //生成随机数
void OutputData(int beginAddr,int n,unsigned int *blk,Buffer *buf,int flag);
void storeData(unsigned int * blk,Buffer *buf);          //存储数据
TempArray *loadData(unsigned int * blk,Buffer *buf,int len,int addr,int templen);  //读取数据

TempArray *sort(TempArray *temp,int len);
void Mpass(int len,int templen,TempArray *temp,TempArray *temp1);                                         //merge
TempArray * MergeSort(TempArray *temp,int templen);       //归并排序

void SelectRelationship(unsigned int * blk,Buffer *buf,TempArray *tempR,TempArray *tempS);   //选择关系
void BinarySearch(unsigned int * blk,Buffer *buf,TempArray *tempR,TempArray *tempS);
void IndexSearch(unsigned int * blk,Buffer *buf,TempArray *tempR,TempArray *tempS);

void MappingRelationship(unsigned int * blk,Buffer *buf);  //投影关系
unsigned int Merge(unsigned int left,int ln,unsigned int right,int rn,Buffer *buf,int addr);
unsigned int Exsort(unsigned int saddr,int n,Buffer *buf,int addr);     //归并排序

void ConnectRelationship(unsigned int * blk,Buffer *buf,TempArray *tempR,TempArray *tempS);   //连接关系
void Nst_Loop_Join(unsigned int * blk,Buffer *buf);
void Sort_Merge_Join(unsigned int * blk,Buffer *buf,TempArray *tempR,TempArray *tempS);
void Hash_Join(unsigned int *blk, Buffer *buf);

void CollectionRelationship(unsigned int * blk,Buffer *buf);  //集合操作
void CalculationIntersection(unsigned int *blk,Buffer *buf,TempArray *temp);    //计算R S的交集
void UnionOfRelation(unsigned int * blk,Buffer *buf,TempArray *temp);       //并集
void IntersectionOfRelation(unsigned int *blk,Buffer *buf,TempArray *temp); //交集
void DifferenceOfRelation(unsigned int *blk,Buffer *buf,TempArray *temp);   //差集

int main()
{
    srand((unsigned)time(NULL));
    Buffer buf; /* A buffer */
    //unsigned char *blk; /* A pointer to a block */
    unsigned int *blk;
    int i = 0;
    int sel;
    /* Initialize the buffer */
    if (!initBuffer(520, 64, &buf))
    {
        perror("Buffer Initialization Failed!\n");
        return -1;
    }
    //storeData(blk, &buf);
    TempArray *tempR = loadData(blk,&buf,16,0,112);
    TempArray *tempS = loadData(blk,&buf,32,20,224);
    tempR = sort(tempR,112);
    tempS = sort(tempS,224);
    while(1)
    {
        printf("\t***** 1 选择\t2 投影\t3 连接\t 4 集合操作 *****\n\n ");
        scanf("%d",&sel);
        switch (sel)
        {
        case 1:  //选择关系
            {
                SelectRelationship(blk,&buf,tempR,tempS);
                continue;
            }
        case 2: //投影关系
            {
                MappingRelationship(blk,&buf);
                continue;
            }
        case 3:  //连接关系
            {
                ConnectRelationship(blk,&buf,tempR,tempS);
               continue;
            }
        case 4: //集合操作
            {
                CollectionRelationship(blk,&buf);
               continue;
            }
        default:
            {
                printf("\t选择序号错误，重新输入!\n\n");
                break;
            }
        }
         //printf("# of IO's is %d\n", buf.numIO); /* Check the number of IO's */
    }
    printf("\n");
    printf("# of IO's is %d\n", buf.numIO); /* Check the number of IO's */
    system("pause");
    return 0;
}
/** \brief  生成随机数
 *  Random
 * \param int low
 * \param  int high
 * \return  int
 *
 */
int Random(int low,int high)  //随机数生成
{
    return rand()%(high-low)+low+1;
}
/** \brief  存储数据
 *     storeData
 * \param unsigned int *blk
 * \param  Buffer * buf
 * \return void
 *
 */
void storeData(unsigned int * blk,Buffer *buf) //存储数据
{
    unsigned int a,b,c,d;
    int Ri,Rj,Si,Sj;
    for(Ri=0;Ri<16;Ri++)
    {
        blk = getNewBlockInBuffer(buf);
        for(Rj=0;Rj<7;Rj++)
        {
            a = Random(1,40);
            b = Random(1,1000);
            *(blk+2*Rj) = a;
            *(blk+2*Rj+1) = b;
        }
        *(blk+2*Rj+1)=Ri+1;
        if(Ri == 15)
        {
            *(blk+2*Rj+1)=0;
        }
        //printf("R %d,%d\n",*blk,*(blk+1));
        if (writeBlockToDisk(blk, Ri, buf) != 0)
        {
            perror("Writing Block Failed!\n");
            return -1;
        }
        freeBlockInBuffer(blk,buf);
    }
    for(Si=0;Si<32;Si++)
    {
        blk = getNewBlockInBuffer(buf);
        for(Sj=0;Sj<7;Sj++)
        {
            c= Random(20,60);
            d = Random(1,1000);
            *(blk+2*Sj)=c;
            *(blk+2*Sj+1)=d;
        }
        *(blk+2*Sj+1) = Si+21; //存下一个的块号
        if(Si==31)
        {
            *(blk+2*Sj+1) = 0;
        }
        //printf("S %d,%d\n",*blk,*(blk+1));
        if (writeBlockToDisk(blk, Si+20, buf) != 0)
        {
            perror("Writing Block Failed!\n");
            return -1;
        }
        freeBlockInBuffer(blk,buf);
    }
}
/** \brief OutputData
 * 打印存储的数据
 * \param int beginAddr
 * \param int n
 * \param unsigned int *blk
 * \param Buffer *buf
 * \param int flag
 * \return void
 *
 */

void OutputData(int beginAddr,int n,unsigned int *blk,Buffer *buf,int flag)
{
    int i,j;
    for(i=beginAddr;i<beginAddr+n;i++)
    {
        blk = readBlockFromDisk(i,buf);
         if(flag==3)
         {
            for(j=0;j<15;j=j+3)
                {
                    printf("(%d, %d, %d) ",*(blk+j),*(blk+j+1),*(blk+j+2));
                }
                printf("\n");
         }
         if(flag==2)
         {
            for(j=0;j<7;j++)
            {
                printf("(%d ,%d) ",*(blk+2*j),*(blk+2*j+1));
            }
            printf("\n");
         }
        if(flag==1)
            {
                for(j=0;j<15;j++)
                {
                    printf("%d ",*(blk+j));
                }
                printf("\n");
            }
        freeBlockInBuffer(blk,buf);

    }
}
/** \brief 读取数据
 *   loadData
 * \param  unsigned int * blk
 * \param  Buffer * buf
 * \return TempArray *
 *
 */
TempArray * loadData(unsigned int * blk,Buffer *buf,int len,int addr,int templen)
{
    unsigned int a,b;
    TempArray *temp;
    temp = malloc(sizeof(TempArray)*templen);
    int i,j,temp_num=0;
    for(i=0;i<len;i++)
    {
        if((blk = readBlockFromDisk(addr+i,buf))==NULL)
        {
            perror("Reading Block Failed!\n");
            return;
        }
        for(j=0;j<7;j++)
        {
            a = *(blk+2*j);
            b = *(blk+2*j+1);
            //printf("R = %d,%d\n",a,b);
            temp[temp_num].c =  a;
            temp[temp_num].d = b;
            temp[temp_num].blk = addr+i;
            temp_num++;
        }
        freeBlockInBuffer(blk,buf);
    }
    return temp;
}


TempArray *sort(TempArray *temp,int len)
{
    int i,j;
    TempArray tempp;
    for(i=0;i<len;i++)
    {
        for(j=len-1;j>=i+1;j--)
        {
            if(temp[j].c < temp[j-1].c)
            {
                tempp = temp[j];
                temp[j] =temp[j-1];
                temp[j-1] = tempp;
            }
        }
    }
    return temp;
}
void Mmerge(int left,int mid,int right,TempArray *temp,TempArray *temp1)
{
    int i=left,j=mid+1,k=left;
    while(i<=mid&&j<=right)
    {
        temp1[k++]=temp[i].c <= temp[j].c ?temp[i++]:temp[j++];
    }
    while(i<=mid) temp1[k++]=temp[i++];
    while(j<=right) temp1[k++]=temp[j++];
}

void Mpass(int len,int templen,TempArray *temp,TempArray *temp1)
{
  int i=1,t;
  while(i<2*(templen-2*len+1))
  {
      Mmerge(i,i+len-1,i+2*len-1,temp,temp1);
      i = i+2*len;
  }
  if((i+len-1) < templen)
  {
      Mmerge(i,i+len-1,templen,temp,temp1);
  }
  else
  {
      for(t=i;t<=templen;t++)
      {
          temp1[t]=temp[t];
      }
  }
}
TempArray * MergeSort(TempArray *temp,int templen)
{
    int len=1;
    TempArray *temp1 = malloc(sizeof(TempArray)*templen);
    while(len < templen)
    {
        Mpass(len,templen,temp,temp1);
        len = 2*len;
        Mpass(len,templen,temp1,temp);
        len=len*2;
    }
    return temp1;
}
/** \brief BinarySearch
 * 二分搜索
 * \param
 * \param
 * \return void
 *
 */
int Binary(int num,TempArray *temp,int len)
{
   int left=0,right=len,mid;
   while(left <= right)
   {
       mid = (left+right)/2;
       if(temp[mid].c == num)
       {
           return mid;
       }
       if(temp[mid].c < num)
       {
          left = mid+1;
       }
       else
        right = mid-1;
   }
  return -1;
}
void BinarySearch(unsigned int * blk,Buffer *buf,TempArray *tempR,TempArray *tempS)
{
  int Rnum = Binary(40,tempR,112);
  int snum = Binary(60,tempS,224);
  int i,j,Ri=Rnum,Si=snum,num=300,t_count;
  TempArray *temp_ = malloc(sizeof(TempArray)*336);
  if(Rnum!=-1)
  {
      i=0;
      temp_[i]=tempR[Rnum];
      while((tempR[Rnum+1].c==40) && (Rnum <= 112)) //向上重复的
      {

          temp_[++i] = tempR[++Rnum];
      }
      while((tempR[Ri-1].c==40) && (Ri>=1)) //向下重复的
      {

          temp_[++i] = tempR[--Ri];
      }
  }
  if(snum!=-1)
  {
   temp_[++i] = tempS[snum];
   while(tempS[snum+1].c==60 && snum<=224)
   {

       temp_[++i] = tempS[++snum];
   }
   while(tempS[Si-1].c==60 && Si>=0)
   {
       temp_[++i] = tempS[--Si];
   }
   blk = getNewBlockInBuffer(buf);
   t_count=0;
   for(j=0;j<=i;j++)
   {
       printf("(%d, %d) \n",temp_[j].c,temp_[j].d);
       *(blk+2*t_count) = temp_[j].c;
       *(blk+2*t_count+1) = temp_[j].d;
       if(t_count == 7)
       {
           *(blk+2*t_count) =num+1;
           writeBlockToDisk(blk,num,buf);
           freeBlockInBuffer(blk,buf);
           num++;
           t_count = 0;
       }
       if(j==i&&t_count<7) //最后一个块不满
       {
           writeBlockToDisk(blk,num,buf);
           freeBlockInBuffer(blk,buf);
       }
   }
  }
  else
    {
        printf("没有要求的元组\n");
    }
}

void IndexSearch(unsigned int * blk,Buffer *buf,TempArray *tempR,TempArray *tempS)
{

}
/** \brief 选择关系
 * 线性搜索 二元搜索 索引算法
 * 结果存放磁盘
 * \param unsigned int * blk
 * \param Buffer *buf
 * \return void
 *
 */
void SelectRelationship(unsigned int * blk,Buffer *buf,TempArray *tempR,TempArray *tempS)
{
 printf("\t1 线性搜索   2 二元搜素   3 索引算法   -1 结束\n");
 int sel=0;
 int i,j,a,b,c,d;
 int line_count=60;  //60 开始存储
 unsigned int *disk_blk;
 while(sel!=-1)
 {
     scanf("%d",&sel);
     switch (sel)
     {
     case 1: //线性搜索
         {
             for(i=0;i<16;i++)  //查R
             {
                 blk = readBlockFromDisk(i,buf);
                 for(j=0;j<7;j++)
                 {
                     if(*(blk+2*j)==40)
                     {
                         a = 40;
                         b = *(blk+2*j+1);
                         printf("a = %d, b = %d\n",a,b);
                         disk_blk = getNewBlockInBuffer(buf);
                         *disk_blk = a;
                         *(disk_blk+1)=b;
                         writeBlockToDisk(disk_blk,line_count,buf);
                         line_count++;
                     }
                 }
                 freeBlockInBuffer(blk,buf);
             }
             line_count+=10;   //中间间隔10个blk，区分 R.A=40 和S.C=60的元组
             for(i=0;i<32;i++)
             {
                 blk = readBlockFromDisk(i+20,buf);
                 for(j=0;j<7;j++)
                 {
                     if(*(blk+2*j)==40)
                     {
                         c = 40;
                         d = *(blk+2*j+1);
                         printf("c = %d, d = %d\n",c,d);
                          disk_blk = getNewBlockInBuffer(buf);
                         *disk_blk = c;
                         *(disk_blk+1)=d;
                         writeBlockToDisk(disk_blk,line_count,buf);
                         line_count++;
                     }
                 }
                 freeBlockInBuffer(blk,buf);
             }
             printf("\n");
             break;
         }
     case 2: //二元搜索
         {
             BinarySearch(blk,buf,tempR,tempS);
             break;
         }
     case 3: //索引算法
         {
             break;
         }
     default:
         {
              break;
         }
     }
 }

}

unsigned int Merge(unsigned int left,int ln,unsigned int right,int rn,Buffer *buf,int addr)
{
    int l=0,r=0;//计数
    int offset=0,i;
    unsigned int tmpaddr=left+addr;//结果存入的地址
    unsigned int *blk1,*blk2;
    while(l<ln||r<rn)
    {
        if(l==ln)//左边结束
            *blk1=MAX;
        else
            blk1=(int *)readBlockFromDisk(left+l,buf);
        if(r==rn)
             *blk2=MAX;//右边结束
        else
            blk2=(int *)readBlockFromDisk(right+r,buf);
        if(*blk1<*blk2)
        {
            writeBlockToDisk(blk1,tmpaddr+offset,buf);
            l++;//左边指针向后
            offset++;//写入的地址向后移动
        }
        else
        {
            writeBlockToDisk(blk2,tmpaddr+offset,buf);
            r++;
            offset++;
        }
        freeBlockInBuffer(blk1,buf);
        freeBlockInBuffer(blk2,buf);
    }
    for(i=0;i<offset;i++)//写回原来的位置
    {
        blk1=(int*)readBlockFromDisk(tmpaddr+i,buf);
        writeBlockToDisk(blk1,left+i,buf);
        freeBlockInBuffer(blk1,buf);
    }
    return left;
}

unsigned int Exsort(unsigned int saddr,int n,Buffer *buf,int addr)
{
    unsigned int left,right;
    if(n==1)   ///complete sorting
        return saddr;
    left=Exsort(saddr,n/2,buf,addr);
    right=Exsort(saddr+n/2,n-n/2,buf,addr);
    return Merge(left,n/2,right,n-n/2,buf,addr);
}
/** \brief 投影关系
 * 实现关系投影，并存储在磁盘上
 * \param unsigned int * blk
 * \param Buffer *buf
 * \return void
 *
 */
void MappingRelationship(unsigned int * blk,Buffer *buf)  //对R.A投影
{
 printf("\t 投影关系   \n");
 int ri,rj,a,basic=200,num=0,counta=0,count=0;
 unsigned int *disk_blk,tmp;
 printf("\t排序前 R.A :\n");
 for(ri=0;ri<16;ri++)
    {
        if((blk = readBlockFromDisk(ri,buf))==NULL)
        {
            perror("Reading Block Failed!\n");
            return;
        }
        for(rj=0;rj<7;rj++)
        {
            a = *(blk+2*rj);
            printf("%d ",a);
            disk_blk = getNewBlockInBuffer(buf);
            *disk_blk = a;
            writeBlockToDisk(disk_blk,basic+num,buf); //200-311.blk
            num++;
            freeBlockInBuffer(disk_blk,buf);
        }
        freeBlockInBuffer(blk,buf);
    }
    printf("\n");
    printf("\t排序后 R.A:\n");
    basic = Exsort(basic,num,buf,500);
    //printf("%d\n",basic);
    for(ri=0;ri<num;ri++)
    {
        blk = readBlockFromDisk(basic+ri,buf);
        printf("%d ",*blk);
        freeBlockInBuffer(blk,buf);
    }
    printf("\n\t去重后 R.A :\n");
    blk=(int*)readBlockFromDisk(basic,buf);
    disk_blk = getNewBlockInBuffer(buf); //结果存在 350-内 R.A
    tmp=*blk;
    *(disk_blk+count) = tmp;
    //writeBlockToDisk(disk_blk,basic+150+counta,buf);
    printf("%d ",tmp);
    for(ri=1; ri<num; ri++)
    {
        while(*blk==tmp)
        {
            freeBlockInBuffer(blk,buf);
            ri++;
            if(ri<num)
                blk=(int*)readBlockFromDisk(basic+ri,buf);
            else
            {
                goto END;
            }
        }
        //disk_blk = getNewBlockInBuffer(buf); //结果存在 350-390内
        tmp=*blk;
        count++;
        *(disk_blk+count) = tmp;
        if(ri==num-1)
            {
                 writeBlockToDisk(disk_blk,basic+150+counta,buf);
                 freeBlockInBuffer(disk_blk,buf);
            }
        else
        {
            if(count == 15)
            {
                 *(disk_blk+count+1) = basic+150+counta+1; //存下一个块号
                 writeBlockToDisk(disk_blk,basic+150+counta,buf);
                 freeBlockInBuffer(disk_blk,buf);
                 count = -1;
                 counta++;
            }
        }
        printf("%d ",tmp);
        freeBlockInBuffer(blk,buf);
    }
END:    printf("\n\n");
}
/** \brief Nst_Loop_Join
 *
 * \param unsigned int * blk
 * \param Buffer *buf
 * \return void
 *
 */

void Nst_Loop_Join(unsigned int * blk,Buffer *buf)
{
 int ri,rj,si,sj,num=1000,blk_count=0,count=0;
 int a,b,c,d;
 unsigned int *desk_blk,*wr_blk;
 for(ri=0;ri<16;ri++)
 {
     blk = readBlockFromDisk(ri,buf);  //R 每个block
     for(rj=0;rj<7;rj++)
     {
         a = *(blk+2*rj);
         for(si=0;si<32;si++)
         {
             desk_blk = readBlockFromDisk(si+20,buf);//s 每个block
             for(sj=0;sj<7;sj++)
             {
                 c = *(desk_blk+2*sj);
                 if(a == c)
                 {
                     b = *(blk+2*rj+1);
                     d = *(desk_blk+2*sj+1);
                     if(blk_count==0)
                      {
                        wr_blk = getNewBlockInBuffer(buf);
                      }
                     *(wr_blk+blk_count)=a;
                     *(wr_blk+blk_count+1)=b;
                     *(wr_blk+blk_count+2)=d;
                     count++;
                     blk_count+=3;
                     if(ri==15&&si==31)   //如果是最后一个块（不满），也进行存储
                     {
                          writeBlockToDisk(wr_blk,num,buf);
                           freeBlockInBuffer(wr_blk,buf);
                     }
                     else
                     {
                            if(blk_count == 15)   //如果块满，则存
                         {
                             *(wr_blk+blk_count) = num+1;  //最后四个字节 存储下一块的块号
                             writeBlockToDisk(wr_blk,num,buf);
                             num++;
                             freeBlockInBuffer(wr_blk,buf);
                             blk_count=0;
                         }
                     }
                  }

             }
             freeBlockInBuffer(desk_blk,buf);
         }
     }
     freeBlockInBuffer(blk,buf);
 }
 OutputData(1000,num-1000,blk,buf,3);
 printf("count = %d\n",count);
}

void Sort_Merge_Join(unsigned int * blk,Buffer *buf,TempArray *tempR,TempArray *tempS)
{
  int i=0,j=0,count=0,flag=0,num = 4000,w_count=0;
  blk = getNewBlockInBuffer(buf); //存结果
  while(i<112&&j<224)
  {
      if(tempR[i].c == tempS[j].c)
      {
        printf("(%d,%d,%d) ",tempR[i].c,tempR[i].d,tempS[j].d);
        *(blk+w_count)=tempR[i].c;
        *(blk+w_count+1) = tempR[i].d;
        *(blk+w_count+2) = tempS[j].d;
        w_count+=3;
        if(tempR[i-1].c < tempR[i].c || i==0) flag=i;
        count++;
        if(count%6==0) printf("\n");
        if(i==111) //边缘特殊处理，因找不到比i最后一个还大的,j不能自增
        {
            i=flag;
            j++;
        }
        else i++;
      }
      else if(tempR[i].c < tempS[j].c) i++;
      else
        {
            j++;
            if(tempS[j].c == tempS[j-1].c)  i = flag;
        }
      if(w_count==15) //够一块存储
      {
          *(blk+w_count) = num+1;
          writeBlockToDisk(blk,num,buf);
          freeBlockInBuffer(blk,buf);
          num++;
          w_count=0;
      }
  }
  if(w_count!=0&&w_count<15) //最后不满一块的时候，直接存储
  {
    writeBlockToDisk(blk,num,buf);
    freeBlockInBuffer(blk,buf);
  }
  printf("count = %d \n",count);
}

void Hash_Join(unsigned int *blk, Buffer *buf)
{

}
/** \brief 连接关系
 * Nst_Loop_Join算法 Sort_Merge_Join算法 Hash_Join算法
 *结果存放磁盘
 * \param unsigned int * blk
 * \param Buffer *buf
 * \return void
 *
 */
void ConnectRelationship(unsigned int * blk,Buffer *buf,TempArray *tempR,TempArray *tempS)
{
    printf("\t1 Nst_Loop_Join \t2 Sort_Merge_Join \t3 Hash_Join \t其他结束\n");
    int sel=0;
    while(sel!=-1)
    {
        scanf("%d",&sel);
        switch (sel)
        {
        case 1: //Nst_Loop_Join算法
            {
                Nst_Loop_Join(blk,buf);
                continue;
            }
        case 2: //Sort_Merge_Join算法
            {
                Sort_Merge_Join(blk,buf,tempR,tempS);
                continue;
            }
        case 3: //Hash_Join算法
            {
                continue;
            }
        default:
            break;
        }
    }
}
/** \brief CalculationIntersection
 * 集合的交集
 * \param unsigned int *blk
 * \param Buffer *buf
 * \return TempArray *temp
 *
 */

void CalculationIntersection(unsigned int *blk,Buffer *buf,TempArray *temp)
{
    int ri,rj,si,sj;
    int a,b,c,d;
    unsigned int *desk_blk;
    for(ri=0;ri<16;ri++)
    {
        blk = readBlockFromDisk(ri,buf);
        for(rj=0;rj<7;rj++)
        {
            a = *(blk+2*rj);
            b = *(blk+2*rj+1);
            for(si=0;si<32;si++)
            {
                desk_blk = readBlockFromDisk(si+20,buf);
                for(sj=0;sj<7;sj++)
                {
                    c = *(desk_blk+2*sj);
                    d = *(desk_blk+2*sj+1);
                    if(a == c && b == d) //重复元组
                     {
                         temp[temp_count].c=c;
                         temp[temp_count].d=d;
                         temp_count++;
                     }
                }
                 freeBlockInBuffer(desk_blk,buf);
            }

        }
         freeBlockInBuffer(blk,buf);
    }

}
/** \brief  UnionOfRelation
 * R S的并，去重
 * \param unsigned int * blk
 * \param Buffer *buf
 * \return void
 *
 */
 void UnionOfRelation(unsigned int * blk,Buffer *buf,TempArray *temp)
 {
     int ri,rj,si,sj,num=1500,blk_count=0,i,snum=1516,s_count=0;
     int a,b,c,d,flag=0,num_count=16;
     unsigned int *desk_blk,*wrA_blk,*wr_blk,*s_blk;
     for(si=0;si<32;si++)
     {
         desk_blk = readBlockFromDisk(si+20,buf);
         wr_blk = getNewBlockInBuffer(buf);
         for(sj=0;sj<7;sj++)
         {
             tempflag=0;
             c = *(desk_blk+2*sj);
             d = *(desk_blk+2*sj+1);
             for(i=0;i<temp_count;i++)
             {
                 if(c == temp[i].c && d == temp[i].d)
                 {
                     tempflag=1;
                     break;
                 }
             }
             if(tempflag==0) //不在重复列表中,才存数据
              {
                 *(wr_blk+2*s_count)=c;
                 *(wr_blk+2*s_count+1)=d;
                 s_count++;
              }
            if(s_count == 7)
             {
                 *(wr_blk+2*s_count+1) = snum+1;
                 writeBlockToDisk(wr_blk,snum,buf);
                 freeBlockInBuffer(wr_blk,buf);
                 s_count=0;
                 snum++;

             }
         }
          if(si==31 && sj == 6) //最后的，不满也要存储
             {
                writeBlockToDisk(wr_blk,snum,buf);
                freeBlockInBuffer(wr_blk,buf);
             }
         freeBlockInBuffer(desk_blk,buf);
     }
     if(temp_count==0)
     {
         printf("集合并中没有重复\n");
     }
     printf("集合并操作之后（去重过）,重复项有%d\n",temp_count);
     OutputData(0,16,blk,buf,2);
     OutputData(1516,snum-1516,blk,buf,2);
 }

 /** \brief IntersectionOfRelation
  * R S的交
  * \param unsigned int *blk
  * \param Buffer *buf
  * \return void
  *
  */

 void IntersectionOfRelation(unsigned int *blk,Buffer *buf,TempArray *temp)
 {
     int i,j,itemp=0,num=2000;
    if(temp_count!=0)
    {
        printf("R 和 S的交：\n");
        for(i=0;i<temp_count;i++)
        {
            blk = getNewBlockInBuffer(buf);
            for(j=0;j<7&&itemp<temp_count;j++)
            {
                *(blk+2*j)=temp[itemp].c;
                *(blk+2*j+1)=temp[itemp].d;
                printf("(%d, %d) ",temp[itemp].c,temp[itemp].d);
                itemp++;
            }
            printf("\n");
            *(blk+2*j+1) = num+1;
            writeBlockToDisk(blk,num,buf);
            num++;
            freeBlockInBuffer(blk,buf);
        }
        //OutputData(2000,num-2000,blk,buf,2);
    }
    else
    {
        printf("R S的交为空\n");
    }

 }
/** \brief DifferenceOfRelation
 *  R和S的差集
 * \param unsigned int *blk
 * \param Buffer *buf
 * \param TempArray *temp
 * \return void
 *
 */
 void DifferenceOfRelation(unsigned int *blk,Buffer *buf,TempArray *temp)
 {
  printf("\t 1 R-S  \t 2 S-R\n");
  int sel,ri,rj,si,sj,a,b,c,d,i,flag=0,num=0,blk_num=2500,blk_num1=3000;
  unsigned int *wr_blk;
  scanf("%d",&sel);
  if(sel==1)
  {
      printf("R-S的差：\n");
      for(ri=0;ri<16;ri++)
      {
       blk = readBlockFromDisk(ri,buf);
       wr_blk = getNewBlockInBuffer(buf);
       for(rj=0;rj<7;rj++)
       {
           flag=0;
           a = *(blk+2*rj);
           b = *(blk+2*rj+1);
           for(i=0;i<temp_count;i++)
           {
               if(a == temp[i].c && b == temp[i].d)
               {
                   flag=1;
                   break;
               }
           }
           if(flag==0)
           {
               *(wr_blk+2*num) = a;
               *(wr_blk+2*num+1) = b;
               printf("(%d, %d) ",a,b);
               num++;
           }
           if(ri==15&&rj==6)  //最后一个块不满的时候，存储
           {
                printf("\n");
               *(wr_blk+2*num+1) = 0;
               writeBlockToDisk(wr_blk,blk_num,buf);
               freeBlockInBuffer(wr_blk,buf);
           }
       }
        printf("\n");
       if(num==7)
       {
           *(wr_blk+2*num+1) = blk_num+1;
           writeBlockToDisk(wr_blk,blk_num,buf);
           blk_num++;
           num = 0;
           freeBlockInBuffer(wr_blk,buf);
       }
       freeBlockInBuffer(blk,buf);
      }
      //OutputData(2500,blk_num-2500,blk,buf,2);
  }
  else if(sel==2)
  {
      printf("S-R的差：\n");
    for(si=0;si<32;si++)
      {
       blk = readBlockFromDisk(si+20,buf);
       wr_blk = getNewBlockInBuffer(buf);
       for(sj=0;sj<7;sj++)
       {
           flag=0;
           c = *(blk+2*sj);
           d = *(blk+2*sj+1);
           for(i=0;i<temp_count;i++)
           {
               if(c == temp[i].c && d == temp[i].d)
               {
                   flag=1;
                   break;
               }
           }
           if(flag==0)
           {
               *(wr_blk+2*num) = c;
               *(wr_blk+2*num+1) = d;
               printf("(%d, %d) ",c,d);
               num++;
           }
           if(si==31&&sj==6)  //最后一个块不满的时候，存储
           {
                printf("\n");
               *(wr_blk+2*num+1) = 0;
               writeBlockToDisk(wr_blk,blk_num1,buf);
               freeBlockInBuffer(wr_blk,buf);
           }
       }
        printf("\n");
       if(num==7)
       {
           *(wr_blk+2*num+1) = blk_num1+1;
           writeBlockToDisk(wr_blk,blk_num1,buf);
           blk_num1++;
           num = 0;
           freeBlockInBuffer(wr_blk,buf);
       }
       freeBlockInBuffer(blk,buf);
      }
  }
  else
  {
    printf("输入错误\n");
  }
 }
/** \brief 集合操作
 * 并、交、差
 * \param unsigned int * blk
 * \param Buffer *buf
 * \return void
 *
 */
void CollectionRelationship(unsigned int * blk,Buffer *buf)
{
    printf("\t 1 并 \t 2 交 \t 3 差 \t 其他结束\n");
    struct TempArray *temp= malloc(sizeof(TempArray)*32);
    int sel=0;
    CalculationIntersection(blk,buf,temp);
    while(sel!=-1)
    {
        scanf("%d",&sel);
        switch (sel)
        {
        case 1: //并  去重
            {
                UnionOfRelation(blk,buf,temp);
                break;
            }
        case 2: //交
            {
                IntersectionOfRelation(blk,buf,temp);
                 break;;
            }
        case 3://差
            {
                DifferenceOfRelation(blk,buf,temp);
                 break;;
            }
        default:
            break;
        }
    }
}








