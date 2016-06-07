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
sql2 = "SELECT [ ESSN = '01' ] (  PROJECTION [ ESSN, PNAME ] ( WORKS_ON JOIN PROJECT ) )"

sql_keys = ["SELECT","PROJECTION","JOIN"] 

Table_list = [["ESSN","ADDRESS","SALARY","SUPERSSN","ENAME","DNO"], #EMPLOYEE
	["DNO","DNAME","DNEMBER","MGRSSN","MGRSTARTDATE"],            #DEPARTMENT
	["PNAME","PNO","PLOCATION","DNO"],                            #PROJECT
	["HOURS","P.ESSN","PNO"]]                                     #WORKS_ON


''' 打印原始执行树'''
def printOriginTree(sql):
    mylist = MyList(None,None,None,None)
    currentNode = MyList(None,None,None,None)
    currentNode = mylist
    print "\t ****origin tree****\n"
    for i in range(len(sql)):
        if sql[i]=="SELECT" or sql[i] == "PROJECTION":
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
            if currentNode.statement != None:
                childList = MyList(None,None,None,None)
                childList.statement = temp
                childList.content = s
                currentNode.LnextNode =childList
                currentNode =  currentNode.LnextNode
            else:
                currentNode.statement = temp
                currentNode.content = s
        if sql[i]=="JOIN":
            print "\t" + sql[i]
            x = sql[i-1] + "\t\t" + sql[i+1] + "\n"
            s = []
            s.append(sql[i-1])
            s.append(sql[i+1])
            print x
            if currentNode.statement != None:
                childList = MyList(None,None,None,None)
                childList.statement = sql[i]
                childList.content = s
                currentNode.nextNode = childList
                currentNode =  currentNode.nextNode
            else:
                currentNode.statement = sql[i]
                currentNode.content = s
    return mylist
            
''' 查找属性所在表'''            
def search(s):
    for i in range(4):
        if s in Table_list[i]:
            if i == 0:
                return "EMPLOYEE"
            elif i==1:
                return "DEPARTMENT"
            elif i==2:
                return "PROJECTION"
            elif i==3:
                return "WORKS_ON"
    return None

    
'''  优化后的查询执行树 '''    
def parseTree(sql_node,sql_arr): 
   currentnode = MyList(None,None,None,None)
   if sql_node.statement == "SELECT":
       if '&' in sql_node.content:
           s= sql_node.content.split('&')
           print s  
           table_s = []
           for i in range(len(s)):
               pro = re.split('=|>|<|!=',s[i])
               print pro
               table_s.append(search(pro[0]))
               print "SELECT"+' '+s[i]+'\n'+search(pro[0])
           print table_s
           sel_list =[]
           sel_list.append(s[0])
           sel_list.append(table_s[0])
           currentnode.content  = sel_list
           currentnode.statement = "SELECT"
           for j in range(1,len(table_s)):
               newnode = MyList(None,None,None,None)
               sel_list =[]
               sel_list.append(s[j])
               sel_list.append(table_s[j])
               newnode.statement = "SELECT"
               newnode.content = sel_list
               currentnode.statement = "JOIN"
               currentnode.LnextNode = currentnode
               currentnode.RnextNode = newnode
   else:
       tempnode = sql_node
       while(tempnode.nextNode != None):
           tempnode = tempnode.nextNode
           if tempnode.statement == "SELECT":
               if '&' in sql_node.content:
                   s= tempnode.content.split('&')
               print s 
       
       return currentnode


''' 打印优化后的查询执行树'''
def printAfterParseTree(afterParseTree):
    print "\t****new tree****\n"

print "input 1 or 2 or 3 to select sql"
while(1):
    sel = raw_input()
    if sel == '1':
        sql_arr = sql0.split(" ")
        sql_node =  printOriginTree(sql_arr)
        afterParseTree = parseTree(sql_node,sql_arr)
        printAfterParseTree(afterParseTree)
    elif sel == '2':
        sql_arr = sql1.split(" ")
        sql_node =  printOriginTree(sql_arr)
        parseTree(sql_node,sql_arr)
    elif sel == '3':
        sql_arr = sql2.split(" ")
        sql_node = printOriginTree(sql_arr)
        parseTree(sql_node,sql_arr)
    else:
        print "over"
        break
        
