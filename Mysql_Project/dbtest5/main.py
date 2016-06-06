# -*- coding: utf-8 -*-
"""
Created on Sat Jun 04 08:34:29 2016

@author: 马晶义
"""
sql0 = "SELECT [ ENAME = 'Mary' & DNAME = 'Research' ] ( EMPLOYEE JOIN DEPARTMENT )"
sql1 = "PROJECTION [ BDATE ] ( SELECT [ ENAME = 'John' & DNAME = ' Research' ] ( EMPLOYEE JOIN DEPARTMENT) )"
sql2 = "SELECT [ ESSN = '01' ] (  PROJECTION [ ESSN, PNAME ] ( WORKS_ON JOIN PROJECT ) )"

sql_keys = ["SELECT","PROJECTION","JOIN","DELETE"] 
''' ('''
left_little_brackets = []
right_little_brackets = []
'''[] '''
left_mid_brackets = []
right_mid_brackets = []

def parseTree(sql_arr):
    arr_key = []
    for i in range(0, len(sql_arr)):
        if sql_arr[i] in sql_keys:
            arr_key.append(sql_arr[i])
        if sql_arr[i] == "(":
           left_little_brackets.append(i)
        if sql_arr[i] == ")":
            right_little_brackets.append(i)
        if sql_arr[i] == '[':
            left_mid_brackets.append(i)
        if sql_arr[i] == ']':
            right_mid_brackets.append(i)
    
    left_littleBrackets_min = min(left_little_brackets)
    right_littleBrackets_max = max(right_little_brackets)
    print left_littleBrackets_min,right_littleBrackets_max
    arr_little = []
    arr_little = sql_arr[left_littleBrackets_min:right_littleBrackets_max+1]
    print arr_little
    left_midBrackets_min = min(left_mid_brackets)
    right_midBrackets_max = max(right_mid_brackets)
    arr_mid =[]
    arr_mid = sql_arr[left_midBrackets_min:right_midBrackets_max+1]
    print arr_mid    
    
sql_arr = sql0.split(" ")
parseTree(sql_arr)
