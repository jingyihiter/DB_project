#查询处理算法的实现
[查看代码入口](https://github.com/jingyihiter/DB_project/blob/master/Mysql_Project/dbtest4/test4/extmem-c/first.c)<br>
关系R具有两个属性A和B，其中A和B的属性值均为int型（4个字节），A的值域为[1, 40]，B的值域为[1, 1000]。<br>
关系S具有两个属性C和D，其中C和D的属性值均为int型（4个字节）。C的值域为[20, 60]，D的值域为[1, 1000]。<br>
>1）实现关系选择算法：基于ExtMem程序库，使用C实现关系选择算法，选出R.A=40或S.C=60的元组，并将结果存放在磁盘上。要求实现至少三种选择算法，包括线性搜索算法，二元搜索算法，和任意一种索引算法（使用B+/B-树有加分）。<br>
>2）实现关系投影算法：基于ExtMem程序库，使用C语言实现关系投影算法，对关系R上的A属性进行投影，并将结果存放在磁盘上。<br>
>3）实现连接操作算法：基于ExtMem程序库，使用C语言实现连接操作算法，对关系R和S计算R.A连接S.C，并将结果存放在磁盘上。要求实现三种连接操作算法：Nest-Loop- Join算法，Sort-Merge-Join算法，Hash-Join算法。<br>
>4）实现集合操作算法：包括并、交、差。<br>

