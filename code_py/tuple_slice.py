test_str="hello,i am lucifer_wsp,i am in xi\'an,where are you?";
print ("The string is \'%s\'." %(test_str));
slice_str=test_str[2:19];
print ("The slice string is \'%s\',the length is %d.\n" %(slice_str,len(slice_str)));

test_tuple=("tuple1","tuple2","tuple3","tuple4","tuple5");
print ("The tuple is \'%s\'." %(str(test_tuple)));
slice_tuple=test_tuple[3:9];
print ("The slice tuple is \'%s\',and the length is %d.\n" %(str(slice_tuple),len(slice_tuple)));

test_list=["list1","list2","list3","list4","lis5","list6"];
print ("The List is \'%s\'." %(str(test_list)));
slice_list=test_list[2:9];
print ("The slice list is \'%s\',the length is %d.\n" %(str(slice_str),len(slice_str)));

print ("bye-bye.exit...\n");
