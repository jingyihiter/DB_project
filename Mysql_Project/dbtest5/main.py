# -*- coding: utf-8 -*-
"""
Created on Sat Jun 04 08:34:29 2016

@author: 马晶义
"""
import re
class MyList:
    def __init__(self,statement,LnextNode,RnextNode,content):
        self.statement = statement
        self.LnextNode = LnextNode
        self.RnextNode = RnextNode
        self.content = content
          

sql0 = "SELECT [ ENAME = 'Mary' & DNAME = 'Research' ] ( EMPLOYEE JOIN DEPARTMENT )"
sql1 = "PROJECTION [ BDATE ] ( SELECT [ ENAME = 'John' & DNAME = ' Research' ] ( EMPLOYEE JOIN DEPARTMENT ) )"
sql2 = "SELECT [ P.ESSN = '01' ] (  PROJECTION [ ESSN, PNAME ] ( WORKS_ON JOIN PROJECT ) )"

sql_keys = ["SELECT","PROJECTION","JOIN"] 

Table_list = [["ESSN","ADDRESS","SALARY","SUPERSSN","ENAME","DNO"],   #EMPLOYEE
	["DNO","DNAME","DNEMBER","MGRSSN","MGRSTARTDATE"],            #DEPARTMENT
	["PNAME","PNO","PLOCATION","DNO"],                            #PROJECT
	["HOURS","P.ESSN","PNO"]]                                       #WORKS_ON


''' 打印原始执行树'''
def printOriginTree(sql):
    mylist = MyList(None,None,None,None)
    currentNode = MyList(None,None,None,None)
    currentNode = mylist
    print u"\t ****初始执行树****\n"
    for i in range(len(sql)):
        if sql[i]=="SELECT" or sql[i] == "PROJECTION":
            currentNode.statement = sql[i]
            temp = sql[i]
            s = '' 
            j = i+1
            if sql[j]=='[':
                j=j+1
                while(j<len(sql) and sql[j]!=']'):
                    #print sql[j]
                    s = s + sql[j]
                    j=j+1
                print temp, s,"\n"
                i = j       
        elif sql[i] =='[' or sql[i] ==']' or sql[i]==')':
            pass
        elif sql[i] == '(':
            currentNode.LnextNode = MyList(None,None,None,None)
            currentNode =  currentNode.LnextNode
        elif sql[i]=="JOIN":
            print "\t" + sql[i]
            x = sql[i-1] + "\t" + sql[i+1] + "\n"
            s = []
            s.append(sql[i-1])
            s.append(sql[i+1])
            print x
            currentNode.statement = sql[i]
            currentNode.content = None
            currentNode.LnextNode = MyList(None,None,None,None)
            currentNode.LnextNode.content = sql[i-1]
            currentNode.RnextNode = MyList(None,None,None,None)
            currentNode.RnextNode.content = sql[i+1]
            i = i+1
        else:
            if currentNode.content == None:
                currentNode.content =''
            if sql[i+1] == "JOIN":
                continue
            currentNode.content = currentNode.content+sql[i]
    return mylist

''' 测试存储的树的正确性'''
def testTreePrint(sql_tree):
    print u"\t****test tree OK****"
    current = sql_tree
    s = []
    while current !=None or len(s)!=0:
        while current!=None:
            if current.statement !=None:
                if current.statement != None and current.statement!="JOIN":
                    print current.statement, current.content
                elif current.statement == "JOIN":
                    print '\t'+ current.statement
                    print current.LnextNode.content,"\t",current.RnextNode.content
                else:
                    print current.statement
            
            s.append(current)
            current = current.RnextNode
        if len(s)!=0:
            current = s.pop()
            current = current.LnextNode
           
''' 查找属性所在表'''            
def search(s):
    table_list = []
    for i in range(4):
        if s in Table_list[i]:
            if i == 0:
                table_list.append("EMPLOYEE")
            elif i==1:
                table_list.append("DEPARTMENT")
            elif i==2:
                table_list.append("PROJECTION")
            elif i==3:
                table_list.append( "WORKS_ON")
    return table_list

''' 查找所在的子树'''
def searchNode(sql_tree,str_node):
    childtree = sql_tree
    while childtree.statement!=str_node:
        childtree = childtree.LnextNode
    return childtree

'''  优化后的查询执行树 '''    
def parseTree(sql_node,sql_arr): 
	#print "\t****parseTree****"
	new_sql = sql_node
	temp = MyList(None,None,None,None)
	join = searchNode(new_sql,"JOIN")
	select = searchNode(new_sql,"SELECT")
	if select == new_sql:
		new_sql = new_sql.LnextNode
	else:
		new_sql.LnextNode = select.LnextNode
	s = select.content.split('&')
	for j in range (len(s)):
		table = []
		table_list = search(s[j].split('=')[0])
		for i in range (len(table_list)):
			if table_list[i] in sql_arr:
				table.append(table_list[i])
			if join.LnextNode.content == table[0]:
				temp = join.LnextNode
				temp.statement = "SELECT"
				temp.content = s[j]
				temp.LnextNode = MyList(None, None, None, None)
				temp.LnextNode.content = table[0]
			if join.RnextNode.content == table[0]:
				temp = join.RnextNode
				temp.statement = "SELECT"
				temp.content = s[j]
				temp.LnextNode = MyList(None, None, None, None)
				temp.LnextNode.content = table[0]
	return new_sql

''' 打印优化后的查询执行树'''
def printAfterParseTree(afterParseTree):
	print u"\t****优化后的执行树 ****\n"
	currentTree = afterParseTree
	s = []
	while currentTree!=None or len(s)!=0:
		while currentTree!=None:
			if currentTree.statement!=None:
				if currentTree.statement != None and currentTree.statement!="SELECT" and currentTree.statement!= "JOIN":
					print currentTree.statement, currentTree.content,'\n'
				elif currentTree.statement == "SELECT":
					print currentTree.statement,currentTree.content,'\n'+ currentTree.LnextNode.content,'\n'
				elif currentTree.statement == "JOIN":
					print "\t",currentTree.statement,'\n'
					if currentTree.LnextNode.statement==None:
						print currentTree.LnextNode.content
					if currentTree.RnextNode.statement==None:
						print currentTree.RnextNode.content
				else:
					print currentTree.statement,'\n'
			s.append(currentTree)
			currentTree = currentTree.RnextNode
		if len(s)!=0:
			currentTree = s.pop()
			currentTree = currentTree.LnextNode


print "input 1 or 2 or 3 to select sql"
while(1):
    sel = raw_input()
    print u"第" + sel + u"条sql语句"
    if sel == '1':
        sql_arr = sql0.split(" ")
        sql_node =  printOriginTree(sql_arr)
        afterParseTree = parseTree(sql_node,sql_arr)
        printAfterParseTree(afterParseTree)
    elif sel == '2':
        sql_arr = sql1.split(" ")
        sql_node =  printOriginTree(sql_arr)
        afterParseTree = parseTree(sql_node,sql_arr)
        #testTreePrint(afterParseTree)
        printAfterParseTree(afterParseTree)
    elif sel == '3':
        sql_arr = sql2.split(" ")
        sql_node = printOriginTree(sql_arr)
        afterParseTree = parseTree(sql_node,sql_arr)
        printAfterParseTree(afterParseTree)
    else:
        print "over"
        break
        
