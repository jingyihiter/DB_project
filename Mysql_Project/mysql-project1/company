/*数据库实验一*/

create database company;

create Table employee(
	ENAME  char(15),
	ESSN   numeric(18,0),
	ADDRESS char(50),
	SALARY  numeric,
	SUPERSSN numeric(18),
	DNO char(20),
	primary key(ESSN),
	foreign key(DNO) references department(DNO)
	);

create Table department(
	DNAME char(20),
	DNO  char(20),
	MGRSSN numeric(18,0),
	MGRSTARDATE char(10),
	primary key(DNO)
	);

create Table PROJECT(
	PNAME char(50),
	PNO char(20),
	PLOCATION char(50),
	DNO char(20),
	primary key(PNO),
	foreign key(DNO) references department(DNO)
	);

create Table works_on(
	ESSN numeric(18,0),
	PNO char(20),
	HOURS int,
	primary key(ESSN,PNO),
	foreign key(ESSN) references employee(ESSN),
	foreign key(PNO) references PROJECT(PNO)
	);


---------------------------------
--  插入数据   --
-- department  --
Insert into department
	values("Research Department","d0",420683196012122323,"2010-11-11");

Insert into department
	values("事业部","d1",420683196012122344,"2007-12-21");

Insert into department
	values("产品部","d2",420683198012122355,"2013-12-22");

Insert into department
	values("人力资源部","d3",420683197012122366,"2011-12-21");

Insert into department
	values("后勤部","d4",420683199012122377,"2007-12-21");

-- project -- 

Insert into project
	values("SQL Project","P1","黑龙江省哈尔滨市哈工大科技园","d0");

Insert into project
	values("仿人机器人","P2","黑龙江省哈尔滨市哈工大科技园","d0");

Insert into project
	values("特定域个性化交互式问答技术研究","P3","黑龙江省哈尔滨市哈工大综合楼","d0");

Insert into project
	values("多任务一体化统计复述生成技术研究","P0","黑龙江省哈尔滨市哈工大","d0");

Insert into project
	values("基于实体关系的文本内容挖掘与集成技术平台","P4","黑龙江省哈尔滨市科技园","d0");

Insert into project
	values("基于XML的分层交互式中文处理开放平台","P5","哈尔滨市南岗区哈工大科技园","d0");

Insert into project
	values("汉语语义角色标注方法研究","P6","黑龙江省哈尔滨市哈工大科技园","d1");

Insert into project
	values("中文词义消歧技术研究","P7","黑龙江省哈尔滨市","d2");

Insert into project
	values("语料库授权","P8","黑龙江省哈尔滨市西大直街哈工大科技园","d3");

Insert into project
	values("多文档自动文摘","P9","黑龙江省哈尔滨市南岗区哈工大综合楼","d4");

--  employee --

Insert into employee
	values("杜克江",510521197401069617,"四川省 泸州市 泸县",5000,420683196012122323,"d0");

Insert into employee
	values("张红",510521197401069618,"四川省 泸州市 泸县",5200,420683196012122323,"d0");

Insert into employee
	values("张宏",510521197401061234,"四川省 泸州市 泸县",5400,420683196012122344,"d1");	

Insert into employee
	values("紫博宏",451423200905305288,"百色市 崇左市 龙州县",5700,420683196012122344,"d1");

Insert into employee
	values("费韩宏",620103196909113216,"甘肃省 兰州市 七里河区",2000,420683196012122344,"d1");

Insert into employee
	values("庾若涵",331124199012300671,"台州市 丽水市 松阳县",12000,420683196012122323,"d0");

Insert into employee
	values("张三",331124199012300687,"台州市 丽水市 松阳县",20000,420683196012122323,"d0");

Insert into employee
	values("张四",331124199012300688,"台州市 丽水市 松阳县",30000,420683196012122323,"d0");

Insert into employee
	values("张五",420683199504044515,"湖北省枣阳市刘升镇",9900,420683196012122323,"d0");

Insert into employee
	values("马六",420684199504044615,"湖北省襄阳市",10000,420683196012122323,"d0");
 -----------------------------------------------------------------------------------------  10个
Insert into employee
	values("王二",420684199504044677,"湖北省枣阳市",12000,331124199012300688,"d0");

 Insert into employee
 	values("王三",420684199504044678,"湖北省枣阳市",10100,331124199012300688,"d0");

 Insert into employee
 	values("王四",420683197312121001,"湖北省枣阳市",2000,331124199012300688,"d0");

 Insert into employee
 	values("王四五",420683197312121002,"湖北省枣阳市",2300,331124199012300688,"d0");


 Insert into employee
 	values("王五六",420683197312121003,"湖北省枣阳市",4000,331124199012300688,"d0");

Insert into employee
 	values("王六七",420683197312121004,"湖北省枣阳市",1000,331124199012300688,"d0");

Insert into employee
 	values("王七",420683197312121005,"湖北省枣阳市",800,331124199012300688,"d0");

Insert into employee
 	values("王和",420683197312121006,"湖北省枣阳市",8000,331124199012300688,"d0");

Insert into employee
 	values("王阿斗",420683197312121007,"湖北省枣阳市",1000,331124199012300688,"d0");

Insert into employee
 	values("王服",420683197312121008,"湖北省枣阳市",900,331124199012300688,"d0");
-------------------------------------------------------------------------------------------20个
Insert into employee
 	values("王付",420683197312121009,"湖北省枣阳市",2900,331124199012300688,"d0");

Insert into employee
 	values("吴瑞",510522197401061010,"四川省成都市",2800,420683196012122344,"d1");

Insert into employee
 	values("吴睿",510522197401061011,"四川省成都市",3100,420683196012122344,"d1");

Insert into employee
 	values("吴图",510522197401061012,"四川省成都市",4000,420683196012122344,"d1");

Insert into employee
 	values("吴分",510522197401061013,"四川省成都市",4100,420683196012122344,"d1");

Insert into employee
 	values("吴的",510522197401061014,"四川省成都市",2000,420683196012122344,"d1");

Insert into employee
 	values("吴付",510522197401061015,"四川省成都市",1800,420683196012122344,"d1");

Insert into employee
 	values("吴市",510522197401061016,"四川省成都市",1700,420683196012122344,"d1");

Insert into employee
 	values("吴上",510522197401061017,"四川省成都市",1600,420683196012122344,"d1");

Insert into employee
 	values("吴用",510522197401061018,"四川省成都市",1800,420683196012122344,"d1");

-------------------------------------------------------------------------------------------30
Insert into employee
 	values("杨端",510522197401061019,"黑龙江省哈尔滨市",1900,420683198012122355,"d2");

Insert into employee
 	values("杨都",510522197401061020,"黑龙江省哈尔滨市",2300,420683198012122355,"d2");

Insert into employee
 	values("杨等",510522197401061021,"黑龙江省哈尔滨市",2600,420683198012122355,"d2");

Insert into employee
 	values("杨放",510522197401061022,"黑龙江省哈尔滨市",2700,420683198012122355,"d2");

Insert into employee
 	values("杨和",510522197401061023,"黑龙江省哈尔滨市",2800,420683198012122355,"d2");
 	
Insert into employee
 	values("杨存",510522197401061024,"黑龙江省哈尔滨市",2900,420683198012122355,"d2");

Insert into employee
 	values("杨表",510522197401061025,"黑龙江省哈尔滨市",2000,420683198012122355,"d2");

Insert into employee
 	values("杨本",510522197401061026,"黑龙江省哈尔滨市",3000,420683198012122355,"d2");

Insert into employee
 	values("杨那",510522197401061027,"黑龙江省哈尔滨市",3200,420683198012122355,"d2");
 	
Insert into employee
 	values("杨面",510522197401061028,"黑龙江省哈尔滨市",1900,420683198012122355,"d2");

--------------------------------------------------------------------------------------------40

Insert into employee
 	values("向过",510522197401061029,"河南省郑州市",3800,510521197401069618,"d3");

Insert into employee
 	values("黄故",510522197401061030,"河南省郑州市",3700,510521197401069618,"d4");

Insert into employee
	values("于空",370786200605211033,"山东省 潍坊市 昌邑市",3500,510521197401069618,"d4");

Insert into employee
	values("于课",370786200605211035,"山东省 潍坊市 昌邑市",2900,510521197401069618,"d4");

Insert into employee
	values("于来",370786200605211036,"山东省 潍坊市 昌邑市",2000,510521197401069618,"d4");

Insert into employee
	values("于里",370786200605211037,"山东省 潍坊市 昌邑市",2000,510521197401069618,"d4");

Insert into employee
	values("于能",370786200605211038,"山东省 潍坊市 昌邑市",3000,510521197401069618,"d4");

Insert into employee
	values("于拍",370786200605211039,"山东省 潍坊市 昌邑市",2900,510521197401069618,"d4");

Insert into employee
	values("于咯",370786200605211041,"山东省 潍坊市 昌邑市",2000,510521197401069618,"d4");

Insert into employee
	values("于坡",370786200605211043,"山东省 潍坊市 昌邑市",2300,510521197401069618,"d4");

---------------------------------------------------------------------------------50
Insert into employee
	values("卫长青",350782198406072011,"福建省 南平市 武夷山市",4000,420683199012122377,"d3");
Insert into employee
	values("卫东方",350782198406072012,"福建省 南平市 武夷山市",4001,420683199012122377,"d3");
Insert into employee
	values("卫大方",350782198406072013,"福建省 南平市 武夷山市",3000,420683199012122377,"d4");
Insert into employee
	values("卫德德",350782198406072014,"福建省 南平市 武夷山市",2700,420683199012122377,"d4");
Insert into employee
	values("卫当初",350782198406072015,"福建省 南平市 武夷山市",2800,420683199012122377,"d4");

Insert into employee
	values("胡美丽",350782198406073011,"福建省 南平市 武夷山市",2800,420683197012122366,"d3");

Insert into employee
	values("胡快乐",350782198406073024,"福建省 南平市 武夷山市",2600,420683197012122366,"d3");

Insert into employee
	values("胡老虎",350782198406073034,"福建省 南平市 武夷山市",2650,420683197012122366,"d3");

Insert into employee
	values("胡共同",350782198406073021,"福建省 南平市 武夷山市",3050,420683197012122366,"d3");

Insert into employee
	values("胡提高",350782198406073014,"福建省 南平市 武夷山市",2890,420683197012122366,"d3");
-----------------------------------------------------------------------------------------------60

--插入 works_on

Insert into works_on
	values(510521197401069617,"P0",1);

Insert into works_on
	values(350782198406073011,"P0",1);

Insert into works_on
	values(350782198406072011,"P0",1);

Insert into works_on
	values(350782198406072012,"P0",1);
--------------------------满足至少参加了3个项目，且工作总时间不超过8小时-----------------------
Insert into works_on
	values(350782198406073014,"P0",2);

Insert into works_on
	values(350782198406073014,"P1",1);

Insert into works_on
	values(350782198406073014,"P2",1);

Insert into works_on
	values(350782198406073014,"P4",1);
---------------------------------------------end ---------------------------------------------

-----------------至少参加三个项目，工作时间超过8小时------------------------------------------
Insert into works_on
	values(510522197401061021,"P2",3);

Insert into works_on
	values(510522197401061021,"p5",4);

Insert into works_on
	values(510522197401061021,"p6",4);
-------------------------end------------------------------------------------------------------
Insert into works_on
	values(420683197312121008,"P8",1);

Insert into works_on
	values(420683197312121009,"p1",1);

Insert into works_on
	values(420683197312121009,"p2",3);
---------------------------------------------------------------------------------------------
	-------参与了全部项目的员工--------
Insert into works_on
	values(510522197401061011,"P0",1);
Insert into works_on
	values(510522197401061011,"P1",2);
Insert into works_on
	values(510522197401061011,"P2",1);
Insert into works_on
	values(510522197401061011,"P3",3);
Insert into works_on
	values(510522197401061011,"P4",1);
Insert into works_on
	values(510522197401061011,"P5",1);
Insert into works_on
	values(510522197401061011,"P6",4);
Insert into works_on
	values(510522197401061011,"P7",1);
Insert into works_on
	values(510522197401061011,"P8",1);
Insert into works_on
	values(510522197401061011,"P9",1);
	 -----------------end-------------------	

	 -------添加d4部门的works_on------
Insert into works_on
	values(370786200605211038,"p9",1);
	-------------end-----------------

-----------------------------实验内容-----------------------------

--1、参加了项目名为“SQL Project”的员工名字
	Select ENAME 
		from employee,works_on 
		where employee.ESSN = works_on.ESSN and works_on.PNO 
		in
		(Select PNO from project where PNAME = "SQL Project");
/*
+--------+
| ENAME  |
+--------+
| 胡提高 |
| 王付   |
+--------+
*/
--2、在“Research Department”工作且工资低于3000元的员工名字和地址；
	Select ENAME,ADDRESS 
		from employee,department 
		where employee.SALARY<3000 
			and employee.DNO = department.DNO 
			and department.DNAME = "Research Department";
/*
+--------+--------------+
| ENAME  | ADDRESS      |
+--------+--------------+
| 王四   | 湖北省枣阳市 |
| 王四五 | 湖北省枣阳市 |
| 王六七 | 湖北省枣阳市 |
| 王七   | 湖北省枣阳市 |
| 王阿斗 | 湖北省枣阳市 |
| 王服   | 湖北省枣阳市 |
| 王付   | 湖北省枣阳市 |
+--------+--------------+
*/
--3、没有参加项目编号为P1的项目的员工姓名；
	Select ENAME 
		from employee 
		where employee.ESSN 
		not in (Select ESSN from works_on where PNO="P1");
/*
+--------+
| ENAME  |
+--------+
| 庾若涵 |
| 张三   |
| 张四   |
| 卫长青 |
| 卫东方 |
| 卫大方 |
| 卫德德 |
| 卫当初 |
| 胡美丽 |
| 胡共同 |
| 胡快乐 |
| 胡老虎 |
| 于空   |
| 于课   |
| 于来   |
| 于里   |
| 于能   |
| 于拍   |
| 于咯   |
| 于坡   |
| 王四   |
| 王四五 |
| 王五六 |
| 王六七 |
| 王七   |
| 王和   |
| 王阿斗 |
| 王服   |
| 张五   |
| 马六   |
| 王二   |
| 王三   |
| 紫博宏 |
| 张红   |
| 杜克江 |
| 张红   |
| 吴瑞   |
| 吴图   |
| 吴分   |
| 吴的   |
| 吴付   |
| 吴市   |
| 吴上   |
| 吴用   |
| 杨端   |
| 杨都   |
| 杨等   |
| 杨放   |
| 杨和   |
| 杨存   |
| 杨表   |
| 杨本   |
| 杨那   |
| 杨面   |
| 向过   |
| 黄故   |
| 费韩宏 |
+--------+
57 rows in set (0.00 sec)
*/
--4、由张红领导的工作人员的姓名和所在部门的名字；
	Select ENAME,DNAME 
		from employee,Department 
		where employee.DNO = Department.DNO and employee.SUPERSSN 
		in (Select ESSN from employee where ENAME="张红");
/*
+-------+------------+
| ENAME | DNAME      |
+-------+------------+
| 向过  | 人力资源部 |
| 于空  | 后勤部     |
| 于课  | 后勤部     |
| 于来  | 后勤部     |
| 于里  | 后勤部     |
| 于能  | 后勤部     |
| 于拍  | 后勤部     |
| 于咯  | 后勤部     |
| 于坡  | 后勤部     |
| 黄故  | 后勤部     |
+-------+------------+
*/
--5、至少参加了项目编号为P1和P2的项目的员工号；
	Select ESSN 
		from employee 
		where ESSN 
		in (Select ESSN from works_on where PNO = "P1"
				intersect Select ESSN from works_on where PNO = "P2");  --mysql 不支持 intersect
	Select ESSN 
		from employee
		where ESSN
		in (Select ESSN from works_on where PNO = "P1") 
		and ESSN in (Select ESSN from works_on where PNO = "P2"); 
/*
+--------------------+
| ESSN               |
+--------------------+
| 350782198406073014 |
| 420683197312121009 |
| 510522197401061011 |
+--------------------+
3 rows in set (0.00 sec)
*/
--6、参加了全部项目的员工号码和姓名；
	Select ESSN ,ENAME
		from employee
		where not exists(
			Select PNO from PROJECT where not exists (
				Select ESSN from works_on where 
					PROJECT.PNO=works_on.PNO and
					employee.ESSN = works_on.ESSN));
		
	-- 自然连接的例子
	Select ESSN,ENAME 
		from employee natural join works_on
		group by ESSN
		having count(*) = (Select count(*) from PROJECT);

/*
+--------------------+-------+
| ESSN               | ENAME |
+--------------------+-------+
| 510522197401061011 | 吴睿  |
+--------------------+-------+
1 row in set (0.02 sec)
*/
--7、员工平均工资低于3000元的部门名称；
	Select DNAME 
		from department 
		where DNO 
		in
		(Select DNO from employee  
			group by DNO  having avg(SALARY) < 3000);

/*
+--------+
| DNAME  |
+--------+
| 产品部 |
| 后勤部 |
+--------+
2 rows in set (0.00 sec)
*/
--8、至少参与了3个项目且工作总时间不超过8小时的员工名字；
	Select ENAME 
		from employee
		where ESSN in
		(Select ESSN from works_on 
			group by ESSN having count(DNO)>=3 and sum(HOURS)<=8);
/*
+--------+
| ENAME  |
+--------+
| 胡提高 |
+--------+
1 row in set (0.02 sec)
*/
--9、每个部门的员工小时平均工资；

	--每个部门的小时工资
	Select avg(SALARY)/avg(HOURS) 
		from works_on,employee
		where works_on.ESSN=employee.ESSN
		group by employee.DNO;

	Select sum(SALARY)/sum(HOURS)
		from works_on,employee
		where works_on.ESSN=employee.ESSN
		group by employee.DNO;
/*
+------------------------+
| avg(SALARY)/avg(HOURS) |
+------------------------+
|          1950.00000000 |
|          1937.50000000 |
|           709.09090922 |
|          2795.12500210 |
|          3000.00000000 |
+------------------------+
5 rows in set (0.00 sec)
*/
	-- 每个员工的小时工资的平均 按部门分
	Select avg(SALARY/HOURS)
		from works_on,employee
		where works_on.ESSN=employee.ESSN
		group by employee.DNO;

/*
+-------------------+
| avg(SALARY/HOURS) |
+-------------------+
|     2441.66667500 |
|     2505.83333000 |
|      722.22223333 |
|     2988.00000000 |
|     3000.00000000 |
+-------------------+
5 rows in set (0.02 sec)
*/