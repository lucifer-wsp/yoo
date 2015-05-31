print ("Using list method as append(),extend() and pop().\n");
 
print ("***************************************************************************"); 
tuple = ("hello ","i ","am ","lucifer.");
print ("The tuple is \'%s\'.\n" %(str(tuple)));
list = [];
list.append(tuple);
print ("using append method of list to add a tuple and new list is \'%s\'.\n" %(str(list)));
list.extend(tuple);
print ("using extend method of list to add a tuple and new list is \'%s\'.\n" %(str(list)));

print ("========================================================================")
print ("using pop method of list to get one elements from list.\n");
index=0;
print ("The %d item value is \'%s\'.\n" %(index+1,list.pop(index)));
print ("After poping the first item ,the list is \'%s\'.\n" %(str(list)));
print ("When use the pop method but not given a arguments ,the poped item is \'%s\'.\n" %(list.pop()));
print ("*******************************************************************************");
print ("bye-bye.\nexit...");
