test_tuple = (1,2,3,4,5);
print ("The tuple is \'%s\'.\n" %(str(test_tuple)));

print ("Test the for in word and use the else word at last.\n");
print ("*****************************************************\n");
for num in test_tuple:
    if num == 10:
        break;
    else:
        print ("The number is %d.\n" %(num));
else:
    print ("Visit all items and exit.\n");


try:
    if(test_tuple[len(test_tuple)-1] == len(test_tuple)):
        print ("The %dth number equals it's index.\n" %(len(test_tuple)));
    else:
        print ("The %d number is %d.\n" %(len(test_tuple),test_tuple[len(test_tuple)-1]));
except KeyError as error:
    print ("Visit error:%s.\n" %(str(error)));
except IndexError:
    pass;
else:
    print ("last else word in try-except.\n");

print ("********************************************************\n");
print ("bye-bye.\n");
print ("exit...\n");
