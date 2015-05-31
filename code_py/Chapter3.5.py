print ("Excise 3.5 --Python 入门经典\n");

#1.create a new list.
dairy_section = ["蒙牛","伊利","蒙牛2号","伊利2号"];

#2.print the string combine first item and last item.
print ("%s.\n" %(dairy_section[0]+dairy_section[len(dairy_section)-1]));

#3.create a new tuple with expired milk info latest.
milk_expiration = ("2015","06","23");

#4.print the expired milk info with tuple.
print ("This milk carton will expire on %s/%s/%s.\n" %(milk_expiration[1],milk_expiration[2],milk_expiration[0]));

#5.create empty dire and add some info.
milk_carton = {};
milk_name = "MN#00001";
fl_oz = "500 ml";
Cost = "￥500.00";
brand_name = "蒙牛2号";

milk_info=(milk_expiration,fl_oz,Cost,brand_name);
milk_carton[milk_name]=milk_info;

#6.print all items info about the dire.
print ("The milk info :\n*********************************************\n");
print ("Milk Number     Expiration Date     Milk Size     Cost          Brand Name\n");
milk_num = list(milk_carton.keys());
print (milk_num[0]+"         "+"%s/%s/%s" %(milk_carton.get(milk_num[0])[0][1],milk_carton.get(milk_num[0])[0][2],milk_carton.get(milk_num[0])[0][0])+
         "         "+milk_carton.get(milk_num[0])[1]+"        "+milk_carton.get(milk_num[0])[2]+"        "+milk_carton.get(milk_num[0])[3]+"\n");
print ("**********************************************\n");

#7.calculate the six carton's price .
print ("The six carton\'s price is:%.02f.\n" %(6*((float)(milk_carton.get(milk_num[0])[2][1:len(milk_carton.get(milk_num[0])[2])]))));

#8.create the cheeses list and add it to dairy_section,then print the dairy_section and remove it.
cheeses = ["鸡肉味de嘎嘣脆","芝士奶酪","xiangxiang奶酪","翔奶酪",];
print ("Before adding the cheeses list,the dairy_section list is :\n%s.\n" %(str(dairy_section)));
dairy_section.append(cheeses);
print ("After adding the cheeses list ,the dairy_section list is :\n%s.\n" %(str(dairy_section)));
dairy_section.remove(cheeses);
print ("After removing the cheeses from dairy_section,the dairy_section list is :\n%s.\n" %(str(dairy_section)));

#9.calculate the number about cheeses.
print ("The cheeses list contain %d cheeses.\n" %(len(cheeses)));

#10.print the five chars of first cheese name.
print ("The first cheese name is :%s.\nThe five chars of first cheese name is :%s.\n" %(cheeses[0],cheeses[0][0:5]));
