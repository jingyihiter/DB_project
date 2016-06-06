#查询优化算法的实现
任选下列查询语句中的三条，将其转化为对应的查询执行树，并且根据设计的查询优化算法，对生成的查询执行树进行优化。<br>
>SELECT [ ENAME = ’Mary’ & DNAME = ’Research’ ] ( EMPLOYEE JOIN DEPARTMENT )<br>
PROJECTION [ BDATE ] ( SELECT [ ENAME = ’John’ & DNAME = ’ Research’ ] ( EMPLOYEE JOIN DEPARTMENT) )<br>
SELECT [ ESSN = ’01’ ] (  PROJECTION [ ESSN, PNAME ] ( WORKS_ON JOIN PROJECT ) )<br>
PROJECTION [ ENAME ] ( SELECT [ SALARY < 3000 ] ( EMPLOYEE JOIN SELECT [ PNO = ’P1’ ] ( WORKS_ON JOIN PROJECT ) )<br>
PROJECTION [ DNAME, SALARY ] ( AVG [ SALARY ] ( SELECT [ DNAME = ’ Research’ ] ( EMPLOYEE  JOIN  DEPART MENT) )

<br>
1）需要设计一个语法分析器，能够识别上述关系代数语句，并且对其进行解析，生成对应的查询执行树，在检查时需要将树的结构显示出来，格式不限。<br>
2）根据本课程所学的查询优化技术，对生成的查询执行树进行优化，并且将最后优化后的查询执行树输出至屏幕，格式不限。<br>
